/** REQUIRED HEADER FILES */
#include <stdio.h>
#include<stdlib.h>
#include "linkedlist.h"

/* MAIN PROGRAM */
int main() {
	/* head pointer */
    ST *p = NULL;
    ST *q = p,*i=NULL;
    int iData, idel, num, index;
    char choice;
/* Printing Instructions */
    while (1) {
        printf("\n--- Linked List Operations Menu ---\n");
        printf("a. Add at beginning of p\n");
        printf("b. Add at beginning of q\n");
        printf("i. Append at end\n");
        printf("p. Pushing element\n");
        printf("n. Inserting element\n");
        printf("t. Pop an element \n");
        printf("d. Display list\n");
        printf("s. Sort insert\n");
	printf("o. Inserted Sort\n");
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
		/* To add begin to p*/
            case 'a':
                printf("Enter data to p add at the beginning: ");
                scanf("%d", &iData);
                add_begin(&p, iData);
                break;
		/* To add begin to q*/
            case 'b':
                printf("Enter data to q add at the beginning: ");
                scanf("%d", &iData);
                add_begin(&q, iData);
                break;
		/* To add end*/
            case 'i':
                printf("Enter data to append: ");
                scanf("%d", &iData);
                append(&p, iData);
                break;
		/* To push node*/
            case 'p':
                printf("push data: \n");
                scanf("%d", &iData);
                push(&p, iData);
                break;
		/* To pop data */
            case 't':
                printf("popped data \n");
                pop(&p);
                break;
		/* To display all nodes */
            case 'd':
                printf("Linked list elements: ");
                display(p);
                printf("\n");
                break;
		/* To find length */
            case 'l':
                printf("Length of the list: %d\n", Length(p));
                break;
		/* To count given number */
            case 'c':
                printf("Enter number to count occurrences: ");
                scanf("%d", &num);
                printf("%d occurs %d times\n", num, intCount(&p, num));
                break;
		/* To find index */
            case 'f':
                printf("Enter number to find index: ");
                scanf("%d", &num);
                getNth(&p, num);
                break;
		/* To insert number */
            case 'n':
                printf("Enter index to insert number: ");
                scanf("%d", &index);
                printf("Enter number: ");
                scanf("%d", &num);
                insertNth(&p, index, num);
                break;
		/* To delete element */
            case 'r':
                printf("Enter number to delete: ");
                scanf("%d", &idel);
                delete(&p, idel);
                break;
		/* To remove duplicates */
            case 'x':
                removeDuplicates(&p);
                printf("Duplicates removed.\n");
                break;
		/* To move data from q to p*/
            case 'm':
                moveNode(&p, &q);
                break;
		/* To enter data in sorted manner */
            case 's':
		  i = (ST *)malloc(sizeof(ST)); 
                printf("Enter data to sort insert: ");
                scanf("%d", &iData);
                i->data = iData;
                i->link = NULL;
                SortedInsert(&p,i);
                break;
		/* To sort list */
            case 'o':
                InsertSort(&p);
                break;
		/* To exit */
            case 'q':
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
/* End main */
