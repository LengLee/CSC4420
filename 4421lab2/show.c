#include<fcntl.h>
#include<unistd.h> 
#include<stdio.h> 

#define Buffer_Size  0

int main (int argc, char *argv[]) {

char buffer[Buffer_Size]; 
int fDes; 

if(argc !=2 ){
	perror("code");
}
fDes = open(argv[1] , O_CREAT | O_WRONLY , 0600); 

if(argc < 2 ){
	perror("code");
}

write(fDes, "Hello world\n" , 12); 
close(fDes); 

fDes = open(argv[1] , O_RDONLY);

if(fDes<0){
	perror("Error reading");
}

while( read(fDes, buffer, Buffer_Size) > 0 ){
	printf("%s" , buffer);  
} 


printf("\n"); 


write(fDes , buffer , Buffer_Size); 

close(fDes); 
 

return 0; 
}
