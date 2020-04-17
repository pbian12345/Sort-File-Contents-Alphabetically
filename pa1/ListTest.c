#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int test_ctor();
int test_prepend();
int test_index();
int test_insert();
int test_delete();
int test_copy();

int main(int argc, char* argv[]){
    //return 0 if tests pass, 1 otherwise
    printf("List CTORS: %d\n", test_ctor());
    printf("List prepend: %d\n", test_prepend());
    printf("List indexList: %d\n", test_index());
    printf("List insert: %d\n", test_insert());
    printf("List delete: %d\n", test_delete());
    printf("List copy: %d\n", test_copy());
    return 0;
}

int test_ctor(){
    //test CTORS, append(), length()
    List A = newList();
    long in[] = {0, 12, 542, 3, 11114};
    long out[] = {0, 12, 542, 3, 11114};
    int out_size = 5;
    for (int i = 0; i < 5; i++){
        append(A, in[i]);
    }
    //now test if in matches out
    if (length(A) != out_size){
        return 1;
    }
    moveFront(A);
    for (int i = 0; i < 5; i++){
        if (out[i] != get(A)){
            return 1;
        }
        moveNext(A);
    }
    return 0;
}
int test_prepend(){
    //test prepend()
    List A = newList();
    long in[] = {0, 12, 542, 3, 11114};
    long out[] = {11114, 3, 542, 12, 0};
    int out_size = 5;
    for (int i = 0; i < 5; i++){
        prepend(A, in[i]);
    }
    //now test if in matches out
    if (length(A) != out_size){
        return 1;
    }
    moveFront(A);
    for (int i = 0; i < 5; i++){
        if (out[i] != get(A)){
            return 1;
        }
        moveNext(A);
    }
    return 0;
}
int test_index(){
    //test index(), moveFront(), moveBack(), moveNext(), movePrev()
    List A = newList();
    long in[] = {1, 2, 3};
    if (index(A) != -1){
        return 1;
    }
    for (int i = 0; i < 3; i++){
        append(A, in[i]);
    }
    if (index(A) != -1){
        return 1;
    }
    moveFront(A);
    if (index(A) != 0){
        return 1;
    }
    moveBack(A);
    if (index(A) != 2){
        return 1;
    }
    movePrev(A);
    movePrev(A);
    if (index(A) != 0){
        return 1;
    }
    moveNext(A);
    if (index(A) != 1){
        return 1;
    }
    return 0;
}
int test_insert(){
    //test insertBefore(), insertAfter()
    List A = newList();
    long in[] = {0, 12, 2, 333, 4321, 5, 26};
    long out1[] = {0, 12, 2};
    long out2[] = {0, 333, 12, 2};
    long out3[] = {0, 333, 12, 2, 4321};
    long out4[] = {5, 0, 333, 12, 2, 4321};
    long out5[] = {5, 26, 0, 333, 12, 2, 4321};

    for (int i = 0; i < 3; i++){
        append(A, in[i]);
    }
    //test out1[]
    moveFront(A);
    for (int i = 0; i < 3; i++){
        if (out1[i] != get(A)){
        return 1;
        }
        moveNext(A);
    }

    moveFront(A);
    insertAfter(A, in[3]);
    //test out2[]
    moveFront(A);
    for (int i = 0; i < 4; i++){
        if (out2[i] != get(A)){
        return 1;
        }
        moveNext(A);
    }

    moveBack(A);
    insertAfter(A, in[4]);
    //test out3[]
    moveFront(A);
    for (int i = 0; i < 5; i++){
        if (out3[i] != get(A)){
        return 1;
        }
        moveNext(A);
    }

    moveFront(A);
    insertBefore(A, in[5]);
    //test out4[]
    moveFront(A);
    for (int i = 0; i < 6; i++){
        if (out4[i] != get(A)){
        return 1;
        }
        moveNext(A);
    }

    moveFront(A);
    moveNext(A);
    insertBefore(A, in[6]);
    //test out5[]
    moveFront(A);
    for (int i = 0; i < 7; i++){
        if (out5[i] != get(A)){
        return 1;
        }
        moveNext(A);
    }

    return 0;
}
int test_delete(){
    //test clear(), delete(), deleteFront(), deleteBack()
    List A = newList();
    long in[] = {10, 1123, 2, 34, 4, 5, 436};
    long out1[] = {10, 1123, 34, 4, 5, 436};
    long out2[] = {1123, 34, 4, 5, 436};
    long out3[] = {1123, 34, 4, 5};
    for (int i = 0; i < 7; i++){
        append(A, in[i]);
    }
    moveFront(A);
    moveNext(A);
    moveNext(A);
    delete(A);
    //test out1[]
    moveFront(A);
    for (int i = 0; i < 6; i++){
        if (out1[i] != get(A)){
            return 1;
        }
        moveNext(A);
    }

    deleteFront(A);
    //test out2[]
    moveFront(A);
    for (int i = 0; i < 5; i++){
        if (out2[i] != get(A)){
            return 1;
        }
        moveNext(A);
    }

    deleteBack(A);
    //test out3[]
    moveFront(A);
    for (int i = 0; i < 4; i++){
        if (out3[i] != get(A)){
            return 1;
        }
        moveNext(A);
    }

    clear(A);
    if (length(A) != 0){
        return 1;
    }
    return 0;
}


int test_copy(){
    //test copy()
    long in[] = {12, 1432, 898};
    long out[] = {12, 1432, 898};
    List A = newList();
    for (int i = 0; i < 3; i++){
        append(A, in[i]);
    }
    List B = copyList(A);
    for (moveFront(A), moveFront(B); index(A) >= 0; moveNext(A), moveNext(B)){
        if (get(A) != get(B)){
            return 1;
        }
    }
    return 0;
}