#include <iostream>
#include <fstream> // For file input/output
#include <string>
#include <sstream>   // For string stream operations
#include <iomanip>   // For setw()
#include <windows.h> // For sleep in showSpinner()
using namespace std;

void showSpinner()
{
    char spinner[] = {'|', '/', '-', '\\'};
    int i = 0;
    while (i < 10) // Run the spinner for 10 iterations (adjust as needed)
    {
        cout << "\rProcessing " << spinner[i % 4] << "   "; // Move cursor to start and show spinner
        cout.flush();                                       // Flush the output buffer
        Sleep(120);                                         // Sleep for 120 milliseconds
        i++;
    }
    cout << endl; // Clear the spinner
}

void waitForEnterToGoBack()
{
    string dummy;
    cout << "\n\nPress Enter to return to the main menu...";
    getline(cin, dummy); // Waits for the user to press Enter
    system("cls");
}

class Student
{
public:
    string name;
    string studentID;
    string password;
    string contactInfo;
    int currentSemester;
    int marks[4];
    float attendance, quizzes, classTests, assignments, midTerm, finalExam;

    Student()
    {
        currentSemester = 1;
        for (int i = 0; i < 4; i++)
        {
            marks[i] = 0; // Initialize marks array
        }
    }

    // Predefined six semesters, each with four courses and fixed credit scores.
    string semesterNames[6] = {
        "Semester 1: Foundation Courses",
        "Semester 2: Core Programming",
        "Semester 3: Data and Logic",
        "Semester 4: Advanced Computing",
        "Semester 5: Systems and Networks",
        "Semester 6: Capstone and Specializations"};

    string predefinedCourses[6][4] = {
        {"MAT101,3,Programming Fundamentals", "CSE101,3,Introduction to Computer Science", "CSE102,3,Data Structures", "PHY101,3,Physics I"},                // Semester 1
        {"CSE201,3,Algorithms", "CSE202,3,Discrete Mathematics", "CSE203,3,Computer Organization", "CSE204,3,Operating Systems"},                            // Semester 2
        {"CSE301,3,Database Management Systems", "CSE302,3,Object-Oriented Programming", "CSE303,3,Software Engineering", "CSE304,3,Computer Networks"},     // Semester 3
        {"CSE401,3,Compiler Design", "CSE402,3,Theory of Computation", "CSE403,3,Artificial Intelligence", "CSE404,3,Machine Learning"},                     // Semester 4
        {"CSE501,3,Cloud Computing", "CSE502,3,Mobile Computing", "CSE503,3,Data Science", "CSE504,3,Distributed Systems"},                                  // Semester 5
        {"CSE601,3,Capstone Project", "CSE602,3,Advanced Topics in Computing", "CSE603,3,Specialization in Software Engineering", "CSE604,3,Data Analytics"} // Semester 6
    };
    void registerStudent()
    {
        cout << "\n===============================" << endl;
        cout << "       Register Student  " << endl;
        cout << "===============================" << endl;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Student ID: ";
        getline(cin, studentID);
        cout << "Enter Password: ";
        getline(cin, password);
        cout << "Enter Contact Info: ";
        getline(cin, contactInfo);

        saveStudentData();
    }

    void saveStudentData()
    {
        ofstream file(studentID + ".txt");
        if (file.is_open())
        {
            // Save student information with pipe delimiter (|) for easy parsing
            file << name << "|"
                 << studentID << "|"
                 << password << "|"
                 << contactInfo << "|"
                 << currentSemester << "|";

            // Extract only the course name from semesterNames
            stringstream ssSemester(semesterNames[currentSemester - 1]);
            string temp;
            getline(ssSemester, temp, ':'); // This reads the "Semester X" part and ignores it
            getline(ssSemester, temp, ' ');
            getline(ssSemester, temp); // This reads the course name part (after the colon)
            file << temp;

            // Save next semester number to the file
            int nextSemester;
            if (currentSemester < 6)
            {
                nextSemester = currentSemester + 1;
            }
            else
            {
                nextSemester = currentSemester; // No further semesters
            }
            file << "|" << nextSemester << "|";

            for (int i = 0; i < 4; i++)
            {
                stringstream ss(predefinedCourses[currentSemester - 1][i]);
                string courseCode, courseTitle, courseCredit;
                getline(ss, courseCode, ',');
                getline(ss, courseCredit, ',');
                getline(ss, courseTitle, ',');

                // Save the course information to the file
                file << courseCode << "|" << courseTitle << "|" << courseCredit << "|";
            }

            file.close();
            system("cls");
            cout << "\nStudent registered successfully!" << endl;
        }
        else
        {
            cout << "Unable to open file." << endl;
        }
    }

