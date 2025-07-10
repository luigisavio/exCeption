#include <string.h>
// TODO check if all of these libraries are really needed
#include <stdlib.h>
#include <stdio.h> 

/*exception structure*/
typedef struct exception {
    exception* pParent;
    exception* pChild;
    int exceptionId;
} exception;

/* function that creates a new exception */
exception* throw(int exceptionId, char* exceptionName, char* exceptionDescription) {
    // allocate memory for exception
    void* pMemoryForException = malloc(sizeof(exception) + strlen(exceptionName) + strlen(exceptionDescription));

    // write to memory that was just allocated, to populate the exception
    ((exception*)pMemoryForException)->exceptionId = exceptionId;
    ((exception*)pMemoryForException)->pChild = NULL;
    ((exception*)pMemoryForException)->pParent = NULL;
    strcpy((char*)(((exception*)pMemoryForException)+1), exceptionName);
    strcpy((char*)(((exception*)pMemoryForException)+1), exceptionDescription);
}

char* exceptionToString(exception* pException) {
    // TODO make recoursive
    char* stringToReturn;
    har *strcat(char *dest, const char *src);
    return 
}



int main(void) {
    exception* testExcp = throw(34543, "funfun", "funfun had some problems");
    printf(exceptionToString(testExcp));
}




