/*
 *Hash Table
 *Date: June 5, 2018
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
    student* next;
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
//Function to make char arrays to lower case
void toLowerCase(char (&arr)[7]){
    for(int i = 0; i < 7; i++){
        arr[i] = tolower(arr[i]);
    }
}
//Function to print out all the students
void printStudents(vector<Student*> &students){
}
//Function to delete a students from the list
void deleteStudents(int id, Student** &list, int &length){
     Student* s = list[hash(id)];

     //If there is nothing at the proper index of the table
     if(s == NULL){
             cout << "The element is missing from the table" << endl;
             return;
     }

     //If its the first element in the chain then it just needs to get deleted and its next moved up
     if(id == s->id){
          list[hash(id)] = s->next;
          delete s;
          return;
     }
     //Loop through the chain until it finds the right id
     while(s->next != NULL){
             //If the student has the right id then it needs to go ahead and delete it.
             if(s->next->id == id){
                    Student* d = s->next;
                    s->next = d->next;
                    delete d;
                    return;
             }

             s = s->next;
     }
     cout << "The element is missing from the table" << endl;
}

//Hash function
int hash(int id, int length){
     return id%length;
}
//Search Method
Student* search(int id, int length, Student** list){
     Student* s = list[hash(id)];
     
     //Loop through the chain and 
     while(s != NULL && s->id != id){
          s = s->next;
     }

     return s;
}
//Add Student Method
void addStudent(student *s, Student** &list, int &length){
     int index = hash(s->id);
     int collisions = 0;
     //If a student with the same id is already input
     if(list[index]->id = id){
          cout << "That student id is already assigned!" << endl;
          return;
     }
     //There is an open slot in the table that a student can go into end of story
     if(list[index] == NULL){
          list[index] = s;
          return;
     }

     collisions++;
     //Find the student at the head of the chain
     Student* c = list[index];
     //Find a slot for the new student to fit into the chain
     while(c->next != NULL){
          collisions++;
          c = c->next;
     }
     c->next = s;
     
     //If the number of collisions exceeds the given max then the table size needs to be doubled
     if(collisions > 3){
          Student** oldTable = list;
          length *= 2;
          list = new Student*[length];
          //Loop through table and rehash all values
          for(int i = 0; i < length; i++){
               student* add  = oldTable[i];
               
               //If there is a student or a chain loop through and add
               while(add != NULL){
                    student* student = add;
                    add = add->next;
                    student->next = NULL;
                    addStudent(student, list, length);
               }
          }
          delete oldTable [];
     }
}