    bool readStudentDataFromFile(string id)
    {
        ifstream file(id + ".txt");
        if (file.is_open())
        {
            string line;
            getline(file, line); // Read the first line for student info
            stringstream ss(line);

            // Split the student data by the pipe delimiter (|)
            getline(ss, name, '|');
            getline(ss, studentID, '|');
            getline(ss, password, '|');
            getline(ss, contactInfo, '|');
            string semesterStr;
            getline(ss, semesterStr, '|');       // Read the semester as a string
            currentSemester = stoi(semesterStr); // Convert the semester string to an integer

            string semesterName;
            getline(ss, semesterName, '|');
            semesterNames[currentSemester - 1] = semesterName;

            string nextSemesterStr;
            getline(ss, nextSemesterStr, '|');
            // int nextSemester = stoi(nextSemesterStr);

            for (int i = 0; i < 4; i++)
            {
                predefinedCourses[currentSemester - 1][i] = ""; // Clear any previous course data before reading new ones
            }

            // Read the courses for the current semester
            for (int i = 0; i < 4; i++)
            {
                string courseCode, courseTitle, courseCredit;
                getline(ss, courseCode, '|');
                getline(ss, courseTitle, '|');
                getline(ss, courseCredit, '|');

                // Combine the course details and store in predefinedCourses
                predefinedCourses[currentSemester - 1][i] = courseCode + "," + courseCredit + "," + courseTitle;
            }

            file.close();
            return true;
        }
        return false; // Return false if the file cannot be opened
    }

    float calculateGradePoint(float marks)
    {
        if (marks >= 80)
            return 4.0; // A+
        else if (marks >= 75)
            return 3.75; // A
        else if (marks >= 70)
            return 3.5; // A-
        else if (marks >= 65)
            return 3.25; // B+
        else if (marks >= 60)
            return 3.0; // B
        else if (marks >= 55)
            return 2.75; // B-
        else if (marks >= 50)
            return 2.5; // C+
        else if (marks >= 45)
            return 2.25; // C
        else if (marks >= 40)
            return 2.0; // D
        else
            return 0.0; // F
    }

