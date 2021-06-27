
//Omer Itach 315814640 
//group number 3 tuvia ruzenberg 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define SIZE_EMPLOYEE 3

typedef struct employee {
	int code;
	char name[15];
	float salary;
}Employee;

#define SIZE 8

typedef char board[SIZE][SIZE];




//========== declarations ========================
void Ex1();
void Ex2();
void Ex3();
void Ex4();
void Ex5();
void Ex6();
void Ex7();


//== EX1 == 
char** Split(char* str, char letter, int* size);
char* Create_string(int first, int last, int SizeofWord, char* str);
void PrintStringArray(char** Str, int Size);
void inputStrChar(char**, char*);

//== EX2 == 
char* clearDigitsAndSpaces(char* str);

//== EX3 ==
void createFile(char* filename);
char commonestLetter(char* fileanme);
int findMax(int* times_of_letters);//finds the maximum in a counters array, return the index
void freeMemory(char** str,int size);

//== EX4 ==
void decode(char* str_to_decode);
void reduce(char* str_to_decode, int first_index, int last_index);

//== EX5 == 
void memoryReport(char* filename, char* declaration);
int check_variable_kind(char ch);
int what_kind_variable(char* declaration, int first_index, int last_index, int size_kind);
void update_file_variables(char* filename, char* declaration, int first_index, int last_index, int size_of_bytes);
void printFile(char* filename);

//== EX6 == 
void createBinaryFile(char* filename);
Employee* get_info();
void updateSalary(char* filename, float threshold);
void displayBinaryFile(char* filename);

//== EX7 ==
void fillBoard(board bin_board);
void printBoard(board bin_board);
unsigned long long boardToBits(board bin_board);
void displayBinaryBoard(unsigned long long coded_bin_board);

//=========== main ================================

void Ex1()
{
	
	char str[100];
	char letter;
	int size;
	printf("EX1: \n");
	inputStrChar(&str,&letter);

	char** NewWordS = Split(str, letter, &size);
	PrintStringArray(NewWordS, size);
	printf("Size is %d\n", size);
	freeMemory(NewWordS,size);
}
void Ex2()
{
	char* str = "abcd2 34fty  78 jurt#";
	char* resultString = clearDigitsAndSpaces(str);
	printf("After cleaning spaces and digits: \n");	
	puts(resultString);
	free(resultString);
	resultString = NULL;
}
void Ex3() {
	
	char ch_most_common;
	createFile("input.txt");
	ch_most_common = commonestLetter("input.txt");

	if (ch_most_common) {
		printf("The commonest letter is %c", ch_most_common);
	}
	else {
		printf("No letter in the file");//initialize max_index to be 0 ,if return 0 so no words added. 
	}

}
void Ex4() {
	char str[] = "Btwlzx Dqqes Eq|pj2 Tjhvqujs Iqoqjy bpg Eqfxtx Xcwwtt";
	printf("Before decode :\n");
	puts(str);
	decode(str);
	printf("After decode :\n");
	puts(str);
}
void Ex5() {
	
	char str[] = "int x, y;";
	memoryReport("check7.txt", str);
	printFile("check7.txt");
}
void Ex6() {
	float threshold;

	printf("Enter the thershold: ");
	scanf("%f", &threshold);
	createBinaryFile("employee.txt");
	printf("File before update\n");
	displayBinaryFile("employee.txt");
	updateSalary("employee.txt", threshold);
	printf("File after update\n");
	displayBinaryFile("employee.txt");

}
void Ex7(){
	unsigned long long num;
    board bin_board;
    fillBoard(bin_board);
	num=boardToBits(bin_board);
	displayBinaryBoard(num);
}

void main() {
	int select = 0, i, all_Ex_in_loop = 0;
	printf("Run menu once or cyclically?\n(Once - enter 0, cyclically - enter other number) ");
	if (scanf("%d", &all_Ex_in_loop) == 1)
		do
		{
			for (i = 1; i <= 7; i++)
				printf("Ex%d--->%d\n", i, i);
			printf("EXIT-->0\n");
			do {
				select = 0;
				printf("please select 0-7 : ");
				scanf("%d", &select);
			} while ((select < 0) || (select > 7));
			switch (select)
			{
			case 1: Ex1(); break;
			case 2: Ex2(); break;
			case 3: Ex3(); break;
			case 4: Ex4(); break;
			case 5: Ex5(); break;
			case 6: Ex6(); break;
			case 7: Ex7(); break;
			}
		} while (all_Ex_in_loop && select);
		return 0;
}

