#include "array_operations.hh"

int greatest_v1(int *itemptr, int size)
{
    int greatest = *itemptr;
    itemptr++;
    size--;
    while(size>0){
        if(*itemptr > greatest){
            greatest = *itemptr;
        }
        itemptr++;
        size--;
    }
    return greatest;
}

int greatest_v2(int *itemptr, int *endptr)
{
    int greatest = *itemptr;
    itemptr++;

    while(itemptr<endptr){
        if(*itemptr > greatest){
            greatest = *itemptr;
        }
        itemptr++;

    }
    return greatest;
}

void copy(int *itemptr, int *endptr, int *targetptr)
{
    while(itemptr != endptr){
        *targetptr = *itemptr;
        targetptr++;
        itemptr++;
    }

}

void reverse(int *leftptr, int *rightptr)
{
    rightptr--;
    while(leftptr < rightptr){
        int helper = *leftptr;
        *leftptr = *rightptr;
        *rightptr = helper;
        leftptr++;
        rightptr--;

    }
}
