# How memory is used

Exception get concatenated in a linked list. This is done to manage exceptions in multiple nested functions.    
Each exception needs to have the following fields:
- Name of function that generated the exception.
- Numeric ID of exception.
- String that describes the exception in a human understandable way.
- Pointer to parent exception.

| Name | Size | Description |
| ---- | ---- | ----------- |
| F     |      |             |