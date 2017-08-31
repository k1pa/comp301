#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int random_number(int count){
	int r1 = (rand() % 10) + 1;
	int r2 = (rand() % 10) + 1;
	int final;
	
	if(count % 2 == 0) final = r1 * 10;
	else final = (r1 + r2) * 10;
	
	return final;
}

int main(void){
	char *str = "complex.csv";
	FILE *file = fopen(str, "w");
	int count = 1;
	int holdPriority = 0;
	int quanta = 0;
	
	if(file != NULL){
		
		srand(time(NULL));
		while(count <= 100){
			holdPriority = count % 4;
			printf("%d\n", count);
			quanta = random_number(count);
			//must be background process as 4 mod 4 equals 0
			if(holdPriority == 0) fprintf(file, "%d,%d,1\n", count, quanta);
			//must be real time
			else if(holdPriority == 1) fprintf(file, "%d,%d,20\n", count, quanta);
			//must be system
			else if(holdPriority == 2) fprintf(file, "%d,%d,10\n", count, quanta);
			//must be user
			else fprintf(file, "%d,%d,5\n", count, quanta);
			
			count++;
		}
	}
	else perror("error: ");
	
	return 0;
}