#include <stdlib.h>
#include <assert.h>
#include "vector.h"
#include <stdio.h>

/* Hidden struct from user */
struct vector_struct {
    datatype* array;  
    int size;    
    int capacity;    
};

/* Create a new vector with the given starting capacity */
Vector vector_create(int capacity) {
    Vector v = malloc(sizeof(struct vector_struct));
    if (!v) {
        fprintf(stderr, "Problem allocating memory.\n");
        exit(1);
    }

    //Allocate memory for the internal array
    v->array = malloc(sizeof(datatype) * capacity);
    if (!v->array) {
        fprintf(stderr, "Problem allocating memory.\n");
        exit(1);
    }

    //Initialize vector properties
    v->capacity = capacity;
    v->size = 0; 
    return v;
}

/* Free all memory allocated for the vector */
void vector_free(Vector vector) {
    // Free the internal array
    free(vector->array);
    //Free the vector structure itself
    free(vector);
}

/* Return the value stored at the given index */
datatype vector_at(Vector vector, int index) {
    //Ensure the index is within bounds
    assert(index < vector->size);
    return vector->array[index];
}

/* Set the value stored at the given index */
void vector_set_at(Vector vector, int index, datatype data) {
    // If the index is out of bounds
    if (index >= vector->size) return;
    // Update the value at the specified index
    vector->array[index] = data;
}

/* Add a new value at the end of the vector. This can grow the size of the vector */
void vector_push_back(Vector vector, datatype data) {
    // If the vector is full, double its capacity
    if (vector->size >= vector->capacity) {
        vector->array = realloc(vector->array, vector->capacity * 2 * sizeof(datatype));
        vector->capacity *= 2;
    }
    // Add the new element and increase size
    vector->array[vector->size++] = data;
}

/* Remove and return the last element of the vector */
datatype vector_pop(Vector vector) {
    //Decrease the size and retrieve the last element
    datatype data = vector->array[--vector->size];
    // Clear the last element
    vector->array[vector->size] = 0;
    return data;
}

/* Return a pointer to the internal array of the vector*/
datatype *vector_array(Vector vector) {
    return vector->array;
}

/* Return the current number of elements in the vector */
int vector_size(Vector vector) {
    return vector->size;
}

/* Set the size of the vector */
void vector_set_size(Vector vector, int size) {
    vector->size = size;
}

/* Return the current capacity of the vector */
int vector_capacity(Vector vector) {
    return vector->capacity;
}

/* Add a value to the current size of the vector */
void vector_add_to_size(Vector vector, int add) {
    vector->size += add;
}