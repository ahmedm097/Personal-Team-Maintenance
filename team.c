//
// 
//
// Program for maintaining a personal team.
//
//
// Uses a linked list to hold the team players.
//
// Author: Mohammed Ahmed


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
//**********************************************************************
// Linked List Definitions
//  Define your linked list node and pointer types
//  here for use throughout the file.
//
//
//   ADD STATEMENT(S) HERE

struct node{
  char *familyName;
  char  *firstName;
  char position;
  int value;
  struct node* next;
};
struct node *head; //head pointer

//**********************************************************************
// Linked List Function Declarations
//
// Functions that modify the linked list.
//  
//
//   

struct node *makePlayer(struct node * head, char  familyName[], char  firstName[], char position, int value); //method to add player
bool sameFamily(struct node * head, char fam[]);
void deletePlayer(struct node ** head, char familyName[]); //method to delete player
void search(struct node * head, char fam[]); //method to search player
void value_less(struct node * head, int val); //check value
void printTeam(struct node * head); //print the team
void deleteList(struct node** head); //delete the whole list
bool duplicate(struct node * head, char fam[]); //check for duplicate name
//bool contains_duplicate

//**********************************************************************
// Support Function Declarations
//

void safegets (char s[], int arraySize);        // gets without buffer overflow
void familyNameDuplicate (char familyName[]);   // marker/tester friendly
void familyNameFound (char familyName[]);       //   functions to print
void familyNameNotFound (char familyName[]);    //     messages to user
void familyNameDeleted (char familyName[]);
void printTeamEmpty (void);
void printTeamTitle(void);
void printNoPlayersWithLowerValue(int value);

//**********************************************************************
// Program-wide Constants
//

const int MAX_LENGTH = 1023;
const char NULL_CHAR = '\0';
const char NEWLINE = '\n';
const char GOALKEEPER = 'G';
const char DEFENDER = 'D';
const char MIDFIELDER = 'M';
const char STRIKER = 'S';


//**********************************************************************
// Main Program
//

int main (void)
{
    const char bannerString[]
        = "Personal Team Maintenance Program.\n\n";
    const char commandList[]
        = "Commands are I (insert), D (delete), S (search by name),\n"
          "  V (search by value), P (print), Q (quit).\n";

    // Declare linked list head.
    //   ADD STATEMENT(S) HERE TO DECLARE LINKED LIST HEAD.
struct node *head = NULL;

    // announce start of program
    printf("%s",bannerString);
    printf("%s",commandList);

    char response;
    char input[MAX_LENGTH+1];
    do
    {
        printf("\nCommand?: ");
        safegets(input,MAX_LENGTH+1);
        // Response is first char entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]);

        if (response == 'I')
        {
            // Insert a player entry into the linked list.
            // Maintain the list in correct order (G, D, M, S).
            //   ADD STATEMENT(S) HERE

            // USE THE FOLLOWING PRINTF STATEMENTS WHEN PROMPTING FOR DATA:

            char familyName[MAX_LENGTH+1], firstName[MAX_LENGTH+1];
            char position;
            int value;

             printf("  family name: ");
             safegets(familyName,MAX_LENGTH+1); //get family name
             printf("  first name: ");
             safegets(firstName,MAX_LENGTH+1); //get first name
             printf("  position: ");
             scanf("%s", &position); //get position
             position = toupper(position);
             printf("  value: ");
             scanf("%d", &value); //get duplace name

//check if family name already exists
            bool x = duplicate(head, familyName);
            if(x == true){
            familyNameDuplicate(familyName);
            response=getchar();

          }
          else{
// add the player
            head = makePlayer(head,familyName,firstName,toupper(position),value);
            response=getchar();
          }


        }
        else if (response == 'D')
        {
            // Delete a player from the list.
            char  familyName[MAX_LENGTH+1];
            printf("\nEnter family name for entry to delete: ");
            safegets(familyName,MAX_LENGTH+1);
          deletePlayer(&head,familyName);
            //   ADD STATEMENT(S) HERE

        }
        else if (response == 'S')
        {
            // Search for a player by family name.
            char  fam[MAX_LENGTH+1];
            printf("\nEnter family name to search for: ");
            safegets(fam,MAX_LENGTH+1);
            search(head, fam);

            //   ADD STATEMENT(S) HERE

        }
        else if (response == 'V')
        {
            // Search for players that are worth less than or equal a value.
            char  value[MAX_LENGTH+1];
            printf("\nEnter value: ");
            safegets(value,MAX_LENGTH+1);
            int x = atoi(value);
            value_less(head, x);
            //   ADD STATEMENT(S) HERE

        }
        else if (response == 'P')
        {
            // Print the team.
            printTeam(head);
            //   ADD STATEMENT(S) HERE
            }
        else if (response == 'Q')
        {
            ; // do nothing, we'll catch this case below
        }
        else
        {
            // do this if no command matched ...
            printf("\nInvalid command.\n%s\n",commandList);
        }
    } while (response != 'Q');

    // Delete the whole linked list that hold the team.
    //   ADD STATEMENT(S) HERE
    deleteList(&head);

    // Print the linked list to confirm deletion.
    //   ADD STATEMENT(S) HERE
    printTeam(head);
    return 0;
}

