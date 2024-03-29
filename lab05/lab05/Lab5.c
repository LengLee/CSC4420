#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

// Function ptototypes
int readX();
void writeX(int);

int main()
{
	int pid;			// pid: used to keep track of the child process
	int x = 19530;		// x: our value as integer
	int i;				// iterator	

	// Write x to file
	writeX(x);

	// output inital value to the screen
	printf("x = %d\n", x);

	// loop 5 times
	for( i = 0; i<5; i++)
	{
		// output the current loop iteration
		printf("\nITERATION %d\n", i+1);

		// flush here so that the stdout buffer doesn't
		// get printed in both processes
		fflush(stdout);

		// Check if fork child process creates a process
		if ((pid = fork()) < 0)
		{
			perror("Error with fork");
			exit(1);
		}

		// Child waits a second for the parent to go first
		else if (pid != 1)
		{			 
			wait(0);
		}

		// Both processes read x from file
		x = readX();

		// Parent prints parent, and performs subraction
		if (pid > 0)
		{
			
			printf("Parent: ");	
			x=x/5;		
		}


		// Child prints child, and performs division
		else if (pid == 0)
		{
			
			printf("Child: ");
			x=x-5;			
		}

		// Both processes output x value and write x to file...
		printf("x = %d\n", x);
		writeX(x);

		// The child terminates
		if (pid == 0)
		{
			exit(0);
		}
	}

	exit(0);
}

/// Returns the value read from .shareX.dat
int readX()
{
	char xChar[10];		// xChar: our value as a char
	int fd;				// fd: file descriptor

	// open to read and store x
	if ( (fd = open(".shareX.dat", O_RDONLY )) == -1 )
	{
		perror("Error opening file");
		exit(2);
	}

	// read xChar from the file
	if ( read(fd, xChar, 10) == -1 )
	{
		perror("Error reading file");
		exit(3);
	}

	// close file for reading
	close(fd);

	// convert xChar to int and return
	return  atoi(xChar);
}

/// Writes the writeX value to the file .shareX.dat
void writeX(int writeX)
{
	char xChar[10];		// xChar: our value as a char
	int fd;				// fd: file descriptor
	int xBytes;			// how much to write

	// open, clear, and create file if not createdi
	if ( (fd = open(".shareX.dat", O_CREAT | O_TRUNC | O_WRONLY, 0644 )) == -1 )
	{
		perror("Error opening file");
		exit(4);
	}

	// convert x to char
	xBytes = sprintf(xChar, "%d", writeX);

	// put xChar in file
	if ( write(fd, xChar, xBytes) == -1 )
	{
		perror("Error writing to file");
		exit(5);
	}

	// close the file for writing
	close(fd);

	return;
}

