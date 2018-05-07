


Installation: 

On Linux, ensure you have all the dependencies: 

On Ubuntu 16.04 : 

sudo apt-get install automake autotools-dev fuse g++ git libcurl4-gnutls-dev libfuse-dev libssl-dev libxml2-dev make pkg-config

On CentOS 7: 

sudo yum install automake fuse fuse-devel gcc-c++ git libcurl-devel libxml2-devel make openssl-devel 

to clone, enter commands from terminal :

git clone https://github.com/lenglee/s3fs-fuse.git
cd s3fs-fuse
./autogen.sh
./configure
make
sudo make install


To make a password file : 

Save a text file in your home directory named .passwd-s3fs 
Save your accessKey:secretKey 

To mount: 

enter command in terminal: sudo s3fs bucket /path/to/mountpoint -o passwd_file=~/.passwd-s3fs 

run command df -h to make sure its mounted



