/*
 * This is a library for reading values of different types from a file.
 * It is used as helper code for lab 1 in COMP280 @ USD.

 * See the associated header (readfile.h) for instructions on how to use this
 * library.

 * WARNING: It is not a particularly safe version of reading functions...
 * but neither is fscanf...
 *
 */
#include <stdio.h>      // the C standard I/O library
#include <stdlib.h>     // the C standard library
#include <string.h>     // the C string library
#include "readfile.h"   

// These are global variables. You are not allowed to use
// global variables in your program, so do not emmulate this.
static FILE *infile=0;
static int  is_inited=0; 

/*
 * reads the next value in the file as a string
 * @param str a string to fill with the read in value
 * @return 0 on success, -1 if there is nothing left to
 *            read in the file
 */
int readString(char str[]) {
	int ret;

	if (!is_inited) {
		return -1;
	}
	ret = fscanf(infile, "%s", str);
	if (ret != 1) { 
		return -1;
	}
	return 0;
}

/*
 * reads the next value in the file as an int
 * @param val the value to "return"
 * @return 0 on success, -1 if there is nothing left to
 *            read in the file
 */
int readInt(int *val) {
	int ret;

	if (!is_inited) {
		return -1;
	}
	ret = fscanf(infile, "%d", val);
	if (ret != 1) { 
		return -1;
	}
	return 0;
}

/*
 * reads the next value in the file as a double
 * @param val the value to "return"
 * @return 0 on success, -1 if there is nothing left to
 *            read in the file
 */
int readDouble(double *val) {
	int ret;

	if (!is_inited) {
		return -1;
	}
	ret = fscanf(infile, "%lf", val);
	if (ret != 1) { 
		return -1;
	}
	return 0;
}

/*
 * open the file for reading
 * @param filename a string containing the name of the file to read
 * @return 0 on success, -1 if the file cannot be opened
 *
 */
int openFile(char *filename) {

	infile = fopen(filename, "r");
	if (!infile) {
		return -1;
	}
	is_inited = 1;
	return 0;
}

/*
 * closes the file
 */
void closeFile() {

	if (infile) {
		fclose(infile);
	}
	is_inited = 0;
}
