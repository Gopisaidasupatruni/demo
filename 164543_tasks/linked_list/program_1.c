#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *link;
} ST;

void append(ST **, int);
void display(ST *);
int Length(ST *head);
int intCount(ST **, int);
void add_begin(ST **, int);
void push(ST **, int);
void pop(ST **);
void delete(ST **, int);
void getNth(ST **, int);
void insertNth(ST** ptr,int index,int num);
void Insertsort(ST** );
void removeDuplicates(ST** );
void moveNode(ST** destRef, ST ** sourceRef);
int main() {
    ST *p = NULL;
    ST *q=p;
    int iData, idel, num, index;
    char choice;

    while (1) {  
        printf("\n--- Linked List Operations Menu ---\n");
        printf("a. Add at beginning of p\n");
        printf("b. Add at beginning of q\n");
        printf("i. Append at end\n");
        printf("p. Pushing element\n");
        printf("n. Inserting element\n");
	printf("t. Pop an element \n");
        printf("d. Display list\n");
        printf("s. Sort list\n");
        printf("l. Get list length\n");
        printf("c. Count occurrences of a number\n");
        printf("f. Get index of a number\n");
        printf("r. Delete a number\n");
	printf("x. Removing duplicates\n");
	printf("m. Move nodes\n");
        printf("q. Quit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'a':
                printf("Enter data to p add at the beginning: ");
                scanf("%d", &iData);
                add_begin(&p, iData);
                break;
            case 'b':
                printf("Enter data to q add at the beginning: ");
                scanf("%d", &iData);
                add_begin(&q, iData);
                break;

            case 'i':
                printf("Enter data to append: ");
                scanf("%d", &iData);
                append(&p, iData);
                break;

	    case 'p':
		printf("push data: \n");
                scanf("%d", &iData);
		push(&p,iData);
		break;

	    case 't':
		printf("popped data \n");
		pop(&p);
		break;
            case 'd':
                printf("Linked list elements: ");
                display(p);
                printf("\n");
                break;

            case 'l':
                printf("Length of the list: %d\n", Length(p));
                break;

            case 'c':
                printf("Enter number to count occurrences: ");
                scanf("%d", &num);
                printf("%d occurs %d times\n", num, intCount(&p, num));
                break;

	    case 's':
                 
                Insertsort(&p);

                break;

	    case 'n':
		
		printf("enter a index to insert data\n");
		scanf(" %d",&index);
                printf("Enter data : ");
                scanf(" %d", &iData);
		insertNth(&p,index,iData);
		printf("\n");
		break;

            case 'f':
                printf("Enter number to find its index: ");
                scanf("%d", &index);
                getNth(&p, index);
                break;

            case 'r':
                printf("Enter number to delete: ");
                scanf("%d", &idel);
                delete(&p, idel);
                printf("Updated list: ");
                display(p);
                printf("\n");
                break;

	    case 'x':
		printf("removing duplicates\n");
                removeDuplicates(&p);
		display(p);
		break;

	    case 'm':
		printf("Moving node \n");
		moveNode(&p,&q);
		display(p);
		printf("\n");
		display(q);
		break;

            case 'q':
                printf("Exiting program...\n");
                return 0;  

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

/* append: To add nodes at the end */
void append(ST **q, int num) {
    ST *temp = *q, *r;
    if (*q == NULL) {
        temp = (ST *)malloc(sizeof(ST));
        temp->data = num;
        temp->link = NULL;
        *q = temp;
    } else {
        while (temp->link != NULL) {
            temp = temp->link;
        }
        r = (ST *)malloc(sizeof(ST));
        r->data = num;
        r->link = NULL;
        temp->link = r;
    }
}

/* display: To display all elements */
void display(ST *q) {
    ST *temp = q;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->link;
    }
}

/* add_begin: To add a node at the beginning */
void add_begin(ST **ptr, int iNum) {
    
    ST *temp = (ST *)malloc(sizeof(ST));
    
    temp->data = iNum;
   
    temp->link = *ptr;
    
    *ptr=temp;

}

/* push: To add a node  */
void push(ST **ptr, int iNum) {
	
    ST *temp = (ST *)malloc(sizeof(ST));
    temp->data = iNum;
    temp->link = *ptr;
    *ptr = temp;
}
/* pop: to remove a node */
void pop(ST**ptr)
{
    if(*ptr==NULL){
	    printf("No elements to pop\n");
            return ;
    }
    ST*temp=*ptr;
    *ptr=temp->link;
    free(temp);

}

/* Length: To count all elements */
int Length(ST *head) {
    int count = 0;
    ST *current = head;
    while (current != NULL) {
        count++;
        current = current->link;
    }
    return count;
}

/* delete: To delete a given node */
void delete(ST **ptr, int num) {
    ST *temp = *ptr, *prv = NULL;
    while (temp != NULL) {
        if (temp->data == num) {
            if (temp == *ptr) {
                *ptr = temp->link;
            } else {
                prv->link = temp->link;
            }
            free(temp);
            return;
        }
        prv = temp;
        temp = temp->link;
    }
    printf("Given data is not present\n");
}

/* getNth: To get the index of a number */
void getNth(ST **ptr, int iNum) {
    ST *temp = *ptr;
    int count = 0;
    while (temp != NULL) {
        if (temp->data == iNum) {
            printf("%d is at index %d\n", iNum, count);
            return;
        }
        temp = temp->link;
        count++;
    }
    printf("Number not found in the list\n");
}
/* To add data at nth index */
void insertNth(ST** ptr,int index,int num)
{
	
	ST*temp = *ptr;
	
        ST*r=*ptr;
        temp = (ST *)malloc(sizeof(ST));
        temp->data = num;
	temp->link=NULL;
	 if(index == 0)
	 {
		temp->link=*ptr;
		*ptr=temp;
		return;
	 }
	int count=1;
        while (r!=NULL ) {
		if(count==index)
		{
			temp->link=r->link;
			r->link=temp;
			return;
		}
		r=r->link;
		count++;

	}
	printf("Enter correct index\n");
}
/* removeDuplicates: Removing duplicates from list */
void removeDuplicates(ST**ptr )
{
	ST *temp=*ptr;
	
        /* Moving each node*/
	
		while(temp!=NULL)
		{
			ST *r=temp;
			while(r->link!=NULL)
			{

                        /* comparing if it is repeating again */
			if(r->link->data == temp->data)
			{
				ST *prv = r->link;
                                
				r->link=r->link->link;
                        	free(prv);
				
			}
			else
			{ 
				r=r->link;
			}
		}
		
		temp=temp->link;
		}
}

/* moveNode: To move a node from q to p */
void moveNode(ST**p,ST **q)
{
    ST *temp = *q;
    
    (*q) = temp->link;
    
    /* Storing it in p */
    temp->link = *p;
    *p = temp;

}

/* Insertsort: Entering elemnts in sorting */
void Insertsort(ST** q) {
ST* last = *q;
ST* temp = *q;
int num;
printf("Enter data:\n");
scanf(" %d",&num);
        temp=(struct node*)malloc(sizeof(struct node));
                temp->data=num;
                if(*q==NULL||(*q)->data>num){
                temp->link=*q;
		*q=temp;
}
else
{
        while(last!=NULL)
        {
                if(last->data <= num &&(last->link==NULL||last->link->data>num))
                {
                        temp->link=last->link;
                        last->link=temp;
                        return;
                }
                last=last->link;
        }
}


}

/* intCount: To count the number of times the given element appears */
int intCount(ST **ptr, int iNum) {
    ST *temp = *ptr;
    int count = 0;
    while (temp != NULL) {
        if (temp->data == iNum) {
            count++;
        }
        temp = temp->link;
    }
    return count;
}

