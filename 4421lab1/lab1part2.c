#include <stdio.h>
#include <time.h> 
#include <sys/stat.h>

int main (int argc, char *argv[])
{

    // define an instance of struct stat (don’t use a pointer).

    struct stat buffer; 

    // Use the stat function store the status of the file in your stat struct
    // stat takes a pointer, so pass your struct by reference with &
    
if ( &buffer == -1)
    { 
        // Use perror to print error message then exit program
        perror("Failed to get status"); 
    }

    // print the last access time for the file using defined instance of
    // struct stat. ctime requires a pointer, hence the & below.
    printf ("%s last accessed at %s", argv[1], ctime(&buffer.st_atime));
}
