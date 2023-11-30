#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* generateString() {
    // Allocate memory for the string (including null terminator)
    char* myString = (char*)malloc(20 * sizeof(char));

    // Check if memory allocation was successful
    if (myString == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Copy a string into the allocated memory
    strcpy(myString, "Hello, World!");

    // Return the generated string
    return myString;
}

int main() {
    // Call the function to get the string
    char* result = generateString();

    // Print the result
    printf("Generated String: %s\n", result);

    // Don't forget to free the allocated memory when done
    free(result);

    return 0;
}
