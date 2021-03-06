#include <stdio.h>
#include<string.h>
#include<stdlib.h>
//structure
struct node{
	char name[100]; 
	char phone[50];  
	struct node * next;  
};
//pointer of type node
struct node *head=NULL;
//for memory allocation 
struct node* getNode();
//function definitions
void insert_phonebook();
void readFile();
void writeFile();
void delete_Record();
void retrieve_Record();
//main method
int main(){
	int begin=1;  
	int action = 0; 
	
	printf("Phonebook Application: \n");
	while(begin){
	 printf("1. Create new entry\n");
        printf("2. Retrieve entries\n");
        printf("3. Delete entry\n");
        printf("4. Load entry\n");
        printf("5. Save Entry\n");      
		printf("Your choice: \n");
	scanf("%d",&action);getchar();  
		switch(action){
			//as per the user input, different methods will run
		case 1: { insert_phonebook();break; }
		case 2: {
		retrieve_Record();break; }
		case 3:{
		delete_Record();break;}
		case 4:{
		readFile();break;}
		case 5: {
		writeFile();break;}
		default:
		printf("Verify Input!");  
		}
	}
}
//for the memory allocation everytime we use the pointer
struct node* getNode() {  
    struct node* newNode;
	newNode = (struct node*)malloc(sizeof(struct node));
	newNode->next = NULL;
	return newNode;
}
//to insert the records
void insert_phonebook(){  	
	char name[100];
	char num[50];
	printf("\nEnter Name: \n");
	gets(name);
	printf("\nEnter Phone Number: \n");
	gets(num);
	//pointer and its memory allocation
	struct node* newNode = getNode();
	//assigning values
	strcpy(newNode->name, name);
	strcpy(newNode->phone, num);
	if(head == NULL) {
		//poiting to newNode
        head = newNode;
	} else {
		//pointer equals head if not NULL
        struct node *temp = head;
		//till NULL
        while(temp->next != NULL){
            temp = temp->next;
		}
		temp->next = newNode;
		//making temp's next ->newNode
	}
}
//to load the entries
void readFile() {
    head = NULL;
    FILE *fp;
	//opening and permission assigned
	fp = fopen("Contacts.txt","a+"); 
	char name[100];
    char num[50];
	//till end of file
	while(fscanf(fp, "%s", name) != EOF) 
		{ 
        fscanf(fp, "%s", num);
        printf("\nName: %s \nPhone Number: %s \n",name, num);
		//pointer of struct type
		struct node* newNode = getNode();
		//values to the struct
        strcpy(newNode->name, name);
        strcpy(newNode->phone, num);
        if(head == NULL) {
            head = newNode;
			//printf("\nList Empty!\n");
        } else {
            struct node *temp = head;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = newNode;
        }
	}
	//closing the file
	fclose(fp); 
}
//for saving the data
void writeFile(){
	FILE *fp;
	//permission
	fp = fopen("Contacts.txt","w");
	//pointer of struct type , equal to head
	struct node *temp=head;
	while(temp != NULL) {
        fprintf(fp,"%s\n%s\n",temp->name,temp->phone);
        temp=temp->next;
    }
	//closing the file
	fclose(fp);
	//confirmation message
	printf("\nAction Saved!\n");
}
//to retrieve a record 
void retrieve_Record() {
	char name[100];
	printf("\nEnter Name You Want to retrieve: \n");
	//to retrieve by name attribute
	gets(name);
	int input;
	if(head==NULL){
        printf("\nThe List is Empty!\n");
	} else{
        struct node *temp=head;
        while(temp != NULL){
			//matching the values
            input =	strcmp(temp->name,name);
            if(input==0) {//if matches then retrieving data
          printf("Name: %s \nPhone Number: %s \n",temp->name, temp->phone);
            }
            temp=temp->next;
            }}
}
//to delete an entry
void delete_Record(){
    char name[100];
    printf("\nEnter Name You Want To Delete: \n");
	//by name attribute
	gets(name);
	int match;  
    if(head == NULL){
        printf("\nList is Empty!\n");
	} 
	else {
		//pointers of struct type
        struct node *temp = head, *temp1 = NULL;
        if(strcmp(head->name, name) == 0) {
            head = head->next;
            return;
        }
        while(temp != NULL){
			match = strcmp(temp->name,name);
			if(match == 0) {
                temp1->next = temp->next;
                free(temp);
				printf("\nRecord Deleted!\n");
			}
			temp1 = temp;
			temp = temp->next;
		}		
	}
}
