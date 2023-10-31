#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// function definitions
void start();
void login();
void registerTeacher();
void mainMenu();
void addStudent();
void deleteStudent();
void changeGrade();
void printGrades();
void choose();
void studentLogin();
void studentMode();

int main() {
	choose();
}

// user chooses which mode
void choose() {
	int choice;

	cout << "              --- GRADES APP --- \n" << endl;
	cout << "	    Press 1 for TEACHER mode " << endl;
	cout << "	    Press 2 for STUDENT mode" << endl;
	cout << "" << endl;
	cin >> choice;

	if (choice == 1) {
		system("cls");
		start();
	}
	else if (choice == 2) {
		system("cls");
		studentLogin();
	}
	else {
		cout << "	    Invalid choice, please try again \n\n" << endl;
		choose();
	}
}

// WELCOME page
// Asks teacher to either LOGIN or REGISTER
void start() {
	int choice;

	cout << "              --- WELCOME --- \n" << endl;
	cout << "	    Press 1 to LOGIN " << endl;
	cout << "	    Press 2 to REGISTER " << endl;
	cout << "" << endl;
	cin >> choice;

	if (choice == 1) {
		login();
	}
	else if (choice == 2) {
		registerTeacher();
	}
	else {
		cout << "	    Invalid choice, please try again \n\n" << endl;
		start();
	}
}

void registerTeacher() {
	string email;
	string password;
	string password2;

	// Teacher enters details 
	cout << "\n\t\t Register \n";
	cout << "\n\t School email address: ";
	cin >> email;
	m:
	cout << "\n\t New password: ";
	cin >> password;
	cout << "\n\t Re-type password: ";
	cin >> password2;
	
	fstream file;

	file.open("records.txt", ios::out | ios::app); // opens file in append mode

	if (password == password2) {
		file << email << " " << password << "\n"; // writes the new student into file
	}
	else {
		cout << "\n\t password didn't match, please try again. \n" << endl;
		goto m; // user will have to create password again
	}
	
	file.close();

	system("cls"); // screen is cleared
	cout << "\n\n\t\t " << " you have been successfully registered " << endl; // displays to user that student was added
	cout << endl;
	
	mainMenu(); // goes to the main menu
}

// teacher is able to login to an existing account
void login() {
	int count = 0;
	string email, password, em, pass;

	cout << "                 --- TEACHER LOGIN --- \n" << endl;
	cout << "	    Enter Email and Password " << endl << endl;
	cout << "	    Email address: ";
	cin >> email;
	cout << "	    Password: ";
	cin >> password;

	ifstream input("records.txt");

	while (input >> em >> pass) { // check each record
		if (em == email && pass == password) { // checks if details entered match the details in the file
			count = 1; // acts as a flag to check if details match
			system("cls");
		}
	}
	input.close();

	if (count == 1) {
		mainMenu(); // if login is successful, user goes to main menu
	}
	else {
		cout << endl;
		cout << "\t Email or password is incorrect, please try again \n";
		cout << endl;
		login(); // user will attempt to login again
	}
}

void mainMenu() {
	int choice;

	cout << "              --- TEACHER GRADING SYSTEM --- \n" << endl;
	cout << "	    Press 1 to ADD NEW STUDENT " << endl;
	cout << "	    Press 2 to DELETE STUDENT " << endl;
	cout << "	    Press 3 to CHANGE GRADE and/or CLASS " << endl;
	cout << "	    Press 4 to PRINT ALL GRADES " << endl;
	cout << "	    Press 5 to LOG OUT " << endl;
	cout << "	    Press 6 to EXIT " << endl;

	cout << " " << endl;
	cin >> choice;

	switch (choice) {
	case 1:
		addStudent();
		break;
	case 2:
		deleteStudent();
		break;
	case 3:
		changeGrade();
		break;
	case 4:
		printGrades();
		break;
	case 5:
		system("cls");
		start(); // user goes back to the welcome page
	case 6:
		exit(0);
	default:
		cout << endl;
		cout << "Invalid choice, taking you back to main menu ... " << endl << endl;
		mainMenu();
		break;
	}
}

