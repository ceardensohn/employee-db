/*
 * employee_db.c 
 *
 * This file contains to code to add to the employee
 * database text. The purpose of the code will take 
 * an input from the user and if successful, will
 * add employe data to the database.
 *
 * This file is part of COMP 280, Project01.
 *
 * Author:
 * Chris Eardensohn (ceardensohn@sandiego.edu)
 */

#include <stdio.h>      // the C standard I/O library
#include <stdlib.h>     // the C standard library
#include <string.h>     // the C string library
#include "readfile.h"   // my file reading routines
 
// TODO: #define any constant values here:
#define MAXFILENAME  128
#define MAXNAME       64
#define MAXEMPLOYEE  1024

struct Employee {
	char first_name[MAXNAME];
	char last_name[MAXNAME];
	 int emp_id;
	 int emp_salary;
};

// The following line allows us to use "Employee" rather than 
// "struct Employee" throughout this code.
typedef struct Employee Employee;

// forward declaration of functions
void getFilenameFromCommandLine(char filename[], int argc, char *argv[]);
void readAndFillArray(char *filename, Employee *emps);
void printDataBase(Employee *emps);
void printMenu();
void findLastName(Employee *emps);
void addEmployee(Employee *emps);
void sortEmpArray (Employee *emps);
int findID(Employee *emps, int target);
int binarySearch(Employee *emps, int target, int start, int end);

int main (int argc, char *argv[]) {

	char filename[MAXFILENAME];
	Employee *emp_array = calloc(MAXEMPLOYEE, sizeof(Employee));
	int active = 1;
	int menu_check = 0;
	int target_id = 0;
	int target = 0;

	// this initializes the filename string from the command line arguments
	getFilenameFromCommandLine(filename, argc, argv);

	// read array and enter data into array
	readAndFillArray(filename, emp_array);
	sortEmpArray(emp_array);

	printDataBase(emp_array);	

	while (active == 1) 
		{
			printMenu();
			scanf("%d", &menu_check);
			//if out of valid input bounds
			if (menu_check < 1 || menu_check > 5)
			{
				printf("Please enter number according to menu.\n");
			}
			//print database function
			if (menu_check == 1)
			{
				printDataBase(emp_array);
			}
			//ID lookup function
			if (menu_check == 2)
			{
				printf("Enter the six digit ID of the Employee to look up\n");
				scanf("%d", &target_id);
				target = findID(emp_array, target_id);
				if (emp_array[target].emp_id == target_id)
				{
					printf("Employee found:\n");
					printf("%-10d %-15s %-15s %-10d\n", 
					emp_array[target].emp_id, emp_array[target].first_name,
					emp_array[target].last_name,emp_array[target].emp_salary);
				}
				if (emp_array[target].emp_id != target_id)
				{
					printf("Employee not found.\n");
				}
			}
			//last name lookup function
			if (menu_check == 3)
			{
				findLastName(emp_array);	
			}
			//add employee function
			if (menu_check == 4)
			{
				addEmployee(emp_array);
				sortEmpArray(emp_array);
			}
			//break loop
			if (menu_check == 5)
			{
				break;
			}

		}	
	
	free(emp_array);
	printf("\nDatabase application closing, good bye.\n");
	return 0;
}

//  ADD YOUR FUNCTION _DEFINITONS_ BELOW THIS LINE

/**
 * print database by  using the read lines from before to print
 * @param *emps the array to be printed
 * @return void
 */

void printDataBase(Employee *emps) {
	printf("ID         FIRST           LAST            SALARY \n");
	printf("--------------------------------------------------\n");
	int i;
	for (i = 0; i < MAXEMPLOYEE; i++) {
		if (emps[i+1].emp_id == 0)
		{
			break;
		}
		printf("%-10d %-15s %-15s %-10d\n", emps[i].emp_id, 
		emps[i].first_name,emps[i].last_name, emps[i].emp_salary);
	}
	printf("--------------------------------------------------\n");
	printf("Number of employees: %d\n", i);
}

/**
 * prints menu to be used by user to select different actions
 * @return void
 */
void printMenu() {
	printf("Employee Database Menu:\n");
	printf("--------------------------------------------------\n");
	printf("\t(1) Display Database\n");
	printf("\t(2) Lookup by ID\n");
	printf("\t(3) Lookup by last name\n");
	printf("\t(4) Add an Employee\n");
	printf("\t(5) Quit\n");
	printf("--------------------------------------------------\n");
	printf("Please enter a number to run matching task:\n");
}

/**prompt six digit id to
 * look up ID using binary search to find id digit. 
 * if true print out employee information, if false print not found message
 * @param *emps the array to pass to find employee ID
 * @param target the user selected ID to find
 * @return the index of employee
 */

int findID(Employee *emps, int target) {
	int i;
	for (i = 0; i < MAXEMPLOYEE; i++)
	{
		if (emps[i+1].emp_id == 0)
		{
			break;
		}
	}
	return binarySearch(emps, target, 0, i);
};

int binarySearch(Employee *emps, int target, int start, int end) {
	if (start > end) 
	{
		return -1;
	}
	int middle = ((start+end) / 2);
	int value = emps[middle].emp_id;
	if (value > target) 
	{
		return binarySearch(emps, target, start, middle-1);	
	}
	if (value < target) 
	{
		return binarySearch(emps, target, middle+1, end);
	}
	return middle;
}

/** function 3: lookup last name, prompt for input
 * compare string employee array
 * if true print out employee information
 * if false print not found message
 * @param *emps the array to look up employee namei
 * @return void
 */ 

