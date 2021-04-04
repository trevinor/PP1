#include <iostream> // for input and output objects
#include <fstream>  // to operate on files
#include <string>   // for strings
#include <iomanip>  // for parametric manipulators
using namespace std;


struct Student{         // this structure holds each student's data for report
    string firstName;       // student's firstName
    string lastName;        // student's lastName
    double testGrades[4];   // student's testGrades (total of 4)
    double finalGrade;      // student's finalGrade
    double average;         // student's average
    char lettergrade;       // student's lettergrade (A, B, C, etc.)
};

void readFile(ifstream &inputfile, Student *students);           // function to read the file
double average(double testGrades[], double finalGrade);     // function for student's average
char findsLetterGrade(double average);                            // function to find a student's grade
void writeFile(Student *students, int size);                // function to write the output file

int main(){
    string line;
    int n = 0;                              // 'n' will be used for a student count

    ifstream inputfile;
    inputfile.open("CIT1325.txt");

    if(inputfile.is_open()){                // if the input file opens
        while(getline(inputfile, line)){
            cout << line << endl;           // +1 to the student count
            n++;
        }

    }
    else{                                   // else
        cout << "Error opening your input file." << endl;

    }

    inputfile.close();                           // closes the input file

    inputfile.open("CIT1325.txt");               // re-opens the input file

    Student *students = new Student[n];             // creates structure array with student count

    readFile(inputfile, students);                       // reads data from file

    writeFile(students, n);                         // writes data to file

    return 0;
}

void readFile(ifstream &inputfile, Student *students){   // reads data from file and structure
    int i = 0;
    while (inputfile >> students[i].firstName){          // reads student's firstName
        inputfile >> students[i].lastName;               // reads student's lastName
        for(int j = 0; j < 4; j++)                  // loop for the 4 testGrades
            inputfile >> students[i].testGrades[j];      // reads student's testGrades
        inputfile >> students[i].finalGrade;             // reads student's finalGrade

        students[i].average = average(students[i].testGrades, students[i].finalGrade);
        students[i].lettergrade = findsLetterGrade(students[i].average);
        i++;                                        // +1 the to student count
    }
    inputfile.close();                                   // closes the input file
}

double average(double testGrades[], double finalGrade){
    double sum = 0;                                 // holds the sum of ALL grades
    for (int i = 0; i < 4; i++)                     // loop for the 4 testGrades
        sum += testGrades[i];                       // sum of all test grades
    sum += finalGrade;                              // adds final grade to sum
    return sum / 5;                                 // returns the average
}

char findsLetterGrade(double average){   // function that returns a letter grade for the students
if(average >= 90)       // if the average is greater or equal to 90
    return 'A';         // return 'A'
else if(average >= 80)  // else if the average is greater or equal to 80
    return 'B';         // return 'B'
else if(average >= 70)  // else if the average is greater or equal to 70
    return 'C';         // return 'C'
else if(average >= 60)  // else if the average is greater or equal to 60
    return 'D';         // return 'D'
else                    // else
    return 'F';         // return 'F'
}

void writeFile(Student *students, int size){
        double totalAverage = 0;                         // initializes double totalAverage to zero
        double testAverages[5] = {0, 0, 0, 0, 0};       // an array of 5 testAverages each initialized to zero
        double maxTestGrade = 0;                        // initializes double maxTestGrade to zero


        ofstream outputfile;                            // output stream class to operate on file
        outputfile.open("GradeReport.txt");  // opens the output file

        outputfile << left << setw(15) << "FIRST"
                   << left << setw(15) << "LAST"                    // header for organization
                   << left << setw(15) << "TEST AVG"
                   << left << setw(15) << "LETTER GRADE" << endl;

        for(int i = 0; i < size; i++){                                  // loop to write:
            outputfile << left << setw(15) << students[i].firstName;    // first name,
            outputfile << left << setw(15) << students[i].lastName;     // last name,
            outputfile << left << setw(15) << fixed << setprecision(2) << students[i].average;  // average,
            outputfile << left << setw(15) << students[i].lettergrade << endl; // and letter grade
                                                                               // of each student to the output file

            for(int j = 0; j < 4; j++){                 // loop to sum of the score of each test for every student and finds the maxTestGrade
                testAverages[j] += students[i].testGrades[j];
                if(j == 3)
                    testAverages[j + 1] += students[i].finalGrade;
                if(maxTestGrade < students[i].testGrades[j])    // if the maxTestGrade is less than the current student's testGrade
                    maxTestGrade = students[i].testGrades[j];   // then maxTestGrade = the current student's testGrade
                if(maxTestGrade < students[i].finalGrade)       // if the maxTestGrade is less than the current student's finalGrade
                    maxTestGrade = students[i].finalGrade;      // then maxTestGrade = the current student's finalGrade
            }
            // note: at the end of this loop the maxTestGrade will be found.
        }

        for(int j = 0; j < 5; j++){                     // loop to find test averages
            testAverages[j] = testAverages[j] / size;
            totalAverage += testAverages[j];
        }

        totalAverage = totalAverage / 5;                // totalAverage is total Average divided by 5

        outputfile << endl;

        for(int i = 0; i < 5; i++){                     // loop that prints each TEST, OVERALL AVERAGE and HIGHEST GRADE
            outputfile << "TEST #" << (i+1) << " AVERAGE: " << testAverages[i] << endl;
        }

        outputfile << endl << "OVERALL TEST AVERAGE: " << fixed << setprecision(2) << totalAverage << endl;
        outputfile << "HIGHEST TEST GRADE: " << maxTestGrade << endl;
        outputfile << "STUDENT WITH THE HIGHEST TEST SCORE: ";

        for(int i = 0; i < size; i++){
            bool found = false;         // initially set to false or not found
            for (int j = 0; j < 4; j++) // a loop is set to loop through each student's testGrades
            if(students[i].testGrades[j] == maxTestGrade){  // if a student's testGrade is equal to maxTestGrade
                found = true;           // set to true because it was found
                outputfile << students[i].firstName << " " << students[i].lastName << endl;         // print student's name
            }
            if(!found)                  // if not found
                if(students[i].finalGrade == maxTestGrade)  // if student with highest finalGrade is equal to maxTestGrade
                    outputfile << students[i].firstName << " " << students[i].lastName << endl;     // print student's name
        }
        outputfile.close();                             // close the output file
}
