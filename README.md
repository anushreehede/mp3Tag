### Installing mid3v2

sudo apt-get install python-pip  
sudo pip install mutagen

### Install chromaprint separately

git clone https://github.com/acoustid/chromaprint.git

### Compiling and running

ffmpeg -i mp3_file -f s16le -acodec pcm_s16le output.raw  

g++ -Wall search1.cpp -I/path/chromaprint/src -L/path/chromaprint/src/src -libchromaprint

./a.out



