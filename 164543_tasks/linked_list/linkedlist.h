#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct node {
    int data;
    struct node *link;
} ST;

void append(ST **, int);
void display(ST *);
int Length(ST *);
int intCount(ST **, int);
void add_begin(ST **, int);
void push(ST **, int);
void pop(ST **);
void delete(ST **, int);
void getNth(ST **, int);
void insertNth(ST **, int, int);
void InsertSort(ST **);
void SortedInsert(ST **,ST*);
void removeDuplicates(ST **);
void moveNode(ST **, ST **);

#endif // LINKEDLIST_H

