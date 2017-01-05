#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <vector>
#include "chromaprint.h"

/*struct MemoryStruct {
  char *memory;
  size_t size;
};
 
static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
     out of memory! 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}*/
int main(int argc, char* argv[])
{
	//int duration;
	/*std::string s = "fpcalc -raw ";
	std::string t(argv[1]);
	s.append(t);
	std::cout<<s<<"\n";*/
	//system("fpcalc -raw ")
	/*std::ifstream fpcalc;
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
  */
	
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

    // new chromaprint object
   ctx = chromaprint_new(CHROMAPRINT_ALGORITHM_DEFAULT);
   if(ctx == NULL)
   {
   	printf("Cannot continue :O\n");
   	exit(1);
   }
   int length = chromaprint_get_item_duration(ctx);
   chromaprint_start(ctx, sample_rate, num_channels);
   //while (has_more_data) {
       int i = chromaprint_feed(ctx, _data, length);
       if(i != 1)
       {
       	printf("%d\nAbort..\n",i);
       	exit(1);
       }
   //}
   chromaprint_finish(ctx);
 
   chromaprint_get_fingerprint(ctx, &fp);
   printf("%s\n", fp);
   chromaprint_dealloc(fp);
 
   chromaprint_free(ctx);

	/*CURL *curl;
  CURLcode res;
  struct MemoryStruct chunk;
  static const char *postthis="Field=1&Field=2&Field=3";
 
  chunk.memory = malloc(1);   will be grown as needed by realloc above */ 
  //chunk.size = 0;    /* no data at this point */
 
  /*curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  if(curl) {
 
    curl_easy_setopt(curl, CURLOPT_URL, "http://www.example.org/");
 
     send all data to this function  */ 
    //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
 
    /* we pass our 'chunk' struct to the callback function */ 
    //curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
 
    /* some servers don't like requests that are made without a user-agent
       field, so we provide one */ 
    //curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
 
    //curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postthis);
 
    /* if we don't provide POSTFIELDSIZE, libcurl will strlen() by
       itself */ 
    //curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
 
    /* Perform the request, res will get the return code */ 
    //res = curl_easy_perform(curl);
    /* Check for errors */ 
    //if(res != CURLE_OK) {
      //fprintf(stderr, "curl_easy_perform() failed: %s\n",
        //      curl_easy_strerror(res));
    /*}
    else {
      
       * Now, our chunk.memory points to a memory block that is chunk.size
       * bytes big and contains the remote file.
       *
       * Do something nice with it!
       */ 
      //printf("%s\n",chunk.memory);
      //printf("Yoyo I just printed contents of chunk\n");
    //}
 
    /* always cleanup */ 
    /*curl_easy_cleanup(curl);
 
    free(chunk.memory);
 
     we're done with libcurl, so clean it up */ 
    //curl_global_cleanup();
  //}
	return 0;
}

// Need to include chromaprint libraries to make a
// post call with these parameters - duration and fp
// passing in headers using a struct/json
