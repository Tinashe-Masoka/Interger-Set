#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to dynamically expand the array when the current size is reached
int *expand_Arr(size_t *size, int *stake) {

    // Allocate new memory with double the previous size
    int *temp_arr = malloc((*size) * 2 * sizeof(int));

    // Copy the contents from the old array to the new expanded array
    for (int i = 0; i < *size; ++i) {
        temp_arr[i] = stake[i];
    }

    // Update the size of the array
    *size = (*size) * 2;

    // Free the old array and return the new expanded array
    free(stake);
    return temp_arr;
}

// Function to add an element to the set, maintaining sorted order
void add(int **set, size_t *size, size_t *len, int *x) {

    int hold = 0;

    // Expand the array if it has reached its current capacity
    if ((*len) == *size) {
        *set = expand_Arr(size, *set);
    }

    // Add the first element directly if the set is empty
    if (*len == 0) {
        (*set)[0] = (*x);
        ++(*len);
        return;
    }

    // Insert the new element while maintaining the sorted order
    for (size_t i = 0; i < (*len); ++i) {

        // Break if the element is already in the set
        if ((*x) == (*set)[i]) break;

        // Shift the larger elements to the right and insert the new element
        if ((*x) < (*set)[i]) {
            hold = (*set)[i];
            (*set)[i] = (*x);
            (*x) = hold;
        }

        // Add the element at the end if it's larger than all current elements
        if (i == (*len - 1)) {
            (*set)[*len] = (*x);
            ++(*len);
        }
    }
}

// Function to print the contents of a set
void printer(int *set, size_t len) {

    // Loop through and print each element in the set
    for (size_t i = 0; i < len; ++i) {
        if (i == (len - 1)) {
            printf("%d\n", set[i]);
            break;
        }
        printf("%d ", set[i]);
    }
}

// Function to delete a specific element from the set
void delete(int **set, size_t *len) {
    size_t i = 0;
    int x = 0;
    
    // Read the element to be deleted
    scanf(" %d", &x);

    // Find the element in the set
    for (; i < (*len); ++i)
        if ((*set)[i] == x) break;

    // Shift elements to the left to remove the deleted element
    for (size_t j = i; j < (*len - 1); ++j) {
        (*set)[j] = (*set)[j + 1];
    }

    // Reduce the length of the set
    --(*len);
}

// Function to compute the union (superset) of two sets and print it
void superset(int **set_x, int **set_y, size_t x_len, size_t y_len) {

    size_t size = x_len + y_len;
    int *s_set = malloc(sizeof(int) * size);
    size_t s_len = x_len;
    int x;

    // Copy the contents of set_x to the union set
    for (size_t i = 0; i < x_len; ++i) {
        s_set[i] = (*set_x)[i];
    }

    // Add elements from set_y to the union set
    for (size_t i = 0; i < y_len; ++i) {
        x = (*set_y)[i];
        add(&s_set, &size, &s_len, &x);
    }

    // Print the resulting union set
    printer(s_set, s_len);
    free(s_set);
}

// Function to compute the intersection of two sets and print it
void intersection(int *x_set, int *y_set, size_t x_len, size_t y_len) {
    size_t k = 0;
    int True = 0;

    // Find common elements between the two sets
    for (size_t i = 0; i < x_len; ++i) {
        for (size_t j = 0; j < y_len; ++j) {
            if (x_set[i] == y_set[j]) {
                k = i;
                True = 1;
            }
        }
    }

    // Print the intersection if common elements are found
    if (True == 1) {
        for (size_t i = 0; i < x_len; ++i) {
            for (size_t j = 0; j < y_len; ++j) {
                if (i == k) {
                    printf("%d\n", x_set[i]);
                    return;
                }
                if (x_set[i] == y_set[j]) printf("%d ", x_set[i]);
            }
        }
    }
}

// Main function to handle user input and execute set operations
int main() {

    size_t x_size = 4;
    size_t y_size = 4;
    int *x_set = malloc(sizeof(int) * x_size);
    int *y_set = malloc(sizeof(int) * y_size);
    size_t x_len = 0;
    size_t y_len = 0;
    char x;
    int y;

    // Continue reading commands until 'q' is entered
    while (scanf(" %c", &x) == 1 && x != 'q') {

        // Add element to set_x or set_y based on user input
        if (x == 'a') {
            scanf(" %c", &x);

            if (x == 'x') {
                scanf(" %d", &y);
                add(&x_set, &x_size, &x_len, &y);

            } else if (x == 'y') {
                scanf(" %d", &y);
                add(&y_set, &y_size, &y_len, &y);
            }

        // Print set_x or set_y
        } else if (x == 'p') {
            scanf(" %c", &x);

            if (x == 'x') {
                printer(x_set, x_len);

            } else if (x == 'y') {
                printer(y_set, y_len);
            }

        // Remove element from set_x or set_y
        } else if (x == 'r') {
            scanf(" %c", &x);

            if (x == 'x') {
                delete(&x_set, &x_len);

            } else if (x == 'y') {
                delete(&y_set, &y_len);
            }

        // Compute the union of set_x and set_y
        } else if (x == 'u') {
            superset(&x_set, &y_set, x_len, y_len);

        // Compute the intersection of set_x and set_y
        } else if (x == 'i') {
            intersection(x_set, y_set, x_len, y_len);
        }
    }

    // Free allocated memory
    free(x_set);
    free(y_set);
}
