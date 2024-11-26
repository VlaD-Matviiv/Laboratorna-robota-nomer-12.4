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
    cout << "\nМеню:\n";
    cout << "1. Додати студента\n";
    cout << "2. Видалити студента\n";
    cout << "3. Редагувати інформацію студента\n";
    cout << "4. Сортувати за середнім балом\n";
    cout << "5. Сортувати за прізвищем\n";
    cout << "6. Сортувати за оцінкою з заданого предмету\n";
    cout << "7. Вивести список студентів\n";
    cout << "8. Вийти\n";
    cout << "Виберіть дію: ";
}

void addStudent(vector<Student>& students) 
{
    Student student;
    cout << "Введіть прізвище студента: ";
    cin >> student.surname;
    cout << "Введіть оцінки з трьох предметів: ";
    cin >> student.grade1 >> student.grade2 >> student.grade3;
    students.push_back(student);
}

void deleteStudent(vector<Student>& students) 
{
    string surname;
    cout << "Введіть прізвище студента для видалення: ";
    cin >> surname;

    auto it = find_if(students.begin(), students.end(), [&surname](const Student& s) 
        {
        return s.surname == surname;
        });

    if (it != students.end()) 
    {
        students.erase(it);
        cout << "Студента видалено.\n";
    }
    else 
    {
        cout << "Студент не знайдений.\n";
    }
}

void editStudent(vector<Student>& students) 
{
    string surname;
    cout << "Введіть прізвище студента для редагування: ";
    cin >> surname;

    auto it = find_if(students.begin(), students.end(), [&surname](const Student& s) 
        {
        return s.surname == surname;
        });

    if (it != students.end()) 
    {
        cout << "Введіть нові оцінки для студента " << surname << ": ";
        cin >> it->grade1 >> it->grade2 >> it->grade3;
        cout << "Інформацію оновлено.\n";
    }
    else 
    {
        cout << "Студент не знайдений.\n";
    }
}

void sortByAverage(vector<Student>& students) 
{
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.average() > b.average();
        });
    cout << "Список відсортовано за середнім балом.\n";
}

void sortBySurname(vector<Student>& students) 
{
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.surname < b.surname;
        });
    cout << "Список відсортовано за прізвищем.\n";
}

void sortByGrade(vector<Student>& students, int subject) 
{
    sort(students.begin(), students.end(), [subject](const Student& a, const Student& b) 
        {
        int gradeA = (subject == 1) ? a.grade1 : (subject == 2) ? a.grade2 : a.grade3;
        int gradeB = (subject == 1) ? b.grade1 : (subject == 2) ? b.grade2 : b.grade3;
        return gradeA > gradeB;
        });
    cout << "Список відсортовано за оцінкою з предмету " << subject << ".\n";
}

void printStudents(const vector<Student>& students) 
{
    cout << "\nСписок студентів:\n";
    cout << left << setw(15) << "Прізвище" << setw(8) << "Предмет 1" << setw(8) << "Предмет 2" << setw(8) << "Предмет 3" << "Середній бал\n";
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
            cout << "Введіть номер предмета (1, 2, 3): ";
            cin >> subject;
            sortByGrade(students, subject);
            break;
        case 7:
            printStudents(students);
            break;
        case 8:
            cout << "Вихід з програми.\n";
            return 0;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    }
}
