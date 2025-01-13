/* Complete the missing code */
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
	int data;
	struct Node* next;
}Node;
Node* createNode(int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}
	newNode->data = data;
	newNode->next = newNode;
	return newNode;
}
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
void deleteNode(Node** head, int data) {
	//code here
	if(*head==NULL)
		printf("error\n");
	Node *temp,*prv=NULL;


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
int main() {
	Node* head = NULL;
	insertAtBeginning(&head, 1);
	insertAtEnd(&head, 2);
	insertAtEnd(&head, 3);
	insertAtBeginning(&head, 4);
	printf("Circular Linked List: ");
	display(head);
	deleteNode(&head, 2);
	printf("Circular Linked List after deleting 2: ");
	display(head);
	return 0;
}

