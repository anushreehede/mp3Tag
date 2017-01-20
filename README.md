### Installing mid3v2

sudo apt-get install python-pip  
sudo pip install mutagen 

### Install curl 

sudo apt-get install libcurl14-gnutls-dev 

### Install chromaprint separately

git clone https://github.com/acoustid/chromaprint.git

### Install jsoncpp 

git clone https://github.com/open-source-parsers/jsoncpp.git 

### Compiling and running

g++ search1.cpp -lcurl -ljsoncpp -std=c++11

./a.out mp3File.mp3



