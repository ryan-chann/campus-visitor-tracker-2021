#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <windows.h>
#pragma warning (disable: 4996)

//Constant Declaration (Visitor Information Module - Ryan Chan Joon Yeew)
SYSTEMTIME time;

//Constant Declaration (Administrative systems Module - Jong Xuan Jie)
#define MAX_NUM_RECORD_STAFF 20 //Assume that the maximum of the staff records had 20


// Constant declaration for visit and exit module(Lee Heng Yong)
const char* DATA_FORMAT_IN = "%d|%s|%s|%s|%s|%s|%s|%.1f|%s\n";
const char* DATA_FORMAT_OUT = "%d|%s|%s|%s|%s|%s|%s|%.1f|%s\n";


//Structure Declaration (Visitor Information Module - Ryan Chan Joon Yew)
typedef struct {
	char name[30], icNum[15], phoneNumber[15], studentID[8], staffID[7];
	int venue, visitorCategory, homeState;
}VisitorInfo;

//Structure in the administrative module (Jong Xuan Jie)
typedef struct
{
	char staffID[6], password[20], name[20], position[15], faculty[5], address[40], contactNum[13], ICnum[15];
}Staff;

//Structure array to store the values of the variables after read the file (Jong Xuan Jie)
Staff allStaffInfo[MAX_NUM_RECORD_STAFF];

//Structure Declaration (Venue information module - Tan Wen Zhang)
typedef struct {
	int day, month, year;
}Date;

struct Venue {
	Date date;
	char venueID[7];
	char category[15];
	char description[15];
	int maxNoOfVisitor;
	int currentVisitor;
	char phoneNumber[15];
	Date lsd; //Last sanitization date
};

//Structure Declaration (Visit and Exit Module - Lee Heng Yong)
typedef struct {
	int visitorNo;
	char dateEntered[12];
	char timeEntered[10];
	char visitorName[50];
	char visitorIC[15];
	char visitorPhoneNo[15];
	char venueID[7];
	double visitorTemperature;
	char timeExited[10];
}Activity;


//Module Declaration (Ryan Chan Joon Yew)
void administrative();
void visitorInformation();
void venueInformationModule();
void visitAndExit();

// Function Declaration (Visitor Information Module - Ryan Chan Joon Yew)
void addVisitor();
void venueInformation();
void visitorCategoryInformation();
void stateInformation();
void inputHomeState(char, int*);
void inputVisitorCategory(char, int*, char*, char*);
void inputVenue(char, int*);
void displayVisitorRecord();
void modifyVisitorRecord();
void searchVisitor();
void chgInfoFromNumToWord(int, int, int, int, char*, char*, char*);
void deleteVisitorRecord();
void logo();
int rMenu();
int menu();

//Functions prototype in the administrative module (Jong Xuan Jie)
int loginofStaff(int* countStaff);
void addNewAdminRecord(int* totalStaff, char* confirmToContinue, int* countStaff);
void searchAdminRecord(int* totalStaff, char* confirmToContinue, int* countStaff2);
void modifyAdminRecord(int* totalStaff, char* confirmToContinue, int* countStaff3);
void displayAdminRecord(int* totalStaff, char* confirmToContinue);
void deleteAdminRecord(int* totalStaff, char* confirmToContinue, int* countStaff4);
void reportAdminRecord(int* totalStaff, char* confirmToContinue, int* countStaff, int* countStaff2, int* countStaff3, int* countStaff4);

//Functions prototype of the menu in the administrative module (Jong Xuan Jie)
int menuAfterLogin(int choiceOfMenu);
int menuOfModify(int choiceOfMenu);
int menuOfSearch(int choiceOfMenu);

//Functions prototype for venue information module (Tan Wen Zhang)
void add();
void search();
void modify();
void display();
void deleteRecord();
void sortdate();

void table1();
void table2();
void body1(int i, int d, int m, int y, char vid[10], char cat[15], char des[15], int max, int current, char phn[15], int ld, int lm, int ly);
void table3();
void header1(char str1[20], char str2[20], char str3[20], char str4[20], char str5[20], char str6[20], char str7[20], char str8[20], char str9[20]);

void tableA();
void header2(char strA[20], char strB[20], char strC[20], char strD[20]);
void tableB();
void body2();
void tableC();

//Function prototypes for visit and exit module (Lee Heng Yong)
void vemenu();
void veadd();
void vesearch();
void vemodify();
void vedisplay();
void vedelete();
void vebackToMain();
char vebackToMenu();

//Main Function (Ryan Chan Joon Yew)
void main() {
	logo();
	int choice;

	choice = menu();

	do {
		//Add display search modify delete
		switch (choice) {
		case 1: {
			visitorInformation();
			choice = menu();
			break;
		}
		case 2: {
			administrative();
			choice = menu();
			break;
		}
		case 3: {
			venueInformationModule();
			choice = menu();
			break;
		}
		case 4: {
			visitAndExit();
			choice = menu();
			break;
		}
		case 5: {
			printf("\nThank you for using our system!!\n");
			exit(0);
			break;
		}
		default: {
			printf("\n\nPLEASE ENTER VALID INPUT ONLY!!\n\n");
			choice = menu();
		}
		}
	} while (choice != 5);

	system("pause");
}

//Tan Wen Zhang
void venueInformationModule() {
	int action;
	printf("You have selected Venue Information Module\n");
	printf("=========================================================\n");
	printf("Action :\n");
	printf("1. add record\n");
	printf("2. search a record\n");
	printf("3. edit a record\n");
	printf("4. display all the record\n");
	printf("5. delete a record\n");
	printf("6. Sort the date of the report\n\n");

	printf("Please Choose a number for action >");
	scanf("%d", &action);

	switch (action)
	{
	case 0:
		break;
	case 1:
		add();
		break;
	case 2:
		search();
		break;
	case 3:
		modify();
		break;
	case 4:
		display();
		break;
	case 5:
		deleteRecord();
		break;
	case 6:
		sortdate();
		break;
	default:
		printf("Invalid action! Plaese try again.\n");
		break;
	}
}

//Tan Wen Zhang
void add() {
	struct Venue venue;
	char choose;
	int record = 0;
	FILE* fptr;

	fptr = fopen("VENUE INFO.txt", "r");
	if (!fptr) {
		printf("Cannot open the file!");
		exit(-1);
	}
	while (fscanf(fptr, "%d/%d/%d\n%[^\n]\n%[^\n]\n%[^\n]\n%d\n%d\n%s\n%d/%d/%d\n\n", &venue.date.day, &venue.date.month, &venue.date.year, &venue.venueID, &venue.category, &venue.description, &venue.maxNoOfVisitor, &venue.currentVisitor, &venue.phoneNumber, &venue.lsd.day, &venue.lsd.month, &venue.lsd.year) != EOF)
		record++;
	do
	{
		fptr = fopen("VENUE INFO.txt", "a");
		if (!fptr) {
			printf("Cannot open the file!");
			exit(-1);
		}
		printf("Record %02d\n==========\n", record);
		printf("Date(dd/mm/yyyy)                     :");
		rewind(stdin);
		scanf("%d/%d/%d", &venue.date.day, &venue.date.month, &venue.date.year);
		printf("VenueID                              :");
		rewind(stdin);
		scanf("%[^\n]", venue.venueID);
		printf("category                             :");
		rewind(stdin);
		scanf("%[^\n]", venue.category);
		printf("description                          :");
		rewind(stdin);
		scanf("%[^\n]", venue.description);
		printf("Max No Of Visitor                    :");
		scanf("%d", &venue.maxNoOfVisitor);
		printf("Current Visitor                      :");
		scanf("%d", &venue.currentVisitor);
		rewind(stdin);
		printf("Phone Number                         :");
		rewind(stdin);
		scanf("%[^\n]", venue.phoneNumber);
		printf("Last Sanitization Date (dd/mm/yyyy)  :");
		scanf("%d/%d/%d", &venue.lsd.day, &venue.lsd.month, &venue.lsd.year);



		fprintf(fptr, "%02d/%02d/%d\n%s\n%s\n%s\n%d\n%d\n%s\n%02d/%02d/%d\n\n", venue.date.day, venue.date.month, venue.date.year, venue.venueID, venue.category, venue.description,
			venue.maxNoOfVisitor, venue.currentVisitor, venue.phoneNumber, venue.lsd.day, venue.lsd.month, venue.lsd.year);


		fclose(fptr);
		printf("Add more record?\n\tY - Yes\n\tN - No\nChoice > ");
		rewind(stdin);
		scanf("%c", &choose);

		record++;

	} while (toupper(choose) == 'Y');
}

//Tan Wen Zhang
void search() {
	struct Venue venue[20];
	int choose, i = 0;
	int day, month, year;
	double temperature;
	int hour, min;
	char choice;
	FILE* fptr;

	do
	{
		printf("Search criteria :\n");
		printf("----------------------------\n");
		printf("1. Date\n");
		printf("2. Last Sanitization Date\n");

		printf("Which criteria do you want to search? :");
		scanf("%d", &choose);

		fptr = fopen("VENUE INFO.txt", "r");
		if (!fptr) {
			printf("Cannot open the file!");
			exit(-1);
		}
		if (choose == 1)
		{
			printf("Searching based on date!\t");
			printf("Enter the date (day/month/year):");
			scanf("%d/%d/%d", &day, &month, &year);

			table1();
			header1("Record", "Date", "VenueID", "Category", "Description", "Max No Of Visitor", "Current Visitor", "Contact No", "Last Sanitization Date");

			while (fscanf(fptr, "%d/%d/%d\n%[^\n]\n%[^\n]\n%[^\n]\n%d\n%d\n%s\n%d/%d/%d\n\n", &venue[i].date.day, &venue[i].date.month, &venue[i].date.year, &venue[i].venueID, &venue[i].category, &venue[i].description, &venue[i].maxNoOfVisitor, &venue[i].currentVisitor, &venue[i].phoneNumber, &venue[i].lsd.day, &venue[i].lsd.month, &venue[i].lsd.year) != EOF)
			{
				if (day == venue[i].date.day && month == venue[i].date.month && year == venue[i].date.year)
				{
					table2();
					body1(i + 1, venue[i].date.day, venue[i].date.month, venue[i].date.year, venue[i].venueID, venue[i].category, venue[i].description, venue[i].maxNoOfVisitor, venue[i].currentVisitor,
						venue[i].phoneNumber, venue[i].lsd.day, venue[i].lsd.month, venue[i].lsd.year);

				}
				i++;
			}
			table3();
		}
		else if (choose == 2)
		{
			printf("Searching based on Last Sanitization Date!\t");
			printf("Enter the Last Sanitization Date : ");
			scanf("%d/%d/%d", &day, &month, &year);

			table1();
			header1("Record", "Date", "VenueID", "Category", "Description", "Max No Of Visitor", "Current Visitor", "Contact No", "Last Sanitization Date");

			while (fscanf(fptr, "%d/%d/%d\n%[^\n]\n%[^\n]\n%[^\n]\n%d\n%d\n%s\n%d/%d/%d\n\n", &venue[i].date.day, &venue[i].date.month, &venue[i].date.year, &venue[i].venueID, &venue[i].category, &venue[i].description, &venue[i].maxNoOfVisitor, &venue[i].currentVisitor, &venue[i].phoneNumber, &venue[i].lsd.day, &venue[i].lsd.month, &venue[i].lsd.year) != EOF)
			{
				if (day == venue[i].lsd.day && month == venue[i].lsd.month && year == venue[i].lsd.year)
				{
					table2();
					body1(i + 1, venue[i].date.day, venue[i].date.month, venue[i].date.year, venue[i].venueID, venue[i].category, venue[i].description, venue[i].maxNoOfVisitor, venue[i].currentVisitor,
						venue[i].phoneNumber, venue[i].lsd.day, venue[i].lsd.month, venue[i].lsd.year);

				}
				i++;
			}
			table3();
		}
		else
			printf("Invalid criteria! Please choose again.\n");

		fclose(fptr);

		printf("Search more record?  [Y] Yes  [N] No  ");
		rewind(stdin);
		scanf("%c", &choice);
		while (toupper(choice) != 'Y' && toupper(choice) != 'N')
		{
			printf("Search more record?  [Y] Yes  [N] No  ");
			rewind(stdin);
			scanf("%c", &choice);
		}

	} while (toupper(choice) == 'Y');
}

//Tan Wen Zhang
void modify() {
	struct Venue venue[20];
	int record, i = 0;
	FILE* fptr;
	char choice;

	do
	{
		fptr = fopen("VENUE INFO.txt", "r");
		if (!fptr) {
			printf("Cannot open the file!");
			exit(-1);
		}
		printf("Which record you want to edit?  >");
		scanf("%d", &record);

		while (fscanf(fptr, "%d/%d/%d\n%[^\n]\n%[^\n]\n%[^\n]\n%d\n%d\n%s\n%d/%d/%d\n\n", &venue[i].date.day, &venue[i].date.month, &venue[i].date.year, &venue[i].venueID, &venue[i].category, &venue[i].description, &venue[i].maxNoOfVisitor, &venue[i].currentVisitor, &venue[i].phoneNumber, &venue[i].lsd.day, &venue[i].lsd.month, &venue[i].lsd.year) != EOF)
		{
			if (record == (i + 1))
			{
				table1();
				header1("Record", "Date", "VenueID", "Category", "Description", "Max No Of Visitor", "Current Visitor", "Contact No", "Last Sanitization Date");
				table2();
				body1(i + 1, venue[i].date.day, venue[i].date.month, venue[i].date.year, venue[i].venueID, venue[i].category, venue[i].description, venue[i].maxNoOfVisitor, venue[i].currentVisitor,
					venue[i].phoneNumber, venue[i].lsd.day, venue[i].lsd.month, venue[i].lsd.year);
				table3();

				printf("--------------------------------------------------------\n\n");
				printf("Record %02d\n==========\n", record);
				printf("Date(dd/mm/yyyy)                     :");
				rewind(stdin);
				scanf("%d/%d/%d", &venue[i].date.day, &venue[i].date.month, &venue[i].date.year);
				printf("VenueID                              :");
				rewind(stdin);
				scanf("%[^\n]", venue[i].venueID);
				printf("category                             :");
				rewind(stdin);
				scanf("%[^\n]", venue[i].category);
				printf("description                          :");
				rewind(stdin);
				scanf("%[^\n]", venue[i].description);
				printf("Max No Of Visitor                    :");
				scanf("%d", &venue[i].maxNoOfVisitor);
				printf("Current Visitor                      :");
				scanf("%d", &venue[i].currentVisitor);
				rewind(stdin);
				printf("Phone Number                         :");
				rewind(stdin);
				scanf("%[^\n]", venue[i].phoneNumber);
				printf("Last Sanitization Date (dd/mm/yyyy)  :");
				scanf("%d/%d/%d", &venue[i].lsd.day, &venue[i].lsd.month, &venue[i].lsd.year);
			}
			i++;
		}
		fclose(fptr);

		fptr = fopen("VENUE INFO.txt", "w");
		if (!fptr) {
			printf("Cannot open the file!");
			exit(-1);
		}

		for (int j = 0; j < i; j++)
		{
			fprintf(fptr, "%02d/%02d/%d\n%s\n%s\n%s\n%d\n%d\n%s\n%02d/%02d/%d\n\n", venue[j].date.day, venue[j].date.month, venue[j].date.year, venue[j].venueID, venue[j].category, venue[j].description, venue[j].maxNoOfVisitor, venue[j].currentVisitor, venue[j].phoneNumber, venue[j].lsd.day, venue[j].lsd.month, venue[j].lsd.year);
		}

		fclose(fptr);


		fptr = fopen("VENUE INFO.txt", "r");
		if (!fptr) {
			printf("Cannot open the file!");
			exit(-1);
		}
		i = 0;
		printf("--------------------------------------------------------\n\n");
		while (fscanf(fptr, "%d/%d/%d\n%[^\n]\n%[^\n]\n%[^\n]\n%d\n%d\n%s\n%d/%d/%d\n\n", &venue[i].date.day, &venue[i].date.month, &venue[i].date.year, &venue[i].venueID, &venue[i].category, &venue[i].description, &venue[i].maxNoOfVisitor, &venue[i].currentVisitor, &venue[i].phoneNumber, &venue[i].lsd.day, &venue[i].lsd.month, &venue[i].lsd.year) != EOF)
		{
			if (record == (i + 1))
			{
				table1();
				header1("Record", "Date", "VenueID", "Category", "Description", "Max No Of Visitor", "Current Visitor", "Contact No", "Last Sanitization Date");
				table2();
				body1(i + 1, venue[i].date.day, venue[i].date.month, venue[i].date.year, venue[i].venueID, venue[i].category, venue[i].description, venue[i].maxNoOfVisitor, venue[i].currentVisitor,
					venue[i].phoneNumber, venue[i].lsd.day, venue[i].lsd.month, venue[i].lsd.year);
				table3();
			}
			i++;
		}
		fclose(fptr);

		printf("Modify more record?  [Y] Yes  [N] No  ");
		rewind(stdin);
		scanf("%c", &choice);
		while (toupper(choice) != 'Y' && toupper(choice) != 'N')
		{
			printf("Modify more record?  [Y] Yes  [N] No  ");
			rewind(stdin);
			scanf("%c", &choice);
		}

	} while (toupper(choice) == 'Y');

}

