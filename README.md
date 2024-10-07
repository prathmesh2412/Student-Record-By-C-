# Student-Record-By-C-
Project Title: Student Record Management System

Project Description:

The Student Record Management System is a C++-based console application designed to manage and automate student academic records efficiently. This project aims to simplify the process of storing, retrieving, updating, and managing student data, including marks in various subjects and calculating their grades and overall performance.

Key Features:

1. Student Record Creation:
   - The system allows users to input essential details like student roll number, name, and marks in subjects (Physics, Chemistry, Maths, English, and Computer Science).
   - The system automatically calculates the percentage and assigns a grade (A, B, C, or F) based on the student's performance.

2. Record Management:
   - Users can create new student records, display all records, search for a specific student by roll number, and modify or delete records.
   - The data is stored in a file named `student.dat` for persistence, ensuring records are available even after closing the program.

3. Result Generation:
   - The system provides a feature to display the overall result of all students in a tabular format.
   - Individual student reports can also be viewed, showing detailed subject marks, percentage, and grade.

4. File Handling:
   - The project implements file handling to store and retrieve student records in a binary file format (`student.dat`), ensuring the integrity of the data.
   - The system also provides backup and restoration mechanisms by creating and renaming temporary files during record deletion.

Key Functionalities

- Add Student Record: Allows the user to input student details and store them in a file.
- Modify Student Record: Enables the user to search for a student by roll number and update their details.
- Delete Student Record: Removes a specific student's record from the system.
- Display All Records: Shows all the students' details in a structured tabular format.
- Search Student Record:Fetches and displays a particular student's record based on their roll number.
- Class Result: Displays a summary of the entire class, including roll number, name, marks in each subject, percentage, and grade.
  
Technologies Used:

- Language:C++
- File Handling:Binary file handling (`student.dat`) for record storage.
- Console Application: Simple text-based user interface.

Project Workflow:

1. Input:The user inputs student details such as name, roll number, and marks in five subjects.
2. Processing:The system calculates the student's percentage and assigns a grade.
3. Output:The processed data is stored, and the system can display student records or overall class results.

Grade Calculation Logic:

- Grade 'A': Percentage >= 60%
- Grade 'B':Percentage between 50% and 59%
- Grade 'C': Percentage between 33% and 49%
- Grade 'F': Percentage < 33%

Conclusion:

This **Student Record Management System** provides an efficient and easy-to-use tool for handling student records, which could be adapted for use in educational institutions. It leverages key programming concepts such as object-oriented programming, file handling, and control structures to automate the process of managing academic records.

This project demonstrates strong skills in C++ programming, including object-oriented design and practical application of file management for data persistence.
