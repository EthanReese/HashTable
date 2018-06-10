/*
 *Create a list of students with different properties
 *Date: September 27, 2017
 *Created by: Ethan Reese
 */
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iomanip>

using namespace std;
//Make a struct that stores the information about the student
struct Student{
    char firstName[20];
    char lastName[20];
    int id;
    double gpa;
};

int addStudent(vector<Student*> &students);
void toLowerCase(char (&arr)[7]);
void printStudents(vector<Student*> &students);
void deleteStudents(vector<Student*> &students, int id);


int main(){
    //Make an infinite loop that continues until the user quits
    vector<Student*> students;
    while(true){
        cout << "Please enter one of the command words: Add, Print, Delete, or Quit: ";
      char input[7];
        //Define character arrays with the command words
        char add[7] = "add";
        char print[7] = "print";
        char del[7] = "delete";
        char quit[7] = "quit";
        
        //Create the vector to store the students in 
      
        cin >> input;
	toLowerCase(input);
        //If the input is an add then it needs to run that function
        if(strcmp(input, add) == 0){
            addStudent(students);
        }
        else if(strcmp(input, print) == 0){
		printStudents(students);
        }
        else if(strcmp(input, del) == 0){
		cout << "Enter the id of the student you would like to delete: ";
		int input;
		cin >> input;

		deleteStudents(students, input);
        }
        else if(strcmp(input, quit) == 0){
            return 0;
        }
        else{
            cout << "Invalid input, please pick one of the proper command terms";
        }
    }
}
//Method to add a student to the full set
int addStudent(vector<Student*> &students){
    cout << "Enter first name: ";
    Student *student = new Student();
    cin >> student->firstName;
    cout << "Enter the last name: ";
    cin >> student->lastName;
    cout << "Enter the student's id number: ";
    cin >> student->id;
    cout << "Enter the student's gpa: ";
    cin >> student->gpa;
    students.push_back(student);
    return 0;
}
//Function to make char arrays to lower case
void toLowerCase(char (&arr)[7]){
    for(int i = 0; i < 7; i++){
        arr[i] = tolower(arr[i]);
    }
}
//Function to print out all the students
void printStudents(vector<Student*> &students){
	//Loop through the vector and print out all the student
	for(vector<Student*>::size_type i = 0; i != students.size(); i++){
		cout << students.at(i)->firstName << " " << students.at(i)->lastName;
		cout << ", "<< students.at(i)->id << ", ";
		cout.setf(ios::fixed);	
		cout << fixed << setprecision(2) << students.at(i)->gpa << endl;

	}

}
//Function to delete a students from the list
void deleteStudents(vector<Student*> &students, int id){
	//Loop through the vector and find if its the right id number
	for(int i = 0; i < students.size(); i++){
		//If the student's id is the student you want to delete then delete it
		if(students.at(i)->id == id){
			delete students.at(i);
			students.erase(students.begin() + i);
		}
	}
}