//============== functions ================================

//== EX1 ==
char** Split(char* str, char letter, int* size)
{
	int i, flag = 0, flag_counter = 0, k = 0, first=0, last, WordSize = 0,size_of_str = strlen(str);
	char** result;
	result = NULL;

	(*size) = 0;

	if (str[0] == letter)
	{
		(*size)++;
	}

	for (i = 1; i < size_of_str; i++)
	{
		if ((str[i - 1] == ' ' ) && (str[i] == letter || str[i] == letter-32))
		{
			(*size)++;
		}
	}

	result = (char**)malloc((*size) * sizeof(char*));

	for (i = 0; i < size_of_str; i++)
	{
		if (i == 0 && (str[i] == letter || str[i] == letter - 32))
		{
			while (str[i] != ' ')
			{
				WordSize++;
				i++;
			}

			last = i-1;//maybe 1
			result[k++] = Create_string(first, last, WordSize, str);
			flag = 1;
			WordSize = 0;
		}
		if (flag == 0)
		{
			flag = 1;
			continue;
		}
		if (str[i - 1] == ' ' && (str[i] == letter || str[i] == letter - 32)) // start counting size for string
		{
			flag_counter = 1;
			first = i;
		}
		if (flag_counter == 1 && str[i] != ' ' ) // Count the strings size
		{
			WordSize++;
		}
		if (flag_counter == 1 && str[i] == ' ') // finish the counting and allocate memory to string
		{
			last = i - 1;
			result[k++] = Create_string(first, last, WordSize, str);
			WordSize = 0;
			flag_counter = 0;
		}
	}

	//the problem is str[first] will always be a 'g' and we will write into result for no reason to a static memory(should throw) , and than try to free the whole array in the free func.
	if ((str[first] == letter || str[first] == letter - 32) && first!=0) {
		last = i - 1;
		result[k] = Create_string(first, last, WordSize, str);
	}

	return result;
}
char *Create_string(int first, int last,int SizeofWord,char *str)
{
	int i, k = 0;
	char* NewWord = (char*)malloc((SizeofWord+1) * sizeof(char));
	for (i = first; i <= last; i++)
	{
		NewWord[k++] = str[i];
	}
	NewWord[k] = '\0';
	return NewWord;
}
void PrintStringArray(char** Str,int Size)
{
	int i;
	for (i = 0; i < Size; i++)
	{
			printf("Word %d : " , i+1);
			puts(Str[i]);
			printf("\n");
	}
}
void freeMemory(char** str,int size) {
	int i; 

	for (i = 0; i < size; i++) {
		free(str[i]);
		str[i] = NULL;
	}

}
void inputStrChar(char** str, char* letter) {

	char small_letter;
	char str_to_get[100];
	printf("Enter a small letter: ");
	rewind(stdin);
	scanf("%c", &small_letter);
	*letter = small_letter;

	printf("Enter a sentence: ");
	rewind(stdin);
	gets(str);
	str = str_to_get;

}

//== EX2 == 
char* clearDigitsAndSpaces(char* str)
{
	char* resultString;
	int i, Strlength = strlen(str), resultStringSize = 0, k = 0;
	resultString = NULL;
	for (i = 0; i < Strlength; i++)
	{
		if ((str[i] != ' ' ) && (str[i] > '9' || str[i] < '0'))
		{
			resultStringSize++;
		}
	}
	resultString = (char*)malloc((resultStringSize+1) * sizeof(char));
	for (i = 0; i < Strlength; i++)
	{
		if ((str[i] != ' ') && (str[i] > '9' || str[i] < '0'))
		{
			resultString[k++] = str[i];
		}
	}
	resultString[k] = '\0';
	return resultString;
}

