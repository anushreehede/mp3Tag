### Installing mid3v2

sudo apt-get install python-pip  
sudo pip install mutagen

### Install chromaprint separately

git clone https://github.com/acoustid/chromaprint.git

### Compiling and running
g++ -Wall search.cpp -I/usr/include/python2.7 -lpython2.7  
./a.out mp3_file