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
#include <ctime>
#include <fstream>

using namespace std;
//Make a struct that stores the information about the student
struct Student{
    char firstName[20];
    char lastName[20];
    int id;
    double gpa;
    Student* next;
};

void toLowerCase(char (&arr)[7]);
void printStudents(int length, Student** list);
void deleteStudents(int id, Student** &list, int &length);
int addStudent(Student *s, Student** &list, int &length);
Student* search(int id, int length, Student** list);
int hashf(int, int);

int main(){
     //Read in the files that are nessecary for random generation
     char firstNames[100][20];
     char lastNames[100][20];

     srand(time(NULL));

     ifstream firstf ("firstnames.txt"), lastf("lastnames.txt");
     if(firstf.is_open() && lastf.is_open()){
          int name = 0;
          while(name++ < 100){
               firstf >> firstNames[name];
               lastf >> lastNames[name];
          }

          firstf.close();
          lastf.close();
     }
     else{
          cout << "There is a major problem" << endl;
          return 1;
     }
     int length = 100;
    Student** list;
    list = new Student*[length];
    for(int i = 0; i < length; i++){
          list[i] = NULL;
    }
     //Make an infinite loop that continues until the user quits
    while(true){
        cout << "Please enter one of the command words: Add, Print, Random, Delete, or Quit: ";
      char input[7];
        //Define character arrays with the command words
        char add[7] = "add";
        char print[7] = "print";
        char del[7] = "delete";
        char quit[7] = "quit";
        char random[7] = "random";
        
        //Create the vector to store the students in 
      
        cin >> input;
	toLowerCase(input);
        //If the input is an add then it needs to run that function
        if(strcmp(input, add) == 0){
            //Get the requred information about the student
            Student* student = new Student();
            student->next = NULL;
            cout << "Enter the first name: ";
            cin >> student->firstName;
            cout << "Enter the last name: ";
            cin >> student->lastName;
            cout << "Enter the student's id number: ";
            cin >> student->id;
            cout << "Enter the student's gpa: ";
            cin >> student->gpa;
            addStudent(student, list, length);
        }
        else if(strcmp(input, print) == 0){
		     printStudents(length, list);
        }
        else if(strcmp(input, del) == 0){
		cout << "Enter the id of the student you would like to delete: ";
		int input;
		cin >> input;

		deleteStudents(input, list, length);
        }
        //Generate a list of random students
        else if(strcmp(input, random) == 0){
               int quota;
               cout << "How many random students would you like to create? ";
               cin >> quota;
               while(quota != 0){
                    //Make a student with random names and gpa
                    Student* student = new Student();
                    student->next = NULL;
                    
                    strcpy(student->firstName, firstNames[rand()%100]);
                    strcpy(student->lastName, lastNames[rand()%100]);

                    student->gpa = (double)(rand()%500)/100;

                    //Find an availiable number for the id
                    int id = 0;
                    while(search(id, length, list) != NULL){
                         id++;
                    }

                    student->id = id;

                    addStudent(student, list, length);

                    quota--;
               }
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
//Function to delete a students from the list
void deleteStudents(int id, Student** &list, int &length){
     Student* s = list[hashf(id, length)];

     //If there is nothing at the proper index of the table
     if(s == NULL){
             cout << "The element is missing from the table" << endl;
             return;
     }

     //If its the first element in the chain then it just needs to get deleted and its next moved up
     if(id == s->id){
          list[hashf(id, length)] = s->next;
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
int hashf(int id, int length){
     return id%length;
}
//Search Method
Student* search(int id, int length, Student** list){
     Student* s = list[hashf(id, length)];
     if(s != NULL){        
             //Loop through the chain and 
             int num = s->id;
             while(s != NULL && s->id != id){
                  s = s->next;
             }
     }

     return s;
}
//Add Student Method
int addStudent(Student *s, Student** &list, int &length){
     int index = hashf(s->id, length);
     int collisions = 0;
     //Find the student at the head of the chain
     Student* c = list[index];
     //There is an open slot in the table that a student can go into end of story
     if(list[index] == NULL){
          list[index] = s;
          return 0;
     }
     //If a student with the same id is already input
     else if(list[index]->id == s->id){
          cout << "That student id is already assigned!" << endl;
          return 1;
     }
     collisions++;
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
          for(int i = 0; i < length; i++){
               list[i] = NULL;
          }
          //Loop through table and rehash all values
          for(int i = 0; i < length; i++){
               Student* add  = oldTable[i];
               
               //If there is a student or a chain loop through and add
               while(add != NULL){
                    Student* student = add;
                    add = add->next;
                    student->next = NULL;
                    addStudent(student, list, length);
               }
          }
          delete oldTable;
     }
     return 0;
}
//Print out the students
void printStudents(int length, Student** list){
    for(int i = 0; i < length; i++){
          Student* s = list[i];
          
          //Go through the chain
          while(s != NULL){
               cout << endl;
               cout << s->firstName << " " << s->lastName << endl;
               cout << s->id << endl;
               cout << s->gpa << endl;
               s = s->next;
          }
    }
}
