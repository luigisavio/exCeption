/*main exception structure*/
typedef struct exc_root{

    int exception_id; // numerical identifier of the exception

    struct exc_root* p_parent; // pointer to parent exception. It is, if present, the exception that generated this exception. Otherwise it is null

    char* fun_name; // string that contains function name that threw this exception
    char* description; // string that conatins description of the exception: what happened?

} exc_root;

/*crates (memory allocation) and initializes a an exception root structure*/
exc_root* exc_create_root();

/* Recoursive function that when called on an exception frees it and all its parent exceptions*/
void exc_free(exc_root* p_exception);

/* Recoursive function that when called on an exception prints its child and it */
void exc_print(const exc_root* p_exception);

/* Throws a new exception */
exc_root* exc_throw(int exception_id, const char* fun_name, const char* description);

/* Adds another exception to the input exception and returns the resulting exception */
exc_root* exc_add_and_throw(exc_root* p_parent, int exception_id, const char* fun_name, const char* description);