    float calculateSGPAFromFile(string studentID)
    {
        ifstream marksFile(studentID + "_marks.txt");
        if (!marksFile.is_open())
        {
            cout << "Error: Unable to open marks file for " << studentID << endl;
            return 0.0;
        }

        string line;
        float totalGradePoints = 0.0;
        int totalCredits = 0;

        showSpinner();
        system("cls");

        cout << "                                   \nGrade Sheet for Student ID: " << studentID << endl
             << endl;

        cout << "\nCourse Marks and Grade Details:" << endl;
        cout << "-------------------------------------------------------------------------------------------------------" << endl;
        cout << left << setw(10) << "Course" << setw(15) << "Credits" << setw(10) << "Attendance"
             << setw(10) << "Quizzes" << setw(12) << "Class Tests" << setw(12) << "Assignments"
             << setw(8) << "Midterm" << setw(10) << "Final" << setw(12) << "Total" << setw(12) << "Grade" << endl;
        cout << "-------------------------------------------------------------------------------------------------------" << endl;

        while (getline(marksFile, line))
        {
            stringstream ss(line);
            string courseCode, courseTitle, courseCreditStr;
            string attendanceStr, quizzesStr, classTestsStr, assignmentsStr, midTermStr, finalExamStr;

            // Parse the line
            getline(ss, courseCode, '|');
            getline(ss, courseTitle, '|');
            getline(ss, courseCreditStr, '|');

            int courseCredit = stoi(courseCreditStr); // Convert course credit from string to int
            totalCredits += courseCredit;

            // Read marks as strings
            getline(ss, attendanceStr, '|');
            getline(ss, quizzesStr, '|');
            getline(ss, classTestsStr, '|');
            getline(ss, assignmentsStr, '|');
            getline(ss, midTermStr, '|');
            getline(ss, finalExamStr, '|');

            // Convert from strings to floating-point numbers
            float attendance = stof(attendanceStr);
            float quizzes = stof(quizzesStr);
            float classTests = stof(classTestsStr);
            float assignments = stof(assignmentsStr);
            float midTerm = stof(midTermStr);
            float finalExam = stof(finalExamStr);

            float totalMarks = attendance + quizzes + classTests + assignments + midTerm + finalExam;
            float gradePoint = calculateGradePoint(totalMarks);
            totalGradePoints += (gradePoint * courseCredit);

            // Display course details in a formatted table
            cout << left << setw(10) << courseCode << setw(15) << courseCreditStr << setw(10) << attendance
                 << setw(10) << quizzes << setw(12) << classTests << setw(12) << assignments
                 << setw(8) << midTerm << setw(10) << finalExam << setw(12) << totalMarks << setw(12) << calculateGradePoint(totalMarks) << endl;
        }
        cout << "-------------------------------------------------------------------------------------------------------" << endl;
        marksFile.close();
        return totalGradePoints / totalCredits;
    }

    void displayPersonalInformation()
    {
        system("cls");
        cout << "\n===============================" << endl;
        cout << "       Personal Information     " << endl;
        cout << "===============================" << endl;
        cout << "Name: " << name << endl;
        cout << "Student ID: " << studentID << endl;
        cout << "Contact Info: " << contactInfo << endl;
        cout << "Current Semester: (" << currentSemester << ") " << semesterNames[currentSemester - 1] << endl;
        cout << "\n--------------------------------------------------" << endl;
        cout << "Courses for Current Semester: " << endl;
        cout << "--------------------------------------------------" << endl;

        // Display current semester courses
        for (int i = 0; i < 4; i++)
        {
            stringstream ss(predefinedCourses[currentSemester - 1][i]);
            string courseCode, courseTitle, courseCredit;
            getline(ss, courseCode, ',');
            getline(ss, courseCredit, ',');
            getline(ss, courseTitle, ',');
            cout << "Course " << i + 1 << ": " << courseCode << " - " << courseTitle << " (" << courseCredit << " credits)" << endl;
        }

        cout << "\n--------------------------------------------------" << endl;
        cin.ignore();
        waitForEnterToGoBack();
    }

    // Function to handle login
    bool login(string id, string pwd)
    {
        if (readStudentDataFromFile(id))
        {
            return (id == studentID && pwd == password);
        }
        return false;
    }

