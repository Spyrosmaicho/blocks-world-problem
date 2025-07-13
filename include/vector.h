#ifndef VECTOR_H_
#define VECTOR_H_

typedef struct vector_struct *Vector;
typedef char datatype;

/* Create a new vector with the given starting capacity */
Vector vector_create(int capacity);

/* Free all memory allocated for the vector */
void vector_free(Vector vector);

/* Return the value stored at the given index */
datatype vector_at(Vector vector, int index);

/* Set the value stored at the given index */
void vector_set_at(Vector vector, int index, datatype data);

/* Add a new value at the end of the vector. This can grow the size of the vector */
void vector_push_back(Vector vector, datatype data);

/* Remove and return the last element of the vector */
datatype vector_pop(Vector vector);

/* Return a pointer to the internal array of the vector*/
datatype *vector_array(Vector vector);

/* Return the current number of elements in the vector */
int vector_size(Vector vector);

/* Set the size of the vector */
void vector_set_size(Vector vector, int size);

/* Return the current capacity of the vector */
int vector_capacity(Vector vector);

/* Add a value to the current size of the vector */
void vector_add_to_size(Vector vector, int add);

#endif