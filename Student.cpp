#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Student
{
private:
    int age;
    string name, rollno;

public:
    Student(string stdRollno, string stdName, int stdAge)
    {
        rollno = stdRollno;
        name = stdName;
        age = stdAge;
    }

    void setRollno(string stdRollno)
    {
        rollno = stdRollno;
    }

    const string& getRollno() const
    {
        return rollno;
    }

    void setName(string stdName)
    {
        name = stdName;
    }

    const string& getName() const
    {
        return name;
    }

    void setAge(int stdAge)
    {
        age = stdAge;
    }

    const int getAge() const
    {
        return age;
    }

    void displayStudent()
    {
        cout << "Roll No : " << rollno << endl;
        cout << "Name : " << name << endl;
        cout << "Age: " << age << endl;
    }
};

// Function to update student record
void updateStudent(vector<Student> &students)
{
    string sname;
    bool found = false;
    int choice;
    cout << "\t\tEnter Name to Update Record : ";
    getline(cin, sname);

    for (int i = 0; i < students.size(); i++)
    {
       
        string storedName = students[i].getName();

        if (storedName == sname)
        {
            found = true;

            cout << "\t\t---Student Found----" << endl;
            cout << "\t\t 1. Update Rollno : " << endl;
            cout << "\t\t 2. Update Name : " << endl;
            cout << "\t\t 3. Update Age : " << endl;
            cout << "Enter Your Choice : ";
            cin >> choice;

            string name;
            string rno;

            switch (choice)
            {
            case 1:
                cout << "\t\tEnter New Rollno : ";
                cin >> rno;
                students[i].setRollno(rno);
                break;
            case 2:
                cout << "\t\tEnter New Name : ";
                cin.ignore();
                getline(cin, name);
                students[i].setName(name);
                break;
            case 3:
                int age;
                cout << "\t\tEnter New Age : ";
                cin >> age;
                students[i].setAge(age);
                break;
            default:
                cout << "\t\tInvalid Number" << endl;
            }
        }
    }

    if (!found)
    {
        cout << "\t\tRecord Not Found Here" << endl;
    }
}

// Function to search student in list
void SearchStudent(vector<Student> &students)
{
    string rollno;
    cout << "\t\tEnter Rollno : ";
    cin >> rollno;

    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].getRollno() == rollno)
        {
            cout << "-----Student Found------" << endl;
            students[i].displayStudent();
            return;
        }
    }
}

// Function to show all list of student
void DisplayAllStudent(vector<Student> &students)
{
    if (students.empty())
    {
        cout << "\t\t No Student Found" << endl;
        return;
    }

    for (int i = 0; i < students.size(); i++)
    {
        students[i].displayStudent();
        cout << endl;
    }
}

// Create a function to add new Student
void addNewStudent(vector<Student> &students, string rollno)
{
    // Check if student already exists
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].getRollno() == rollno)
        {
            cout << "\t\tStudent Already Exists..." << endl;
            return;
        }
    }

    string name;
    cout << "Enter Name: ";
    getline(cin,name);

    int age;
    cout << "Enter Age: ";
    cin >> age;

    Student newStudent(rollno, name, age);
    students.push_back(newStudent);

    cout << "\t\tStudent Added Successfully..." << endl;
}

//Function to delete student in list
void deleteStudent(vector<Student>& students, string name){

    for(int i=0;i<students.size();i++){
        if(students[i].getName() == name){
            students.erase(students.begin()+i);
            cout << "\t\tStudent Removed Successfully" << endl;
        }
    }
}

void writeStudentsToFile(const vector<Student> &students, const string &filename)
{
    ofstream outFile("students.txt");

    if (!outFile)
    {
        cerr << "Error opening file: " << "students.txt" << endl;
        return;
    }

    for (const auto &student : students)
    {
        outFile << student.getRollno() << "," << student.getName() << "," << student.getAge() << endl;
    }

    outFile.close();
}

void readStudentsFromFile(vector<Student> &students, const string &filename)
{
    ifstream inFile("students.txt");

    if (!inFile)
    {
        cerr << "Error opening file: " << "students.txt" << endl;
        return;
    }

    students.clear();

    string rollno, name, ageStr;
    while (getline(inFile, rollno, ',') && getline(inFile, name, ',') && getline(inFile, ageStr))
    {
        int age = stoi(ageStr);
        students.push_back(Student(rollno, name, age));
    }

    inFile.close();
}

int main()
{
    system("clear");
    vector<Student> students;
    const string filename = "students.txt";

    // Read existing student data from file
    readStudentsFromFile(students, filename);


    char choice;
    do
    {
        int op;
        cout << "\t\t--------------------------" << endl;
        cout << "\t\t Student Management System" << endl;
        cout << "\t\t--------------------------" << endl;
        cout << "\t\t1. Add New Student" << endl;
        cout << "\t\t2. Display All Student" << endl;
        cout << "\t\t3. Search Student" << endl;
        cout << "\t\t4. Update Student" << endl;
        cout << "\t\t5. Delete Student" << endl;
        cout << "\t\t6. Save and Exit" << endl;
        cout << "\t\tEnter Your Choice : ";
        cin >> op;

        // Clear the newline character from the buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string rollno;
        switch (op)
        {
        case 1:
            cout << "Enter Rollno : ";
            getline(cin,rollno);
            addNewStudent(students, rollno);
            break;
        case 2:
            DisplayAllStudent(students);
            break;
        case 3:
            SearchStudent(students);
            break;
        case 4:
            updateStudent(students);
            break;
        case 5:
            {
                string name;
                cout << "Enter Name to Delete : ";
                getline(cin, name);
                deleteStudent(students, name);
            }
            break;
        case 6:
            // Save the students to the file and exit
            writeStudentsToFile(students, filename);
            cout << "Exiting the program. Thank you!\n";
            exit(1);
        default:
            cout << "\t\tInvalid Number....." << endl;
        }
        cout << "\t\tDo You Want to Continue [Yes / No] ? :";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}