// Libraries
#include <stdio.h>
#include <string.h>

// Macros
#define FILENAME_LEN 64
#define STRING_LEN 512
#define NAME_LENGTH 20
#define NUMBER_OF_EMPLOYEES 10

// File and Struct Array Setup
FILE* stream;
errno_t err;
size_t employee_index = 0;
char input_choice = ' ';
char filename[FILENAME_LEN] = "default.txt";

// Struct
struct Employee {
	char name[NAME_LENGTH];
	float hourly_rate;
	float hours_worked;
};

// Menu Methods
void addEmployee(struct Employee employees[NUMBER_OF_EMPLOYEES]) {
	printf("\nName: ");
	scanf_s("%s", employees[employee_index].name, NAME_LENGTH);
	if (employees[employee_index].name[0] == '-' && employees[employee_index].name[1] == '1') {
		return;
	}

	printf("Hours: ");
	scanf_s("%f", &employees[employee_index].hours_worked);
	if (employees[employee_index].hourly_rate == -1) {
		return;
	}

	printf("Rate: ");
	scanf_s("%f", &employees[employee_index].hourly_rate);
	if (employees[employee_index].hours_worked == -1) {
		return;
	}

	printf("\n");

	employee_index++;
};
void updateEmployee(struct Employee employees[NUMBER_OF_EMPLOYEES]) 
{ 
	printf("\nChoose an employee:\n");

	for (size_t i = 0; employee_index > i; i++)
	{
		printf("%d. %s\n", i, employees[i].name);
	}

	size_t selection = -1;

	printf("? ");
	scanf_s("%d", &selection);
	printf("\n");


	printf("Name: ");
	scanf_s("%s", employees[selection].name, NAME_LENGTH);

	printf("Hours: ");
	scanf_s("%f", &employees[selection].hours_worked);

	printf("Rate: ");
	scanf_s("%f", &employees[selection].hourly_rate);

	printf("\n");
};
void printSingleRecord(struct Employee employees[NUMBER_OF_EMPLOYEES]) 
{ 
	printf("\nChoose an employee.\n");

	for (size_t i = 0; employee_index > i; i++)
	{
		printf("%d. %s\n", i, employees[i].name);
	}

	size_t selection = -1;

	printf("? ");
	scanf_s("%d", &selection);
	printf("\n");

	printf("Employee: %s, ", employees[selection].name);
	printf("Hours: %.2f, ", employees[selection].hours_worked);
	printf("Rate: %.2f ", employees[selection].hourly_rate);
	printf("\n\n");
};
void printAllRecords(struct Employee employees[NUMBER_OF_EMPLOYEES]) 
{
	printf("\n");
	for (size_t i = 0; employee_index > i; i++)
	{
		printf("Employee: %s, ", employees[i].name);
		printf("Hours: %.2f, ", employees[i].hours_worked);
		printf("Rate: %.2f ", employees[i].hourly_rate);
		printf("\n");
	}
	printf("\n");
};
void menu(struct Employee employees[NUMBER_OF_EMPLOYEES])
{
	int choice = -1;

	do {
		puts("What would you like to do?");
		puts("1. Add Employee");
		puts("2. Update Employee");
		puts("3. Print Single Record");
		puts("4. Print All Records");
		puts("5. Save and Exit");

		printf("? ");
		scanf_s("%d", &choice);

		switch (choice)
		{
		case 1: addEmployee(employees); break;
		case 2: updateEmployee(employees); break;
		case 3: printSingleRecord(employees); break;
		case 4: printAllRecords(employees); break;
		case 5: puts("\nExiting.\n");  break;
		}
	} while (5 != choice);
};