//Tan Wen Zhang
void display() {
	struct Venue venue[20];
	int i = 0, recordId;
	FILE* fptr;
	fptr = fopen("VENUE INFO.txt", "r");
	if (!fptr) {
		printf("Cannot open the file!");
		exit(-1);
	}
	table1();
	header1("Record", "Date", "VenueID", "Category", "Description", "Max No Of Visitor", "Current Visitor", "Contact No", "Last Sanitization Date");

	while (fscanf(fptr, "%d/%d/%d\n%[^\n]\n%[^\n]\n%[^\n]\n%d\n%d\n%s\n%d/%d/%d\n\n", &venue[i].date.day, &venue[i].date.month, &venue[i].date.year, &venue[i].venueID, &venue[i].category, &venue[i].description, &venue[i].maxNoOfVisitor, &venue[i].currentVisitor, &venue[i].phoneNumber, &venue[i].lsd.day, &venue[i].lsd.month, &venue[i].lsd.year) != EOF)
	{
		table2();
		body1(i + 1, venue[i].date.day, venue[i].date.month, venue[i].date.year, venue[i].venueID, venue[i].category, venue[i].description, venue[i].maxNoOfVisitor, venue[i].currentVisitor,
			venue[i].phoneNumber, venue[i].lsd.day, venue[i].lsd.month, venue[i].lsd.year);

		i++;
	}
	table3();
	fclose(fptr);
}

//Tan Wen Zhang
void deleteRecord() {
	struct Venue venue[20];
	char choose, choice;
	int record, i = 0, y = 0;
	FILE* fptr;
	do
	{
		fptr = fopen("VENUE INFO.txt", "r");
		if (!fptr) {
			printf("Cannot open the file!");
			exit(-1);
		}
		printf("Which record you want to delete? >");
		scanf("%d", &record);

		while (fscanf(fptr, "%d/%d/%d\n%[^\n]\n%[^\n]\n%[^\n]\n%d\n%d\n%s\n%d/%d/%d\n\n", &venue[i].date.day, &venue[i].date.month, &venue[i].date.year, &venue[i].venueID, &venue[i].category, &venue[i].description, &venue[i].maxNoOfVisitor, &venue[i].currentVisitor, &venue[i].phoneNumber, &venue[i].lsd.day, &venue[i].lsd.month, &venue[i].lsd.year) != EOF)
		{
			if (record == (i + 1))
			{
				table1();
				header1("Record", "Date", "VenueID", "Category", "Description", "Max No Of Visitor", "Current Visitor", "Contact No", "Last Sanitization Date");
				table2();
				body1(i + 1, venue[i].date.day, venue[i].date.month, venue[i].date.year, venue[i].venueID, venue[i].category, venue[i].description, venue[i].maxNoOfVisitor, venue[i].currentVisitor,
					venue[i].phoneNumber, venue[i].lsd.day, venue[i].lsd.month, venue[i].lsd.year);
				table3();

				printf("\nAre you sure want to delete this record? [Y]=yes [N]=no  ");
				rewind(stdin);
				scanf("%c", &choose);
				y = i;

			}
			i++;
		}
		fclose(fptr);

		if (toupper(choose) == 'Y')
		{
			for (int j = y; j < i; j++)
				venue[j] = venue[j + 1];

			fptr = fopen("VENUE INFO.txt", "w");
			if (!fptr) {
				printf("Cannot open the file!");
				exit(-1);
			}

			for (int j = 0; j < (i - 1); j++)
			{
				fprintf(fptr, "%02d/%02d/%d\n%s\n%s\n%s\n%d\n%d\n%s\n%02d/%02d/%d\n\n", venue[j].date.day, venue[j].date.month, venue[j].date.year, venue[j].venueID, venue[j].category, venue[j].description, venue[j].maxNoOfVisitor, venue[j].currentVisitor, venue[j].phoneNumber, venue[j].lsd.day, venue[j].lsd.month, venue[j].lsd.year);
			}

			fclose(fptr);
		}
		else
			printf("Record not deleted.\n");

		printf("Delete more record?  [Y] Yes  [N] No  ");
		rewind(stdin);
		scanf("%c", &choice);
		while (toupper(choice) != 'Y' && toupper(choice) != 'N')
		{
			printf("Delete more record?  [Y] Yes  [N] No  ");
			rewind(stdin);
			scanf("%c", &choice);
		}

	} while (toupper(choice) == 'Y');
}

//Tan Wen Zhang
void sortdate() {
	struct Venue venue[20], t;
	char choose;
	int  i = 0;
	FILE* fptr;
	fptr = fopen("VENUE INFO.txt", "r");
	if (!fptr) {
		printf("Cannot open the file!");
		exit(-1);
	}
	fptr = fopen("VENUE INFO.txt", "r");
	table1();
	header1("Record", "Date", "VenueID", "Category", "Description", "Max No Of Visitor", "Current Visitor", "Contact No", "Last Sanitization Date");
	while (fscanf(fptr, "%d/%d/%d\n%[^\n]\n%[^\n]\n%[^\n]\n%d\n%d\n%s\n%d/%d/%d\n\n", &venue[i].date.day, &venue[i].date.month, &venue[i].date.year, &venue[i].venueID, &venue[i].category, &venue[i].description, &venue[i].maxNoOfVisitor, &venue[i].currentVisitor, &venue[i].phoneNumber, &venue[i].lsd.day, &venue[i].lsd.month, &venue[i].lsd.year) != EOF)
	{
		table2();
		body1(i + 1, venue[i].date.day, venue[i].date.month, venue[i].date.year, venue[i].venueID, venue[i].category, venue[i].description, venue[i].maxNoOfVisitor, venue[i].currentVisitor,
			venue[i].phoneNumber, venue[i].lsd.day, venue[i].lsd.month, venue[i].lsd.year);

		i++;
	}
	table3();
	fclose(fptr);

	printf(" Do you want to sort all the record(s) by date ? [Y] Yes  [N] No  ");
	rewind(stdin);
	scanf("%c", &choose);
	while (toupper(choose) != 'Y' && toupper(choose) != 'N')
	{
		printf(" \033[0;31mInvalid choice! Please try again.\033[0;0m\n\n");
		printf(" Do you want to sort all the record(s) by date ? [Y] Yes  [N] No  ");
		rewind(stdin);
		scanf("%c", &choose);
	}

	if (toupper(choose) == 'Y')
	{
		for (int p = 0; p < i; p++)
		{
			for (int b = p + 1; b < i; b++)
			{
				if (venue[p].date.day > venue[b].date.day)
				{
					t = venue[p];
					venue[p] = venue[b];
					venue[b] = t;
				}
				if (venue[p].date.month > venue[b].date.month)
				{
					t = venue[p];
					venue[p] = venue[b];
					venue[b] = t;
				}
				if (venue[p].date.year > venue[b].date.year)
				{
					t = venue[p];
					venue[p] = venue[b];
					venue[b] = t;
				}
			}
		}
	}
	fptr = fopen("VENUE INFO.txt", "w");
	if (!fptr) {
		printf("Cannot open the file!");
		exit(-1);
	}

	for (int j = 0; j < i; j++)
	{
		fprintf(fptr, "%02d/%02d/%d\n%s\n%s\n%s\n%d\n%d\n%s\n%02d/%02d/%d\n\n", venue[j].date.day, venue[j].date.month, venue[j].date.year, venue[j].venueID, venue[j].category, venue[j].description, venue[j].maxNoOfVisitor, venue[j].currentVisitor, venue[j].phoneNumber, venue[j].lsd.day, venue[j].lsd.month, venue[j].lsd.year);
	}

	fclose(fptr);

	fptr = fopen("VENUE INFO.txt", "r");
	table1();
	header1("Record", "Date", "VenueID", "Category", "Description", "Max No Of Visitor", "Current Visitor", "Contact No", "Last Sanitization Date");
	while (fscanf(fptr, "%d/%d/%d\n%[^\n]\n%[^\n]\n%[^\n]\n%d\n%d\n%s\n%d/%d/%d\n\n", &venue[i].date.day, &venue[i].date.month, &venue[i].date.year, &venue[i].venueID, &venue[i].category, &venue[i].description, &venue[i].maxNoOfVisitor, &venue[i].currentVisitor, &venue[i].phoneNumber, &venue[i].lsd.day, &venue[i].lsd.month, &venue[i].lsd.year) != EOF)
	{
		table2();
		body1(i + 1, venue[i].date.day, venue[i].date.month, venue[i].date.year, venue[i].venueID, venue[i].category, venue[i].description, venue[i].maxNoOfVisitor, venue[i].currentVisitor,
			venue[i].phoneNumber, venue[i].lsd.day, venue[i].lsd.month, venue[i].lsd.year);

		i++;
	}
	table3();
	fclose(fptr);

}

//Tan Wen Zhang
void table1() {
	printf(" %c", 218);

	for (int i = 0; i < 8; i++)
		printf("%c", 196);
	printf("%c", 194);
	for (int i = 0; i < 12; i++)
		printf("%c", 196);
	printf("%c", 194);
	for (int i = 0; i < 10; i++)
		printf("%c", 196);
	printf("%c", 194);
	for (int i = 0; i < 17; i++)
		printf("%c", 196);
	printf("%c", 194);
	for (int i = 0; i < 17; i++)
		printf("%c", 196);
	printf("%c", 194);
	for (int i = 0; i < 20; i++)
		printf("%c", 196);
	printf("%c", 194);
	for (int i = 0; i < 17; i++)
		printf("%c", 196);
	printf("%c", 194);
	for (int i = 0; i < 14; i++)
		printf("%c", 196);
	printf("%c", 194);
	for (int i = 0; i < 27; i++)
		printf("%c", 196);

	printf("%c\n", 191);
}

//Tan Wen Zhang
void table2() {
	printf(" %c", 195);

	for (int i = 0; i < 8; i++)
		printf("%c", 196);
	printf("%c", 197);
	for (int i = 0; i < 12; i++)
		printf("%c", 196);
	printf("%c", 197);
	for (int i = 0; i < 10; i++)
		printf("%c", 196);
	printf("%c", 197);
	for (int i = 0; i < 17; i++)
		printf("%c", 196);
	printf("%c", 197);
	for (int i = 0; i < 17; i++)
		printf("%c", 196);
	printf("%c", 197);
	for (int i = 0; i < 20; i++)
		printf("%c", 196);
	printf("%c", 197);
	for (int i = 0; i < 17; i++)
		printf("%c", 196);
	printf("%c", 197);
	for (int i = 0; i < 14; i++)
		printf("%c", 196);
	printf("%c", 197);
	for (int i = 0; i < 27; i++)
		printf("%c", 196);

	printf("%c\n", 180);
}

//Tan Wen Zhang
void table3()
{
	printf(" %c", 192);

	for (int i = 0; i < 8; i++)
		printf("%c", 196);
	printf("%c", 193);
	for (int i = 0; i < 12; i++)
		printf("%c", 196);
	printf("%c", 193);
	for (int i = 0; i < 10; i++)
		printf("%c", 196);
	printf("%c", 193);
	for (int i = 0; i < 17; i++)
		printf("%c", 196);
	printf("%c", 193);
	for (int i = 0; i < 17; i++)
		printf("%c", 196);
	printf("%c", 193);
	for (int i = 0; i < 20; i++)
		printf("%c", 196);
	printf("%c", 193);
	for (int i = 0; i < 17; i++)
		printf("%c", 196);
	printf("%c", 193);
	for (int i = 0; i < 14; i++)
		printf("%c", 196);
	printf("%c", 193);
	for (int i = 0; i < 27; i++)
		printf("%c", 196);

	printf("%c\n", 217);
}

//Tan Wen Zhang
void header1(char str1[20], char str2[20], char str3[20], char str4[20], char str5[20], char str6[20], char str7[20], char str8[20], char str9[20])
{
	printf(" %-2c%-7s%-2c%-11s%-2c%-9s%-2c%-16s%-2c%-16s%-2c%-19s%-2c%-16s%-2c%-13s%-2c%-26s%-2c\n"
		, 179, str1, 179, str2, 179, str3, 179, str4, 179, str5, 179, str6, 179, str7, 179, str8, 179, str9, 179);
}

//Tan Wen Zhang
void body1(int i, int d, int m, int y, char vid[10], char cat[15], char des[15], int max, int current, char phn[15], int ld, int lm, int ly)
{
	printf(" %-2c%-7d%-2c%02d/%02d/%-5d%-2c%-9s%-2c%-16s%-2c%-16s%-2c%-19d%-2c%-16d%-2c%-13s%-2c%02d/%02d/%-20d%c\n", 179, i, 179, d, m, y, 179, vid, 179, cat, 179, des, 179, max, 179, current, 179, phn, 179, ld, lm, ly, 179);
}

