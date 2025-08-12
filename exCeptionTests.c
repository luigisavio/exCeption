#include "exCeption.h"

int main(void){
    exc_root* test_excp = exc_throw(34543, "yunfun", "funfun had some problems");

    exc_root* second_test_excp = exc_add_and_throw(test_excp, 563, "halo", "bonjour");

    exc_print(second_test_excp);

    exc_free(second_test_excp);
}