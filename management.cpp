#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>



using namespace std;

struct employee {
    string name;
    string email;
    int wage;
};


class EmployeeManagementSys {
private:
    string readData;
    string fileName = "employeeInfo.txt";

    ifstream fin;
     ofstream fout;
public:
   

    void addEmployee() {
         fout.open("employeeInfo.txt", ios::app);
         cout << setprecision(2) << fixed;
        string name;
        string email;
        int pNumber;
        float wage;

        cout << "please enter employee name(first and last): " << endl;
         getline(cin >> ws, name);

         cout << name << endl;

        cout << "Please enter " << name << "'s email: " << endl;
       cin >> email;

        cout << "Please enter  " << name << "'s phone number: " << endl;
        cin >> pNumber;


    
        cout << "Please enter "  << name << "'s starting wage: $" << endl;
        cin.clear();
        cin >> wage;

        fout << "Name:" << name << "| Email:" << email << "| Phone Number:" << to_string(pNumber) << "| Salary:$";
        fout << setprecision(2) << fixed << wage << endl; // round to two decimal places
        fout.close();

    }

    bool isEmployee(string _findName, string employeeData) {
         int namePos = employeeData.find("Name:");
        string employeeName = employeeData.substr(namePos+5);

        int end = employeeName.find("|"); // position of element after last letter of name
        employeeName = employeeName.substr(0, end);
        
        if (_findName == employeeName) {
            return true;
        }

        return false;
    }



    void findEmployee() {
        string findName;
        bool foundName = false;
        vector<string> employees;

        cout << "Please enter first and last name of employee: ";
         cin.ignore();
        getline(cin, findName);
    

        ifstream fin(fileName);


         while(getline(fin, readData)) { // searching file for name

            if (isEmployee(findName, readData)) {
                foundName = true;
                cout << "Employee found! " << readData << endl;
                break;
            }
        }

        if(!foundName) {cout << "Not found in employee database! Please try again "<< endl;}

    }


void deleteEmployee() {
    string deleteName;
    string readData;

    cout << "Please enter first and last name of employee to be deleted: ";
    cin.ignore();
    getline(cin, deleteName);
 // Open input file
    ifstream fin(fileName);
    ofstream tempFile("temp.txt");    // Open temporary file

    if (!fin || !tempFile) {
        cerr << "Error opening files!" << endl;
        return;
    }

    bool found = false;

    while (getline(fin, readData)) { // Read each line from input file
        if (isEmployee(deleteName, readData)) {
            cout << "Employee data---> " << readData << endl;
            found = true;
        } else {
            tempFile << readData << endl; // Write to temporary file
        }
    }

    fin.close();
    tempFile.close();

    remove("employeeInfo.txt");           // Delete the original file
    rename("temp.txt", "employeeInfo.txt");// Rename the temporary file

    if (found) {
        cout << "Employee data deleted successfully." << endl;
    } else {
        cout << "Employee not found. Please try agian" << endl;
    }
}



    void homeMenu() {
        cout << "----------------------" << endl;
        cout << "Please select an option: " << endl;
        cout << "1.) Find Employee" << endl;
        cout << "2.) Add New Employee" << endl;
        cout << "3.) Delete Employee" << endl;
        cout << "4.) Exit" << endl;
        cout << "----------------------" << endl;

    }
};





int main() {
    EmployeeManagementSys sys;

     sys.homeMenu();
    int num;
    cin>> num;

    switch(num) {
        case 1:
            sys.findEmployee();
            break;
        case 2:
            sys.addEmployee();
            break;
        case 3:
            sys.deleteEmployee();
            break;
        case 4:
            cout << "Exited!" << endl;
            break;
        }

}