//Tan Wen Zhang
void tableA()
{
	printf(" %c", 218);
	for (int i = 0; i < 8; i++)
		printf("%c", 196);
	printf("%c", 194);
	for (int i = 0; i < 12; i++)
		printf("%c", 196);
	printf("%c", 194);
	for (int i = 0; i < 15; i++)
		printf("%c", 196);
	printf("%c", 194);
	for (int i = 0; i < 13; i++)
		printf("%c", 196);
	printf("%c\n", 191);
}

//Tan Wen Zhang
void header2(char strA[20], char strB[20], char strC[20], char strD[20])
{
	printf(" %-2c%-7s%-2c%-11s%-2c%-14s%-2c%-13s%-2c\n", 179, strA, 179, strB, 179, strC, 179, strD, 179);
}

//Tan Wen Zhang
void tableB()
{
	printf(" %c", 195);
	for (int i = 0; i < 8; i++)
		printf("%c", 196);
	printf("%c", 197);
	for (int i = 0; i < 12; i++)
		printf("%c", 196);
	printf("%c", 197);
	for (int i = 0; i < 15; i++)
		printf("%c", 196);
	printf("%c", 197);
	for (int i = 0; i < 13; i++)
		printf("%c", 196);
	printf("%c\n", 180);
}

//Tan Wen Zhang
void tableC()
{
	printf(" %c", 192);
	for (int i = 0; i < 8; i++)
		printf("%c", 196);
	printf("%c", 193);
	for (int i = 0; i < 12; i++)
		printf("%c", 196);
	printf("%c", 193);
	for (int i = 0; i < 15; i++)
		printf("%c", 196);
	printf("%c", 193);
	for (int i = 0; i < 13; i++)
		printf("%c", 196);
	printf("%c\n", 217);
}

//Tan Wen Zhang
void body2(int recordId, int day, int month, int year, char category[20], double temperature)
{
	printf(" %-4c%02d   %-2c%02d/%02d/%04d %-2c%-7s%-2c%-4c%.1lf%2c%-4c%-2c\n"
		, 179, recordId, 179, day, month, year, 179, category, 179, temperature, 167, 'C', 179);
}

//Menu function (Ryan Chan Joon Yew)
int menu() {
	int selection;
	GetLocalTime(&time);

	printf("Today's Date : %d/%d/%d at %d:%d \n\n", time.wDay, time.wMonth, time.wYear, time.wHour, time.wMinute);
	printf("\n1. Visitor Informations\n");
	printf("2. Administrative system\n");
	printf("3. Venue Informations\n");
	printf("4. Visit and Exits\n");
	printf("5. Exit\n\n");
	printf("Selection > ");
	rewind(stdin);
	scanf("%d", &selection);

	return selection;
}


//Main function of the administrative module (Jong Xuan Jie)
void administrative() {

	int valid;                                           //Delcare the valid to store the variable of the return value in the login function
	int totalStaff;                                      //When read the binary file, how many records had been recorded in the file
	int choiceOfMenu;                                    //Variable for the menu
	char addconfirm = 'N';                               //Delcare the character first to make sure the while loop can run
	int count = 0, count2 = 0, count3 = 0, count4 = 0;   //Variable to store the count of the add, search, modify and delete

	valid = loginofStaff(&totalStaff); //Value of valid will be store after login function return the value
									   //the total records had been used also will store into the pointer(totalStaff)

	while (toupper(addconfirm) == 'N')  //While the user enter n in the last part of the functions, 
										//it will loop the main menu everytime to prompt the user to enter their choose
	{
		choiceOfMenu = menuAfterLogin(8);  //Declare the value of menu is 8 to make sure the menu can run

		if (choiceOfMenu == 1)          //Choice 1 will display add function
		{
			addNewAdminRecord(&totalStaff, &addconfirm, &count);
			printf("\n");
		}
		else if (choiceOfMenu == 2)     //Choice 2 will display search function
		{
			searchAdminRecord(&totalStaff, &addconfirm, &count2);
			printf("\n");
		}
		else if (choiceOfMenu == 3)     //Choice 3 will display modify function
		{
			modifyAdminRecord(&totalStaff, &addconfirm, &count3);
			printf("\n");
		}
		else if (choiceOfMenu == 4)     //Choice 4 will display display function
		{
			displayAdminRecord(&totalStaff, &addconfirm);
			printf("\n");
		}
		else if (choiceOfMenu == 5)     //Choice 5 will display report function
		{
			reportAdminRecord(&totalStaff, &addconfirm, &count, &count2, &count3, &count4);
			printf("\n");
		}
		else if (choiceOfMenu == 6)     //Choice 6 will display delete function
		{
			deleteAdminRecord(&totalStaff, &addconfirm, &count4);
			printf("\n");
		}
		else if (choiceOfMenu == 7)      //Choice 7 will exit the program
		{
			exit(0);
		}
	}
}

//Login function of the administrative module (Jong Xuan Jie)
int loginofStaff(int* countStaff)
{
	Staff staffDetails;  //Structure of the user input the ID & pasword in login function
	*countStaff = 0;     //Store the total of the records had been recorded 
	int valid = 1;       //Assume the valid is 1 to make sure it can run the while loop necessity
	int i = 0;

	FILE* fileAllStaffOfLogin;   //File open to read the records that had been recorded
	fileAllStaffOfLogin = fopen("administrativeStaff.bin", "rb");
	if (!fileAllStaffOfLogin)
	{
		printf("Unable open the file\n");
		exit(-1);
	}

	while (fread(&allStaffInfo[i], sizeof(Staff), 1, fileAllStaffOfLogin) != 0) //Read the information in the file and store it into the structure array
	{
		*countStaff += 1;     //If there is one record, it will +1 until there is not have any record
		i++;                  //The value of the structure array will start at 0 and everytime will increase 1 if there has any record 
	}

	//Close the file
	fclose(fileAllStaffOfLogin);   //Close the file

	while (valid == 1)
	{
		//Prompt the user input the ID & password to access the login function
		printf("Enter your TARUC Staff ID : ");
		rewind(stdin);
		scanf("%s", &staffDetails.staffID);

		printf("Enter your password : ");
		rewind(stdin);
		scanf("%s", &staffDetails.password);


		for (i = 0; i < *countStaff; i++)
		{
			//Check the ID & password is correct or not 
			if (strcmp(staffDetails.staffID, allStaffInfo[i].staffID) == 0 && strcmp(staffDetails.password, allStaffInfo[i].password) == 0)
			{
				valid = 0;   //If correct will return valid = 0 and stop looping
				break;
			}

			//If the ID or password is wrong
			else if (strcmp(staffDetails.staffID, allStaffInfo[i].staffID) != 0 || strcmp(staffDetails.password, allStaffInfo[i].password) != 0)
			{
				valid = 1;   //If the ID & password is wrong, it will return valid = 1

				//If the ID is correct & password wrong, it will return valid = 2 and stop the looping
				if (strcmp(staffDetails.staffID, allStaffInfo[i].staffID) == 0 && strcmp(staffDetails.password, allStaffInfo[i].password) != 0)
				{
					valid = 2;
					break;
				}
			}
		}

		//Find the result that will display base on the valid had been return
		if (valid == 0)
		{
			printf("\nLogin successful ! Welcome staff %s\n\n", staffDetails.staffID);
		}
		//Valid will equal to 1 when it can't login successful
		else if (valid == 1) {
			printf("\nWrong Staff ID & Password ! Press key in again\n\n");
			valid = 1;
		}
		else if (valid == 2)
		{
			printf("\nWrong Password ! Press key in again\n\n");
			valid = 1;
		}

	}
	return valid;
}

//Add function of the administrative module (Jong Xuan Jie)
void addNewAdminRecord(int* totalStaff, char* confirmToContinue, int* countStaff)
{
	Staff addNewStaffDetail;
	int valid = 1;
	char addConfirm = 'N';
	char choiceAddNew = 'Y';

	while (toupper(choiceAddNew) == 'Y' || toupper(addConfirm) == 'N')
	{
		//i = current staff element, exp last element of staff is 6, total staff = 7, so it will start at element 7
		int i = *totalStaff;

		//Enter the information of the new staff
		do 
		{
			rewind(stdin);
			printf("The ID of New Staff: ");
			scanf("%s", &allStaffInfo[i].staffID);
            
			//If the ID is same with the record(s) in the file, user need enter again
			for (int a=0; a<*totalStaff; a++)
			{
				if (strcmp(allStaffInfo[i].staffID, allStaffInfo[a].staffID) == 0)
				{
					printf("Same ID in the file ! Please enter again\n\n");
					valid = 1;
					break;
				}
			}
		} while (valid == 1);

		rewind(stdin);
		printf("The Password of New Staff: ");
		scanf("%s", &allStaffInfo[i].password);
		
		do 
		{
			rewind(stdin);
			printf("The Name of New Staff: ");
			scanf("%[^\n]", allStaffInfo[i].name);

			//If the name is same with the record(s) in the file, user need enter again
			for (int a = 0; a < *totalStaff; a++)
			{
				if (strcmp(allStaffInfo[i].name, allStaffInfo[a].name) == 0)
				{
					printf("Same name in the file ! Please enter again\n\n");
					valid = 1;
					break;
				}
			}

		} while (valid == 1);

		rewind(stdin);
		printf("The Position of New Staff: ");
		scanf("%[^\n]", allStaffInfo[i].position);

		do
		{
			rewind(stdin);
			printf("The Faculty of New Staff: ");
			scanf("%s", &allStaffInfo[i].faculty);

			//Assume that the max elements of faculty is 4
			if (strlen(allStaffInfo[i].faculty) >= 5)
			{
				printf("The maximum element of faculty only have 4 ! Please enter again\n\n");
			}
		} while (strlen(allStaffInfo[i].faculty) >= 5);

		rewind(stdin);
		printf("The Address of New Staff: ");
		scanf("%[^\n]", allStaffInfo[i].address);

		//Restore the variable of the valid = 1
		valid = 1;

		//When valid = 1, do the looping to prompt user input the information again
		while (valid == 1)
		{
			rewind(stdin);
			printf("The Contact Number of New Staff (xxx-xxxxxxxx) : ");
			scanf("%s", &allStaffInfo[i].contactNum);

			//Statements to check the format contact number
			if (strlen(allStaffInfo[i].contactNum) == 12)
			{
				for (int j = 0; j < 3; j++)
				{
					if (allStaffInfo[i].contactNum[j] != '-' && isdigit(allStaffInfo[i].contactNum[j]) != 0)
					{
						if (j == 2 && allStaffInfo[i].contactNum[3] == '-')
						{
							for (int j = 4; j < 12; j++)
							{
								if (allStaffInfo[i].contactNum[j] != '-' && isdigit(allStaffInfo[i].contactNum[j]) != 0)
								{
									valid = 0;
								}
								else
								{
									valid = 1;
									break;
								}
							}
						}
					}
					else
					{
						valid = 1;
						break;
					}
				}
				if (valid == 1)
				{
					printf("\nWrong format ! Please enter again\n\n");
				}

			}
			else
			{
				printf("\nWrong format ! Please enter again\n\n");
			}
		}

		//Restore the variable of the valid = 1
		valid = 1;

		//When valid = 1, do the looping to prompt user input the information again
		while (valid == 1)
		{
			rewind(stdin);
			printf("The IC number of New Staff (xxxxxx-xx-xxxx) : ");
			scanf("%s", &allStaffInfo[i].ICnum);

			//Statements to check the format IC
			if (strlen(allStaffInfo[i].ICnum) == 14)
			{
				for (int j = 0; j < 6; j++)
				{
					if (allStaffInfo[i].ICnum[j] != '-' && isdigit(allStaffInfo[i].ICnum[j]) != 0)
					{
						if (j == 5 && allStaffInfo[i].ICnum[6] == '-')
						{
							for (int j = 7; j < 9; j++)
							{
								if (allStaffInfo[i].ICnum[j] != '-' && isdigit(allStaffInfo[i].ICnum[j]) != 0)
								{
									if (j == 8 && allStaffInfo[i].ICnum[9] == '-')
									{
										for (int j = 10; j < 14; j++)
										{
											if (allStaffInfo[i].ICnum[j] != '-' && isdigit(allStaffInfo[i].ICnum[j]) != 0)
											{
												valid = 0;
											}
											else
											{
												valid = 1;
												break;
											}
										}
									}
								}
								else
								{
									valid = 1;
									break;
								}
							}
						}
					}
					else
					{
						valid = 1;
						break;
					}
				}
				if (valid == 1)
				{
					printf("\nWrong format ! Please enter again\n\n");
				}
			}
			else
			{
				printf("\nWrong format ! Please enter again\n\n");
			}
		}

		//Restore the variable to A
		addConfirm = 'A';

		while (toupper(addConfirm) != 'N' && toupper(addConfirm) != 'Y')
		{
			//Ask user confirm that information is correct or not, if not will enter again
			rewind(stdin);
			printf("\nAre you sure that your information about New Staff is correct (Y/N): ");
			scanf("%c", &addConfirm);

			//When user enter N, need user key in the new information again
			if (toupper(addConfirm) == 'N')
			{
				printf("\nPlease enter your information again\n\n");
			}

			//If user not enter Y or N, will need user key in again
			else if (toupper(addConfirm) != 'N' && toupper(addConfirm) != 'Y')
			{
				printf("\nYou can enter 'Y' or 'N' only ! Please enter again\n\n");
			}

			//If the information had been confirm, add the information of new staff into the file, total staff in file will + 1
			else if (toupper(addConfirm) == 'Y')
			{
				FILE* fileaddNewInformation;
				fileaddNewInformation = fopen("administrativeStaff.bin", "ab");
				if (!fileaddNewInformation) {
					printf("Unable open the file\n");
					exit(-1);
				}

				//Add the record that already confirm into the file
				fwrite(&allStaffInfo[i], sizeof(Staff), 1, fileaddNewInformation);

				//Count of add + 1
				*countStaff += 1;

				//Total records in the file + 1
				*totalStaff = i + 1;

				//Close the file
				fclose(fileaddNewInformation);

				//Restore the variable to A
				choiceAddNew = 'A';

				while (toupper(choiceAddNew) != 'N' && toupper(choiceAddNew) != 'Y')
				{
					//Ask user want continue add the information of new staff or not, if yes, it will loop and need user add the information again
					rewind(stdin);
					printf("\nAdd more record(s) of New Staff (Y/N): ");
					scanf("%c", &choiceAddNew);

					//If user not enter Y or N, will need user key in again
					if (toupper(choiceAddNew) != 'N' && toupper(choiceAddNew) != 'Y')
					{
						printf("\nYou can only enter 'Y' or 'N' ! Please enter again\n\n");
					}
				}
			}
		}
	}
	//Store the character 'N' into pointer to make sure the looping can run in main function
	*confirmToContinue = choiceAddNew;
}

