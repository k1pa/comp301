#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1

int main(void){
	pid_t pid;
	int status;
	char command[150];
	char *p; 
	char ** res = NULL;
	//type_prompt();
	printf("> ");
	
	while(TRUE){
		
		//scanf returns the number of variables that have been assigned input
		//probably do not need to do this however checking is always good
		if(scanf("%150[^\n]", command) == 1){
			if(strcmp(command,"exit") == 0 || strcmp(command, "quit") == 0) exit(0);

			printf("> ");
			int n_spaces = 0;
			char str[175] = "/bin/";
			strcat(str,command);
				
			p = strtok(str, " ");
			while (p){
					
				res = realloc(res, sizeof (char *) * ++n_spaces);
					
				if(res == NULL) exit(1);
					
				res[n_spaces - 1] = p;
					
				p = strtok(NULL, " ");
			}
			res = realloc (res, sizeof (char*) * (n_spaces +1));
			res[n_spaces] = '\0';
			
			//printf();
			pid = fork();
			if(pid == -1){
				exit(1);
			}
			else if(pid > 0){
				//parent code
				waitpid(pid, &status, 0);
			} else {
				//child code
				//printf(command);
				
				execve(res[0] ,res ,NULL);
				perror("error with execve method\n");
				_exit(1);
					
			}
			
		}
		else {
			while(getchar() != '\n');
		}
	}
	
	return 0;
}
