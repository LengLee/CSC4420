#include<fcntl.h>
#include<unistd.h> 
#include<stdio.h> 
#include<stdlib.h>

#define Buffer_Size  0

int main (int argc, char *argv[]) {

char buffer[Buffer_Size]; 
int fDes;
int m ,n; 

 
fDes = open(argv[3] , O_CREAT | O_WRONLY , 0600); 

if(argc < 4 ){
	perror("code");
}

write(fDes, "Hello world\n" , 12); 
write(fDes,"Hello\n" , 6);
write(fDes,"Hello this is a test\n",21);
close(fDes); 

m = atoi(argv[1]);
n = atoi(argv[2]);
int lineNum = 1; 

if(m < 0 || n < 0 ){
	perror("error");
}
 
fDes = open(argv[3] , O_RDONLY);

if(fDes<0){
	perror("Error reading");
}



while(read(fDes, buffer, sizeof(int) != 0) ){

if(buffer[Buffer_Size] == '\n'){
	lineNum++; 
}

if(lineNum >=m && lineNum <=n){
	printf("%s", buffer); 
}

}  

printf("\n");
close(fDes); 
 

return 0; 
}
