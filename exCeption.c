#include <string.h>
// TODO check if all of these libraries are really needed
#include <stdlib.h>
#include <stdio.h> 


/*string field of exception structure*/
typedef struct exc_stringField{
    char* pString; // pointer to first char of string
    int stringLen; // length of the string
} exc_stringField;


/*main exception structure*/
typedef struct exc_exception{

    int exceptionId; // numerical identifier of the exception

    struct exc_exception* pParent; // pointer to parent exception. Need to write struct since typedef has yet to happen
    struct exc_exception* pChild; // pointer to child exception. Need to write struct since typedef has yet to happen

    exc_stringField funName; // string field that contains function name that threw this exception
    exc_stringField description; // string field that contains exception description

} exc_exception;


/*crates (memory allocation) and initializes a main exception structure*/
exc_exception* exc_createExceptionStruct(){

    // allocate memory
    exc_exception* pException = (exc_exception*) malloc(sizeof(exc_exception));

    // initialize fields
    pException->exceptionId = 0;
    pException->pChild = NULL;
    pException->pParent = NULL;
    pException->funName.pString = NULL;
    pException->funName.stringLen = 0;
    pException->description.pString = NULL;
    pException->description.stringLen = 0;

    return pException;
}


int exc_getExceptionId(const exc_exception* pException){
    return pException->exceptionId;
}


void exc_setExceptionId(exc_exception* pException, int exceptionId){
    pException->exceptionId = exceptionId;
}


char* exc_getExceptionFunName(const exc_exception* pException){
    return pException->funName.pString;
}


void exc_setExceptionStringField(exc_stringField* pStringField, const char* content){

    // check if exception string field was already set
    if (pStringField->pString != NULL){
        free((void*)pStringField->pString); // overwriting field, old string can be freed
    } else {
        // no need to free, field was never set before
    }

    // calculate the length of string and write it to the exception
    pStringField->stringLen = strlen(content);

    // allocate memory for string
    pStringField->pString = (char*) malloc((pStringField->stringLen)+1); // +1 for terminator char, do not call another time strlen for better performance
    
    // write string to allocated memory
    strcpy(pStringField->pString, content); // TODO check reutrn value

}


void exc_setExceptionFunName(exc_exception* pException, const char* funName){
    exc_setExceptionStringField(&pException->funName, funName);
}


char* exc_getExceptionDescription(const exc_exception* pException){
    return pException->description.pString;
}


void exc_setExceptionDescription(exc_exception* pException, const char* description){
    exc_setExceptionStringField(&pException->description, description);
}


exc_exception* exc_getParentException(const exc_exception* pException){
    return pException->pParent;
}


void exc_setParentException(exc_exception* pException, exc_exception* pParent){
    pException->pParent = pParent;
}


exc_exception* exc_getChildException(const exc_exception* pException){
    return pException->pChild;
}


void exc_setChildException(exc_exception* pException, exc_exception* pChild){
    pException->pChild = pChild;
}


void exc_freeException(exc_exception* pException){

    // get parent exception
    exc_exception* pParent = exc_getParentException(pException);

    if (pParent == NULL){
        // this exception has no child, no need to free childs
    } else {
        exc_freeException(pParent); // free the parent of this exception
    }
    // free this exception
    free((void*)(pException->funName.pString));
    free((void*)(pException->description.pString));
    free((void*)pException);
}


void exc_printException(const exc_exception* pException){

    // TODO receive pointer to function used to print, to be more flexible
    // get parent exception
    exc_exception* pParent = exc_getParentException(pException);

    if (pParent == NULL) {
        // do nothing, no parent
    } else {
        // also print the parent
        exc_printException(pParent);
    }
    // and always print this exception
    printf("Error %i occurred in function %s: %s\n",
        exc_getExceptionId(pException),
        exc_getExceptionFunName(pException),
        exc_getExceptionDescription(pException));
}


/* 
# Summary
    Function that creates a new exception. Allocates memory, writes to it and then returns pointer.
# Inputs
- exceptionId
    Numerical ID of the exception to be thrown.
- funName
    String containing the name of the function that is throwing the exception.
- description
    String containg a human understandable description of what happened.
# Outputs
- return
    Pointer to new exception. 
# Warnings    
    Allocates memory, so the returned exception must be freed later on!
*/
exc_exception* exc_throw(int exceptionId, const char* funName, const char* description){

    // create new exception main structure
    exc_exception* pException = exc_createExceptionStruct();

    // set exception ID
    exc_setExceptionId(pException, exceptionId);

    // set the name of the function
    exc_setExceptionFunName(pException, funName);

    // set description of the function
    exc_setExceptionDescription(pException, description);

    return pException;
}

exc_exception* exc_addThrow(exc_exception* pParentException, int exceptionId, const char* funName, const char* description){
    // create new exception
    exc_exception* pNewException = exc_throw(exceptionId, funName, description);

    // link new exception to already existing exception
    exc_setParentException(pNewException, pParentException);
    exc_setChildException(pParentException, pNewException);

    return pNewException;
}


int main(void){
    exc_exception* testExcp = exc_throw(34543, "yunfun", "funfun had some problems");

    exc_exception* secondTestExcp = exc_addThrow(testExcp, 563, "halo", "bonjour");

    exc_printException(secondTestExcp);

    exc_freeException(secondTestExcp);
}




