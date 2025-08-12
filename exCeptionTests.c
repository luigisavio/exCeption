#include "exCeption.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){
    exc_root* test_excp = exc_throw(34543, "yunfun", "funfun had some problems");

    exc_root* second_test_excp = exc_add_and_throw(test_excp, 563, "halo", "bonjour");

    //exc_print(second_test_excp);

    char* p_char = exc_to_str(second_test_excp);

    printf("%s\n", p_char);

    free(p_char);

    exc_free(second_test_excp);
}