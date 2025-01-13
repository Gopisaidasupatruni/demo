/*
 * Program to manage circular linked list operations: Insert, Delete, and Sum Even Numbers
 * Author: Gopisai
 * Date: 18/10/2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;            /* Data stored in the node */
    struct Node* next;   /* Pointer to the next node in the list */
} Node;

/*
 * Function: createNode
 * --------------------
 * 
 * Allocates memory for a new node, initializes it with the given data, and returns it.
 * 
 * returns: Pointer to the newly created node.
 */
Node* createNode(int data) {
    Node* newNode = malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = data;     /* Initialize data */
        newNode->next = NULL;     /* Next will be set during insertion */
    }
    return newNode;
}

/*
 * Function: insertAtBeginning
 * ---------------------------
 * Inserts a new node at the beginning of the circular linked list.
 * 
 * head: Pointer to the head node of the list.
 * data: Data to be inserted in the new node.
 */
void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;       
       	/* If list is empty, new node is the only node */
        newNode->next = *head; 
       	/* Circular link back to itself */
    } else {
        Node* temp = *head;
        while (temp->next != *head) {  
		/* Traverse to the last node */
            temp = temp->next;
        }
        temp->next = newNode;        
	/* Last node points to the new node */
        newNode->next = *head;       
	/* New node points to the current head */
        *head = newNode;           
      	/* Update head to the new node */
    }
}

/*
 * Function: insertAtEnd
 * ---------------------
 * Inserts a new node at the end of the circular linked list.
 */
void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;       
       	/* If list is empty, new node is the only node */
        newNode->next = *head;  
	/* Circular link back to itself */
    } else {
        Node* temp = *head;
        while (temp->next != *head) { 
	       	/* Traverse to the last node */
            temp = temp->next;
        }
        temp->next = newNode;
	/* Last node points to the new node */
        newNode->next = *head;    
     	/* New node points to the current head */
    }
}

/*
 * Function: deleteNode
 * --------------------
 * Deletes a node with the specified data from the circular linked list.
 */
void deleteNode(Node** head, int data) {
    if (*head == NULL) {
        printf("List is empty\n");  /* Handle empty list case */
        return;
    }

    Node* temp = *head;
    Node* prv = NULL;

    /* Check if the head node is the node to be deleted */
    if (temp->data == data) {
        if (temp->next == *head) {
            free(temp);          /* If the only node in the list */
            *head = NULL;        /* Set head to NULL */
            return;
        } else {
            while (temp->next != *head) {  
		    /* Traverse to the last node */
                temp = temp->next;
            }
            temp->next = (*head)->next;  
	    /* Update last node to point to second node */
            free(*head);   
	    /* Free the head node */
            *head = temp->next; 
   	    /* Update head pointer */
            return;
        }
    }

    /* Traverse the list to find the node to be deleted */
    prv = *head;
    temp = (*head)->next;
    while (temp != *head) {
        if (temp->data == data) {
            prv->next = temp->next;  
	    /* Bypass the node to be deleted */
            free(temp);  
	    /* Free the node */
            return;
        }
        prv = temp; 
       	/* Move previous pointer to the current node */
        temp = temp->next; 
       	/* Move to the next node */
    }

    printf("Node with data %d not found\n", data);
}

/*
 * Function: display
 * -----------------
 * Prints all the data elements in the circular linked list.
 * 
 * head: Pointer to the head node of the list.
 */
void display(Node* head) {
    if (head == NULL) {
        printf("List is empty\n");  
	/* Handle empty list case */
        return;
    }

    Node* current = head;
    do {
        printf("%d ", current->data); 
       	/* Print the data of each node */
        current = current->next;
    } while (current != head); 
    /* Continue until we reach the head again */
    printf("\n");
}

/*
 * Function: sumEvenNumbers
 * ------------------------
 * Calculates and prints the sum of all even numbers in the circular linked list.
 * 
 * head: Pointer to the head node of the list.
 */
void sumEvenNumbers(Node* head) {
    if (head == NULL) {
        printf("List is empty\n");  
	/* Handle empty list case */
        return;
    }

    int sum = 0;
    Node* current = head;

    do {
        if (current->data % 2 == 0) {
            sum += current->data;
	    /* Add even numbers to the sum */
        }
        current = current->next;
    } while (current != head);
    /* Continue until we reach the head again */

    printf("Sum of even numbers: %d\n", sum);
}

/*main:  Main program to demonstrate the circular linked list operations */
int main() {
    Node* head = NULL;  /* Initialize an empty list */

    insertAtBeginning(&head, 1);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 3);
    insertAtBeginning(&head, 4);

    printf("Circular Linked List: ");
    display(head);  
    /* Display the list */

    deleteNode(&head, 1); 
    /* Delete node with data 1 */

    printf("Circular Linked List after deleting 1: ");
    display(head); 
    /* Display the list after deletion */

    sumEvenNumbers(head);  
    /* Calculate and print the sum of even numbers */

    return 0;
}