// Standard Methods
void loadFromFile(struct Employee employees[NUMBER_OF_EMPLOYEES])
{
	// Request Filename
	printf("\nFilename?\n");
	printf("? ");
	scanf_s("%s", &filename, FILENAME_LEN);
	
	// Check if file open
	err = fopen_s(&stream, filename, "r");

	// Check if file open
	if (err != 0)
	{
		// Print that file didn't open
		printf("\nFile could not be opened\n\n");
	}
	else
	{
		// Print that file opened
		printf("\nFile Opened.\n\n");

		// Print Header
		printf("%-10s%-13s%s\n", "Name", "Hourly Rate", "Hours Worked");

		// Scan Data in Structure from File
		//fscanf_s(stream, "%s %f %f", name, &hourly_rate, &hours_worked);
		fscanf_s(stream, "%s", employees[employee_index].name, NAME_LENGTH);
		fscanf_s(stream, "%f", &employees[employee_index].hourly_rate);
		fscanf_s(stream, "%f", &employees[employee_index].hours_worked);

		// Print Results
		printf("%s %f %f\n", employees[employee_index].name, employees[employee_index].hourly_rate, employees[employee_index].hours_worked);

		employee_index++;

		// Loop Until FEOF Break
		while (1)
		{
			// Scan Data in Structure from File
			fscanf_s(stream, "%s", employees[employee_index].name, NAME_LENGTH);
			fscanf_s(stream, "%f", &employees[employee_index].hourly_rate);
			fscanf_s(stream, "%f", &employees[employee_index].hours_worked);

			// Break if End of File Stream
			if (feof(stream))
			{
				break;
			}

			// Print Results
			printf("%s %f %f\n", employees[employee_index].name, employees[employee_index].hourly_rate, employees[employee_index].hours_worked);

			employee_index++;
		}
		puts("");
		printf("Stream Closed.\n\n");
		fclose(stream);
	}

	menu(employees);
}
void loadFromKeyboard(struct Employee employees[NUMBER_OF_EMPLOYEES])
{
	printf("\n");
	menu(employees);
}
void inputChoice(struct Employee employees[NUMBER_OF_EMPLOYEES])
{
	printf("How would you like to load the file?\n");
	printf("F: File\n");
	printf("K: Keyboard\n");
	printf("? ");
	scanf_s("%c", &input_choice, 1);

	switch (input_choice)
	{
	case 'f':
	case 'F':
		loadFromFile(employees);
		break;
	case 'k':
	case 'K':
		loadFromKeyboard(employees);
		break;
	default:
		break;
	}
}

// Save
void saveFile(struct Employee employees[NUMBER_OF_EMPLOYEES])
{
	// Loop through employee index and write to file
	for (size_t i = 0; employee_index > i; i++)
	{
		printf("Line %d written to file.\n", i);
		fprintf_s(stream, "%s ", employees[i].name, NAME_LENGTH);
		fprintf_s(stream, "%f ", employees[i].hourly_rate);
		fprintf_s(stream, "%f\n", employees[i].hours_worked);
	}
	printf("\nFile Saved.");
	fclose(stream);
	puts("\nStream Closed.");
};
void saveFileMenu(struct Employee employees[NUMBER_OF_EMPLOYEES])
{
	if ('f' == input_choice || 'F' == input_choice)
	{
		puts("Saving to opened file.");
		err = fopen_s(&stream, filename, "w+");
		
		if (err == 0) 
		{
			saveFile(employees);
		} 
		else
		{
			printf("Couldn't save to file.\nExiting.\n");
			exit(2);
		}
	}
	else if ('k' == input_choice || 'K' == input_choice)
	{
		printf("Filename?\n");
		printf("? ");
		scanf_s("%s", &filename, FILENAME_LEN);

		printf("\nSaving to new file.\n");
		err = fopen_s(&stream, filename, "w+");

		if (err == 0)
		{
			saveFile(employees);
		}
		else
		{
			printf("Couldn't save to file.\nExiting.\n");
			exit(2);
		}
	}
};

// Main
int main(void)
{
	struct Employee employees[NUMBER_OF_EMPLOYEES];

	inputChoice(employees);

	saveFileMenu(employees);

	system("pause");
}
