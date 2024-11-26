// Lab 12.4

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <Windows.h>

using namespace std;

struct Student 
{
    string surname;
    int grade1; 
    int grade2; 
    int grade3; 
    double average() const 
    {
        return (grade1 + grade2 + grade3) / 3.0;
    }
};

void printMenu() 
{
    cout << "\n����:\n";
    cout << "1. ������ ��������\n";
    cout << "2. �������� ��������\n";
    cout << "3. ���������� ���������� ��������\n";
    cout << "4. ��������� �� ������� �����\n";
    cout << "5. ��������� �� ��������\n";
    cout << "6. ��������� �� ������� � �������� ��������\n";
    cout << "7. ������� ������ ��������\n";
    cout << "8. �����\n";
    cout << "������� ��: ";
}

void addStudent(vector<Student>& students) 
{
    Student student;
    cout << "������ ������� ��������: ";
    cin >> student.surname;
    cout << "������ ������ � ����� ��������: ";
    cin >> student.grade1 >> student.grade2 >> student.grade3;
    students.push_back(student);
}

void deleteStudent(vector<Student>& students) 
{
    string surname;
    cout << "������ ������� �������� ��� ���������: ";
    cin >> surname;

    auto it = find_if(students.begin(), students.end(), [&surname](const Student& s) 
        {
        return s.surname == surname;
        });

    if (it != students.end()) 
    {
        students.erase(it);
        cout << "�������� ��������.\n";
    }
    else 
    {
        cout << "������� �� ���������.\n";
    }
}

void editStudent(vector<Student>& students) 
{
    string surname;
    cout << "������ ������� �������� ��� �����������: ";
    cin >> surname;

    auto it = find_if(students.begin(), students.end(), [&surname](const Student& s) 
        {
        return s.surname == surname;
        });

    if (it != students.end()) 
    {
        cout << "������ ��� ������ ��� �������� " << surname << ": ";
        cin >> it->grade1 >> it->grade2 >> it->grade3;
        cout << "���������� ��������.\n";
    }
    else 
    {
        cout << "������� �� ���������.\n";
    }
}

void sortByAverage(vector<Student>& students) 
{
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.average() > b.average();
        });
    cout << "������ ����������� �� ������� �����.\n";
}

void sortBySurname(vector<Student>& students) 
{
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.surname < b.surname;
        });
    cout << "������ ����������� �� ��������.\n";
}

void sortByGrade(vector<Student>& students, int subject) 
{
    sort(students.begin(), students.end(), [subject](const Student& a, const Student& b) 
        {
        int gradeA = (subject == 1) ? a.grade1 : (subject == 2) ? a.grade2 : a.grade3;
        int gradeB = (subject == 1) ? b.grade1 : (subject == 2) ? b.grade2 : b.grade3;
        return gradeA > gradeB;
        });
    cout << "������ ����������� �� ������� � �������� " << subject << ".\n";
}

void printStudents(const vector<Student>& students) 
{
    cout << "\n������ ��������:\n";
    cout << left << setw(15) << "�������" << setw(8) << "������� 1" << setw(8) << "������� 2" << setw(8) << "������� 3" << "������� ���\n";
    for (const auto& student : students) 
    {
        cout << left << setw(15) << student.surname
            << setw(8) << student.grade1
            << setw(8) << student.grade2
            << setw(8) << student.grade3
            << fixed << setprecision(2) << student.average() << endl;
    }
}

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector<Student> students;
    int choice;

    while (true) 
    {
        printMenu();
        cin >> choice;

        switch (choice) 
        {
        case 1:
            addStudent(students);
            break;
        case 2:
            deleteStudent(students);
            break;
        case 3:
            editStudent(students);
            break;
        case 4:
            sortByAverage(students);
            break;
        case 5:
            sortBySurname(students);
            break;
        case 6:
            int subject;
            cout << "������ ����� �������� (1, 2, 3): ";
            cin >> subject;
            sortByGrade(students, subject);
            break;
        case 7:
            printStudents(students);
            break;
        case 8:
            cout << "����� � ��������.\n";
            return 0;
        default:
            cout << "������� ����. ��������� �� ���.\n";
        }
    }
}
