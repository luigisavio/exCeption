#include <string.h>
// TODO check if all of these libraries are really needed
#include <stdlib.h>
#include <stdio.h>
#include "exCeption.h" // "" so the preprocessor looks first in the directories relative to this project

#define NULL_POINTER NULL

const char* STR_PART_ZERO = "An exception occurred, trace:\n";
const int STR_PART_ZERO_SIZE = 30;
const char* STR_PART_ONE = "-> In function \'";
const int STR_PART_ONE_SIZE = 16;
const char* STR_PART_TWO = "\': ";
const int STR_PART_TWO_SIZE = 3;
const char* STR_PART_THREE = ".\n";
const int STR_PART_THREE_SIZE = 2; // TODO consider moving these global definitions somewhere else

/* # Public functions */

exc_root* exc_create_root(void){

    // allocate memory
    exc_root* p_exception = (exc_root*) malloc(sizeof(exc_root));

    // initialize fields
    p_exception->exception_id = 0;
    p_exception->p_parent = NULL_POINTER;
    p_exception->fun_name.length = 0;
    p_exception->fun_name.p_first_char = NULL_POINTER;
    p_exception->description.length = 0;
    p_exception->description.p_first_char = NULL_POINTER;

    return p_exception;
}

void exc_free(exc_root* p_exception){

    if (p_exception->p_parent == NULL_POINTER){
        // this exception has no child, no need to free childs
    } else {
        exc_free(p_exception->p_parent); // free the parent of this exception
    }
    // free this exception. First free the strings, and only then the root
    free((void*)(p_exception->fun_name.p_first_char));
    free((void*)(p_exception->description.p_first_char));
    free((void*) p_exception);
}

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
        p_exception->fun_name.p_first_char,
        p_exception->description.p_first_char);
}

char* exc_to_str(const exc_root* p_exception){

    // allocate memory for the strings. Allocated enough memory for the strings associated to this exception and all of its parents
    int mem_to_allocate = STR_PART_ZERO_SIZE + exc_str_len(p_exception) + 1; // add one for terminator char
    char* p_char_to_return = malloc(mem_to_allocate);

    // start by adding the introduction to exception
    strcpy(p_char_to_return, STR_PART_ZERO);
    // and then add the actual exception strings
    exc_add_own_str_to_str(p_exception, p_char_to_return + STR_PART_ZERO_SIZE);

    return p_char_to_return;
}

exc_root* exc_throw(int exception_id, const char* fun_name, const char* description){

    // create new exception main structure
    exc_root* p_exception = exc_create_root();

    // write to the new exception the input parameters
    p_exception->exception_id = exception_id;
    p_exception->description.length = strlen(description);
    p_exception->description.p_first_char = (char*) malloc(p_exception->description.length+1);
    strcpy(p_exception->description.p_first_char, description);
    p_exception->fun_name.length = strlen(fun_name);
    p_exception->fun_name.p_first_char = (char*) malloc(p_exception->fun_name.length+1);
    strcpy(p_exception->fun_name.p_first_char, fun_name);

    return p_exception;
}

exc_root* exc_add_and_throw(exc_root* p_parent, int exception_id, const char* fun_name, const char* description){
    // create new exception
    exc_root* p_resulting_exception = exc_throw(exception_id, fun_name, description);

    // link new exception to already existing exception
    p_resulting_exception->p_parent = p_parent;

    return p_resulting_exception;
}

/* # Private functions */

int exc_str_len(const exc_root* p_exception){

    int this_exc_str_len = STR_PART_ONE_SIZE + p_exception->fun_name.length + STR_PART_TWO_SIZE + p_exception->description.length + STR_PART_THREE_SIZE;

    if (p_exception->p_parent == NULL_POINTER) {
        // exception has no parent, return just the length of strings of this exception
        return this_exc_str_len;
    }else{
        // exception has parent, return this exception strings length plus the parent exception (recursive function)
        return (this_exc_str_len + exc_str_len(p_exception->p_parent));
    }
}

void exc_add_own_str_to_str(const exc_root* p_exception, char* p_first_char){

    // since strings are all known in size, use string copy instead of string cat. It is more efficient.

    int tempOffset = 0;
    strcpy(p_first_char, STR_PART_ONE);
    tempOffset = STR_PART_ONE_SIZE;
    strcpy(p_first_char + tempOffset, p_exception->fun_name.p_first_char); // add function name string
    tempOffset += p_exception->fun_name.length;
    strcpy(p_first_char + tempOffset, STR_PART_TWO);
    tempOffset += STR_PART_TWO_SIZE;
    strcpy(p_first_char + tempOffset, p_exception->description.p_first_char); // add description string
    tempOffset += p_exception->description.length;
    strcpy(p_first_char + tempOffset, STR_PART_THREE);
    tempOffset += STR_PART_THREE_SIZE;

    if (p_exception->p_parent == NULL_POINTER) {
        // no parent exception, add terminator char and finish
        strcpy(p_first_char + tempOffset, "");
        return;
    }else{
        // also add string of parent exception
        exc_add_own_str_to_str(p_exception->p_parent, p_first_char + tempOffset);
    }
}




