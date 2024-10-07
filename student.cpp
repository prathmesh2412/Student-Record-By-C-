#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>

// For cross-platform clear screen
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// Function to clear the console screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Function to pause the console
void pause() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Student class definition
class Student {
private:
    int rollNo;
    std::string name;
    int p_marks, c_marks, m_marks, e_marks, cs_marks;
    float percentage;
    char grade;

    void calculate() {
        percentage = (p_marks + c_marks + m_marks + e_marks + cs_marks) / 5.0f;
        if (percentage >= 60)
            grade = 'A';
        else if (percentage >= 50)
            grade = 'B';
        else if (percentage >= 33)
            grade = 'C';
        else
            grade = 'F';
    }

public:
    void getData() {
        std::cout << "\nEnter the roll number of student: ";
        std::cin >> rollNo;
        std::cin.ignore(); // Clear newline character from the buffer

        std::cout << "Enter the name of student: ";
        std::getline(std::cin, name);

        std::cout << "Enter the marks in Physics out of 100: ";
        std::cin >> p_marks;

        std::cout << "Enter the marks in Chemistry out of 100: ";
        std::cin >> c_marks;

        std::cout << "Enter the marks in Maths out of 100: ";
        std::cin >> m_marks;

        std::cout << "Enter the marks in English out of 100: ";
        std::cin >> e_marks;

        std::cout << "Enter the marks in Computer Science out of 100: ";
        std::cin >> cs_marks;

        calculate();
    }

    void showData() const {
        std::cout << "\nRoll Number of Student: " << rollNo;
        std::cout << "\nName of Student: " << name;
        std::cout << "\nMarks in Physics: " << p_marks;
        std::cout << "\nMarks in Chemistry: " << c_marks;
        std::cout << "\nMarks in Maths: " << m_marks;
        std::cout << "\nMarks in English: " << e_marks;
        std::cout << "\nMarks in Computer Science: " << cs_marks;
        std::cout << "\nPercentage of Student: " << std::fixed << std::setprecision(2) << percentage << "%";
        std::cout << "\nGrade of Student: " << grade << "\n";
    }

    void showTabular() const {
        std::cout << std::left << std::setw(10) << rollNo
                  << std::setw(20) << name
                  << std::setw(10) << p_marks
                  << std::setw(10) << c_marks
                  << std::setw(10) << m_marks
                  << std::setw(10) << e_marks
                  << std::setw(10) << cs_marks
                  << std::setw(10) << std::fixed << std::setprecision(2) << percentage
                  << std::setw(5) << grade << "\n";
    }

    int getRollNo() const { return rollNo; }

    // Serialize student data to a string
    std::string serialize() const {
        return std::to_string(rollNo) + "," + name + "," +
               std::to_string(p_marks) + "," + std::to_string(c_marks) + "," +
               std::to_string(m_marks) + "," + std::to_string(e_marks) + "," +
               std::to_string(cs_marks) + "," + std::to_string(percentage) + "," +
               std::string(1, grade) + "\n";
    }

    // Deserialize student data from a string
    static Student deserialize(const std::string& data) {
        Student s;
        std::stringstream ss(data);
        std::string token;

        std::getline(ss, token, ',');
        s.rollNo = std::stoi(token);

        std::getline(ss, s.name, ',');

        std::getline(ss, token, ',');
        s.p_marks = std::stoi(token);

        std::getline(ss, token, ',');
        s.c_marks = std::stoi(token);

        std::getline(ss, token, ',');
        s.m_marks = std::stoi(token);

        std::getline(ss, token, ',');
        s.e_marks = std::stoi(token);

        std::getline(ss, token, ',');
        s.cs_marks = std::stoi(token);

        std::getline(ss, token, ',');
        s.percentage = std::stof(token);

        std::getline(ss, token, ',');
        s.grade = token[0];

        return s;
    }
};

// Function prototypes
void writeStudent();
void displayAll();
void displaySpecific(int rollNo);
void modifyStudent();
void deleteStudent();
void classResult();
void resultMenu();
void entryMenu();
void intro();

// File name constant
const std::string FILE_NAME = "student.dat";