//== EX3 == 
void createFile(char* filename) {
	char ch;
	FILE* fptr;

	fptr = NULL;
	fptr = fopen(filename, "w");
	if (!fptr) {
		printf("Could not opent the file");
	}

	
	while ((ch = getchar()) != EOF)
	{
		fputc(ch, fptr);
		rewind(stdin);
	}
	fclose(fptr);

}
char commonestLetter(char* filename) {
	
	int amount_of_letters[26] = { 0 }, ch_index;
	char ch;
	FILE* fptr;

	fptr = NULL;
	ch = NULL;//compiler want initialize ch beacuse its inside the loop term.

	fptr = fopen(filename, "r");

	if (!fptr) {
		printf("could not open the file");
	}
	
	while (fscanf(fptr, "%c", &ch) != EOF) {
		if (ch >= 'a' && ch <= 'z') {
			amount_of_letters[ch - 'a']++;
		}
		else if ((ch >= 'A' && ch <= 'Z')) {
			amount_of_letters[ch - 'A']++;
		}
	}
	fclose(fptr);

	ch_index=findMax(amount_of_letters);
	return ch_index + 'A';//revert the index into a capital letter form. 
}
int findMax(int* times_of_letters) {
	int max, max_index, i;

	max = times_of_letters[0];
	max_index = 0;

	for (i = 1; i < 26; i++) {
		if (times_of_letters[i] >= max) {//we need "=" beacuse we want the biggest letter lexicography
			max = times_of_letters[i];
			max_index = i;
		}
	}

	return max_index;
}

//== EX4 == 
void decode(char* str_to_decode) {
	int i, first_index, last_index;

	i = 0;
	first_index = 0;

	while (str_to_decode[i] != '\0') {
	
		if (str_to_decode[i] == ' ') {
			last_index = i-1;
			reduce(str_to_decode, first_index, last_index);
		   first_index = i + 1;
		}
		i++;
	}
	reduce(str_to_decode, first_index,i-1);

}
void reduce(char* str_to_decode, int first_index, int last_index) {
	int i, reduce_index;

	reduce_index = 1;
	for ( i = first_index; i <= last_index; i++)
	{
		str_to_decode[i] -= reduce_index;
		reduce_index++;
	}
}

//== EX5 ==
// memoryDeport
void memoryReport(char* filename, char* declaration) {
	
	int size_kind, i, first_index, last_index, size_of_bytes;

	size_kind = check_variable_kind(declaration[0]);

	i = 0;
	while (declaration[i]!=' '){
		i++;
	}

	first_index = i+1;
	for ( i = i+1; declaration[i]!='\0'; i++)
	{
		
		if (declaration[i] == ',') {
			last_index = i - 1;
			size_of_bytes=what_kind_variable(declaration, first_index, last_index, size_kind);
			update_file_variables(filename,declaration, first_index, last_index,size_of_bytes);
			first_index = i + 2;
		}
		if (declaration[i] == ';') {
			last_index = i - 1;
			size_of_bytes=what_kind_variable(declaration, first_index, last_index, size_kind);
			update_file_variables(filename, declaration, first_index, last_index, size_of_bytes);
			break;
		}
	}
}
//check size variable kind
int check_variable_kind(char ch) {

	switch (ch)
	{
	case 'c':
		return 1;
	case 's':
		return 2;
	case 'i' : 
		return 4;
	case 'l':
		return 4;
	case 'f':
		return 4;
	case 'd':
		return 8;
	default:
		break;
	}
}
//checke exactly what kind of (pointer ,regular,array) variables from this kind
int what_kind_variable(char* declaration, int first_index, int last_index, int size_kind) {

	int i, digit, x, str_index;
	double sum;
	char* str;

	str = NULL;
	x = 1;
	sum = 0;


	//check if the next word is long
	str = (char*)malloc((last_index - first_index) + 2 * sizeof(char));
	str_index = 0;
	for (i = first_index; i <= last_index; i++)
	{
		str[str_index++] = declaration[i];
	}
	str[str_index] = '\0';
	if (strcmp(str, "long") == 0) {
		return NULL;
	}

	//Check if pointer / array / regular
	if (declaration[first_index] == '*') {
		return 4;
	}
	else if (declaration[last_index] == ']') {

		for (i = last_index - 1; declaration[i] != '['; i--)
		{
			digit = declaration[i] - '0';
			sum += digit * x;
			x *= 10;
		}
		return sum * size_kind;
	}
	else {
		return size_kind;
	}

	free(str);
}
//wirte into the file
void update_file_variables(char* filename, char* declaration, int first_index, int last_index, int size_of_bytes) {
	
	int i, str_index;
	char* str;
	FILE* fptr;

	fptr = NULL;
	fptr = fopen(filename, "a");

	
	if (fptr) {
		str = (char*)malloc((last_index - first_index) + 2 * sizeof(char));
		str_index = 0;
		for (i = first_index; i <= last_index; i++)
		{
			str[str_index++] = declaration[i];
		}
		str[str_index] = '\0';

		fprintf(fptr, "%s requires %d bytes\n", str, size_of_bytes);
		fclose(fptr);
	}

	else {
		printf("could not open then file");
	}
	
	
}
void printFile(char* filename){
	
	char ch;
	FILE* fptr = fopen(filename, "r");


	if (fptr) {
		while ((ch=fgetc(fptr)) != EOF)
		{
			if (ch =='\n') {
				printf("\n");
			}
			printf("%c", ch);
		}
		fclose(fptr);
	}
	else {
		printf("could not opent the file");
	}
}

