/* Structure to contain a string and its size. Used to write just one time the string size and avoid using strlen function multiple times*/
typedef struct exc_string{

    int length; // size of the string (number of bytes with the same meaning of strlen function)
    char* p_first_char; // actual string
} exc_string;

/*main exception structure*/
typedef struct exc_root{

    int exception_id; // numerical identifier of the exception

    struct exc_root* p_parent; // pointer to parent exception. It is, if present, the exception that generated this exception. Otherwise it is null

    exc_string fun_name; // string that contains function name that threw this exception
    exc_string description; // string that contains description of the exception: what happened?

} exc_root;

/*crates (memory allocation) and initializes a an exception root structure*/
exc_root* exc_create_root();

/* Recursive function that when called on an exception frees it and all its parent exceptions*/
void exc_free(exc_root* p_exception);

/* Recursive function that when called on an exception prints its child and it */
void exc_print(const exc_root* p_exception);

/* Throws a new exception */
exc_root* exc_throw(int exception_id, const char* fun_name, const char* description);

/* Allocates memory and returns pointer to string that represents exception */
char* exc_to_str(const exc_root* p_exception);

/* Returns the sum of the lengths of strings associated to an exception and all of its parents exceptions*/
int exc_str_len(const exc_root* p_exception);

/* Adds own strings to an already existing string */
void exc_add_own_str_to_str(const exc_root* p_exception, char* p_first_char);

/* Adds another exception to the input exception and returns the resulting exception */
exc_root* exc_add_and_throw(exc_root* p_parent, int exception_id, const char* fun_name, const char* description);