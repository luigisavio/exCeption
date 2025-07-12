#include <string.h>
// $TODO check if all of these libraries are really needed
#include <stdlib.h>
#include <stdio.h> 

/*exception structure*/
typedef struct exc_exception {

    int exceptionId; // numerical identifier of the exception

    struct exc_exception* pParent; // pointer to parent exception. Need to write struct since typedef has yet to happen
    struct exc_exception* pChild; // pointer to child exception. Need to write struct since typedef has yet to happen

    char* pFunName; // pointer to first char of string that contains function name that threw this exception
    int funNameStrLen; // length of string function name (EXCLUDING terminator char)

    char* pDescription; // pointer to first char of string that contains exception description
    int descriptionStrLen; // length of description string (EXCLUDING terminator char)

} exc_exception;

/* 
# Summary
    Function that creates a new exception. Allocates memory, writes to it and then returns pointer.
# Inputs
    exceptionId
        Numerical ID of the exception to be thrown.
    funName
        String containing the name of the function that is throwing the exception.
    description
        String containg a human understandable description of what happened.
# Outputs
    return
        Pointer to new exception. 
# Warnings    
    Allocates memory, so the returned exception must be freed later on!
*/
exc_exception* exc_throw(int exceptionId, char* funName, char* description) {

    int sizeOfException = sizeof(exc_exception);
    int funNameStrLen = strlen(funName);
    int descriptionStrLen = strlen(description);

    // allocate memory for main exception structure
    exc_exception* pException = (exc_exception*) malloc(sizeOfException);

    // write to memory that was just allocated, to populate the exception
    pException->exceptionId = exceptionId;
    pException->pChild = NULL;
    pException->pParent = NULL;
    pException->funNameStrLen = strlen(funName);
    pException->descriptionStrLen = strlen(description);

    // allocate memory for function name string
    pException->pFunName = (char*) malloc(pException->funNameStrLen+1); // +1 for terminator char, do not call another time strlen for better performance
    // write function name to allocated memory
    strcpy(pException->pFunName, funName); // $TODO check reutrn value

    // allocate memory for exception description string
    pException->pDescription = (char*) malloc(pException->descriptionStrLen);
    // write to memory that was just allocated
    strcpy(pException->pDescription, description); // $TODO check reutrn value

    return pException;
}

int exc_getExceptionId(exc_exception* pException){
    return pException->exceptionId;
}

char* exc_getExceptionFunName(exc_exception* pException){
    return pException->pFunName;
}

char* exc_getExceptionDescription(exc_exception* pException){
    return pException->pDescription;
}

void exc_freeException(exc_exception* pException) {
    if (pException->pChild == NULL){
        // this exception has no child, no need to free childs
    } else {
        exc_freeException(pException->pChild); // free the child of this exception
    }
    // free this exception
    free((void*)(pException->pFunName));
    free((void*)(pException->pDescription));
    free((void*)pException);
}

int main(void) {
    exc_exception* testExcp = exc_throw(34543, "yunfun", "funfun had some problems");

    printf("ID: %i, funName: %s, description: %s \n", exc_getExceptionId(testExcp), exc_getExceptionFunName(testExcp), exc_getExceptionDescription(testExcp));

    exc_freeException(testExcp);
}




