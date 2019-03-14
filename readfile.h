#ifndef _READFILE_H_
#define _READFILE_H_
/*
 * This is a library for reading values of different types from a file.
 * It is used as helper code for lab 1 in COMP280.
 *
 * To use this library:
 *   (0) #include "readfile.h" at the top of your .c file
 *
 *   (1) call openFile() passing in the file name string to open
 *        openFile("input.txt");
 *     
 *   (2) make calls to read<type> (e.g. readInt) to read values from
 *       the file.  These functions return 0 when the read was successful
 *       and -1 when not (like the file could have nothing left to read)
 *       You need to be careful to call the right function here to
 *       correspond to the next value to be read in the file (if you
 *       want to read in an int, make sure to call readInt and not
 *       read_char, for example)  Examples:
 *
 *       int x, ret, total;
 *
 *       ret = openFile("input.txt");
 *       if(ret == -1) {
 *          printf("open file failed\n");
 *          exit(1);
 *       }
 *       
 *       total = 0;
 *       ret = readInt(&x);
 *       while(ret != -1) {
 *         total += x;
 *         ret = readInt(&x);
 *       }
 *       
 *         
 *
 *   (3) call closeFile() when you are all done reading values
 *       from the file
 */


/*
 * open the file for reading
 * @param filename: a string containing the name of the file to read
 * @return: 0 on success, -1 if the file cannot be opened
 *
 */
int openFile(char *filename);

/*
 * close the file for reading
 */
void closeFile();

/*
 * reads the next value in the file as a string
 * @param str a string to fill with the read in value
 * @return 0 on success, -1 if there is nothing left to
 *            read in the file
 */
int readString(char str[]);

/*
 * reads the next value in the file as an int
 * @param val the value to "return"
 * @return 0 on success, -1 if there is nothing left to
 *            read in the file
 */
int readInt(int *val);

/*
 * reads the next value in the file as a float
 * @param val the value to "return"
 * @return 0 on success, -1 if there is nothing left to
 *            read in the file
 */
int readDouble(double *val);

#endif
