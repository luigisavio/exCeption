#include "exCeption.h"
#include <stdlib.h>
#include <stdio.h>

/* Declare some functions */
exc_root* sumOfPositiveNumbers(int a, int b, int* c){

    if (a<=0) {
        return exc_throw(1, "sumOfPositiveNumbers", "a is negative");
    }else if (b<=0)
    {
        return exc_throw(2, "sumOfPositiveNumbers", "b is negative");
    } else {
        *c = a+b;
        return EXC_NONE;
    }
    
}
// TODO try better ways to handle exceptions
exc_root* averageOfNumbers(int a, int b, int* c){

    int result;

    exc_root* exception = sumOfPositiveNumbers(a, b, &result);

    if (exception != EXC_NONE) {
        return exc_add_and_throw(exception, 1, "averageOfNumbers", "error in sum function");
    }
        
    *c = result/2;
    
    return EXC_NONE;
}

int main(void){
    
    int c;
    exc_root* exception = averageOfNumbers(-1, 1, &c);

    exc_print(exception);

    exc_free(exception);
}