    void registerForSemester()
    {
        system("cls");
        cout << "\n==========================================================================" << endl;
        cout << "                        Semester Registration" << endl;
        cout << "==========================================================================" << endl;

        if (currentSemester >= 6)
        {
            cout << "All semesters are completed! Congratulations on finishing your program." << endl;
            return;
        }

        cout << "You are currently eligible to register for " << semesterNames[currentSemester - 1] << "." << endl;

        // Display each course with its details in a table-like format
        cout << "\nCourses offered this semester:" << endl;
        cout << "---------------------------------------------------------------" << endl;
        cout << left << setw(15) << "Code" << setw(40) << "Title" << setw(10) << "Credits" << endl;
        cout << "---------------------------------------------------------------" << endl;
        for (int i = 0; i < 4; i++)
        {
            stringstream ss(predefinedCourses[currentSemester - 1][i]);
            string courseCode, courseTitle, courseCredit;
            getline(ss, courseCode, ',');
            getline(ss, courseCredit, ',');
            getline(ss, courseTitle, ',');

            cout << left << setw(15) << courseCode << setw(40) << courseTitle << setw(10) << courseCredit << endl;
        }
        cout << "---------------------------------------------------------------" << endl;

        // Ask if the student wants to register for this semester
        string confirmation;
        cout << "\nWould you like to register for this semester? (yes/no): ";
        cin.ignore();
        getline(cin, confirmation);
        if (confirmation != "yes")
        {
            system("cls");
            cout << "Registration for this semester is skipped. You can register later." << endl;
            return;
        }

        system("cls");
        showSpinner();
        system("cls");
        cout << "---------------------------------------------------------------------------------" << endl;
        cout << left << setw(15) << "Code" << setw(40) << "Title" << setw(10) << "Credits" << setw(15) << "Status" << endl;
        cout << "---------------------------------------------------------------------------------" << endl;
        for (int i = 0; i < 4; i++)
        {
            stringstream ss(predefinedCourses[currentSemester - 1][i]);
            string courseCode, courseTitle, courseCredit;
            getline(ss, courseCode, ',');
            getline(ss, courseCredit, ',');
            getline(ss, courseTitle, ',');

            cout << left << setw(15) << courseCode << setw(40) << courseTitle << setw(10) << courseCredit << setw(15) << "Registered" << endl;
        }
        cout << "---------------------------------------------------------------------------------" << endl;
        cout << "Registration for the semester is completed!" << endl;

        currentSemester++;

        // If there are more semesters, display the next semester
        if (currentSemester < 6)
        {
            cout << "\nNext up: " << semesterNames[currentSemester - 1] << "." << endl;
        }
        else
        {
            cout << "\nYou have completed all semesters!" << endl;
        }
        waitForEnterToGoBack();
        saveStudentData();
    }

    // Function to save marks to a file
    void saveMarksToFile(string studentID, float attendance[], float quizzes[], float classTests[], float assignments[], float midTerm[], float finalExam[])
    {
        // Open the file to overwrite the marks
        ofstream marksFile(studentID + "_marks.txt", ios::out); // Open file in overwrite mode
        if (marksFile.is_open())
        {
            // Loop through the courses and save the data
            for (int i = 0; i < 4; i++)
            {
                stringstream ss(predefinedCourses[currentSemester - 1][i]);
                string courseCode, courseTitle, courseCredit;
                getline(ss, courseCode, ',');
                getline(ss, courseCredit, ',');
                getline(ss, courseTitle, ',');

                marksFile << courseCode << " | "
                          << courseTitle << " | "
                          << courseCredit << " | "
                          << attendance[i] << " | "
                          << quizzes[i] << " | "
                          << classTests[i] << " | "
                          << assignments[i] << " | "
                          << midTerm[i] << " | "
                          << finalExam[i] << " |\n";
            }
            marksFile.close();
        }
        else
        {
            cout << "Error: Unable to save marks to file." << endl;
        }
    }
};

class Admin
{
public:
    string adminUsername = "a";
    string adminPassword = "a";

    bool login(string username, string password)
    {
        return (username == adminUsername && password == adminPassword);
    }
};