//**********************************************************************
// Support Function Definitions

// Function to get a line of input without overflowing target char array.
void safegets (char s[], int arraySize)
{
    int i = 0, maxIndex = arraySize-1;
    char c;
    while (i < maxIndex && (c = getchar()) != NEWLINE)
    {
        s[i] = c;
        i = i + 1;
    }
    s[i] = NULL_CHAR;
}

// Function to call when user is trying to insert a family name
// that is already in the book.
void familyNameDuplicate (char familyName[])
{
    printf("\nAn entry for <%s> is already in the team!\n"
           "New entry not entered.\n",familyName);
}

// Function to call when a player with this family name was found in the team.
void familyNameFound (char familyName[])
{
    printf("\nThe player with family name <%s> was found in the team.\n",
             familyName);
}

// Function to call when a player with this family name was not found in the team.
void familyNameNotFound (char familyName[])
{
    printf("\nThe player with family name <%s> is not in the team.\n",
             familyName);

}

// Function to call when a family name that is to be deleted
// was found in the team.
void familyNameDeleted (char familyName[])
{
    printf("\nDeleting player with family name <%s> from the team.\n",
             familyName);
}

// Function to call when printing an empty team.
void printTeamEmpty (void)
{
    printf("\nThe team is empty.\n");
}

// Function to call to print title when whole team being printed.
void printTeamTitle (void)
{
    printf("\nMy Team: \n");
}

// Function to call when no player in the team has lower or equal value to the given value
void printNoPlayersWithLowerValue(int value)
{
	printf("\nNo player(s) in the team is worth less than or equal to <%d>.\n", value);
}

//**********************************************************************
// Add your functions below this line.
bool sameFamily(struct node * head,char *fam)
{
   struct node *p;
   //to check the whole linked list
   for (p = head; p != NULL; p = p->next){
     //if name is equal
     if(p->familyName == fam){
       return true;
     }
   }
   familyNameDuplicate(fam);
   return false;
}
//check duplicate name
bool duplicate(struct node * head, char fam[]){
//if head is null then theres no same person
if(head == NULL){

  return false;
}else{
  struct node *p;
  //loop through the whole code
for (p = head; p != NULL; p = p->next){
  //if they found a same name return true
  if(strcmp(p->familyName, fam) == 0){
    return true;
  }
}

}
//if not return false
  return false;
}

//deleting the list
void deleteList(struct node** head)
{


  struct node *current = *head;
  struct node  *next;
//start from head to the end of the list deleting it one by one and freeing it each time
      while (current != NULL)
      {
         next = current->next;
         free(current);
         current = next;
      }
      *head = NULL;
}

