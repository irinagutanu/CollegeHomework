//Operating System Homework 2017, C

//COLLATZ FUNCTION GETS A NUMBER N
//IF N%2==0 THEN N = N/2 ELSE N = 3*N+1
//THE FUNCTION IS PROVEN TO ALWAYS END FOR N=1, FOR ANY GIVEN N 

//THE CODE BELOW CREATES A SEPARATE CHILD WITH FORK() FOR EACH ARGUMENT, CALCULATES THE SEQUENCE GIVEN BY COLLATZ AND SAVES IT IN ITS
//OWN PLACE IN MEMORY; THEN THE PARENT PRINTS ALL THE CHILDREN AND DELETES THE RESULTS FROM THE SHARED MEMORY

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>   
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

#define MSIZE 1000

int collatz(int n, char* p){
	char buffer[100];
	sprintf(buffer, "%d", n);
	strcat(p, buffer);
	strcat(p, " ");
	if( n == 0 ) return 0;
	if( n == 1){
		strcat(p, "\n");
		return 1;
	}
	if( n % 2 == 0 ){
		return collatz(n/2, p);
	}
	return collatz(3*n+1, p);
}

void childrenCollatz(char* val, char* p){
	int value = atoi(val);
	strcpy(p, val);
	strcat(p, ": ");
	collatz(value, p);
	printf("Done Parent %d Me %d\n", getppid(), getpid());
}


int main(int argc, char* argv[]){
	char shm_name[] = "myshm";
	int shm_fd, i, k=0;
	shm_fd = shm_open( shm_name ,  O_CREAT|O_RDWR,   S_IRUSR|S_IWUSR ) ;
	if( shm_fd < 0){
		perror(NULL);
		return errno;
	} 

	size_t shm_size = getpagesize()*(argc-1);
	if( ftruncate(shm_fd, shm_size) == -1){
		perror(NULL);
		shm_unlink(shm_name);
		return errno;
	}

	char* shm_ptr = mmap(0, shm_size, PROT_READ, MAP_SHARED, shm_fd, 0);
	if(shm_ptr==MAP_FAILED){
		perror(NULL);
		shm_unlink(shm_name);
		return errno;
	}

	pid_t pid;
	printf("Starting parent %d\n", getpid());
	for (i = 1; i < argc; i++) {
  		if ((pid = fork()) < 0) {
    		perror("fork");
    		return errno;
  		} 
  		else if (pid == 0) {
  			void* p;
  			p= mmap(0,getpagesize(),PROT_WRITE|PROT_READ, MAP_SHARED, shm_fd, getpagesize()*(i-1));
    		if( p == MAP_FAILED){
    			perror(NULL);
    			return errno;
    		}
    		char *seq = (char*)p;
    		childrenCollatz(argv[i], seq);
    		if(munmap(p, getpagesize()) == -1) {
    			perror(NULL);
    			return errno;
    		}
    		exit(0);
  		}
	}
	
	for (i=1; i < argc; i++) {
		wait(NULL);
		shm_ptr=mmap(0,getpagesize(),PROT_WRITE|PROT_READ, MAP_SHARED, shm_fd, getpagesize()*(i-1));
		printf("%s",shm_ptr);
		munmap(shm_ptr,getpagesize());
	}
	shm_unlink(shm_name);
	return 0;
}