void addStudent() {
	int studentID;
	string firstName;
	string lastName;
	string className;
	static char grade;

	// teacher will enter new student details
	cout << "\n\t\t Add new student \n";
	cout << "\n\t Student ID: ";
	cin >> studentID;
	cout << "\n\t Student first name: ";
	cin >> firstName;
	cout << "\n\t Student last name: ";
	cin >> lastName;
	cout << "\n\t Student class: ";
	cin >> className;
	cout << "\n\t Student grade: ";
	cin >> grade;

	fstream file;

	file.open("database.txt", ios::out | ios::app); // opens file in append mode

	file << studentID << " " << firstName << " " << lastName << " " << className << " " << grade << "\n"; // writes the new student into file

	file.close();

	cout << "\n\n\t\t " << firstName << " " << lastName << " has been added" << endl; // displays to user that student was added
	cout << endl;

	mainMenu();
}

void deleteStudent() {
	int studentID;
	int id;
	string fName;
	string lName;
	string c; // class
	char grade;

	vector<string> v;

	int count = 0;

	cout << "\n\t Student ID: ";
	cin >> studentID;

	// change studentID into a string, then into a char so it can be compared with the ID in the file
	string sID = to_string(studentID);
	char charID = sID[0];

	ifstream data("database.txt");
	string line;

	while (data >> id >> fName >> lName >> c >> grade) { // check each record
		if (id == studentID) {
			count = 1; // flag to check if details match
		}
	}
	data.close();

	if (count == 1) {
		data.open("database.txt");
		if (data.is_open()) {
			while (getline(data, line)) {
				v.push_back(line); // adds all records into the vector
			}
			data.close();
		}

		// temporary file to store the records appart from the one that is being deleted
		fstream temp;
		temp.open("database2.txt", ios::out | ios::app);

		for (int i = 0; i < v.size(); i++) {
			string s = v[i];
			char c = (char)s[0]; // student id

			if (c == charID) { // if the record is the one being deleted
				// do nothing
			}
			else {
				temp << v[i] << "\n"; // write the records into the temp file
			}
		}
		temp.close();
		// delete the old file and rename the temp file to the name of the previous one
		remove("database.txt");
		rename("database2.txt", "database.txt");

		cout << "\n	    Student has been deleted" << endl;
		cout << endl;

		m:
		int choice;
		cout << "\n	    Press 1 to go to MAIN MENU " << endl;
		cout << "\n	    Press 2 to go to EXIT " << endl;
		cin >> choice;

		if (choice == 1) {
			mainMenu();
		}
		else if (choice == 2) {
			exit(0);
		}
		else {
			cout << "\n	    Invalid option. please try again. " << endl;
			goto m;
		}

	}
	else {
		cout << endl;
		cout << "\t Student cannot be found or doesn't exist. Please try again. \n";
		deleteStudent();
	}
}

void changeGrade() {
	int studentID;
	int id;
	string fName;
	string lName;
	string c; // class
	char grade;

	vector<string> v;

	int count = 0;

	cout << "\n\t Student ID: ";
	cin >> studentID;

	string sID = to_string(studentID);
	char charID = sID[0];

	ifstream data("database.txt");
	string line;

	while (data >> id >> fName >> lName >> c >> grade) { // check each record
		if (id == studentID) {
			count = 1; // acts as a flag to check if details match
		}
	}
	data.close();

	if (count == 1) {
		data.open("database.txt");
		if (data.is_open()) {
			while (getline(data, line)) {
				v.push_back(line);
			}
			data.close();
		}

		// temporary file 
		fstream temp;
		temp.open("database2.txt", ios::out | ios::app);

		// teacher enters new student details
		cout << "\n\t First name: ";
		string first_name;
		cin >> first_name;

		cout << "\n\t Last name: ";
		string last_name;
		cin >> last_name;

		cout << "\n\t Enter new/old class: ";
		string class_no;
		cin >> class_no;

		cout << "\n\t Enter new/old grade: ";
		string new_grade;
		cin >> new_grade;

		// new student is written into the temporary file
		temp << studentID << " " << first_name << " " << last_name << " " << class_no << " " << new_grade << "\n";

		for (int i = 0; i < v.size(); i++) {
			string s = v[i];
			char c = (char)s[0]; // student id

			if (c == charID) { // all records apart from the student that has been changed is written to temp
				// do nothing
			}
			else {
				temp << v[i] << "\n";
			}
		}
		temp.close();
		// delete the old file and rename the temp file to the name of the previous one
		remove("database.txt");
		rename("database2.txt", "database.txt");

		cout << "\n	    Student details have been changed" << endl;
		cout << endl;

		m:
		int choice;
		cout << "\n	    Press 1 to go to MAIN MENU " << endl;
		cout << "\n	    Press 2 to go to EXIT " << endl;
		cin >> choice;

		if (choice == 1) {
			mainMenu();
		}
		else if (choice == 2) {
			exit(0);
		}
		else {
			cout << "\n	    Invalid option. please try again. " << endl;
			goto m;
		}

	}
	else {
		cout << endl;
		cout << "\t Student cannot be found or doesn't exist. Please try again. \n";
		changeGrade();
	}
}