// prints the team
void printTeam(struct node * head){
//if head == null then team is empty
  if(head==NULL){
    printTeamEmpty();
  }else{
    printTeamTitle();

    struct node *p;

  for (p = head; p != NULL; p = p->next){
printf("\n");
    printf("%s\n",p->familyName);
    printf("%s\n",p->firstName);
    printf("%c\n",p->position);
    printf("%d\n",p->value);

  }
}
}
//check for people with value less than or equal to val
void value_less(struct node * head, int val){
  struct node *p;
  int i = 0;
   for (p = head; p != NULL; p = p->next){
//if its true
     if(p->value <= val){
       printf("\n");
       printf("%s\n",p->familyName);
       printf("%s\n",p->firstName);
       printf("%c\n",p->position);
       printf("%d\n",p->value);

       i=i+1;
     }
   }
   //if there nobody with value less than or equal to val
   if(i==0){
     printNoPlayersWithLowerValue(val);
   }
}
//seach the entire list for somebody
void search(struct node * head, char fam[]){
  struct node *p;
  int i = 0;
   for (p = head; p != NULL; p = p->next){
//if true
     if(strcmp(p->familyName, fam) == 0){

       familyNameFound(fam);
       printf("\n");
       printf("%s\n",p->familyName);
       printf("%s\n",p->firstName);
       printf("%c\n",p->position);
       printf("%d\n",p->value);

       i=i+1;
     }
   }
   //else
   if(i==0){
     familyNameNotFound(fam);

   }
}
//delete a player from list
void deletePlayer(struct node ** head, char  familyName[]){

  struct node *p;

   struct node *temp = *head;
   struct node *n;
  int i = 0;
//if nothing is in the list then the player cannot be found
  if(*head == NULL){
    familyNameNotFound (familyName);

  }
for (p = *head; p != NULL; p = p->next)
{
// if its found
    if(strcmp(p->familyName, familyName) == 0){
      //checking the front of the list


    //if its at head
      if(p == *head || (temp->next == NULL)){
        n = temp->next;
        free(temp);
        *head=n;
      }
      // if its at the tail
      else if(p->next == NULL){
        while(temp->next != NULL)
     {
        n=temp;
        temp=temp->next;
     }
     free(n->next);
     n->next=NULL;
      }
      //if its in the middle
      else{
        while(temp->next != p->next)
     {
        n=temp;
        temp=temp->next;
     }

     free(n->next);
     n->next=temp->next;

//

      }


      i=i+1;
    }


    }

  if(i==0 && head != NULL ){
    familyNameNotFound(familyName);

  }
  else if(head != NULL){
    familyNameDeleted (familyName);

  }


}




struct node * makePlayer(struct node* head, char familyName[], char firstName[], char position, int value){

  struct node *p;
  //add player to p
p = (struct node *)malloc(sizeof(struct node));
  p->familyName=malloc(MAX_LENGTH+1);
  p->firstName=malloc(MAX_LENGTH+1);
  strcpy(p->familyName,familyName);
  strcpy(p->firstName,firstName);
     p->value= value;
     p->position = position;

// if list is empty
  if(head == NULL)
  {
     p->next=head;
     head = p;
     return head;
}


  else{


  switch(p->position) {

  //if a goalkeeper was inserted
        case 'G' :
        //if the head does not have a player with position g put that player in the front*/
  		if(head->position!='G'){
                  p->next=head;
                  head=p;
              }
  		else{
  		//*if a goalkeeper is in front skip
                struct node * temp = head;
                while(temp->next!=NULL && temp->next->position=='G'){
  	            temp=temp->next;
                  }
                  //if theres someone other than play with position G
                  p->next=temp->next;
                  temp->next=p;
              }
              break;

  	//if a defender was inserted
        case 'D' :
              //if there is a midfielder or striker in the front just add defender in the head
              if(head->position=='M'||head->position=='S'){
                  p->next=head;
                  head=p;
              }
  		else{
  	//if a defender is in front skip
                  struct node * temp = head;
             while(temp->next!= NULL && temp->next->position!='M' && temp->next -> position!='S'){
  	            temp=temp->next;
                  }
                    //if theres someone other than player with position D
                  p->next=temp->next;
                  temp->next=p;
              }
              break;

  //if a midfielder was inserted
        case 'M' :
             //if a striker is in the front , put midfielder in the head*/
              if(head->position=='S'){
                  p->next=head;
                  head=p;
              }else{
             //if a defender is in front skip
                  struct node* temp = head;
                  while(temp->next!=NULL&&temp->next->position!='S'){
  	            temp=temp->next;
                  }
                    //if theres someone other than player with position G
                  p->next=temp->next;
                  temp->next=p;
              }
              break;

  //if a striker is inserted
  	 case 'S' :
     {
                  //add S to the back of the list
                	struct node* temp = head;
                  while(temp->next!=NULL){
  	              temp=temp->next;
                  }
                  p->next=temp->next;
                  temp->next=p;

   }

 }}return head;}
