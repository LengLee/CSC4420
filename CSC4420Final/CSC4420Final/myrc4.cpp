#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/file.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <syslog.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <dirent.h>
#include <curl/curl.h>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <list>
#include <vector>

#include <openssl/rc4.h> 
#include <openssl/md5.h>

#include <fstream> 

using namespace std; 



void myrc4(int argc, char* argv[]){

int fd=open(argv[1] ,O_RDWR); // open argv[1]

int f=open(argv[2], O_RDWR | O_CREAT , 0666); //open or create new file argv[2]

size_t bsize = lseek(fd,0,SEEK_END); //define size of buffer

char *buf = (char *) malloc(bsize);     //allocate mem size of buffer

char *buffer = (char *) malloc(bsize);

string p = "pass";  //string for the rc4 key

lseek(fd,0,SEEK_SET);   //seek back to beginning in fd 

if(read(fd, buf, bsize) == -1){
cout<<"Error reading \n";
} //read the fd from 0 offset -> end into buf 

RC4_KEY key;        //rc4 key

// char* digest_buff = (char*)malloc(KEY_LENGTH);

char passWord[p.length()];
strcpy(passWord, p.c_str());
char digest_buff[MD5_DIGEST_LENGTH];

// use md5 function
MD5((const unsigned char*)passWord, strlen(passWord), (unsigned char*) &digest_buff);  

RC4_set_key(&key, strlen(digest_buff) ,(const unsigned char*) digest_buff); //set key

RC4(&key, bsize, (const unsigned char*)buf, (unsigned char*)buffer);  //perform rc4

lseek(fd,0,SEEK_SET);

if(write(f, buffer, bsize) == -1){
 cout<<"Error writing \n" ;  
}//write the rc4 buffer back into fd

lseek(fd,0,SEEK_SET);

free(buf);
// free(digest_buff);
free(buffer);

} 

int main(int argc, char* argv[]){

//int fd=open("/home/lenglee/Desktop/standalone/Wayne.jpg",O_RDWR); 

myrc4(argc, argv); 


return 0; 
}
