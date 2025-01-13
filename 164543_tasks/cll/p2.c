/* Print the sum of all even numbers stored in a circular linked list. */
/*
 * Author :Gopisai
 * Date : 18/10/2024 
 */
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
	int data;
	struct Node* next;
}Node;
/*Node* createNode(int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}
	newNode->data = data;
	newNode->next = newNode;
	return newNode;
}*/
/*
 * Author :Gopisai
 * Date : 18/10/2024 
 */
Node* createNode(int data) {
    Node* newNode = malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL; // Will be set when inserted
    }
    return newNode;
}

/*
 * Author :Gopisai
 * Date : 18/10/2024 
 */
void insertAtBeginning(Node** head, int data) {
	// code here
	Node* newNode = createNode(data);
	if (*head == NULL) {
		*head = newNode;
	} else {
		Node * temp = *head ;
		while (temp->next != *head) {
			temp = temp->next;
		}
		temp->next = newNode;
	}

		newNode->next = *head;
		*head = newNode;
	
}
/*
 * Author :Gopisai
 * Date : 18/10/2024 
 */
void insertAtEnd(Node** head, int data) {
	//code here
	Node* newNode = createNode(data);
	if (*head == NULL) {
		*head = newNode;
	} else {
		Node * temp = *head ;
		while (temp->next != *head) {
			temp = temp->next;
		}
		temp->next = newNode;
		
	}
		newNode->next = *head;

}
/* deleteNode */
/*
 * Author :Gopisai
 * Date : 18/10/2024 
 */
void deleteNode(Node** head, int data) {
	//code here
	if(*head==NULL)
		printf("error\n");
	Node *temp=*head;
	Node *prv=NULL;


	if(temp->data==data)

	{
		if(temp->next==(Node*)*head)
		{
			free(temp);
		        *head=NULL;
			return;
		}
		else
		{
			while(temp->next!=*head)
				temp=temp->next;
			temp->next=(*head)->next;
				free(*head);
			*head=temp->next;
			return;
		}
	}

	prv=*head;
	temp=(*head)->next;
	while(temp!=*head)
	{
		if(temp->data==data)
		{
                	prv->next=temp->next;
		     free(temp);
	     return;
		}
               prv=temp;
       temp=temp->next;		       
			


		}
	printf("not found\n");
}

/*
 * Author :Gopisai
 * Date : 18/10/2024 
 */
void display(Node* head) {
	 Node* current = head;
	if (head == NULL) {
		printf("List is empty\n");
		return;
	}
	do {
		printf("%d ", current->data);
		current = current->next;
	} while (current != head);

}
/*
 * Author :Gopisai
 * Date : 18/10/2024 
 */
void sumEvenNumbers(Node* head) {
    if (head == NULL) 
	    return; 

    int sum = 0;
    Node* current = head;

    do {
        if (current->data % 2 == 0){
            sum += current->data; 
        }
        current = current->next; 
    } while (current != head); 

    printf("Sum of even numbers: %d\n", sum);
}

int main() {
	Node* head = NULL;
	insertAtBeginning(&head, 1);
	insertAtEnd(&head, 2);
	insertAtEnd(&head, 3);
	insertAtBeginning(&head, 4);
	printf("Circular Linked List: ");
	display(head);
	printf("\n");
	deleteNode(&head, 1);
	printf("Circular Linked List after deleting 1: ");
	display(head);
	printf("\n");
	sumEvenNumbers(head);
	return 0;
}