//== EX6 ==
void createBinaryFile(char* filename) {
	int i;
	Employee* employee_list;
	FILE* fptr;
	fptr = NULL;

	employee_list = get_info();
	fptr = fopen(filename, "wb");

	if (fptr!=NULL) {

			for (i = 0; i < SIZE_EMPLOYEE; i++) {
				fwrite(&employee_list[i], sizeof(Employee), 1, fptr);
			}
			fclose(fptr);
	}
	else {
		printf("could not open the file\n");
	}
	free(employee_list);
}
Employee* get_info() {
	int i;
	Employee* employee_arr;

	employee_arr = (Employee*)malloc(SIZE_EMPLOYEE * sizeof(Employee));

	for (i = 0; i < SIZE_EMPLOYEE; i++) {
		
		printf("Enter emplyee code: ");
		scanf("%d", &employee_arr[i].code);
		printf("Enter emplyee name: ");
		//gets(employee_arr[i].name);//maybe
		scanf("%s", &employee_arr[i].name);
		printf("Enter emplyee salary:");
		scanf("%f", &employee_arr[i].salary);
	}

	return employee_arr;
}
void updateSalary(char* filename, float threshold) {

	int i;
	int bonus_arr[SIZE_EMPLOYEE];
	char *temp_file_name="temp.txt";
	FILE* fptr, *fptr2;
	fptr = NULL;
	Employee employee;

	for (i = 0; i < SIZE_EMPLOYEE; i++) {
		printf("Enter %d employe bonus: ", i + 1);
		scanf("%d",& bonus_arr[i]);
	}

	
	fptr = fopen(filename, "rb+");
	fptr2 = fopen(temp_file_name, "rb+");

	i = 0;
	if (fptr&&fptr2) {

		while (fread(&employee, sizeof(Employee), 1, fptr) == 1) {
			
			employee.salary += bonus_arr[i++];
			if (employee.salary <= threshold) {
				fwrite(&employee, sizeof(employee), 1, fptr2);
			}
		}
		fclose(fptr);
		fclose(fptr2);
	}
	else if (fptr) {
		fclose(fptr);
		printf("could not open the file");
	}
	else {
		fclose(fptr2);
		printf("could not open the file");
	}

	remove(filename);
	rename(temp_file_name, filename);
}
void displayBinaryFile(char* filename) {
	FILE* fptr;
	fptr = NULL;
	Employee employee;

	fptr = fopen(filename, "rb");

	if (fptr != NULL) {
		while (fread(&employee, sizeof(employee), 1, fptr) == 1) {
			printf("%d %s %.2f\n", employee.code, employee.name, employee.salary);
		}
		fclose(fptr);
	}
	else {
		printf("could not open the file");
	}
}

//== EX7 ==
void fillBoard(board bin_board) {
	int i, j;
	
	srand(time(NULL));

	

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			bin_board[i][j] = (rand() % 2) + '0';
		}
	}
	
	printf("Board before:\n");
	printBoard(bin_board);

}

void printBoard(board bin_board) {
	int i, j;


	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			printf("[%c]    ", bin_board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
}

unsigned long long boardToBits( board bin_board) {

	int i, j; 
	unsigned long long num, external;

	external = 1;
	num = 0;

	for (i = SIZE-1; i >=0; i--) {
		for (j = SIZE - 1; j >= 0; j--) {

			if (bin_board[i][j] == '1') {
				num += external;
			}

			external *= 2;
	 	}
	}
	
	printf("Decimal value %llu\n\n",num);
	return num;
}

void displayBinaryBoard(unsigned long long coded_bin_board) {

	
		unsigned long long mask = 1, op, i;
		mask <<= 63;
		
		printf("Back to Binary:\n\n");
		for (i = 1; i <= 64; i++)
		{
			op = coded_bin_board & mask;
			coded_bin_board <<= 1;
			if (op)// MSB = 1;
			{
				printf("1    ");
			}
			else//MSB = 0 
			{
				printf("0    ");
			}
			if (i % 8 == 0)
			{
				printf("\n");
			}
		}
		printf("\n");

}