void findLastName(Employee *emps) {
	char target[MAXNAME];
	int i, cmp_result;
	printf("Enter the last name of the employee:\n");
	scanf("%s", target);

	for (i = 0; i < MAXEMPLOYEE; i++)
	{
		cmp_result = strcmp(emps[i].last_name, target);
		if (cmp_result == 0)
		{
			printf("Employee found:\n");
			printf("%-10d %-15s %-15s %-10d\n", emps[i].emp_id, 
			emps[i].first_name,emps[i].last_name, emps[i].emp_salary);
			break; 
		}
	}
	if (cmp_result != 0 ) 
	{
		printf("Employee not found.\n");
	}
}

/** add employee function  prompt for ID number, first and
 * last name, and salaray. must be valid inputs, else print invalid
 * ask to confirm, if 1, confirms, 0, rejects. add employee to end of stack
 * @param *emps the employee array to add into
 * @return void
 */

void addEmployee(Employee *emps) {
	int add_id, add_salary, confirm;
	char add_fname[MAXNAME], add_lname[MAXNAME];
	printf("Enter information for new employee.\n");
	printf("You will have a chance to confirm entry\n");
	printf("After all fields have been filled.\n");
	int ret = 1;
	while (ret == 1)
	{
		printf("Enter six digit ID of new employee:\n");
		scanf("%d", &add_id);
		if (add_id >= 100000 && add_id <= 999999)
		{
			break;	
		}
		printf("Invalid input, please enter a six digit ID.\n");
	}
	printf("Enter first name of new employee:\n");
	scanf("%s", add_fname);
	printf("Enter last name of new employee\n");
	scanf("%s", add_lname);
	while (ret == 1)
	{
		printf("Enter salary of new employee(30000 to 150000):\n");
		scanf("%d", &add_salary);
		if (add_salary >= 30000 && add_salary <=150000)
		{
			break;
		}
		printf("Invalid input, value must be between 30000 and 150000.\n");
	}
	printf("Enter '1' to confirm or '0' to cancel:\n");
	scanf("%d", &confirm);
	if (confirm == 1)
	{
		int i;
		for (i = MAXEMPLOYEE; i > 0; i--)
		{
			emps[i] = emps[i-1];
		}
		emps[0].emp_id = add_id;
		strcpy(emps[0].first_name, add_fname);
		strcpy(emps[0].last_name, add_lname);
		emps[0].emp_salary = add_salary;
	}
}


/**
 * Sorts array by id number
 *@param *emps is the emp_array to be sorted
 *@return void
 */
void sortEmpArray(Employee *emps) {
	int i = 0 , j = 0;
	Employee tmp;
	for (i = 0; i < MAXEMPLOYEE - 1; i++)
	{
		for (j = 0; j < MAXEMPLOYEE - i - 1; j++) 
		{
			if (emps[j+2].emp_id != 0)
			{
				if (emps[j].emp_id > emps[j+1].emp_id)
				{
				tmp = emps[j];
				emps[j] = emps[j+1];
				emps[j+1] = tmp;
				}
			}
		}
	}
}

/**
 * This is a function to test the readfile library on a DB input file: you will
 * not really call this in your program, but use it as an example of how to use
 * the readfile library functions.
 * @param filename the filename to open and read
 * edit code to turn read text into an array of employees
 */
void readAndFillArray(char *filename, Employee *emps) {
	printf("filename '%s'\n", filename);

	int ret = openFile(filename);  // try to open the DB file
	if (ret == -1) {
		printf("bad error: can't open %s\n", filename);
		exit(1);
	}

	int id, salary;
	char fname[MAXNAME], lname[MAXNAME];	
	int i = 0;

	while (ret != -1) {    
		ret = readInt(&id);         // read the first line of values from file
		emps[i].emp_id = id;
		if (ret) { break; }
		ret = readString(fname);
		strcpy(emps[i].first_name, fname);
		if (ret) { break; }
		ret = readString(lname);
		strcpy(emps[i].last_name, lname);
		if (ret) { break; }
		ret = readInt(&salary);
		emps[i].emp_salary = salary;
		if (ret == 0) { // stuff was read in okay
		//	printf("%d %s %s %d\n", id, fname, lname, salary);
			i++;
		}
	}

	closeFile();  // when all done close the file
}

/**
 *  DO NOT MODIFY THIS FUNCTION. It works "as is".
 *
 *  This function gets the filename passed in as a command line option
 *  and copies it into the filename parameter. It exits with an error 
 *  message if the command line is badly formed.
 *  @param filename the string to fill with the passed filename
 *  @param argc, argv the command line parameters from main 
 *               (number and strings array)
 */
void getFilenameFromCommandLine(char filename[], int argc, char *argv[]) {

	if (argc != 2) {
		printf("Usage: %s database_file\n", argv[0]);
		// exit function: quits the program immediately...some errors are not 
		// recoverable by the program, so exiting with an error message is 
		// reasonable error handling option in this case
		exit(1);   
	}
	if (strlen(argv[1]) >= MAXFILENAME) { 
		printf("Filename, %s, is too long, cp to shorter name and try again\n",
				filename);
		exit(1);
	}
	strcpy(filename, argv[1]);
}

/**
 * employee_db.c 
 *
 * This file contains to code to add to the employee
 * database text. The purpose of the code will take 
 * an input from the user and if successful, will
 * add employe data to the database.
 */
