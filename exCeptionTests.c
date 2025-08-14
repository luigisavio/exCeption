#include "exCeption.h"
#include <stdlib.h>
#include <stdio.h>

/* Declare some functions */
exc sumOfPositiveNumbers(int a, int b, int* c){

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

exc averageOfNumbers(int a, int b, int* c){

    int result;

    exc exception = sumOfPositiveNumbers(a, b, &result);

    if (exception != EXC_NONE) {
        return exc_add_and_throw(exception, 1, "averageOfNumbers", "error in sum function");
    }
        
    *c = result/2;
    
    return EXC_NONE;
}

int sumOfPositiveNumbers2(int a, int b, exc* exc){

    if (a<=0) {
        *exc = exc_throw(1, "sumOfPositiveNumbers2", "a is negative");
        return 0;
    }else if (b<=0)
    {
        *exc = exc_throw(2, "sumOfPositiveNumbers2", "b is negative");
        return 0;
    } else {
        *exc = EXC_NONE;
        return a+b;
    }
    
}

int averageOfNumbers2(int a, int b, exc* exc){

    int sum = sumOfPositiveNumbers2(a, b, exc);

    if (*exc != EXC_NONE) {
        *exc = exc_add_and_throw(*exc, 1, "averageOfNumbers2", "error in sum function");
        return 0;
    }else{
        return sum/2;
    }
}

int main(void){
    
    int c;
    exc exception = averageOfNumbers(-1, 1, &c);

    exc_print(exception);

    exc_free(exception);

    c = averageOfNumbers2(1, -1, &exception);
    exc_print(exception);

    exc_free(exception);
}