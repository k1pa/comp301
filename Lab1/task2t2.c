#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

int main(int argc, char *argv[]){
	int fd;
	struct stat mystat;
	char *pmap;
	
	//printf("%s  %s  %d\n", argv[0], argv[1], argc);
	
	if(argc == 2){
		
		fd = open(argv[1], O_RDWR);
		if(fd == -1){
			perror("open");
			exit(1);
		}
		
		if(fstat(fd, &mystat) < 0){
			perror("fstat");
			close(fd);
			exit(1);
		}
		
		pmap = (char *) mmap(0, mystat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		
		if(pmap == MAP_FAILED){
			perror("mmap");
			close(fd);
			exit(1);
		}
		//printf("hello\n");
		//reverse the string by characters here
		long int size = mystat.st_size - 2;
		char hold_start;
		char hold_end;
		int n_loops = size / 2;
		int count = 0;
		printf("n_loops = %d\n",n_loops);
		
		//loop through and reverse
		while(count < n_loops){
			hold_start = pmap[count];
			hold_end = pmap[size - count];
			pmap[count] = hold_end;
			pmap[size - count] = hold_start;
			count++;
			
		}
		
		
		printf("%s\n",pmap);
		if(munmap(pmap, mystat.st_size) == -1){
			perror("unmap unsuccessful");
			close(fd);
			exit(1);
		}
		close(fd);
		return 0;
		
	}
	printf("incorrect number of argument, requires a file name\n");
	return 1;
}
