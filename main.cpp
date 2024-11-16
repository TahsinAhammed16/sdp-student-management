#include <iostream>
#include <fstream> // For file input/output
#include <string>
#include <sstream> // For string stream operations

using namespace std;

class Student
{
public:
    string name;
    string studentID;
    string password;
    string contactInfo;
    int currentSemester;

    Student()
    {
        currentSemester = 1;
    }

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

            file.close();
            return true;
        }
        return false; // Return false if the file cannot be opened
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
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
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
                    cout << "2. View Enrolled Courses" << endl;
                    cout << "3. View Marks and Grades" << endl;
                    cout << "4. Update Personal Information" << endl;
                    cout << "5. Log Out" << endl;
                    cout << "\nEnter your choice: ";
                    cin >> studentChoice;

                    switch (studentChoice)
                    {
                    case 1:
                        break;
                    case 2:
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