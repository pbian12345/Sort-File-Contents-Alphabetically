
#include<stdio.h>
#include<stdlib.h>
#include "List.h"

typedef struct NodeObj{
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
}NodeObj;

typedef struct NodeObj* Node;

typedef struct ListObj{
    Node head;
    Node tail;
    Node cursor;
    int length;
}ListObj;


// Constructors-Destructors ---------------------------------------------------

Node newNode (int in_data){
    Node temp = malloc(sizeof(NodeObj));
    temp->data = in_data;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}
void freeNode (Node* to_del){
    if (to_del != NULL && *to_del != NULL){
        free(*to_del);
        *to_del = NULL;
    }
}

 // Creates and returns a new empty List.
List newList(void){
    List temp = malloc(sizeof(ListObj));
    temp->head = NULL;
    temp->tail = NULL;
    temp->cursor = NULL;
    temp->length = 0;
    return temp;
}

// Frees all heap memory associated with *pL, and sets
// *pL to NULL.
void freeList(List* pL){
    if (pL != NULL && *pL != NULL){
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}

// Access functions -----------------------------------------------------------

// Returns the number of elements in L.
int length(List L){
    if (L == NULL){
        return 0;
    }
    if (L->head == NULL || L->tail == NULL){
        return 0;
    }
    return L->length;
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
    if (L == NULL){
        printf("List Error: calling index() on null\n");
        exit(1);
    }
    if (L->head == NULL || L->tail == NULL || L->cursor == NULL){
        return -1;
    }
    int index = 0;
    for (Node temp = L->head; temp != L->cursor; temp = temp->next){
        index++;
    }
    return index;
}

// Returns front element of L. Pre: length()>0
int front(List L){
    if (L = NULL){
        printf("List Error: calling front() on null\n");
        exit(1);
    }
    else if (length(L) == 0){
        printf("List Error: calling front() on empty\n");
        exit(1);
    }
    return L->head->data;
}

// Returns back element of L. Pre: length()>0
int back(List L){
    if (L == NULL){
        printf("List Error: calling back() on null\n");
        exit(1);
    }
    return L->tail->data;
}

// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L){
    if (L == NULL){
        printf("List Error: calling get() on null\n");
        exit(1);
    }
    if (index(L) < 0){
        printf("List Error: calling get() on undefined cursor\n");
        exit(1);
    }
    return L->cursor->data;
}

// Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.
int equals(List A, List B){
    if (A == NULL || B == NULL){
        printf("List Error: calling equals() on null");
        exit(1);
    }

    int eq = 0;
    Node N = NULL;
    Node M = NULL;

    eq = (length(A) == length(B));
    N = A->head;
    M = B->head;
    while (eq && N != NULL){
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

// Manipulation procedures ----------------------------------------------------

// Resets L to its original empty state.
void clear(List L){
    while (length(L) != 0){
        deleteFront(L);
    }
    // for (int i = 1; i < length(L); i++){
    //     deleteBack(L);
    // }
}

// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
    if (L == NULL){
        printf("List Error: calling moveFront() on null\n");
        exit(1);
    }
    else if (length(L) == 0){
        printf("List Error: calling moveFront() on empty\n");
        exit(1);
    }
    L->cursor = L->head;
}

// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
    if (L == NULL){
        printf("List Error: calling moveBack() on null\n");
        exit(1);
    }
    else if (length(L) == 0){
        printf("List Error: calling moveBack() on empty\n");
        exit(1);
    }
    L->cursor = L->tail;
}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L){
    if (L == NULL){
        printf("List Error: calling movePrev() on null\n");
        exit(1);
    }
    if (L->cursor->prev == NULL){
        L->cursor = NULL;
    }
    else {
        L->cursor = L->cursor->prev;
    }
}

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L){
    if (L == NULL){
        printf("List Error: calling moveNext() on null\n");
        exit(1);
    }
    if (L->cursor->next == NULL){
        L->cursor = NULL;
    }
    else {
        L->cursor = L->cursor->next;
    }
}

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int data){
    if (L == NULL){
        printf("List Error: calling prepend() on null\n");
        exit(1);
    }

    Node temp = newNode(data);
    if (length(L) == 0){
        L->head = temp;
        L->tail = temp;
        L->length++;
    }
    else {
        L->head->prev = temp;
        temp->next = L->head;
        L->head = temp;
        L->length++;
    }
}

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, int data){
    if (L == NULL){
        printf("List Error: calling append() on null\n");
        exit(1);
    }

    Node temp = newNode(data);
    if (length(L) == 0){
        L->head = temp;
        L->tail = temp;
        L->length++;
    }
    else {
        L->tail->next = temp;
        temp->prev = L->tail;
        L->tail = temp;
        L->length++;
    }
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data){
    if (L == NULL){
        printf("List Error: calling insertBefore() on null\n");
        exit(1);
    }
    if (index(L) < 0){
        printf("List Error: calling insertBefore() on cursor undefined\n");
        exit(1);
    }

    if (L->cursor->prev == NULL){
        prepend(L, data);
    }
    else {
        Node temp = newNode(data);
        temp->prev = L->cursor->prev;
        L->cursor->prev = temp;
        temp->next = L->cursor;
        temp->prev->next = temp;
        L->length++;
    }
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data){
    if (L == NULL){
        printf("List Error: calling insertBefore() on null\n");
        exit(1);
    }
    if (index(L) < 0){
        printf("List Error: calling insertBefore() on cursor undefined\n");
        exit(1);
    }

    if (L->cursor->next == NULL){
        append(L, data);
    }
    else {
        Node temp = newNode(data);
        temp->next = L->cursor->next;
        L->cursor->next = temp;
        temp->prev = L->cursor;
        temp->next->prev = temp;
        L->length++;
    }
}

// Delete the front element. Pre: length()>0
void deleteFront(List L){
    if (L == NULL){
        printf("List Error: calling deleteFront() on null\n");
        exit(1);
    }
    if (length(L) < 1){
        printf("List Error: calling deleteFront() on empty\n");
        exit(1);
    }

    Node temp = L->head;
    if (length(L) > 1){
        L->head->next->prev = NULL;
        L->head = L->head->next;
        L->length--;
    }
    else {
        L->head = NULL;
        L->tail = NULL;
        L->length--;
    }
    freeNode(&temp);
}

// Delete the back element. Pre: length()>0
void deleteBack(List L){
    if (L == NULL){
        printf("List Error: calling deleteBack() on null\n");
        exit(1);
    }
    if (length(L) < 1){
        printf("List Error: calling deleteBack() on empty\n");
        exit(1);
    }

    Node temp = L->tail;
    if (length(L) > 1){
        L->tail->prev->next = NULL;
        L->tail = L->tail->prev;
        L->length--;
    }
    else {
        L->tail = NULL;
        L->head = NULL;
        L->length--;
    }
    freeNode(&temp);
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
    if (L == NULL){
        printf("List Error: calling delete() on null\n");
        exit(1);
    }
    if (L->cursor == NULL){
        printf("List Error: calling delete() on undefined cursor\n");
        exit(1);
    }

    if (L->head == L->cursor){
        L->cursor->next->prev = NULL;
        L->cursor->next = L->head;
        L->length--;
    }
    else if (L->tail == L->cursor){
        L->cursor->prev->next = NULL;
        L->cursor->prev = L->tail;
        L->length--;
    }
    else {
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;
        L->length--;
    }
    freeNode(&L->cursor);
}

// Other operations -----------------------------------------------------------

// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L){
    if (L == NULL){
        printf("List Error: calling printList() on null\n");
        exit(1);
    }
    Node temp = NULL;
    for (temp = L->head; temp != NULL; temp = temp->next){
        fprintf(out, "%d ", temp->data);
    }
    // fprintf(out, "\n");
}

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L){
    List temp = newList();
    for (moveFront(L); index(L) >= 0; moveNext(L)){
        append(temp, get(L));
    }
    return temp;
}