int main()
{
    Admin admin;
    Student student;
    int choice, adminChoice, studentChoice;
    string username, password, studentID;

    while (true)
    {
        cout << "\n===============================" << endl;
        cout << "   Student Management System  " << endl;
        cout << "===============================" << endl;
        cout << "1. Admin Login" << endl;
        cout << "2. Register Student" << endl;
        cout << "3. Student Login" << endl;
        cout << "4. Exit" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;
        system("cls");

        switch (choice)
        {
        case 1:
            cout << "\n===============================" << endl;
            cout << "        Admin Login   " << endl;
            cout << "===============================" << endl;
            cout << "Enter Admin Username: ";
            cin.ignore(); // To clear the input buffer
            getline(cin, username);
            cout << "Enter Admin Password: ";
            getline(cin, password);
            if (admin.login(username, password))
            {
                system("cls");
                cout << "Admin logged in successfully!" << endl;
                bool isAdminLoggedIn = true; // Boolean flag to control the loop
                while (isAdminLoggedIn)
                {
                    cout << "\n===============================" << endl;
                    cout << "        Admin Menu   " << endl;
                    cout << "===============================" << endl;
                    cout << "1. Register Student" << endl;
                    cout << "2. Set Marks for Students" << endl;
                    cout << "3. View All Registered Student Records" << endl;
                    cout << "4. Display Individual Student Profile/Generate Grade Sheet" << endl;
                    cout << "5. Update Student Data" << endl;
                    cout << "6. Delete Student Data" << endl;
                    cout << "7. Log Out" << endl;
                    cout << "\nEnter your choice: ";
                    cin >> adminChoice;
                    system("cls");

                    switch (adminChoice)
                    {
                    case 1:
                        break;
                    case 2: // Admin sets marks for students
                    {
                        string studentID;
                        cout << "Enter Student ID to set marks: ";
                        cin.ignore();
                        getline(cin, studentID);

                        // Check if the student file exists
                        if (student.readStudentDataFromFile(studentID))
                        {
                            float attendance[4], quizzes[4], classTests[4], assignments[4], midTerm[4], finalExam[4];

                            // Loop through all 4 courses and get marks
                            for (int i = 0; i < 4; i++)
                            {
                                stringstream ss(student.predefinedCourses[student.currentSemester - 1][i]);
                                string courseCode, courseTitle, courseCredit;
                                getline(ss, courseCode, ',');
                                getline(ss, courseCredit, ',');
                                getline(ss, courseTitle, ',');

                                cout << "\n--------------------------------------------------" << endl;
                                cout << "Course " << (i + 1) << ": " << courseCode << " - " << courseTitle << endl;
                                cout << "--------------------------------------------------\n";

                                // Input for attendance
                                do
                                {
                                    cout << "Enter Attendance (out of 5): ";
                                    cin >> attendance[i];
                                    if (attendance[i] < 0 || attendance[i] > 5)
                                    {
                                        cout << "Invalid input! Attendance must be between 0 and 5." << endl;
                                    }
                                } while (attendance[i] < 0 || attendance[i] > 5);

                                // Input for quizzes
                                do
                                {
                                    cout << "Enter Quizzes (out of 5): ";
                                    cin >> quizzes[i];
                                    if (quizzes[i] < 0 || quizzes[i] > 5)
                                    {
                                        cout << "Invalid input! Quizzes must be between 0 and 5." << endl;
                                    }
                                } while (quizzes[i] < 0 || quizzes[i] > 5);

                                // Input for class tests
                                do
                                {
                                    cout << "Enter Class Tests & Tutorial (out of 10): ";
                                    cin >> classTests[i];
                                    if (classTests[i] < 0 || classTests[i] > 10)
                                    {
                                        cout << "Invalid input! Class Tests must be between 0 and 10." << endl;
                                    }
                                } while (classTests[i] < 0 || classTests[i] > 10);

                                // Input for assignments/presentations
                                do
                                {
                                    cout << "Enter Assignment/Presentation/Lab/Project (out of 10): ";
                                    cin >> assignments[i];
                                    if (assignments[i] < 0 || assignments[i] > 10)
                                    {
                                        cout << "Invalid input! Assignments must be between 0 and 10." << endl;
                                    }
                                } while (assignments[i] < 0 || assignments[i] > 10);

                                // Input for mid-term exam
                                do
                                {
                                    cout << "Enter Mid-Term Exam score (out of 30): ";
                                    cin >> midTerm[i];
                                    if (midTerm[i] < 0 || midTerm[i] > 30)
                                    {
                                        cout << "Invalid input! Mid-Term Exam must be between 0 and 30." << endl;
                                    }
                                } while (midTerm[i] < 0 || midTerm[i] > 30);

                                // Input for final exam
                                do
                                {
                                    cout << "Enter Final Exam score (out of 40): ";
                                    cin >> finalExam[i];
                                    if (finalExam[i] < 0 || finalExam[i] > 40)
                                    {
                                        cout << "Invalid input! Final Exam must be between 0 and 40." << endl;
                                    }
                                } while (finalExam[i] < 0 || finalExam[i] > 40);

                                system("cls");
                                cout << "\nMarks for " << courseCode << " - " << courseTitle << " successfully entered!" << endl;
                                student.saveMarksToFile(studentID, attendance, quizzes, classTests, assignments, midTerm, finalExam);
                                cin.ignore();
                            }
                        }
                        else
                        {
                            cout << "No student found with that ID." << endl;
                        }
                        system("cls");
                        cout << "All marks for Student ID: " << studentID << " have been successfully entered and saved!" << endl;
                        break;
                    }

                    case 3:
                        break;
                    case 4:
                    {
                        cout << "Enter Student ID to view profile/grade sheet: ";
                        cin.ignore(); // Clear input buffer
                        getline(cin, studentID);

                        if (student.readStudentDataFromFile(studentID))
                        {
                            // Calculate SGPA
                            float sgpa = student.calculateSGPAFromFile(studentID);

                            if (sgpa > 0.0)
                            {
                                cout << "SGPA: " << fixed << setprecision(2) << sgpa << endl;
                                waitForEnterToGoBack();
                            }
                            else
                            {
                                cout << "Failed to calculate SGPA. Please check the student data." << endl;
                            }
                        }
                        else
                        {
                            cout << "Student not found." << endl;
                        }
                        system("cls");
                        break;
                    }

                    case 5:
                        break;
                    case 6:
                        break;
                    case 7:
                        cout << "Admin logged out successfully!" << endl;
                        isAdminLoggedIn = false; // Set flag to false to exit loop
                        break;
                    default:
                        cout << "Invalid choice, please try again." << endl;
                    }
                }
            }
            else
            {
                cout << "Invalid Admin credentials, returning to main menu." << endl;
            }
            break;
        case 2:
            student.registerStudent();
            break;
        case 3:
            cout << "\n===============================" << endl;
            cout << "        Student Login  " << endl;
            cout << "===============================" << endl;
            cout << "Enter Student ID: ";
            cin.ignore();
            getline(cin, studentID);
            cout << "Enter Password: ";
            getline(cin, password);
            system("cls");
            if (student.login(studentID, password))
            {
                system("cls");
                cout << "Student logged in successfully!" << endl;
                bool isStudentLoggedIn = true;

                while (isStudentLoggedIn)
                {

                    cout << "\n===============================" << endl;
                    cout << "        Student Menu  " << endl;
                    cout << "===============================" << endl;
                    cout << "1. Semester Registration" << endl;
                    cout << "2. View Personal Information" << endl;
                    cout << "3. View Marks and Grades" << endl;
                    cout << "4. Update Personal Information" << endl;
                    cout << "5. Log Out" << endl;
                    cout << "\nEnter your choice: ";
                    cin >> studentChoice;

                    switch (studentChoice)
                    {
                    case 1:
                        student.registerForSemester();
                        break;
                    case 2:
                        cout << "\n===============================" << endl;
                        cout << "    Personal Information       " << endl;
                        cout << "===============================" << endl;
                        student.displayPersonalInformation();
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    case 5:
                        system("cls");
                        cout << "Student logged out successfully!" << endl;
                        isStudentLoggedIn = false;
                        break;
                    default:
                        cout << "Invalid choice, please try again." << endl;
                    }
                }
            }
            else
            {
                cout << "Invalid Student credentials, returning to main menu." << endl;
            }
            break;
        case 4:
            cout << "Exiting the system!" << endl;
            return 0;
        default:
            cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}