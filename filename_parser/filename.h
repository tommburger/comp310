#ifndef FILENAME_H
#define FILENAME_H

#include <stdio.h>
#include <stdbool.h>

// The maximum filename length is 255 characters.
// This does not counting the nul character at the end.
#define NAME_MAX 255
typedef char Filename[NAME_MAX+1];

// The maximum number of directory levels supported by this interface.
// This is not a Linux limit.
#define MAX_NESTING 16

struct Pathname {
    // a filename is absolute if it starts with a "/".
    // otherwise, it is relative.
    bool isAbsolute;

    // the number of elements in the pathComponents string.
    int numPathComponents;

    // The set of directory name components along with the final filename.
    // Only the first numPathComponents elements of the array are valid.
    Filename pathComponents[MAX_NESTING];
};

// breaks fullName down into its parts.  Returns true if the fullName
// is valid.  
// A return value of false means that something is wrong with
// the name and the Pathname structure is undefined.
bool parseFullFilename(struct Pathname * pn, char * fullName);

// prints the full filename as defined by the Pathname structure
// to the file f.
void printFullFilename(struct Pathname * pn, FILE * f);

#endif