// Function to write a student record to the file
void writeStudent() {
    std::ofstream outFile(FILE_NAME, std::ios::app);
    if (!outFile) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    Student s;
    s.getData();
    outFile << s.serialize();
    outFile.close();
    std::cout << "\nStudent record has been created.\n";
    pause();
}

// Function to display all student records
void displayAll() {
    clearScreen();
    std::ifstream inFile(FILE_NAME);
    if (!inFile) {
        std::cerr << "Error opening file for reading.\n";
        pause();
        return;
    }

    std::cout << "\n\n\n\t\tDISPLAY ALL RECORDS\n\n";

    Student s;
    while (inFile.peek() != EOF) {
        std::string line;
        std::getline(inFile, line);
        if (line.empty()) continue;
        s = Student::deserialize(line);
        s.showData();
        std::cout << "\n====================================\n";
        pause();
    }

    inFile.close();
    pause();
}

// Function to display a specific student record
void displaySpecific(int rollNo) {
    clearScreen();
    std::ifstream inFile(FILE_NAME);
    if (!inFile) {
        std::cerr << "Error opening file for reading.\n";
        pause();
        return;
    }

    Student s;
    bool found = false;
    while (inFile.peek() != EOF) {
        std::string line;
        std::getline(inFile, line);
        if (line.empty()) continue;
        s = Student::deserialize(line);
        if (s.getRollNo() == rollNo) {
            s.showData();
            found = true;
            break;
        }
    }

    inFile.close();

    if (!found) {
        std::cout << "\n\nRecord not found.\n";
    }

    pause();
}

// Function to modify a student record
void modifyStudent() {
    clearScreen();
    std::cout << "\n\n\tModify Student Record";
    std::cout << "\n\nEnter the roll number of the student to modify: ";
    int rollNo;
    std::cin >> rollNo;
    std::cin.ignore(); // Clear newline character

    std::ifstream inFile(FILE_NAME);
    if (!inFile) {
        std::cerr << "Error opening file for reading.\n";
        pause();
        return;
    }

    std::vector<Student> students;
    Student s;
    bool found = false;

    // Read all students
    while (inFile.peek() != EOF) {
        std::string line;
        std::getline(inFile, line);
        if (line.empty()) continue;
        s = Student::deserialize(line);
        if (s.getRollNo() == rollNo) {
            std::cout << "\nCurrent details of the student:\n";
            s.showData();
            std::cout << "\nEnter new details:\n";
            s.getData();
            found = true;
        }
        students.push_back(s);
    }

    inFile.close();

    if (!found) {
        std::cout << "\nRecord not found.\n";
        pause();
        return;
    }

    // Write all students back to the file
    std::ofstream outFile(FILE_NAME, std::ios::trunc);
    if (!outFile) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    for (const auto& student : students) {
        outFile << student.serialize();
    }

    outFile.close();
    std::cout << "\n\n\tRecord updated successfully.\n";
    pause();
}

// Function to delete a student record
void deleteStudent() {
    clearScreen();
    std::cout << "\n\n\tDelete Student Record";
    std::cout << "\n\nEnter the roll number of the student to delete: ";
    int rollNo;
    std::cin >> rollNo;
    std::cin.ignore(); // Clear newline character

    std::ifstream inFile(FILE_NAME);
    if (!inFile) {
        std::cerr << "Error opening file for reading.\n";
        pause();
        return;
    }

    std::vector<Student> students;
    Student s;
    bool found = false;

    // Read all students except the one to delete
    while (inFile.peek() != EOF) {
        std::string line;
        std::getline(inFile, line);
        if (line.empty()) continue;
        s = Student::deserialize(line);
        if (s.getRollNo() == rollNo) {
            found = true;
            continue; // Skip adding this student to the list
        }
        students.push_back(s);
    }

    inFile.close();

    if (!found) {
        std::cout << "\nRecord not found.\n";
        pause();
        return;
    }

    // Write remaining students back to the file
    std::ofstream outFile(FILE_NAME, std::ios::trunc);
    if (!outFile) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    for (const auto& student : students) {
        outFile << student.serialize();
    }

    outFile.close();
    std::cout << "\n\n\tRecord deleted successfully.\n";
    pause();
}