//Search function of the administrative module (Jong Xuan Jie)
void searchAdminRecord(int* totalStaff, char* confirmToContinue, int* countStaff2) {
	int choiceOfMenu;
	char searchID[6], searchName[20], confirmContinue = 'Y';  //Assume that variable of continue to search the records is 'Y'
	int valid = 2, i;        //Assume that valid = 2 to make sure the while loop can loop successful

	while (toupper(confirmContinue) == 'Y' || valid == 2)
	{
		//Display the search menu and prompt user input the choice and assume that will start at 'choice 4'
		choiceOfMenu = menuOfSearch(4);

		//Retore the variable to 'A'
		confirmContinue = 'A';

		if (choiceOfMenu == 1)     //If choice is 1, ask user input the ID to search the record of the staff ID
		{
			rewind(stdin);
			printf("What is the ID of the TARUC Staff: ");
			scanf("%s", &searchID);

			for (i = 0; i < *totalStaff; i++) {
				if (strcmp(searchID, allStaffInfo[i].staffID) == 0)    //Valid = 1 when staff ID found
				{
					valid = 1;
					break;
				}
				else if (strcmp(searchID, allStaffInfo[i].staffID) != 0)
				{
					valid = 2;
				}
			}
			if (valid == 1)
			{
				//Display the information of staff
				printf("\t+--------+----------------------+-----------------+-------+------------------------------------------+--------------------+-----------------+\n");
				printf("\t%s%8s%-4s%14s%6s%17s%s%7s%-9s%16s%9s%18s%3s%13s%5s\n",
					"|", "Staff ID", "|", "Name of Staff", "|", "Position of TARUC", "|", "Faculty", "|", "Address of the TARUC Staff", "|", "Contact Number", "|", "IC Number", "|");
				printf("\t+--------+----------------------+-----------------+-------+------------------------------------------+--------------------+-----------------+\n");
				printf("\t%-2s%-7s%-2s%-21s%-2s%-16s%-2s%-6s%-2s%-41s%-2s%-19s%-2s%-15s%2s\n",
					"|", allStaffInfo[i].staffID, "|", allStaffInfo[i].name, "|", allStaffInfo[i].position, "|", allStaffInfo[i].faculty, "|", allStaffInfo[i].address, "|", allStaffInfo[i].contactNum, "|", allStaffInfo[i].ICnum, "|");
				printf("\t+--------+----------------------+-----------------+-------+------------------------------------------+--------------------+-----------------+\n");

				//Count of search + 1
				*countStaff2 += 1;

				while (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N')
				{
					//Ask user want to continue to search the record or not	
					rewind(stdin);
					printf("\nAre you want to continue to search the Information of others TARUC Staff (Y/N): ");
					scanf("%c", &confirmContinue);

					if (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N')
					{
						printf("\nYou can enter 'Y' or 'N' only\n\n");
					}
				}

			}
			else if (valid == 2)
			{
				printf("\nThe ID of Staff not found ! Please see the menu and choose again\n\n");
			}

		}
		
		else if (choiceOfMenu == 2)     //If choice is 2, ask user input the name to search the record of the name of the staff
		{
			rewind(stdin);
			printf("What is the Name of the TARUC Staff: ");
			scanf("%[^\n]", searchName);

			for (i = 0; i < *totalStaff; i++) {
				if (strcmp(searchName, allStaffInfo[i].name) == 0)    //Valid = 1 when the name of staff found
				{
					valid = 1;
					break;
				}
				else if (strcmp(searchName, allStaffInfo[i].name) != 0)
				{
					valid = 2;
				}
			}
		
			if (valid == 1)
			{
				//Display the information of staff
				printf("\t+--------+----------------------+-----------------+-------+------------------------------------------+--------------------+-----------------+\n");
				printf("\t%s%8s%-4s%14s%6s%17s%s%7s%-9s%16s%9s%18s%3s%13s%5s\n",
					"|", "Staff ID", "|", "Name of Staff", "|", "Position of TARUC", "|", "Faculty", "|", "Address of the TARUC Staff", "|", "Contact Number", "|", "IC Number", "|");
				printf("\t+--------+----------------------+-----------------+-------+------------------------------------------+--------------------+-----------------+\n");
				printf("\t%-2s%-7s%-2s%-21s%-2s%-16s%-2s%-6s%-2s%-41s%-2s%-19s%-2s%-15s%2s\n",
					"|", allStaffInfo[i].staffID, "|", allStaffInfo[i].name, "|", allStaffInfo[i].position, "|", allStaffInfo[i].faculty, "|", allStaffInfo[i].address, "|", allStaffInfo[i].contactNum, "|", allStaffInfo[i].ICnum, "|");
				printf("\t+--------+----------------------+-----------------+-------+------------------------------------------+--------------------+-----------------+\n");

				//Count of search + 1
				*countStaff2 += 1;

				while (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N')
				{
					//Ask user want to continue to search the record or not	
					rewind(stdin);
					printf("\nAre you want to continue to search the Information of others TARUC Staff (Y/N): ");
					scanf("%c", &confirmContinue);

					if (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N')
					{
						printf("\nYou can enter 'Y' or 'N' only\n\n");
					}
				}

			}
			else if (valid == 2)
			{
				printf("\nThe Name of Staff not found !\n\n");
			}
		}
		else if (choiceOfMenu == 3)     //If choice is 3, exit the program
		{
			exit(0);
		}
	}
	//Store the character 'N' into pointer to make sure the looping can run in main function
	*confirmToContinue = confirmContinue;
}

//Modify function of the administrative module (Jong Xuan Jie)
void modifyAdminRecord(int* totalStaff, char* confirmToContinue, int* countStaff3)
{
	int choiceOfMenu, valid = 1, a, i = 0;
	char confirmContinue, addConfirm = 'Y';

	Staff modifyStaff;
	Staff PreviousStaff;
	FILE* fileModifyRecord;

	while (valid == 1)
	{
		//Prompt the user input the staff ID that need modify
		rewind(stdin);
		printf("Enter the Staff ID that you want modify the information of him/her : ");
		scanf("%s", PreviousStaff.staffID);

		//Restore the variable to A
		confirmContinue = 'A';

		while (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N')
		{
			//Ask the user confirm to modify the information of the staff base on the ID 
			rewind(stdin);
			printf("Do you confirm the Staff ID : %s is the staff you want modify (Y/N): ", PreviousStaff.staffID);
			scanf("%c", &confirmContinue);

			if (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N')
			{
				printf("You can enter 'Y' or 'N' only ! Please enter again\n\n");
			}

		}

		if (toupper(confirmContinue) == 'Y')
		{
			for (i = 0; i < *totalStaff; i++)
			{
				if (strcmp(PreviousStaff.staffID, allStaffInfo[i].staffID) != 0)
				{
					valid = 1;
				}
				else if (strcmp(PreviousStaff.staffID, allStaffInfo[i].staffID) == 0)
				{
					valid = 0;
					a = i;
					break;
				}
			}
			if (valid == 1)
			{
				printf("\nStaff ID not found ! Key in again\n\n");
			}
			else if (valid == 0)
			{
				printf("\nStaff ID found. Please see the MENU and enter your choose\n\n");
			}
		}
		else if (toupper(confirmContinue) == 'N')
		{
			printf("Please enter the staff ID again\n");
		}
	}

	while (valid == 0 || toupper(confirmContinue) == 'N' || toupper(addConfirm) == 'Y')
	{
		//Open the file to overwrite the record after user confirm the modify
		fileModifyRecord = fopen("administrativeStaff.bin", "wb");
		if (!fileModifyRecord) {
			printf("Unable open the file\n");
			exit(-1);
		}

		//Display the menu of modify
		choiceOfMenu = menuOfModify(9);

		//Choice 1 = modify Staff ID
		if (choiceOfMenu == 1)
		{
			do
			{
				//Prompt the user input the new Staff ID
				rewind(stdin);
				printf("\nNew ID of the Staff: ");
				scanf("%s", &modifyStaff.staffID);

				do
				{
					//Ask user confirm to modify the new Staff ID or not
					rewind(stdin);
					printf("\nDo you confirm modify the new ID of the staff %s (Y/N): ", PreviousStaff.staffID);
					scanf("%c", &confirmContinue);

					if (toupper(confirmContinue) == 'Y')
					{
						strcpy(allStaffInfo[a].staffID, modifyStaff.staffID);
						valid = 1;

						for (int b = 0; b < *totalStaff; b++)
						{
							fwrite(&allStaffInfo[b], sizeof(Staff), 1, fileModifyRecord);
						}

						//Count of modify + 1
						*countStaff3 += 1;
					}
					else if (toupper(confirmContinue) == 'N')
					{
						printf("Please enter the new staff ID again\n");
					}
					else if (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N')
					{
						printf("You can enter 'Y' or 'N' only ! Please enter again\n");
					}
				} while (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N');

			} while (toupper(confirmContinue) == 'N');
		}

		//Choice 2 = modify password of staff
		else if (choiceOfMenu == 2)
		{
			do
			{
				//Prompt the user input the new password
				rewind(stdin);
				printf("New Password of the Staff: ");
				scanf("%s", &modifyStaff.password);

				do
				{
					//Ask user confirm to modify the new password or not
					rewind(stdin);
					printf("\nDo you confirm modify the new password of the staff %s (Y/N): ", PreviousStaff.staffID);
					scanf("%c", &confirmContinue);

					if (toupper(confirmContinue) == 'Y')
					{
						strcpy(allStaffInfo[a].password, modifyStaff.password);
						valid = 1;

						for (int b = 0; b < *totalStaff; b++)
						{
							fwrite(&allStaffInfo[b], sizeof(Staff), 1, fileModifyRecord);
						}

						//Count of modify + 1
						*countStaff3 += 1;
					}
					else if (toupper(confirmContinue) == 'N')
					{
						printf("Please enter the new password again\n");
					}
					else if (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N')
					{
						printf("You can enter 'Y' or 'N' only ! Please enter again\n");
					}
				} while (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N');

			} while (toupper(confirmContinue) == 'N');
		}

		//Choice 3 = modify name of staff
		else if (choiceOfMenu == 3)
		{
			do
			{
				//Prompt the user input the new name
				rewind(stdin);
				printf("\nNew Name of the Staff: ");
				scanf("%[^\n]", modifyStaff.name);

				do
				{
					//Ask user confirm to modify the new name or not
					rewind(stdin);
					printf("\nDo you confirm modify the new name of the staff %s (Y/N): ", PreviousStaff.staffID);
					scanf("%c", &confirmContinue);

					if (toupper(confirmContinue) == 'Y')
					{
						strcpy(allStaffInfo[a].name, modifyStaff.name);
						valid = 1;

						for (int b = 0; b < *totalStaff; b++)
						{
							fwrite(&allStaffInfo[b], sizeof(Staff), 1, fileModifyRecord);
						}

						//Count of modify + 1
						*countStaff3 += 1;
					}
					else if (toupper(confirmContinue) == 'N')
					{
						printf("Please enter the new name again\n");
					}
					else if (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N')
					{
						printf("You can enter 'Y' or 'N' only ! Please enter again\n");
					}
				} while (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N');

			} while (toupper(confirmContinue) == 'N');
		}

		//Choice 4 = modify position of staff
		else if (choiceOfMenu == 4)
		{
			do
			{
				////Prompt the user input the new position
				rewind(stdin);
				printf("\nNew Position of the Staff: ");
				scanf("%[^\n]", modifyStaff.position);

				do
				{
					//Ask user confirm to modify the new position or not
					rewind(stdin);
					printf("\nDo you confirm modify the new position of the staff %s (Y/N): ", PreviousStaff.staffID);
					scanf("%c", &confirmContinue);

					if (toupper(confirmContinue) == 'Y')
					{
						strcpy(allStaffInfo[a].position, modifyStaff.position);
						valid = 1;

						for (int b = 0; b < *totalStaff; b++)
						{
							fwrite(&allStaffInfo[b], sizeof(Staff), 1, fileModifyRecord);
						}

						//Count of modify + 1
						*countStaff3 += 1;
					}
					else if (toupper(confirmContinue) == 'N')
					{
						printf("Please enter the new position again\n");
					}
					else if (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N')
					{
						printf("You can enter 'Y' or 'N' only ! Please enter again\n");
					}

				} while (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N');

			} while (toupper(confirmContinue) == 'N');
		}

		//Choice 5 = modify faculty of staff
		else if (choiceOfMenu == 5)
		{
			do
			{
				//Prompt the user input the new faculty
				rewind(stdin);
				printf("\nNew Faculty of the Staff: ");
				scanf("%s", &modifyStaff.faculty);

				do
				{
					//Ask user confirm to modify the new faculty or not
					rewind(stdin);
					printf("\nDo you confirm modify the new faculty of the staff %s (Y/N): ", PreviousStaff.staffID);
					scanf("%c", &confirmContinue);

					if (toupper(confirmContinue) == 'Y')
					{
						strcpy(allStaffInfo[a].faculty, modifyStaff.faculty);
						valid = 1;

						for (int b = 0; b < *totalStaff; b++)
						{
							fwrite(&allStaffInfo[b], sizeof(Staff), 1, fileModifyRecord);
						}

						//Count of modify + 1
						*countStaff3 += 1;
					}
					else if (toupper(confirmContinue) == 'N')
					{
						printf("Please enter your new faculty again\n");
					}
					else if (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N')
					{
						printf("You can enter 'Y' or 'N' only ! Please enter again\n");
					}
				} while (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N');

			} while (toupper(confirmContinue) == 'N');
		}

		//Choice 6 = modify name of staff
		else if (choiceOfMenu == 6)
		{
			do
			{
				//Prompt the user input the new address
				rewind(stdin);
				printf("\nNew address of the Staff: ");
				scanf("%s", &modifyStaff.address);

				do
				{
					//Ask user confirm to modify the new address or not
					rewind(stdin);
					printf("\nDo you confirm modify the new address of the staff %s (Y/N): ", PreviousStaff.staffID);
					scanf("%c", &confirmContinue);

					if (toupper(confirmContinue) == 'Y')
					{
						strcpy(allStaffInfo[a].address, modifyStaff.address);
						valid = 1;

						for (int b = 0; b < *totalStaff; b++)
						{
							fwrite(&allStaffInfo[b], sizeof(Staff), 1, fileModifyRecord);
						}

						//Count of modify + 1
						*countStaff3 += 1;
					}
					else if (toupper(confirmContinue) == 'N')
					{
						printf("Please enter the new address again\n");
					}
					else if (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N')
					{
						printf("You can enter 'Y' or 'N' only ! Please enter again\n");
					}
				} while (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N');

			} while (toupper(confirmContinue) == 'N');
		}

		//Choice 7 = modify contact number of staff
		else if (choiceOfMenu == 7)
		{
			do
			{
				//Prompt the user input the new contact number
				rewind(stdin);
				printf("\nNew Contact Number of the Staff: ");
				scanf("%s", &modifyStaff.contactNum);
				do
				{
					//Ask user confirm to modify the new contact number or not
					rewind(stdin);
					printf("\nDo you confirm modify the new contact number of the staff %s (Y/N): ", PreviousStaff.staffID);
					scanf("%c", &confirmContinue);

					if (toupper(confirmContinue) == 'Y')
					{
						strcpy(allStaffInfo[a].contactNum, modifyStaff.contactNum);
						valid = 1;

						for (int b = 0; b < *totalStaff; b++)
						{
							fwrite(&allStaffInfo[b], sizeof(Staff), 1, fileModifyRecord);
						}

						//Count of modify + 1
						*countStaff3 += 1;
					}
					else if (toupper(confirmContinue) == 'N')
					{
						printf("Please enter the new contact number again\n");
					}
					else if (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N')
					{
						printf("You can enter 'Y' or 'N' only ! Please enter again\n");
					}
				} while (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N');

			} while (toupper(confirmContinue) == 'N');
		}

		//	//Choice 8 = modify IC number of staff
		else if (choiceOfMenu == 8)
		{
			do
			{
				//Prompt the user input the new IC number
				rewind(stdin);
				printf("\nNew IC Number of the Staff: ");
				scanf("%s", &modifyStaff.ICnum);

				do
				{
					//Ask user confirm to modify the new IC number or not
					rewind(stdin);
					printf("\nDo you confirm modify the new IC number of the staff %s (Y/N): ", PreviousStaff.staffID);
					scanf("%c", &confirmContinue);

					if (toupper(confirmContinue) == 'Y')
					{
						strcpy(allStaffInfo[a].ICnum, modifyStaff.ICnum);
						valid = 1;

						for (int b = 0; b < *totalStaff; b++)
						{
							fwrite(&allStaffInfo[b], sizeof(Staff), 1, fileModifyRecord);
						}

						//Count of modify + 1
						*countStaff3 += 1;
					}
					else if (toupper(confirmContinue) == 'N')
					{
						printf("Please enter the new IC number again\n");
					}
					else if (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N')
					{
						printf("You can enter 'Y' or 'N' only ! Please enter again\n");
					}
				} while (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N');

			} while (toupper(confirmContinue) == 'N');
		}

		//Close the file
		fclose(fileModifyRecord);

		do
		{
			//Ask user want continue to modify the records or not
			rewind(stdin);
			printf("\nDo you want to continue to modify the more information of the staff %s (Y/N) : ", PreviousStaff.staffID);
			scanf("%c", &addConfirm);
			if (toupper(addConfirm) == 'Y')
			{
				printf("\n");
			}
			else if (toupper(addConfirm) != 'Y' && toupper(addConfirm) != 'N')
			{
				printf("You can enter 'Y' or 'N' only ! Please enter again\n");
			}
		} while (toupper(addConfirm) != 'Y' && toupper(addConfirm) != 'N');
	}

	//Store the character 'N' into pointer to make sure the looping can run in main function
	*confirmToContinue = addConfirm;
}

//Delete function of the administrative module (Jong Xuan Jie)
void deleteAdminRecord(int* totalStaff, char* confirmToContinue, int* countStaff4) {
	Staff deleteStaff;
	int i, valid = 0;
	char addConfirm, confirmContinue = 'Y';

	while (valid == 0 || toupper(confirmContinue) == 'Y' || toupper(addConfirm) == 'N')
	{
		//Prompt the user input the staff ID that need delete the information of the staff ID
		rewind(stdin);
		printf("Enter the staff ID that you want delete : ");
		scanf("%s", &deleteStaff.staffID);

		do
		{
			//Ask the user confirm to delete the information of the staff or not
			rewind(stdin);
			printf("\nDo you confirm delete the information of Staff %s (Y/N) : ", deleteStaff.staffID);
			scanf("%c", &addConfirm);

			if (toupper(addConfirm) == 'Y')
			{
				for (i = 0; i < *totalStaff; i++)
				{
					//If the staff record found, valid will = 1
					if (strcmp(deleteStaff.staffID, allStaffInfo[i].staffID) == 0)
					{
						valid = 1;
						break;
					}
					else
					{
						valid = 0;
					}
				}

				if (valid == 1)
				{
					//Change the element(s) after the staff that will need delete 
					for (int j = i; j < *totalStaff; j++)
					{
						allStaffInfo[i] = allStaffInfo[i + 1];
					}

					//Total staff will - 1
					*totalStaff -= 1;

					//Count of delete + 1
					*countStaff4 += 1;

					//Open the file to overwrite the new staff record(s)
					FILE* deleteAdmin;
					deleteAdmin = fopen("administrativeStaff.bin", "wb");
					if (!deleteAdmin)
					{
						printf("Unable open the file\n\n");
						exit(-1);
					}

					//Rewrite the records in file
					for (i = 0; i < *totalStaff; i++)
					{
						fwrite(&allStaffInfo[i], sizeof(Staff), 1, deleteAdmin);
					}

					//Close the file
					fclose(deleteAdmin);

					do
					{
						//Ask user want to continue to delete the record of the staff or not
						rewind(stdin);
						printf("\nDo you want to continue to delete the information of other TARUC Staff (Y/N) : ");
						scanf("%c", &confirmContinue);

						if (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N')
						{
							printf("You can only enter Y or N ! Please enter again\n");
						}
					} while (toupper(confirmContinue) != 'Y' && toupper(confirmContinue) != 'N');
				}
				else
				{
					printf("Staff ID not found ! Please enter again\n\n");
				}
			}
			else if (toupper(addConfirm) != 'N' && toupper(addConfirm) != 'Y')
			{
				printf("You can only enter Y or N ! Please enter again\n");
			}
			else if (toupper(addConfirm) == 'N')
			{
				printf("Please enter the Staff ID again\n\n");
			}

		} while (toupper(addConfirm) != 'N' && toupper(addConfirm) != 'Y');
	}

	//Store the character 'N' into pointer to make sure the looping can run in main function
	*confirmToContinue = confirmContinue;
}

//Report function of the administrative module (Jong Xuan Jie)
void reportAdminRecord(int* totalStaff, char* confirmToContinue, int* countStaff, int* countStaff2, int* countStaff3, int* countStaff4) {
	int staffAvailable;
	double perStaff;

	//Calculate the percentage of the staff that had been used
	perStaff = ((double)*totalStaff / MAX_NUM_RECORD_STAFF) * 100.00;

	//Calculate the number of staff that still available
	staffAvailable = MAX_NUM_RECORD_STAFF - *totalStaff;

	printf("\t+-------------------------------------------------------------+\n");
	printf("\t%-9s%43s%11s\n", "|", "Report of the Record(s) of TARUC Staff(s)", "|");
	printf("\t+-------------------------------------------------------------+\n");
	printf("\t%-3s%-48s%-5s%d%5s\n", "|", "Total staff record(s) that still available", ":", staffAvailable, "|");
	printf("\t+-------------------------------------------------------------+\n");
	printf("\t%-3s%-48s%-2s%.2f%%%4s\n", "|", "Percentage of the staff record(s) had been used", ":", perStaff, "|");

	//If count of add had, display the report of add
	if (*countStaff > 0)
	{
		printf("\t+-------------------------------------------------------------+\n");
		printf("\t%-3s%-48s%-5s%d%6s\n", "|", "Total record(s) had been add", ":", *countStaff, "|");
	}

	//If count of search had, display the report of search
	if (*countStaff2 > 0)
	{
		printf("\t+-------------------------------------------------------------+\n");
		printf("\t%-3s%-48s%-5s%d%6s\n", "|", "Total record(s) had been search", ":", *countStaff2, "|");
	}

	//If count of modify had, display the report of modify
	if (*countStaff3 > 0)
	{
		printf("\t+-------------------------------------------------------------+\n");
		printf("\t%-3s%-48s%-5s%d%6s\n", "|", "Total record(s) had been modify", ":", *countStaff3, "|");
	}

	//If count of delete had, display the report of delete
	if (*countStaff4 > 0)
	{
		printf("\t+-------------------------------------------------------------+\n");
		printf("\t%-3s%-48s%-5s%d%6s\n", "|", "Total record(s) had been delete", ":", *countStaff4, "|");
	}
	printf("\t+-------------------------------------------------------------+\n");

	//Store the character 'N' into pointer to make sure the looping can run in main function
	*confirmToContinue = 'N';
}

//Display function of the administrative module (Jong Xuan Jie)
void displayAdminRecord(int* totalStaff, char* confirmToContinue) {

	//Display the information of all staff
	printf("\t+-------------------------------------------------------------------------------------------------------------------------------------------+\n");
	printf("\t%-41s%59s%41s\n", "+", "The Information of Administrative Staff(s) in TARUC Collage", "+");
	printf("\t+--------+----------------------+-----------------+-------+------------------------------------------+--------------------+-----------------+\n");
	printf("\t%s%8s%-4s%14s%6s%17s%s%7s%-9s%16s%9s%18s%3s%13s%5s\n",
		"|", "Staff ID", "|", "Name of Staff", "|", "Position of TARUC", "|", "Faculty", "|", "Address of the TARUC Staff", "|", "Contact Number", "|", "IC Number", "|");
	printf("\t+--------+----------------------+-----------------+-------+------------------------------------------+--------------------+-----------------+\n");

	for (int i = 0; i < *totalStaff; i++)
	{
		printf("\t%-2s%-7s%-2s%-21s%-2s%-16s%-2s%-6s%-2s%-41s%-2s%-19s%-2s%-15s%2s\n",
			"|", allStaffInfo[i].staffID, "|", allStaffInfo[i].name, "|", allStaffInfo[i].position, "|", allStaffInfo[i].faculty, "|", allStaffInfo[i].address, "|", allStaffInfo[i].contactNum, "|", allStaffInfo[i].ICnum, "|");
	}

	printf("\t+--------+----------------------+-----------------+-------+------------------------------------------+--------------------+-----------------+\n");
	printf("\t%-58sTotal Staff Record(s) : %d%57s\n", "+", *totalStaff, "+");
	printf("\t+-------------------------------------------------------------------------------------------------------------------------------------------+\n");

	//Store the character 'N' into pointer to make sure the looping can run in main function
	*confirmToContinue = 'N';
}

//Menu of the modify function of the administrative module (Jong Xuan Jie)
int menuOfModify(int choiceOfMenu) {

	//When choice is more than or equal to 9 will start looping to prompt the user input the choice again
	while (choiceOfMenu >= 9) {
		printf("\n\t+-----------------------------------------------------+\n");
		printf("\t%-13s%-30s%12s\n", "|", "Modify MENU of the TARUC Staff", "|");
		printf("\t+-----------------------------------------------------+\n");
		printf("\t%-6s%-48s%s\n", "|", "1. Modify the ID of TARUC Staff", "|");
		printf("\t%-6s%-48s%s\n", "|", "2. Modify the Password of TARUC Staff", "|");
		printf("\t%-6s%-48s%s\n", "|", "3. Modify the Name of TARUC Staff", "|");
		printf("\t%-6s%-48s%s\n", "|", "4. Modify the Position of TARUC Staff", "|");
		printf("\t%-6s%-48s%s\n", "|", "5. Modify the Faculty of TARUC Staff", "|");
		printf("\t%-6s%-48s%s\n", "|", "6. Modify the Address of TARUC Staff", "|");
		printf("\t%-6s%-48s%s\n", "|", "7. Modify the Contact Number of TARUC Staff", "|");
		printf("\t%-6s%-48s%s\n", "|", "8. Modify the IC number of TARUC Staff", "|");
		printf("\t+-----------------------------------------------------+\n\n");

		printf("What is your choose --> ");
		scanf("%d", &choiceOfMenu);

		if (choiceOfMenu >= 9)
		{
			printf("Wrong choice ! Please choose again\n");
		}
	}

	//Return the value of choice
	return choiceOfMenu;
}

//Menu of the search function of the administrative module (Jong Xuan Jie)
int menuOfSearch(int choiceOfMenu)
{
	//When choice is more than or equal to 4 will start looping to prompt the user input the choice again
	while (choiceOfMenu >= 4) {
		printf("\n\t+-------------------------------------------------------------+\n");
		printf("\t%-16s%-46s%s\n", "|", "Search MENU of the TARUC Staff", "|");
		printf("\t+-------------------------------------------------------------+\n");
		printf("\t%s%-61s%s\n", "|", "1. Search the Information of Staff by using TARUC Staff ID", "|");
		printf("\t%s%-61s%s\n", "|", "2. Search the Information of Staff by using TARUC Staff Name", "|");
		printf("\t%s%-61s%s\n", "|", "3. Exit the program", "|");
		printf("\t+-------------------------------------------------------------+\n\n");

		printf("What is your choose --> ");
		scanf("%d", &choiceOfMenu);

		if (choiceOfMenu >= 4) {
			printf("Wrong choice ! Please choose again\n");
		}
	}

	//Return the value of choice
	return choiceOfMenu;
}

//Menu after login and all sub functions of the administrative module (Jong Xuan Jie)
int menuAfterLogin(int choiceOfMenu) {

	//When choice is more than or equal to 8 will start looping to prompt the user input the choice again
	while (choiceOfMenu >= 8)
	{
		printf("\n\t+---------------------------------------+\n");
		printf("\t%-5s%-35s%s\n", "|", "Menu of the Administrative Staff", "|");
		printf("\t+---------------------------------------+\n");
		printf("\t%s%-39s%s\n", "|", "1. Add the information of the New Staff", "|");
		printf("\t%s%-39s%s\n", "|", "2. Search the record(s) of the Staff", "|");
		printf("\t%s%-39s%s\n", "|", "3. Modify the information of the Staff", "|");
		printf("\t%s%-39s%s\n", "|", "4. Display all information of all Staff", "|");
		printf("\t%s%-39s%s\n", "|", "5. Display the report of the Staff", "|");
		printf("\t%s%-39s%s\n", "|", "6. Delete the record(s) of the Staff", "|");
		printf("\t%s%-39s%s\n", "|", "7. Exit the program", "|");
		printf("\t+---------------------------------------+\n");
		printf("\nWhat is your choose --> ");
		scanf("%d", &choiceOfMenu);

		if (choiceOfMenu >= 8) {
			printf("Wrong choice ! Please choose again\n");
		}
	}

	//Return the value of choice
	return choiceOfMenu;
}

//Logo (Ryan Chan Joon Yew)
void logo(){
	printf("*************************************************\n");
	printf("******             ***        ***          ******\n");
	printf("*****              ***        ***           *****\n");
	printf("****               ***        ***            ****\n");
	printf("***                ***        ***             ***\n");
	printf("**                 ***        ***              **\n");
	printf("*                  ***        ***               *\n");
	printf("**                 ***        ***              **\n");
	printf("***                ***        ***             ***\n");
	printf("****               ***        ***            ****\n");
	printf("*****              ***        ***           *****\n");
	printf("******             ***        ***          ******\n");
	printf("*************************************************\n");
}

//Visitor Information's main function module (Ryan Chan Joon Yew)
void visitorInformation() {
	int choice;

	choice = rMenu();

	do {
		//Add display search modify delete
		switch (choice) {
		case 1: {
			addVisitor();
			choice = rMenu();
			break;
		}
		case 2: {
			displayVisitorRecord();
			choice = rMenu();
			break;
		}
		case 3: {
			searchVisitor();
			choice = rMenu();
			break;
		}
		case 4: {
			modifyVisitorRecord();
			choice = rMenu();
			break;
		}
		case 5: {
			deleteVisitorRecord();
			choice = rMenu();
			break;
		}
		case 6: {
			printf("\nThank you for using our system!!\n");
			exit(0);
			break;
		}
		default: {
			printf("\n\nPLEASE ENTER VALID INPUT ONLY!!\n\n");
			choice = rMenu();
		}
		}
	} while (choice != 6);

	system("pause");
}

//Add function for visitor information module (Ryan Chan Joon Yew)
void addVisitor() {
	VisitorInfo visitor; //Structure Initialization

	//Variable Initialization
	char selection, selection2, selection3, selection4, selection5;
	int recordAdded = 0;

	//File Pointers
	FILE* fPtr;

	//File Open 
	fPtr = fopen("visitorRecord.dat", "ab");

	//File Opening Checking
	if (fPtr == NULL) {
		printf("\nUnable to open file \n\n");
		exit(-1);
	}

	//Ask the user if they want to add visitor record
	printf("Add visitor record? \n");
	printf("Y = Yes ||  N = No\n\n");
	printf("Selection > ");
	rewind(stdin);
	scanf("%c", &selection);

	//Switch Statement for validation
	do {
		switch (toupper(selection)) {
		case 'Y': {

			//Gets Visitor Name from user
			printf("\nEnter visitor's name > ");
			rewind(stdin);
			scanf("%[^\n]", &visitor.name);

			//Gets Visitor IC from user
			printf("Enter visitor's IC number (000000-00-0000) > ");
			rewind(stdin);
			scanf("%s", &visitor.icNum);


			//Gets Phone Number from user
			printf("Enter visitor's phone number (000-000-0000) > ");
			rewind(stdin);
			scanf("%s", &visitor.phoneNumber);

			//Ask users whether they wanted to see the reference before input
			printf("\nDo you want to see the list of state before entering home state?\n");
			printf("Y = Yes || N = No \n\n");
			printf("Selection > ");
			rewind(stdin);
			scanf("%c", &selection2);

			//Call Home State input function with input and output parameter
			inputHomeState(selection2, &visitor.homeState);

			//Ask user whether they wanted to see the reference before input
			printf("\nDo you want to see the visitor category menu?\n");
			printf("Y = Yes || N = No \n\n");
			printf("Selection > ");
			rewind(stdin);
			scanf("%c", &selection3);

			//Call Visitor Category input function with input and output parameter
			inputVisitorCategory(selection3, &visitor.visitorCategory, &visitor.studentID, &visitor.staffID);


			//Ask users whether they wanted to see the reference before input
			printf("\nDo you want to see the venue list?\n");
			printf("Y = Yes || N = No \n\n");
			printf("Selection > ");
			rewind(stdin);
			scanf("%c", &selection4);

			//Call Venue input function with input and output parameter
			inputVenue(selection4, &visitor.venue);


			printf("Are you sure to Add Visitor Record? \n");
			printf("Y = yes || N = No\n\n");
			printf("Selection > ");
			rewind(stdin);
			scanf("%c", &selection5);
			if (toupper(selection5) == 'Y') {
				fwrite(&visitor, sizeof(visitor), 1, fPtr);
				recordAdded++;
				printf("\n Record sucessfully added\n");
				printf("%\n%d records added.\n\n", recordAdded);
			}


			else if (toupper(selection5) == 'N') {
				printf("\n%d records added.\n\n", recordAdded);
			}

			else {
				printf("\n\nPlease Enter Y or N only\n\n");
			}

			//Ask the user if they want to add visitor record
			printf("Add visitor record? \n");
			printf("Y = Yes ||  N = No\n\n");
			printf("Selection > ");
			rewind(stdin);
			scanf("%c", &selection);
			break;
		}


		case 'N': {
			printf("\n\n%d records added.\n\n", recordAdded);
			break;
		}
		default: {
			printf("\n\nPlease enter Y or N only!!\n\n");
			printf("Add visitor record? \n");
			printf("Y = Yes ||  N = No\n\n");
			printf("Selection > ");
			rewind(stdin);
			scanf("%c", &selection);
		}
		}
	} while (toupper(selection) == 'Y' && toupper(selection) != 'N');
	fclose(fPtr);
}

//Search function for visitor information module (Ryan Chan Joon Yew)
void searchVisitor() {
	VisitorInfo visitorSearch[100];
	int index = 0, visitorCount, recordsCount = 0, found = 0;
	char vVenue[60], visitorType[30], state[30], searchName[30];
	FILE* fptr;
	fptr = fopen("visitorRecord.dat", "rb");
	if (fptr == NULL) {
		printf("\nUnable to open file! \n");
		exit(-1);
	}
	printf("Enter name to search > ");
	rewind(stdin);
	scanf("%[^\n]", &searchName);

	while (fread(&visitorSearch[index], sizeof(VisitorInfo), 1, fptr) != 0) {
		index++;
	}
	fclose(fptr);

	visitorCount = index;

	printf("Search for %s\n", searchName);
	printf("%-25s %-16s %-14s %-12s %-26s %-25s %-11s %-11s\n", "Name", "IC Number", "Phone Number", "Category", "Venue", "Hometown", "Student ID", "Staff ID");
	printf("%-25s %-16s %-14s %-12s %-26s %-25s %-11s %-11s\n", "====", "=========", "============", "========", "=====", "========", "==========", "========");

	for (index = 0; index < visitorCount; index++) {
		if (strcmp(strupr(searchName), strupr(visitorSearch[index].name)) == 0) {
			found = 1;
			chgInfoFromNumToWord(index, visitorSearch[index].homeState, visitorSearch[index].venue, visitorSearch[index].visitorCategory, &state, &vVenue, &visitorType);
			printf("%-25s %-16s %-14s %-12s %-26s %-25s %-11s %-11s\n", visitorSearch[index].name, visitorSearch[index].icNum, visitorSearch[index].phoneNumber, visitorType, vVenue, state, visitorSearch[index].studentID, visitorSearch[index].staffID);
			recordsCount++;
		}
	}

	if (found == 0) {
		printf("\nRecord not found.\n");
	}
	printf("\n%d records found out of %d\n\n", recordsCount, visitorCount);
}

//Modify function for visitor information module (Ryan Chan Joon Yew)
void modifyVisitorRecord() {
	VisitorInfo visitor[100];
	VisitorInfo visitorMod;
	int index = 0, visitorCount, found = 0, selection2, selection3, selection4, modifiedCount = 0;
	char state[30], vVenue[60], visitorType[30], confirm, confirm2;

	FILE* fptr;
	fptr = fopen("visitorRecord.dat", "rb");
	if (fptr == NULL) {
		printf("Unable to open file! \n");
		exit(-1);
	}

	while (fread(&visitor[index], sizeof(VisitorInfo), 1, fptr)) {
		index++;
	}

	visitorCount = index;
	fclose(fptr);

	printf("\n Enter Name of the visitor to be modified > ");
	rewind(stdin);
	scanf("%[^\n]", visitorMod.name);

	do {
		for (index = 0; index < visitorCount; index++) {
			if (strcmp(strupr(visitorMod.name), strupr(visitor[index].name)) == 0) {
				found = 1;
				printf("%-25s %-16s %-14s %-12s %-26s %-25s %-11s %-11s\n", "Name", "IC Number", "Phone Number", "Category", "Venue", "Hometown", "Student ID", "Staff ID");
				printf("%-25s %-16s %-14s %-12s %-26s %-25s %-11s %-11s\n", "====", "=========", "============", "========", "=====", "========", "==========", "========");
				chgInfoFromNumToWord(index, visitor[index].homeState, visitor[index].venue, visitor[index].visitorCategory, &state, &vVenue, &visitorType);
				printf("%-25s %-16s %-14s %-12s %-26s %-25s %-11s %-11s\n", visitor[index].name, visitor[index].icNum, visitor[index].phoneNumber, visitorType, vVenue, state, visitor[index].studentID, visitor[index].staffID);

				//Gets Visitor Name from user
				printf("Enter visitor's name > ");
				rewind(stdin);
				scanf("%[^\n]", &visitorMod.name);

				//Gets Visitor IC from user
				printf("Enter visitor's IC number (000000-00-0000) > ");
				rewind(stdin);
				scanf("%s", &visitorMod.icNum);


				//Gets Phone Number from user
				printf("Enter visitor's phone number (000-000-0000) > ");
				rewind(stdin);
				scanf("%s", &visitorMod.phoneNumber);

				//Ask users whether they wanted to see the reference before input
				printf("\nDo you want to see the list of state before entering home state?\n");
				printf("Y = Yes || N = No \n\n");
				printf("Selection > ");
				rewind(stdin);
				scanf("%c", &selection2);

				//Call Home State input function with input and output parameter
				inputHomeState(selection2, &visitorMod.homeState);

				//Ask user whether they wanted to see the reference before input
				printf("\nDo you want to see the visitor category menu?\n");
				printf("Y = Yes || N = No \n\n");
				printf("Selection > ");
				rewind(stdin);
				scanf("%c", &selection3);

				//Call Visitor Category input function with input and output parameter
				inputVisitorCategory(selection3, &visitorMod.visitorCategory, &visitorMod.studentID, &visitorMod.staffID);


				//Ask users whether they wanted to see the reference before input
				printf("\nDo you want to see the venue list?\n");
				printf("Y = Yes || N = No \n\n");
				printf("Selection > ");
				rewind(stdin);
				scanf("%c", &selection4);

				//Call Venue input function with input and output parameter
				inputVenue(selection4, &visitorMod.venue);


				printf("Confirm modify?\n");
				printf("(Y = yes || Any other key = No)\n\n");
				printf("Selection > ");
				rewind(stdin);
				scanf("%c", &confirm);
				if (toupper(confirm) == 'Y') {
					visitor[index] = visitorMod;

					printf("%-25s %-16s %-14s %-12s %-26s %-25s %-11s %-11s\n", "Name", "IC Number", "Phone Number", "Category", "Venue", "Hometown", "Student ID", "Staff ID");
					printf("%-25s %-16s %-14s %-12s %-26s %-25s %-11s %-11s\n", "====", "=========", "============", "========", "=====", "========", "==========", "========");
					chgInfoFromNumToWord(index, visitor[index].homeState, visitor[index].venue, visitor[index].visitorCategory, &state, &vVenue, &visitorType);
					printf("%-25s %-16s %-14s %-12s %-26s %-25s %-11s %-11s\n", visitor[index].name, visitor[index].icNum, visitor[index].phoneNumber, visitorType, vVenue, state, visitor[index].studentID, visitor[index].staffID);
					modifiedCount++;
				}
			}
		}
		if (found == 0) {
			printf("Visitor not found. \n");
		}

		printf("Any other visitor record to modify? (Y = yes || N = no) > ");
		rewind(stdin);
		scanf("%c", &confirm2);

		if (toupper(confirm2) == 'Y') {
			printf("\n Enter Name of the visitor to be modified > ");
			rewind(stdin);
			scanf("%[^\n]", visitorMod.name);
		}
		else if (toupper(confirm2) != 'N' && toupper(confirm2) != 'Y') {
			while (toupper(confirm2) != 'N' && toupper(confirm2) != 'Y') {
				printf("Please enter Y or N only!\n");
				printf("Any other visitor record to modify? (Y = yes || N = no) > ");
				rewind(stdin);
				scanf("%c", &confirm2);
			}
			if (toupper(confirm2) == 'Y') {
				printf("\n Enter Name of the visitor to be modified > ");
				rewind(stdin);
				scanf("%[^\n]", visitorMod.name);
			}
		}
	} while (toupper(confirm2) == 'Y' || toupper(confirm2) != 'N');

	printf("%d records modified.\n", modifiedCount);

	fptr = fopen("visitorRecord.dat", "wb");
	if (fptr == NULL) {
		printf("Unable to open file! \n");
		exit(-1);
	}

	for (index = 0; index < visitorCount; index++) {
		fwrite(&visitor[index], sizeof(VisitorInfo), 1, fptr);
	}

	fclose(fptr);
}

//Delete function for visitor information module (Ryan Chan Joon Yew)
void deleteVisitorRecord() {
	VisitorInfo visitor[100];
	VisitorInfo visitorDel;
	int index = 0, visitorCount, found = 0, deleteCount = 0, j = 0;
	char state[30], vVenue[60], visitorType[30], confirm, confirm2;

	FILE* fptr;
	fptr = fopen("visitorRecord.dat", "rb");
	if (fptr == NULL) {
		printf("Unable to open file! \n");
		exit(-1);
	}

	while (fread(&visitor[index], sizeof(VisitorInfo), 1, fptr)) {
		index++;
	}

	visitorCount = index;
	fclose(fptr);

	printf("\n Enter Name of the visitor to be deleted > ");
	rewind(stdin);
	scanf("%[^\n]", &visitorDel.name);

	printf("Sure to delete?\n");
	printf("(Y = Yes || N = No)\n\n");
	printf("Selection >");
	rewind(stdin);
	scanf("%c", &confirm);

	do {
		if (toupper(confirm) == 'Y') {

			for (index = 0; index < visitorCount; index++) {
				if (strcmp(strupr(visitorDel.name), strupr(visitor[index].name)) == 0) {
					found = 1;
					for (j = index; j < visitorCount; j++) {
						visitor[j] = visitor[j + 1];
					}

					deleteCount++;
					visitorCount--;

					printf("%-25s %-16s %-14s %-12s %-26s %-25s %-11s %-11s\n", "Name", "IC Number", "Phone Number", "Category", "Venue", "Hometown", "Student ID", "Staff ID");
					printf("%-25s %-16s %-14s %-12s %-26s %-25s %-11s %-11s\n", "====", "=========", "============", "========", "=====", "========", "==========", "========");

					for (index = 0; index < visitorCount; index++) {
						chgInfoFromNumToWord(index, visitor[index].homeState, visitor[index].venue, visitor[index].visitorCategory, &state, &vVenue, &visitorType);
						printf("%-25s %-16s %-14s %-12s %-26s %-25s %-11s %-11s\n", visitor[index].name, visitor[index].icNum, visitor[index].phoneNumber, visitorType, vVenue, state, visitor[index].studentID, visitor[index].staffID);
					}
				}
			}

			printf("%d records deleted\n", deleteCount);
			if (found == 0) {
				printf("Visitor not found. \n");
			}

			printf("Any other visitor record to delete? (Y = yes || N = no) > ");
			rewind(stdin);
			scanf("%c", &confirm2);

			if (toupper(confirm2) == 'Y') {
				printf("\n Enter Name of the visitor to be deleted > ");
				rewind(stdin);
				scanf("%[^\n]", visitorDel.name);

				printf("Sure to delete?\n");
				printf("(Y = Yes || N = No)\n\n");
				printf("Selection >");
				rewind(stdin);
				scanf("%c", &confirm2);
			}


			else if (toupper(confirm2) != 'N' && toupper(confirm2) != 'Y') {
				while (toupper(confirm2) != 'N' && toupper(confirm2) != 'Y') {
					printf("Any other visitor record to delete? (Y = yes || N = no) > ");
					rewind(stdin);
					scanf("%c", &confirm);
				}
				if (toupper(confirm2) == 'Y') {
					printf("\n Enter Name of the visitor to be deleted > ");
					rewind(stdin);
					scanf("%[^\n]", visitorDel.name);
				}
			}
		}


	} while (toupper(confirm2) == 'Y' || toupper(confirm2) != 'N');

	printf("%d records deleted.\n", deleteCount);

	fptr = fopen("visitorRecord.dat", "wb");
	if (fptr == NULL) {
		printf("Unable to open file! \n");
		exit(-1);
	}

	for (index = 0; index < visitorCount; index++) {
		fwrite(&visitor[index], sizeof(VisitorInfo), 1, fptr);
	}

	fclose(fptr);
}

//Display function for visitor information module (Ryan Chan Joon Yew)
void displayVisitorRecord() {
	VisitorInfo visitor[100];
	int index = 0, visitorCount;
	char state[30], vVenue[60], visitorType[30];

	FILE* fPtr;

	char fileName[40];

	printf("Enter file name > ");
	rewind(stdin);
	scanf("%s", &fileName);

	fPtr = fopen(fileName, "rb");

	if (fPtr == NULL) {
		printf("Unable to open the file! \n");
		exit(-1);
	}

	printf("%-25s %-16s %-14s %-12s %-26s %-25s %-11s %-11s\n", "Name", "IC Number", "Phone Number", "Category", "Venue", "Hometown", "Student ID", "Staff ID");
	printf("%-25s %-16s %-14s %-12s %-26s %-25s %-11s %-11s\n", "====", "=========", "============", "========", "=====", "========", "==========", "========");

	while (fread(&visitor[index], sizeof(VisitorInfo), 1, fPtr) != 0) {
		index++;
	}

	visitorCount = index;
	for (index = 0; index < visitorCount; index++) {
		chgInfoFromNumToWord(index, visitor[index].homeState, visitor[index].venue, visitor[index].visitorCategory, &state, &vVenue, &visitorType);
		printf("%-25s %-16s %-14s %-12s %-26s %-25s %-11s %-11s\n", visitor[index].name, visitor[index].icNum, visitor[index].phoneNumber, visitorType, vVenue, state, visitor[index].studentID, visitor[index].staffID);
	}
	printf("\n\nTotal Visitor Records = %d\n\n", visitorCount);

	fclose(fPtr);

}

//Change from integer to string function (Ryan Chan Joon Yew)
void chgInfoFromNumToWord(int index, int homestate, int venue, int visitorCategory, char* state[30], char* vVenue[60], char* visitorType[30]) {
	switch (homestate) {
	case 1: {
		strcpy(state, "Malacca");
		break;
	}
	case 2: {
		strcpy(state, "Sarawak");
		break;
	}
	case 3: {
		strcpy(state, "Sabah");
		break;
	}
	case 4: {
		strcpy(state, "Penang");
		break;
	}
	case 5: {
		strcpy(state, "Terengganu");
		break;
	}
	case 6: {
		strcpy(state, "Kelantan");
		break;
	}
	case 7: {
		strcpy(state, "Johor");
		break;
	}
	case 8: {
		strcpy(state, "Kedah");
		break;
	}
	case 9: {
		strcpy(state, "Perlis");
		break;
	}
	case 10: {
		strcpy(state, "Perak");
		break;
	}
	case 11: {
		strcpy(state, "Selangor");
		break;
	}
	case 12: {
		strcpy(state, "Negeri Sembilan");
		break;
	}
	case 13: {
		strcpy(state, "Pahang");
		break;
	}
	case 14: {
		strcpy(state, "Wilayah Persekutuan");
		break;
	}
	default: {
		printf("\n\nState is not in the list!!\n\n");
	}
	}

	switch (venue) {
	case 1: {
		strcpy(vVenue, "The Red Bricks Cafeteria");
		break;
	}
	case 2: {
		strcpy(vVenue, "Yum Yum Cafeteria");
		break;
	}
	case 3: {
		strcpy(vVenue, "Fort Margherita Cafe");
		break;
	}
	case 4: {
		strcpy(vVenue, "Casuarina Cafe");
		break;
	}
	case 5: {
		strcpy(vVenue, "Memory Full House Cafe");
		break;
	}
	case 6: {
		strcpy(vVenue, "Tun Tan Siew Sin Building");
		break;
	}
	case 7: {
		strcpy(vVenue, "Cyber Centre");
		break;
	}
	case 8: {
		strcpy(vVenue, "University College Hall");
		break;
	}
	case 9: {
		strcpy(vVenue, "Library");
		break;
	}
	case 10: {
		strcpy(vVenue, "Sport Complex");
		break;
	}
	case 11: {
		strcpy(vVenue, "CPE Centre");
		break;
	}
	case 12: {
		strcpy(vVenue, "East Campus");
		break;
	}
	default: {
		printf("\n\nVenue is not in the list!!\n\n");
	}
	}

	switch (visitorCategory) {
	case 1: {
		strcpy(visitorType, "Staff");
		break;
	}
	case 2: {
		strcpy(visitorType, "Student");
		break;
	}
	case 3: {
		strcpy(visitorType, "Supplier");
		break;
	}
	case 4: {
		strcpy(visitorType, "Repairman");
		break;
	}
	case 5: {
		strcpy(visitorType, "Visitor");
		break;
	}
	}

}

//Venue list (Ryan Chan Joon Yew)
void venueInformation() {
	printf("1.  The Red Bricks Cafeteria\n");
	printf("2.  Yum Yum Cafeteria\n");
	printf("3.  Fort Margherita Cafe\n");
	printf("4.  Casuarina Cafe\n");
	printf("5.  Memory Full House Cafe\n");
	printf("6.  Tun Tan Siew Sin Building\n");
	printf("7.  Cyber Centre\n");
	printf("8.  University College Hall\n");
	printf("9.  Library\n");
	printf("10. Sport Complex\n");
	printf("11. CPE Centre\n");
	printf("12. East Campus\n");
}

//Visitor Category list (Ryan Chan Joon Yew)
void visitorCategoryInformation() {
	printf("1.  Staff\n");
	printf("2.  Student\n");
	printf("3.  Supplier\n");
	printf("4.  Repairman\n");
	printf("5.  Visitor\n");
}

//State list (Ryan Chan Joon Yew)
void stateInformation() {
	printf("1.  Malacca\n");
	printf("2.  Sarawak\n");
	printf("3.  Sabah\n");
	printf("4.  Penang\n");
	printf("5.  Terengganu\n");
	printf("6.  Kelantan\n");
	printf("7.  Johor\n");
	printf("8.  Kedah\n");
	printf("9.  Perlis\n");
	printf("10. Perak\n");
	printf("11. Selangor\n");
	printf("12. Negeri Sembilan\n");
	printf("13. Pahang\n");
	printf("14. Wilayah Persekutuan\n");
}

// Input venue function (Ryan Chan Joon Yew)
void inputVenue(char selection4, int* venue) {
	//If Yes call menu function and ask user to input home state
	if (toupper(selection4) == 'Y') {
		venueInformation();

		printf("\n\nEnter venue > ");
		rewind(stdin);
		scanf("%d", *&venue);

		//While loop for validation checking
		while (*venue < 1 || *venue > 12) {

			//Display menu and ask user to input again
			venueInformation();
			printf("\n\nPlease enter from 1 to 12 only\n");
			printf("\nEnter venue > ");
			rewind(stdin);
			scanf("%d", *&venue);
		}
	}
	//If No call directly ask user to input home state
	else if (toupper(selection4) == 'N') {
		printf("\nEnter venue > ");
		rewind(stdin);
		scanf("%d", *&venue);

		//Validation Checking
		while (*venue < 1 || *venue > 12) {

			//Display menu and ask user to input again
			venueInformation();
			printf("\n\nPlease enter from 1 to 12 only\n");
			printf("\nEnter venue > ");
			rewind(stdin);
			scanf("%d", *&venue);

		}
	}

	//If user input other than Y and N 
	else {

		//Loop until the user input a valid response
		while (toupper(selection4) != 'Y' && toupper(selection4) != 'N') {
			printf("Please key in Y or N only!!\n");
			printf("\nDo you want to see the venue list\n ");
			printf("Y = Yes || N = No \n");
			printf("Selection > ");
			rewind(stdin);
			scanf("%c", &selection4);
			if (toupper(selection4) == 'Y') {
				venueInformation();
				printf("\n\nEnter venue > ");
				rewind(stdin);
				scanf("%d", *&venue);

				while (*venue < 1 || *venue > 12) {
					venueInformation();
					printf("\n\nPlease enter from 1 to 12 only\n");
					printf("\nEnter venue > ");
					rewind(stdin);
					scanf("%d", *&venue);
				}
			}
			else if (toupper(selection4) == 'N') {
				printf("\nEnter venue > ");
				rewind(stdin);
				scanf("%d", *&venue);
				while (*venue < 1 || *venue > 12) {
					stateInformation();
					printf("\n\nPlease enter from 1 to 14 only\n");
					printf("\nEnter venue > ");
					rewind(stdin);
					scanf("%d", *&venue);
				}
			}
		}
	}
}

//Input visitor category function (Ryan Chan Joon Yew)
void inputVisitorCategory(int selection3, int* visitorCategory, char* studentID[8], char* staffID[7]) {
	//If Yes ask user gets Visitor Category input from user
	if (toupper(selection3) == 'Y') {
		visitorCategoryInformation();

		printf("\n\nEnter visitor's category> ");
		rewind(stdin);
		scanf("%d", *&visitorCategory);

		//If visitor is a staff gets staff ID from user
		if (*visitorCategory == 1) {
			printf("Enter Staff ID > ");
			rewind(stdin);
			scanf("%s", *&staffID);

			strcpy(*&studentID, " ");
		}

		//If visitor is a student gets student ID from user
		else if (*visitorCategory == 2) {
			printf("Enter Student ID > ");
			rewind(stdin);
			scanf("%s", *&studentID);

			strcpy(*&staffID, " ");
		}
		else {

			strcpy(*&staffID, " ");
			strcpy(*&studentID, " ");
		}


		//Validation Checking with while loop
		while (*visitorCategory < 1 || *visitorCategory > 5) {

			//Calls menu function for reference and gets user input again
			visitorCategoryInformation();
			printf("\n\nPlease enter from 1 to 5 only\n");
			printf("\nEnter visitor's category > ");
			rewind(stdin);
			scanf("%d", *&visitorCategory);

			//If visitor is a staff gets staff ID from user
			if (*visitorCategory == 1) {
				printf("Enter Staff ID > ");
				rewind(stdin);
				scanf("%s", *&staffID);

				strcpy(*&studentID, " ");
			}

			//If visitor is a student gets student ID from user
			else if (*visitorCategory == 2) {
				printf("Enter Student ID > ");
				rewind(stdin);
				scanf("%s", *&studentID);

				strcpy(*&staffID, " ");
			}
			else {

				strcpy(*&staffID, " ");
				strcpy(*&studentID, " ");
			}
		}
	}


	//If user does not want to see reference directly get user's input without calling function
	else if (toupper(selection3) == 'N') {
		printf("\n\nEnter visitor's category> ");
		rewind(stdin);
		scanf("%d", *&visitorCategory);

		if (*visitorCategory == 1) {
			printf("Enter Staff ID > ");
			rewind(stdin);
			scanf("%s", *&staffID);

			strcpy(*&studentID, " ");
		}

		else if (*visitorCategory == 2) {
			printf("Enter Student ID > ");
			rewind(stdin);
			scanf("%s", *&studentID);

			strcpy(*&staffID, " ");
		}
		else {

			strcpy(*&staffID, " ");
			strcpy(*&studentID, " ");
		}

		while (*visitorCategory < 1 || *visitorCategory > 5) {
			visitorCategoryInformation();
			printf("\n\nPlease enter from 1 to 5 only\n");
			printf("\nEnter visitor's category > ");
			rewind(stdin);
			scanf("%d", *&visitorCategory);

			if (*visitorCategory == 1) {
				printf("Enter Staff ID > ");
				rewind(stdin);
				scanf("%s", *&staffID);

				strcpy(*&studentID, " ");
			}

			else if (*visitorCategory == 2) {
				printf("Enter Student ID > ");
				rewind(stdin);
				scanf("%s", *&studentID);

				strcpy(*&staffID, " ");
			}
			else {

				strcpy(*&staffID, " ");
				strcpy(*&studentID, " ");
			}
		}
	}

	//If user enter other than Y and N ask user to enter again until there is a valid input
	else {
		while (toupper(selection3) != 'Y' && toupper(selection3) != 'N') {
			printf("Please key in Y or N only!!\n");
			printf("\nDo you want to see the visitor category menu?\n");
			printf("Y = Yes || N = No \n");
			printf("Selection > ");
			rewind(stdin);
			scanf("%c", &selection3);

			if (toupper(selection3) == 'Y') {
				visitorCategoryInformation();

				printf("\n\nEnter visitor's category > ");
				rewind(stdin);
				scanf("%d", *&visitorCategory);

				if (*visitorCategory == 1) {
					printf("Enter Staff ID > ");
					rewind(stdin);
					scanf("%s", *&staffID);

					strcpy(*&studentID, " ");
				}

				else if (*visitorCategory == 2) {
					printf("Enter Student ID > ");
					rewind(stdin);
					scanf("%s", *&studentID);

					strcpy(*&staffID, " ");
				}
				else {

					strcpy(*&staffID, " ");
					strcpy(*&studentID, " ");
				}

				while (*visitorCategory < 1 || *visitorCategory > 5) {
					visitorCategoryInformation();
					printf("\n\nPlease enter from 1 to 5 only\n");
					printf("\nEnter visitor's category > ");
					rewind(stdin);
					scanf("%d", *&visitorCategory);

					if (*visitorCategory == 1) {
						printf("Enter Staff ID > ");
						rewind(stdin);
						scanf("%s", *&staffID);

						strcpy(*&studentID, " ");
					}

					else if (*visitorCategory == 2) {
						printf("Enter Student ID > ");
						rewind(stdin);
						scanf("%s", *&studentID);

						strcpy(*&staffID, " ");
					}
					else {

						strcpy(*&staffID, " ");
						strcpy(*&studentID, " ");
					}
				}
			}
			else if (toupper(selection3) == 'N') {
				printf("\n\nEnter visitor's category> ");
				rewind(stdin);
				scanf("%d", *&visitorCategory);

				if (*visitorCategory == 1) {
					printf("Enter Staff ID > ");
					rewind(stdin);
					scanf("%s", *&staffID);

					strcpy(*&studentID, " ");
				}

				else if (*visitorCategory == 2) {
					printf("Enter Student ID > ");
					rewind(stdin);
					scanf("%s", *&studentID);

					strcpy(*&staffID, " ");
				}
				else {

					strcpy(*&staffID, " ");
					strcpy(*&studentID, " ");
				}

				while (*visitorCategory < 1 || *visitorCategory > 5) {
					stateInformation();
					printf("\n\nPlease enter from 1 to 5 only\n");
					printf("\nEnter visitor's category > ");
					rewind(stdin);
					scanf("%d", *&visitorCategory);
					if (*visitorCategory == 1) {
						printf("Enter Staff ID > ");
						rewind(stdin);
						scanf("%s", *&staffID);

						strcpy(*&studentID, " ");
					}

					else if (*visitorCategory == 2) {
						printf("Enter Student ID > ");
						rewind(stdin);
						scanf("%s", *&studentID);

						strcpy(*&staffID, " ");
					}
					else {

						strcpy(*&staffID, " ");
						strcpy(*&studentID, " ");
					}
				}
			}
		}
	}
}

//Input Home State function (Ryan Chan Joon Yew)
void inputHomeState(char selection2, int* homeState) {
	//If Yes call menu function and ask user to input home state
	if (toupper(selection2) == 'Y') {
		stateInformation();

		printf("\n\nEnter visitor's home state > ");
		rewind(stdin);
		scanf("%d", *&homeState);

		//While loop for validation checking
		while (*homeState < 1 || *homeState > 14) {

			//Display menu and ask user to input again
			stateInformation();
			printf("\n\nPlease enter from 1 to 14 only\n");
			printf("\nEnter visitor's home state > ");
			rewind(stdin);
			scanf("%d", *&homeState);
		}
	}
	//If No call directly ask user to input home state
	else if (toupper(selection2) == 'N') {
		printf("\nEnter visitor's home state > ");
		rewind(stdin);
		scanf("%d", *&homeState);

		//Validation Checking
		while (*homeState < 1 || *homeState > 14) {

			//Display menu and ask user to input again
			stateInformation();
			printf("\n\nPlease enter from 1 to 14 only\n");
			printf("\nEnter visitor's home state > ");
			rewind(stdin);
			scanf("%d", *&homeState);

		}
	}

	//If user input other than Y and N 
	else {

		//Loop until the user input a valid response
		while (toupper(selection2) != 'Y' && toupper(selection2) != 'N') {
			printf("Please key in Y or N only!!\n");
			printf("\nDo you want to see the list of state before entering home state?\n");
			printf("Y = Yes || N = No \n");
			printf("Selection > ");
			rewind(stdin);
			scanf("%c", &selection2);
			if (toupper(selection2) == 'Y') {
				stateInformation();
				printf("\n\nEnter visitor's home state > ");
				rewind(stdin);
				scanf("%d", *&homeState);

				while (*homeState < 1 || *homeState > 14) {
					stateInformation();
					printf("\n\nPlease enter from 1 to 14 only\n");
					printf("\nEnter visitor's home state > ");
					rewind(stdin);
					scanf("%d", *&homeState);
				}
			}
			else if (toupper(selection2) == 'N') {
				printf("\nEnter visitor's home state > ");
				rewind(stdin);
				scanf("%d", *&homeState);
				while (*homeState < 1 || *homeState > 14) {
					stateInformation();
					printf("\n\nPlease enter from 1 to 14 only\n");
					printf("\nEnter visitor's home state > ");
					rewind(stdin);
					scanf("%d", *&homeState);
				}
			}
		}
	}
}

//Visitor Information module menu(Ryan Chan Joon Yew)
int rMenu() {
	int selection;
	GetLocalTime(&time);

	printf("Today's Date : %d/%d/%d at %d:%d \n\n", time.wDay, time.wMonth, time.wYear, time.wHour, time.wMinute);
	printf("Visitor Information Module\n");
	printf("===========================\n");
	printf("\n1. Add Visitor Record\n");
	printf("2. Display Visitor Record\n");
	printf("3. Search Visitor Record\n");
	printf("4. Modify Visitor Record\n");
	printf("5. Delete Visitor Record\n");
	printf("6. Exit\n\n");
	printf("Selection > ");
	rewind(stdin);
	scanf("%d", &selection);

	return selection;
}


//Visit and Exit module (Lee Heng Yong)
void visitAndExit()
{
	char backtoMenu;
	menu();
	backtoMenu = vebackToMenu();
	while ((backtoMenu == 'y') || (backtoMenu == 'Y'))
	{
		system("cls");
		menu();
		backtoMenu = vebackToMenu();
	}
}

//(Lee Heng Yong)
void vemenu()
{
	// Declare Variables
	bool validInput = false;
	int selectedFunction;

	// validation
	while (validInput == false)
	{
		// Display Menu
		printf(" Visits & Exits Menu\n");
		printf(" ===================\n");
		printf(" 1. Add Activity Record\n");
		printf(" 2. Search Activity Record\n");
		printf(" 3. Modify Activity Record\n");
		printf(" 4. Display Activity Record\n");
		printf(" 5. Remove Activity Record\n");
		printf(" 6. Exit\n");

		// Ask user to select
		printf("\nPlease select a Function: ");
		scanf("%d", &selectedFunction);

		// Clear Screen
		system("cls");

		// Input Validation
		if ((selectedFunction == 1) || (selectedFunction == 2) || (selectedFunction == 3) || (selectedFunction == 4) || (selectedFunction == 5) || (selectedFunction == 6))
		{
			validInput = true;
		}
		else
		{
			validInput = false;
			printf("Invalid Input! Please choose only 1 to 6 \n");
			getchar();
		}

		// Funtion Select
		switch (selectedFunction)
		{
		case 1: veadd();
			break;
		case 2: vesearch();
			break;
		case 3: vemodify();
			break;
		case 4: vedisplay();
			break;
		case 5: vedelete();
			break;
		case 6: vebackToMain();
			break;
		}
	}
}

//(Lee Heng Yong)
void veadd()
{
	// Clear Screen
	system("cls");

	// Declare Variables
	Activity act;

	// Open file for ammend
	FILE* fptr;
	fptr = fopen("Activity.txt", "a");
	if (!fptr) {
		printf("Error!!! Unable to open the file.");
		exit(-1);
	}

	// Display Header
	printf("Add Activity Record\n");
	printf("=============================\n");

	// User Input
	printf("Entry Number              : ");
	scanf("%d", &act.visitorNo);
	rewind(stdin);

	printf("Name                      : ");
	gets(act.visitorName);
	rewind(stdin);

	printf("Date Enter(DD:MM:YY)      : ");
	gets(act.dateEntered);
	rewind(stdin);

	printf("Time Enter(HH:MM:SS)      : ");
	gets(act.timeEntered);
	rewind(stdin);

	printf("IC Number(XXXXXX-XX-XXXX) : ");
	gets(act.visitorIC);
	rewind(stdin);

	printf("Phone Number              : ");
	gets(act.visitorPhoneNo);
	rewind(stdin);

	printf("Venue ID                  : ");
	gets(act.venueID);
	rewind(stdin);

	printf("Temperature               : ");
	scanf("%f", &act.visitorTemperature);
	rewind(stdin);

	printf("Time Exit(HH:MM:SS)       : ");
	gets(act.timeExited);
	rewind(stdin);

	// Save to File
	fwrite(&act, sizeof(act), 1, fptr);

	// Print Message
	printf("\n\tData has been recorded!\n");

	// Close File
	fclose(fptr);

	// Capture Enter Key
	getch();
}

//(Lee Heng Yong)
void vesearch()
{
	// Declare Variables
	Activity act;
	int flag = 0, n = 1;

	// Display Header
	printf("Search Activity Record\n");
	printf("====================================\n");

	// User Input
	printf("Entry Number : ");
	scanf("%d", &n);

	// Open File to Read
	FILE* fptr;
	fptr = fopen("Activity.txt", "r");
	if (!fptr) {
		printf("Error!!! Unable to open the file.");
		exit(-1);
	}
	while ((fread(&act, sizeof(act), 1, fptr)) > 0)
	{
		if (act.visitorNo == n)
		{
			printf("====================================\n");
			printf("\nEntry Number               : %d", act.visitorNo);
			printf("\nName of Visitor            : %s", act.visitorName);
			printf("\nDate Enter(DD:MM:YY)       : %s", act.dateEntered);
			printf("\nTime Enter(HH:MM:SS)       : %s", act.timeEntered);
			printf("\nIC Number (XXXXXX-XX-XXXX) : %s", act.visitorIC);
			printf("\nPhone Number               : %s", act.visitorPhoneNo);
			printf("\nVenue ID                   : %s", act.venueID);
			printf("\nTemperature is             : %.1f*C", act.visitorTemperature);
			printf("\nTime Exit(HH:MM:SS) is     : %s", act.timeExited);
			printf("\n\n====================================\n");
			flag = 1;
		}
	}

	// Close File
	fclose(fptr);
	if (flag == 0)
		printf("\n\n Record not exist.\n");
	getch();
}

//(Lee Heng Yong)
void vemodify()
{
	// Declare Variables
	Activity act;
	int no, found = 0;

	// Dsplay Header
	printf("Modify Activity Record\n");
	printf("====================================\n");

	//Open file to Read and Ammend
	FILE* fptr;
	fptr = fopen("Activity.txt", "r+");
	if (!fptr) {
		printf("Error!!! Unable to open the file.");
		exit(-1);
	}

	// User Input
	printf("Please Enter Entry Number  : ");
	scanf("%d", &no);

	while ((fread(&act, sizeof(act), 1, fptr)) > 0 && found == 0)
	{
		if (act.visitorNo == no)
		{
			// Display Current Data
			printf("====================================\n");
			printf("\nEntry Number               : %d", act.visitorNo);
			printf("\nName of Visitor            : %s", act.visitorName);
			printf("\nDate Enter(DD:MM:YY)       : %s", act.dateEntered);
			printf("\nTime Enter(HH:MM:SS)       : %s", act.timeEntered);
			printf("\nIC Number(XXXXXX-XX-XXXX)  : %s", act.visitorIC);
			printf("\nPhone Number               : %s", act.visitorPhoneNo);
			printf("\nVenue ID                   : %s", act.venueID);
			printf("\nTemperature                : %.1f", act.visitorTemperature);
			printf("\nTime Exit(HH:MM:SS)        : %s", act.timeExited);
			printf("\n\n====================================\n");

			// User input New Data
			printf("Please Enter The New Details of Visitor\n");

			printf("Entry Number                : ");
			scanf("%d", &act.visitorNo);
			rewind(stdin);

			printf("Name                        : ");
			gets(act.visitorName);
			rewind(stdin);

			printf("Date Enter (DD:MM:YY)       : ");
			gets(act.dateEntered);
			rewind(stdin);

			printf("Time Enter (HH:MM:SS)       : ");
			gets(act.timeEntered);
			rewind(stdin);

			printf("IC Number (XXXXXX-XX-XXXX)  : ");
			gets(act.visitorIC);
			rewind(stdin);

			printf("Phone Number                : ");
			gets(act.visitorPhoneNo);
			rewind(stdin);

			printf("Venue ID                    : ");
			gets(act.venueID);
			rewind(stdin);

			printf("Temperature                 : ");
			scanf("%f", &act.visitorTemperature);
			rewind(stdin);

			printf("Time Exit(HH:MM:SS)         : ");
			gets(act.timeExited);
			rewind(stdin);

			// Write to file
			fseek(fptr, -(long)sizeof(act), 1);
			fwrite(&act, sizeof(act), 1, fptr);
			printf("\n\t Record Updated\n");
			found = 1;
		}
	}

	// Close File
	fclose(fptr);
	if (found == 0)

		// Print Message
		printf("\n\t Record Not Found \n");
	getch();
}

//(Lee Heng Yong)
void vedisplay()
{
	// Declare Variables
	Activity act;

	// Open file to read
	FILE* fptr;
	fptr = fopen("Activity.txt", "r");
	if (!fptr) {
		printf("Error!!! Unable to open the file.");
		exit(-1);
	}
	// Output
	printf("Display Activity Record\n");
	printf("=================================================================================================================\n");
	printf("|%-6s|%-18s|%-12s|%-12s|%-14s|%-13s|%-8s|%9s|%9s|\n", "Number", "Visitor Name", "Date Entered", "Time Entered", "IC Number", "Phone Number", "Venue ID", "Temperature", "Time Exit");
	while ((fread(&act, sizeof(act), 1, fptr)) > 0)
	{
		printf("|%-6d|%-18s|%-12s|%-12s|%-14s|%-13s|%-8s|%9.1f*C|%9s|\n", act.visitorNo, act.visitorName, act.dateEntered, act.timeEntered, act.visitorIC, act.visitorPhoneNo, act.venueID, act.visitorTemperature, act.timeExited);
	}

	// Close File
	fclose(fptr);
	getch();
}

//(Lee Heng Yong)
void vedelete()
{
	// Declare Variables
	int no;
	Activity act;

	// Open files
	FILE* fptr2;
	FILE* fptr;

	// Display Header
	printf("Remove Activity Record\n");
	printf("====================================\n");

	// User Input
	printf("Entry Number to delete : ");
	scanf("%d", &no);


	// Open Files to Read and Write
	fptr = fopen("Activity.txt", "r");
	if (!fptr) {
		printf("Error!!! Unable to open the file.");
		exit(-1);
	}
	fptr2 = fopen("Temp.txt", "w");
	if (!fptr) {
		printf("Error!!! Unable to open the file.");
		exit(-1);
	}
	rewind(fptr);

	// Swap Out selected data
	while ((fread(&act, sizeof(act), 1, fptr)) > 0)
	{
		if (act.visitorNo != no)
		{
			fwrite(&act, sizeof(act), 1, fptr2);
		}
	}

	// Close the files
	fclose(fptr2);
	fclose(fptr);

	// Delete files
	remove("Activity.txt");

	// Rename the filename
	rename("Temp.txt", "Activity.txt");

	// Ending Message
	printf("\n\tRecord Deleted..\n");
	getch();
}

//(Lee Heng Yong)
char vebackToMenu()
{
	// Declare Variables
	char backtoMenu;

	// Ask user
	printf("Back to menu?\n");
	printf("Y/y - Yes | N/n - No (end program)\n");
	printf("Answer = ");
	rewind(stdin);
	scanf("%c", &backtoMenu);

	// Return Value
	return backtoMenu;
}

//(Lee Heng Yong)
void vebackToMain()
{

}
