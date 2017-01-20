#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <vector>
#include <cstdint>
#include <memory>
// chromaprint library 
#include <chromaprint.h>
// jsoncpp library
#include <json/json.h>
//curl library
#include <curl/curl.h>

/* API key for AcoustID */
const char* apikey = "1GL74GpVcM";

/* holder for curl fetch */
struct curl_fetch_st {
    char *payload;
    size_t size;
};

/* callback for curl fetch */
size_t curl_callback (void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;                             /* calculate buffer size */
    struct curl_fetch_st *p = (struct curl_fetch_st *) userp;   /* cast pointer to fetch struct */

    /* expand buffer */
    p->payload = (char *) realloc(p->payload, p->size + realsize + 1);

    /* check buffer */
    if (p->payload == NULL) {
      /* this isn't good */
      fprintf(stderr, "ERROR: Failed to expand buffer in curl_callback");
      /* free buffer */
      free(p->payload);
      /* return */
      return -1;
    }

    /* copy contents to buffer */
    memcpy(&(p->payload[p->size]), contents, realsize);

    /* set new buffer size */
    p->size += realsize;

    /* ensure null termination */
    p->payload[p->size] = 0;

    /* return size */
    return realsize;
}

/* fetch and return url body via curl */
CURLcode curl_fetch_url(CURL *ch, const char *url, struct curl_fetch_st *fetch) {
    CURLcode rcode;                   /* curl result code */

    /* init payload */
    fetch->payload = (char *) calloc(1, sizeof(fetch->payload));

    /* check payload */
    if (fetch->payload == NULL) {
        /* log error */
        fprintf(stderr, "ERROR: Failed to allocate payload in curl_fetch_url");
        /* return error */
        return CURLE_FAILED_INIT;
    }

    /* init size */
    fetch->size = 0;

    /* set url to fetch */
    curl_easy_setopt(ch, CURLOPT_URL, url);

    /* set calback function */
    curl_easy_setopt(ch, CURLOPT_WRITEFUNCTION, curl_callback);

    /* pass fetch struct pointer */
    curl_easy_setopt(ch, CURLOPT_WRITEDATA, (void *) fetch);

    /* set default user agent */
    curl_easy_setopt(ch, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    /* set timeout */
    curl_easy_setopt(ch, CURLOPT_TIMEOUT, 5);

    /* enable location redirects */
    curl_easy_setopt(ch, CURLOPT_FOLLOWLOCATION, 1);

    /* set maximum allowed redirects */
    curl_easy_setopt(ch, CURLOPT_MAXREDIRS, 1);

    /* fetch the url */
    rcode = curl_easy_perform(ch);

    /* return */
    return rcode;
}

int main(int argc, char* argv[])
{
	std::string s = "fpcalc -raw ";
	std::string t(argv[1]);
	s.append(t);
  s.append(" > finger.txt");
  const char* command = s.c_str();
  std::cout<<command<<"\n";
	system(command);
	std::ifstream fpcalc;
	fpcalc.open("finger.txt");
	if(!fpcalc)
	{
		std::cout<<"Could not open file\n";
		return 1;
	}
	std::string str, duration, fpt;
	while(!fpcalc.eof())
	{
		getline(fpcalc,str);

		std::size_t pos = str.find("DURATION");
		if(pos != std::string::npos)
		{   
		    pos+=9;
		    while(str[pos] != '\0')
		    {
			  duration.push_back(str[pos]);
			  ++pos;
		    }
		    duration.push_back('\0');
		}

		std::size_t pos1 = str.find("FINGERPRINT");
		if(pos1 != std::string::npos)
		{   
		    pos1+=12;
		    while(str[pos1] != '\0')
		    {
			  fpt.push_back(str[pos1]);
			  ++pos1;
		    }
		    fpt.push_back('\0');
		}
	}
	std::cout<<duration<<"\n"<<fpt<<"\n";
  
	fpcalc.close();
  
	
    CURL *ch;                                               /* curl handle */
    CURLcode rcode;                                         /* curl result code */

    //json_object *json;                                      /* json post body */
    //enum json_tokener_error jerr = json_tokener_success;    /* json parse error */

    struct curl_fetch_st curl_fetch;                        /* curl fetch struct */
    struct curl_fetch_st *cf = &curl_fetch;                 /* pointer to fetch struct */
    struct curl_slist *headers = NULL;                      /* http headers to send with request */

    /* url to test site */
    const char* url = "http://api.acoustid.org/v2/lookup";

    /* init curl handle */
    if ((ch = curl_easy_init()) == NULL) {
        /* log error */
        fprintf(stderr, "ERROR: Failed to create curl handle in fetch_session");
        /* return error */
        return 1;
    }

    /* set content type */
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");

    /* build post data */
    Json::Value root;
    Json::StyledWriter writer;
    Json::Reader reader;
    root["format"] = "json";
    root["client"] = apikey;
    root["duration"] = duration; // change string to int 
    root["fingerprint"] = fpt;
    root["meta"] = "recordings";

    std::string params = writer.write(root);

    /* set curl options */
    curl_easy_setopt(ch, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(ch, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(ch, CURLOPT_POSTFIELDS, params); // check!

    /* fetch page and capture return code */
    rcode = curl_fetch_url(ch, url, cf);

    /* cleanup curl handle */
    curl_easy_cleanup(ch);

    /* free headers */
    curl_slist_free_all(headers);

    
    /* check return code */
    if (rcode != CURLE_OK || cf->size < 1) {
        /* log error */
        fprintf(stderr, "ERROR: Failed to fetch url (%s) - curl said: %s",
            url, curl_easy_strerror(rcode));
        /* return error */
        return 2;
    }

    /* check payload */
    if (cf->payload != NULL) {
        /* print result */
        printf("CURL Returned: \n%s\n", cf->payload);
        /* parse return */
        //json = json_tokener_parse_verbose(cf->payload, &jerr);
        reader.parse(cf->payload, root);
        std::cout << root.toStyledString()<<"\n";  
        /* free payload */
        free(cf->payload);
    } else {
        /* error */
        fprintf(stderr, "ERROR: Failed to populate payload");
        /* free payload */
        free(cf->payload);
        /* return */
        return 3;
    }
	return 0;
}

//using chromaprint 
/*
   //int length = atoi(duration.c_str());
   //int16_t *fingerp = (int16_t)atoi(fpt.c_str());
   ChromaprintContext *ctx;
   char *fp;
   const int sample_rate = 44100;
   const int num_channels = 2;

   // reading the raw audio file  
  size_t valueCount = sample_rate * num_channels;
  FILE *_file;
    int16_t *_data = NULL;
    //_data = (int16_t *) data;
    _file=fopen("output.raw","r");
    if(_file == NULL) exit(1);
    fread(_data, sizeof(_data[0]), valueCount, _file);
    fclose(_file);

    std::cout<<"Step 1\n";
    // new chromaprint object
   ctx = chromaprint_new(CHROMAPRINT_ALGORITHM_DEFAULT);
   if(ctx == NULL)
   {
    printf("Cannot continue :O\n");
    exit(1);
   }
   int length = 2;//chromaprint_get_item_duration(ctx);
   std::cout<<"Step 2\n"<<length<<"\n";
   chromaprint_start(ctx, sample_rate, num_channels);
   std::cout<<"Step 3\n";
   //while (has_more_data) {
       int i = chromaprint_feed(ctx, _data, length);
       if(i != 1)
       {
        printf("%d\nAbort..\n",i);
        exit(1);
       }
   //}
   std::cout<<"Step 4\n";
   chromaprint_finish(ctx);
 
   chromaprint_get_fingerprint(ctx, &fp);
   printf("%s\n", fp);
   chromaprint_dealloc(fp);
 
   chromaprint_free(ctx);
   */
  
