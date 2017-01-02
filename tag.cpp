#include <iostream>
#include <string.h>
#include <stdlib.h>
int main(int argc, char* argv[])
{
	std::cout<<"Following is the ID3v2 metadata for the track requested\n";
	std::string s = "mid3v2 -l ";
	s.append(argv[1]);
	const char* c = s.c_str();
	system(c);
	// editing 
	for(int i=1; i<=7; ++i)
	{
		switch(i)
		{
			case 1: {
				std::cout<<"\nEditing artist \n";
	            std::string tag1 = "mid3v2 -a '";
	            std::string artist;
	            getline(std::cin,artist);
	            if(artist.compare("-") == 0)
	            	continue;
	            tag1.append(artist);
	            tag1.append("' ");
	            tag1.append(argv[1]);
	            const char* d = tag1.c_str();
	            system(d);
			} break;
			case 2: {
				std::cout<<"\nEditing album \n";
	            std::string tag2 = "mid3v2 -A '";
	            std::string album;
	            getline(std::cin,album);
	            if(album.compare("-") == 0)
	            	continue;
	            tag2.append(album);
	            tag2.append("' ");
	            tag2.append(argv[1]);
	            const char* e = tag2.c_str();
	            system(e);
			} break;
			case 3: {
				std::cout<<"\nEditing title \n";
	            std::string tag3 = "mid3v2 -t '";
	            std::string title;
	            getline(std::cin,title);
	            if(title.compare("-") == 0)
	            	continue;
	            tag3.append(title);
	            tag3.append("' ");
	            tag3.append(argv[1]);
	            const char* f = tag3.c_str();
	            system(f);
			} break;
			case 4: {
				std::cout<<"\nEditing comment \n";
	            std::string tag4 = "mid3v2 -c '";
	            std::string comment;
	            getline(std::cin,comment);
	            if(comment.compare("-") == 0)
	            	continue;
	            tag4.append(comment);
	            tag4.append("' ");
	            tag4.append(argv[1]);
	            const char* g = tag4.c_str();
	            system(g);
			} break;
			case 5: {
				std::cout<<"\nEditing genre \n";
	            std::string tag5 = "mid3v2 -g '";
	            std::string genre;
	            getline(std::cin,genre);
	            if(genre.compare("-") == 0)
	            	continue;
	            tag5.append(genre);
	            tag5.append("' ");
	            tag5.append(argv[1]);
	            const char* h = tag5.c_str();
	            system(h);
			} break;
			case 6: {
				std::cout<<"\nEditing year \n";
	            std::string tag6 = "mid3v2 -y '";
	            std::string year;
	            getline(std::cin,year);
	            if(year.compare("-") == 0)
	            	continue;
	            tag6.append(year);
	            tag6.append("' ");
	            tag6.append(argv[1]);
	            const char* j = tag6.c_str();
	            system(j);
			} break;
			case 7: {
				std::cout<<"\nEditing track number \n";
	            std::string tag7 = "mid3v2 -Tnum '";
	            std::string number;
	            getline(std::cin,number);
	            if(number.compare("-") == 0)
	            	continue;
	            tag7.append(number);
	            tag7.append("' ");
	            tag7.append(argv[1]);
	            const char* k = tag7.c_str();
	            system(k);
			} break;
			default: break;
		}
	}
	system(c);
	return 0; 
}