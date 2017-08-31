/*
	Name: Shaun Allen
	ID: 1259316
*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//define the node structure, and the attributes of a node
typedef struct node{
  int process_ID;
  int quanta;
  int num_tickets;
  struct node *next;
} node;

//methods declaration
 node* create_new_node(int a,int b,int c);
void insert(node* n);
 node* delete(int id);
void traverse();
void find(int id);

node *new_node, *ptr, *prev, *temp;
node *first = NULL, *last = NULL;

//creates a new node and returns a pointer to it to add/insert into the linked list
node* create_new_node(int p_ID, int quan, int num_tick){
  new_node = (node *) malloc(sizeof(node));

  if(!new_node){
    printf("memory was not successfully allocated :(\n");
    return 0;
  }
  else {
    new_node->process_ID = p_ID;
    new_node->quanta = quan;
    new_node->num_tickets = num_tick;
	new_node->next = NULL;

    return new_node;
  }
}

//i use this method for traversing the list untill count is negative, setting temp to correct node
void traverse(int lotto_count){
	temp = first;
	lotto_count -= temp->num_tickets;
	while(lotto_count > 0 && temp != NULL){
		temp = temp->next;
		lotto_count -= temp->num_tickets;
	}
}

//insert a node n into the linked list
void insert(node* n){

 if(first != NULL){
	last->next = n;
	last = n;
 }
 else{
	 first = n;
	 last = n;
 }
}

//find a node & set correct pointers
void find(int id){
	ptr = first;
	while(ptr->process_ID != id && ptr != NULL){
		prev = ptr;
		ptr = ptr->next;
	}
}

//delete a node and remove correct pointers
node* delete(int id){
	find(id);
	if(ptr == NULL){
		return NULL;
	}
	else{
		if(id == first->process_ID) first = first->next;
		else{
			if(ptr->next == NULL){
			prev->next = NULL;
			last = prev;
			}
			else{
				prev->next = ptr->next;
			}
		}
		return ptr;
	}
}

//convert string to int and return node pointer
struct node* makeNode(char *str){
	int id = 0;
	int quan = 0;
	int tickets = 0;
	char str_token[100];
	strcpy(str_token, strtok(str, ","));

	id = atoi(str_token);
	strcpy(str_token ,strtok(NULL, ","));
	quan = atoi(str_token);
	strcpy(str_token, strtok(NULL, ","));
	tickets = atoi(str_token);
	
	return create_new_node(id, quan, tickets);
}

//schedule processes to run on "cpu"
void schedule(node* root){
	int max = 900;
	double priority1 = 0;
	double priority2 = 0;
	double priority3 = 0;
	double priority4 = 0;
	int ticket_number = 0;
	int priority = 0;
	srand(time(NULL));
	
	while(first != NULL){
		ticket_number = (rand() % max) + 1;
		traverse(ticket_number);
		
		priority = temp->num_tickets;
		//the plus 1 scattered throughout is for the switching overhead
		//priority is 1
		if(priority == 1){
			if(temp->quanta <= 20){
				priority1 += temp->quanta + 1;
				max -= temp->num_tickets;
				delete(temp->process_ID);
			}
			else{
				priority1 += 21;
				temp->quanta -= 20;
			}
		}
		//priority is 2
		else if(priority == 5){
			if(temp->quanta <= 20){
				priority2 += temp->quanta + 1;
				max -= temp->num_tickets;
				delete(temp->process_ID);
			}
			else{
				priority2 += 21;
				temp->quanta -= 20;
			}
		}
		//priority is 3
		else if(priority == 10){
			if(temp->quanta <= 20){
				priority3 += temp->quanta + 1;
				max -= temp->num_tickets;
				delete(temp->process_ID);
			}
			else{
				priority3 += 21;
				temp->quanta -= 20;
			}
		}
		//priority is 4
		else{
			if(temp->quanta <= 20){
				priority4 += temp->quanta + 1;
				max -= temp->num_tickets;
				delete(temp->process_ID);
			}
			else{
				priority4 += 21;
				temp->quanta -= 20;
			}
		}
	}
	priority1 = priority1 / 25;
	priority2 = priority2 / 25;
	priority3 = priority3 / 25;
	priority4 = priority4 / 25;
	printf("priority1 average job completion time: %.2f\n", priority1);
	printf("priority2 average job completion time: %.2f\n", priority2);
	printf("priority3 average job completion time: %.2f\n", priority3);
	printf("priority4 average job completion time: %.2f\n", priority4);
}

int main(void){
	node *root = NULL;
	char str[1024];
	FILE *file;
	
	printf("please enter a csv file to read from\n");
	//node* root = create_new_node(p_ID,quan,num_tik);
	while(1){
		scanf("%1023s", str);
		
		if((file = fopen(str, "r"))){
			
			fgets(str, 1024, file);
			
			root = makeNode(str);
			insert(root);
			fflush(stdout);
			while(fgets(str, 1024, file)){
				insert(makeNode(str));
			}
			
			schedule(root);
			break;
		}
		else{
			perror("Error: ");
		}
		fflush(stdin);
		
		printf("please enter a csv file to read from\n");
	}
	
	//fclose(file); //do not need this as it is happening in main, and all opened file buffers
	//are automatically closed.
	return 0;
}