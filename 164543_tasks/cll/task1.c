/* Circular linked list */
/*
 * Author :Gopisai
 * Date : 18/10/2024 
 */
/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>

/* Structure definition */
typedef struct Node {
    int data;
    struct Node* next;  
} Node;

/* createNode : Function to create a new node */
/*
 * Author :Gopisai
 * Date : 18/10/2024 
 */
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {  
	    /* Check for memory allocation failure */
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    /* Initialize next to point to itself (for circular list)*/
    newNode->next = newNode;  
    return newNode;
}

/* insertAtBeginning: Function to insert a node at the beginning of the circular linked list */
/*
 * Author :Gopisai
 * Date : 18/10/2024 
 */
void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {  /* If list is empty, new node is the only node has head*/
        *head = newNode;
    } else {
        Node* temp = *head;
        /* Traverse to the last node */
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;  
	/* Link last node to new node */
    }
    newNode->next = *head;  
    /* Point new node next to the head */
    *head = newNode;  
    /* Update head to point to the new node */
}

/* insertAtEnd: Function to insert a node at the end of the circular linked list */
/*
 * Author :Gopisai
 * Date : 18/10/2024 
 */
void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {  
	    /* If list is empty, new node is the only node */
        *head = newNode;
    } else {
        Node* temp = *head;
        /* Traverse to the last node */
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;  
	/* Link last node to new node */
    }
    newNode->next = *head;  
    /* Point new node's next to the head */
}

/* deleteNode: Function to delete a node with specific data from the circular linked list */
/*
 * Author :Gopisai
 * Date : 18/10/2024 
 */
void deleteNode(Node** head, int data) {
    if (*head == NULL) {  /* If list is empty, nothing to delete */
        printf("List is empty\n");
        return;
    }

    Node *temp = *head, *prev = NULL;

    /* Check if the node to be deleted is the head node */
    if (temp->data == data) {
        /* If there is only one node */
        if (temp->next == *head) {
            free(temp);
            *head = NULL;
            return;
        } else {
            /* If there are more nodes */
            while (temp->next != *head) {
                temp = temp->next;
            }
            temp->next = (*head)->next;
            free(*head);
            *head = temp->next;  /* Update head */
            return;
        }
    }

    /* Traverse the list to find the node to be deleted */
    prev = *head;
    temp = (*head)->next;
    while (temp != *head) {
        if (temp->data == data) {
            prev->next = temp->next;  /* Link previous node to next node */
            free(temp);  /* Free the node to be deleted */
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Node with data %d not found\n", data);  /* If node not found */
}

/* display: Function to display the circular linked list */
/*
 * Author :Gopisai
 * Date : 18/10/2024 
 */
void display(Node* head) {
    if (head == NULL) {  /* If list is empty */
        printf("List is empty\n");
        return;
    }
    Node* current = head;
    do {
        printf("%d ", current->data);  
	/* Print data of each node */
        current = current->next;
    } while (current != head);  
    /* Stop when we return to the head */
    printf("\n");
}
/* main: Inserting ,deleting and displaying nodes in circular linked list */ 
int main() {
    Node* head = NULL;  /* Initialize an empty circular linked list */

    /* Insert elements into the list */
    insertAtBeginning(&head, 1);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 3);
    insertAtBeginning(&head, 4);

    printf("Circular Linked List: ");
    display(head);  /* Display the list */

    /* Delete a node with value 2 */
    deleteNode(&head, 2);
    printf("Circular Linked List after deleting 2: ");
    display(head);  
    /* Display the list again after deletion */

    return 0;
}

