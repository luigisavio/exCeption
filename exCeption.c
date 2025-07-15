#include <string.h>
// TODO check if all of these libraries are really needed
#include <stdlib.h>
#include <stdio.h>

#define NULL_POINTER NULL // null pointer


/*main exception structure*/
typedef struct exc_root{

    int exception_id; // numerical identifier of the exception

    struct exc_root* p_parent; // pointer to parent exception. It is, if present, the exception that generated this exception. Otherwise it is null

    char* fun_name; // string that contains function name that threw this exception
    char* description; // string that conatins description of the exception: what happened?

} exc_root;


/*crates (memory allocation) and initializes a an exception root structure*/
exc_root* exc_create_root(){

    // allocate memory
    exc_root* p_exception = (exc_root*) malloc(sizeof(exc_root));

    // initialize fields
    p_exception->exception_id = 0;
    p_exception->p_parent = NULL_POINTER;
    p_exception->fun_name = NULL_POINTER;
    p_exception->description= NULL_POINTER;

    return p_exception;
}

/* Recoursive function that when called on an exception frees it and all its parent exceptions*/
void exc_free(exc_root* p_exception){

    if (p_exception->p_parent == NULL_POINTER){
        // this exception has no child, no need to free childs
    } else {
        exc_free(p_exception->p_parent); // free the parent of this exception
    }
    // free this exception. First free the strings, and only then the root
    free((void*)(p_exception->fun_name));
    free((void*)(p_exception->description));
    free((void*) p_exception);
}

/* Recoursive function that when called on an exception prints its child and it */
void exc_print(const exc_root* p_exception){

    // TODO receive pointer to function used to print, to be more flexible
    // get parent exception

    // if the exception has a parent, also print the parent
    if (p_exception->p_parent != NULL_POINTER) {
        exc_print(p_exception->p_parent);
    }

    // and always print this exception
    printf("Error %i occurred in function %s: %s\n",
        p_exception->exception_id,
        p_exception->fun_name,
        p_exception->description);
}


/* Throws a new exception */
exc_root* exc_throw(int exception_id, const char* fun_name, const char* description){

    // create new exception main structure
    exc_root* p_exception = exc_create_root();

    // write to the new exception the input parameters
    p_exception->exception_id = exception_id;
    p_exception->description = (char*) malloc(strlen(description)+1);
    strcpy(p_exception->description, description);
    p_exception->fun_name = (char*) malloc(strlen(fun_name)+1);
    strcpy(p_exception->fun_name, fun_name);

    return p_exception;
}

/* Adds another exception to the input exception and returns the resulting exception */
exc_root* exc_add_and_throw(exc_root* p_parent, int exception_id, const char* fun_name, const char* description){
    // create new exception
    exc_root* p_resulting_exception = exc_throw(exception_id, fun_name, description);

    // link new exception to already existing exception
    p_resulting_exception->p_parent = p_parent;

    return p_resulting_exception;
}


int main(void){
    exc_root* test_excp = exc_throw(34543, "yunfun", "funfun had some problems");

    exc_root* second_test_excp = exc_add_and_throw(test_excp, 563, "halo", "bonjour");

    exc_print(second_test_excp);

    exc_free(second_test_excp);
}