void printGrades() {
	fstream data;
	data.open("database.txt", ios::in); // 'read mode'

	cout << "              --- GRADES --- \n" << endl;
	cout << "	    ID NAME CLASS GRADE \n" << endl;

	if (data.is_open()) {
		string line;
		while (getline(data, line)) { // stores every line in data into the variable 'line'
			cout << "	    " << line << endl; // print every line
		}
		data.close();
	}

	m:
	int choice;
	cout << "\n	    Press 1 to go to MAIN MENU " << endl;
	cout << "\n	    Press 2 to go to EXIT " << endl;
	cin >> choice;

	if (choice == 1) {
		mainMenu();
	}
	else if (choice == 2) {
		exit(0);
	}
	else {
		cout << "\n	    Invalid option. please try again. " << endl;
		goto m;
	}
}

void studentLogin() {
	int count = 0;
	string email, password, em, pass;

	cout << "                 --- STUDENT LOGIN --- \n" << endl;
	cout << "	    Enter Email and Password " << endl << endl;
	cout << "	    Email address: ";
	cin >> email;
	cout << "	    Password: ";
	cin >> password;

	ifstream input("studentLogin.txt");

	while (input >> em >> pass) { // check each record
		if (em == email && pass == password) { // checks if details entered match the details in the file
			count = 1; // acts as a flag to check if details match
			system("cls");
		}
	}
	input.close();

	if (count == 1) {
		studentMode(); // if login is successful, user goes to main menu
	}
	else {
		cout << endl;
		cout << "\t Email or password is incorrect, please try again \n";
		cout << endl;
		studentLogin(); // user will attempt to login again
	}
}

void studentMode() {
	int studentID;
	int id;
	string fName;
	string lName;
	string c; // class
	char grade;

	vector<string> v;

	int count = 0;

	m:
	cout << endl;
	cout << "	    Enter your unique student ID:  ";
	cin >> studentID;

	string sID = to_string(studentID);
	char charID = sID[0];

	ifstream data("database.txt");
	string line;

	while (data >> id >> fName >> lName >> c >> grade) { // check each record
		if (id == studentID) {

			count = 1; // acts as a flag to check if details match
			cout << "\n You achieved a: " << grade; 
			cout << "\n\n ";

			// prints a different message depending on their grade
			if (grade == 'A') {
				cout << "Amazing job, you're doing great, keep it up " + fName;
			}
			else if (grade == 'B') {
				cout << "Good work, try and push for an A next time " + fName;
			}
			else if (grade == 'C') {
				cout << "Not bad, keep working hard " + fName;
			}
			else {
				cout << "Please attend the before and/or after school intervention sessions for more guidance " + fName;
			}

			break;
		}
	}
	data.close();

	if (count == 0) {
		cout << "\n\t\t Student ID incorrect, or grade has not yet been published by your teacher,";
		cout << "\n\t\t please try again, or contact your teacher. ";
		cout << endl;
		goto m; // student will attemp their ID again
	}

	cout << endl;

	d:
	int choice;
	cout << "\n	    Press 1 to go to START " << endl;
	cout << "\n	    Press 2 to go to EXIT " << endl;
	cin >> choice;

	if (choice == 1) {
		system("cls");
		choose();
	}
	else if (choice == 2) {
		exit(0);
	}
	else {
		cout << "\n	    Invalid option. please try again. " << endl;
		goto d;
	}
}




