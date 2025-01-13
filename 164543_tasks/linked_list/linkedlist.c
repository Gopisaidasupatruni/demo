/**REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

/* append: To add nodes at the end */
void append(ST **q, int num) {
    ST *temp = *q, *r;
    if (*q == NULL) {
        temp = (ST *)malloc(sizeof(ST));
        temp->data = num;
	/* adding at beginning */
        temp->link = NULL;
        *q = temp;
    }
   /* if atleast one node */ 
    else {
	    /* Traversing upto end */
        while (temp->link != NULL) {
            temp = temp->link;
        }
	/* add end */
        r = (ST *)malloc(sizeof(ST));
        r->data = num;
        r->link = NULL;
        temp->link = r;
    }
}
/* End append */
/* display: To display all elements */
void display(ST *q) {
    ST *temp = q;
    /* Traversing through all nodes */
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->link;
    }
}

/* add_begin: To add a node at the beginning */
void add_begin(ST **ptr, int iNum) {
	/* Adding nodes at beggining */
    ST *temp = (ST *)malloc(sizeof(ST));
    temp->data = iNum;
    temp->link = *ptr;
    *ptr = temp;
}

/* push: To add a node  */
void push(ST **ptr, int iNum) {
	/* pushing nodes at front*/
    ST *temp = (ST *)malloc(sizeof(ST));
    temp->data = iNum;
    temp->link = *ptr;
    *ptr = temp;
}

/* pop: to remove a node */
void pop(ST **ptr) {
	/* popping last enterd element */
    if (*ptr == NULL) {
        printf("No elements to pop\n");
        return;
    }
    ST *temp = *ptr;
    *ptr = temp->link;
    free(temp);
}

/* Length: To count all elements */
int Length(ST *head) {
    int count = 0;
    ST *current = head;
    while (current != NULL) {
	    /* To count all nodes */
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

/* insertNth: To insert data at nth index */
void insertNth(ST **ptr, int index, int num) {
    ST *temp = *ptr, *r = *ptr;
    temp = (ST *)malloc(sizeof(ST));
    temp->data = num;
    temp->link = NULL;
    if (index == 0) {
        temp->link = *ptr;
        *ptr = temp;
        return;
    }
    int count = 1;
    while (r != NULL) {
        if (count == index) {
            temp->link = r->link;
            r->link = temp;
            return;
        }
        r = r->link;
        count++;
    }
    printf("Enter correct index\n");
}

/* removeDuplicates: Removing duplicates from list */
void removeDuplicates(ST **ptr) {
    ST *temp = *ptr;
    while (temp != NULL) {
        ST *r = temp;

        while (r->link != NULL) {
            if (r->link->data == temp->data) {
                ST *prv = r->link;
                r->link = r->link->link;
                free(prv);
            } else {
                r = r->link;
            }
        }
        temp = temp->link;
    }
}

/* moveNode: To move a node from q to p */
void moveNode(ST **p, ST **q) {
    ST *temp = *q;
    *q = temp->link;
    temp->link = *p;
    *p = temp;
}

/* Sortedinsert: Entering elements in sorting */
void SortedInsert(ST **q,ST*new) {
    ST *last = *q, *temp = *q;
    int num;
   
    if (*q == NULL || (*q)->data > new->data) {
        new->link = *q;
        *q = new;
    } else {
        while (last != NULL) {
            if (last->data <= new->data && (last->link == NULL || last->link->data > new->data)) {
                new->link = last->link;
                last->link = new;
                return;
            }
            last = last->link;
        }
    }
}
/* InsertSort: Function to sort the linked list using InsertSort */
void InsertSort(ST** p) {
    ST* s = NULL;  
    ST*temp = *p; 

    while (temp != NULL) {
        ST* next = temp->link; 
	temp->link=NULL;
        SortedInsert(&s,temp); 
        temp = next;
    }
*p=s;
  
}
/* intCount: To count occurrences of a number */
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

