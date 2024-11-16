#include <iostream>
#include <fstream> // For file input/output
#include <string>
#include <sstream> // For string stream operations

using namespace std;

int main()
{
    int choice;
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
            break;
        case 2:
            break;
        case 3:
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