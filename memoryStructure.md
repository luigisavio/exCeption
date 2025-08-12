# How memory is used
Exception get concatenated in a linked list. This is done to manage exceptions in multiple nested functions.    
  
Each element of the list is defined by the following structure.
| Name                        | Data type                              | Description                                                                                                                                   |
| --------------------------- | -------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------- |
| Pointer to parent exception | Pointer to another exception structure | Pointer that points to the lower level exception. NULL_POINTER if there is no lower level exception.                                          |
| Exception code              | 4 bytes signed integer                 | Code that identifies the exception that happened in function N. May be used by higher level functions to identify the exception and handle it |
| Function name               | Pointer to char                        | Pointer to name of the function that generated the exception.                                                                                 |
| Exception string            | Pointer to char                        | Pointer to description of what happened.                                                                                |  
  
Each time an exception is created, memory allocations happens three times:  
- One time to allocate memory for the main structure.
- One time to allocate memory to store the string associated to the function name. This string will be accessible through the pointer stored in the main structure.
- One time to allocate memory to store the string associated to the exception description. This string will be accessible through the pointer stored in the main structure.