// Function to display class results in tabular form
void classResult() {
    clearScreen();
    std::ifstream inFile(FILE_NAME);
    if (!inFile) {
        std::cerr << "Error opening file for reading.\n";
        pause();
        return;
    }

    std::cout << "\n\n\t\tALL STUDENTS RESULT\n\n";
    std::cout << "============================================================\n";
    std::cout << std::left << std::setw(10) << "Roll No."
              << std::setw(20) << "Name"
              << std::setw(10) << "Physics"
              << std::setw(10) << "Chemistry"
              << std::setw(10) << "Maths"
              << std::setw(10) << "English"
              << std::setw(10) << "Comp Sci"
              << std::setw(10) << "%age"
              << std::setw(5) << "Grade" << "\n";
    std::cout << "============================================================\n";

    Student s;
    while (inFile.peek() != EOF) {
        std::string line;
        std::getline(inFile, line);
        if (line.empty()) continue;
        s = Student::deserialize(line);
        s.showTabular();
    }

    inFile.close();
    pause();
}

// Function to handle the result menu
void resultMenu() {
    int choice, rollNo;
    char ans;
    do {
        clearScreen();
        std::cout << "\n\n\n\tRESULT MENU";
        std::cout << "\n\n\t1. Class Result";
        std::cout << "\n\n\t2. Student Report Card";
        std::cout << "\n\n\t3. Back to Main Menu";
        std::cout << "\n\n\tEnter Choice (1-3): ";
        std::cin >> choice;
        std::cin.ignore(); // Clear newline character

        switch (choice) {
            case 1:
                classResult();
                break;
            case 2:
                std::cout << "\nEnter Roll Number of Student: ";
                std::cin >> rollNo;
                std::cin.ignore(); // Clear newline character
                displaySpecific(rollNo);
                break;
            case 3:
                return;
            default:
                std::cout << "\nInvalid choice. Please try again.\n";
                pause();
        }
    } while (true);
}

// Function to handle the entry/edit menu
void entryMenu() {
    int choice, rollNo;
    do {
        clearScreen();
        std::cout << "\n\n\n\tENTRY MENU";
        std::cout << "\n\n\t1. Create Student Record";
        std::cout << "\n\n\t2. Display All Students Records";
        std::cout << "\n\n\t3. Search Student Record";
        std::cout << "\n\n\t4. Modify Student Record";
        std::cout << "\n\n\t5. Delete Student Record";
        std::cout << "\n\n\t6. Back to Main Menu";
        std::cout << "\n\n\tPlease Enter Your Choice (1-6): ";
        std::cin >> choice;
        std::cin.ignore(); // Clear newline character

        switch (choice) {
            case 1:
                writeStudent();
                break;
            case 2:
                displayAll();
                break;
            case 3:
                std::cout << "\nEnter Roll Number to Search: ";
                std::cin >> rollNo;
                std::cin.ignore(); // Clear newline character
                displaySpecific(rollNo);
                break;
            case 4:
                modifyStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                return;
            default:
                std::cout << "\nInvalid choice. Please try again.\n";
                pause();
        }
    } while (true);
}

// Function to display the introduction screen
void intro() {
    clearScreen();
    std::cout << "\n\n\n\tSTUDENT REPORT CARD PROJECT";
    std::cout << "\n\n\n\tMADE BY : PRATHMESH KHANAPURE";
    std::cout << "\n\n\tSCHOOL : TILAK MAHARASTRA VIDHYAPEETH\n";
    pause();
}

// Main function
int main() {
    intro();
    int choice;

    do {
        clearScreen();
        std::cout << "\n\n\n\tMAIN MENU";
        std::cout << "\n\n\t1. RESULT MENU";
        std::cout << "\n\n\t2. ENTRY/EDIT MENU";
        std::cout << "\n\n\t3. EXIT";
        std::cout << "\n\n\tPlease Select Your Option (1-3): ";
        std::cin >> choice;
        std::cin.ignore(); // Clear newline character

        switch (choice) {
            case 1:
                resultMenu();
                break;
            case 2:
                entryMenu();
                break;
            case 3:
                std::cout << "\nExiting the program. Goodbye!\n";
                break;
            default:
                std::cout << "\nInvalid choice. Please try again.\n";
                pause();
        }
    } while (choice != 3);

    return 0;
}
