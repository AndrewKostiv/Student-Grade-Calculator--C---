#include <string>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <ctype.h>
#include <fstream>
#include <limits>

std::string toLetter(int numberGrade);
struct Student;
void menuPrints(std::vector<Student> &students);
void menuGetStudents(std::vector<Student> &students);
bool save(const std::vector<Student> &students);
bool load(std::vector<Student> &students);

struct Student
{
private:
    double average;

public:
    std::string name;
    std::vector<double> grades = {};

    double getAverage() const
    {
        double avg = 0;
        for (auto grade : grades)
        {
            avg += grade;
        }
        avg = avg / grades.size();
        return avg;
    }

    bool operator<(const Student &other) const
    {
        return getAverage() < other.getAverage();
    }

    void print()
    {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Average : " << getAverage() << " : " << '"' << toLetter(getAverage()) << '"' << std::endl;
    }
};

std::string toLetter(int numberGrade)
{
    if (numberGrade >= 95)
    {
        return "A";
    }
    else if (numberGrade >= 85)
    {
        return "B";
    }
    else if (numberGrade >= 80)
    {
        return "C";
    }
    else if (numberGrade >= 75)
    {
        return "D";
    }
    else
    {
        return "F";
    }
}

void sortStudents(std::vector<Student> &students)
{
    std::sort(students.begin(), students.end(), [](Student a, Student b)
              { return a.getAverage() > b.getAverage(); });
}

void inputGrade(double &grade)
{
    std::cin >> grade;
    while (std::cin.fail() || grade > 100)
    {
        std::cout << "Invalid input. Grade range is 0 - 100";
        std::cout << "Add grade: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> grade;
    }
}

void inputName(std::string &name)
{
    std::cin >> name;
    while (std::cin.fail() || name.size() > 100)
    {
        std::cout << "Invalid input. Name is too large" << std::endl;
        std::cout << "Input student name: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> name;
    }
}

std::vector<Student> addStudents(int studentCount)
{
    std::vector<Student> students;
    for (int i = 0; i < studentCount; i++)
    {
        Student student;
        std::cout << "Input student name: ";
        std::string name;
        inputName(name);
        student.name = name;
        std::cout << std::endl;

        std::cout << "Type -1 to stop inputing grades" << std::endl;
        double gradeInput = 0;
        while (!(gradeInput < 0))
        {
            std::cout << "Add grade: " << std::endl;
            inputGrade(gradeInput);
            if (gradeInput < 0)
                break;
            std::cout << std::endl;
            student.grades.push_back(gradeInput);
        }
        students.push_back(student);
    }
    return students;
}

void printStudents(std::vector<Student> &students)
{
    if (students.empty())
    {
        std::cout << "Students vector is empty" << std::endl;
        return;
    }
    sortStudents(students);
    std::cout << std::endl;
    std::cout << " -- Student Data -- " << std::endl;
    for (auto student : students)
    {
        student.print();
        std::cout << std::endl;
    }
}

bool findMaxAndMin(const std::vector<Student> &students, Student &maxStudent, Student &minStudent)
{
    if (!students.empty())
    {
        maxStudent = students.at(0);
        minStudent = students.at(0);

        for (auto student : students)
        {
            if (student.getAverage() > maxStudent.getAverage())
                maxStudent = student;
            if (student.getAverage() < minStudent.getAverage())
                minStudent = student;
        }
        return true;
    }
    else
    {
        return false;
    }
}

void printMaxAndMin(const std::vector<Student> &students)
{
    if (!students.empty())
    {
        Student maxStudent;
        Student minStudent;
        findMaxAndMin(students, maxStudent, minStudent);
        std::cout << "-- Max score -- " << std::endl;
        std::cout << "Student name: " << maxStudent.name << std::endl;
        std::cout << "Student average : " << maxStudent.getAverage() << " : " << '"' << toLetter(maxStudent.getAverage()) << '"' << std::endl;
    }
}

void menuPrints(std::vector<Student> &students)
{
    printStudents(students);
    printMaxAndMin(students);
    std::cout << "Add more students? [y|n]" << std::endl;
    char input;
    std::cin >> input;
    input = tolower(input);
    if (input == 'y')
    {
        menuGetStudents(students);
    }
    else
    {
        return;
    }
}

void inputCount(int &count)
{
    std::cin >> count;
    while (std::cin.fail() || count > 10)
    {
        std::cout << "Invalid input. Only inputs 1-10 are allowed" << std::endl;
        std::cout << "How many students: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> count;
    }
}

void menuGetStudents(std::vector<Student> &students)
{
    std::cout << "How many students: ";
    int studentCount;
    inputCount(studentCount);

    std::vector<Student> newStudents = addStudents(studentCount);
    students.insert(students.end(), newStudents.begin(), newStudents.end());

    save(students);
    std::cout << "Submit students? [y|n] ";
    char input;
    std::cin >> input;
    input = tolower(input);
    if (input == 'y')
    {
        menuPrints(students);
    }
    else
    {
        menuGetStudents(students);
    }
}

bool save(const std::vector<Student> &students)
{
    std::ofstream outFile("StudentData.txt"); // overwrite once

    if (!outFile)
    {
        std::cerr << "Error: Could not open file for writing.\n";
        return false;
    }

    for (const auto &s : students)
    {
        outFile << s.name << " ";
        for (double g : s.grades)
        {
            outFile << " " << g;
        }
        outFile << "\n"; // newline between students
    }

    outFile.close();
    return true;
}

bool load(std::vector<Student> &students)
{
    std::ifstream inFile("StudentData.txt");

    if (!inFile)
    {
        std::cerr << "Error: Could not open file for reading.\n";
        return false;
    }

    std::string name;
    while (inFile >> name)
    {
        Student s;
        s.name = name;

        double grade;
        s.grades.clear();
        while (inFile.peek() != '\n' && inFile >> grade)
        {
            s.grades.push_back(grade);
        }
        students.push_back(s);
    }
    inFile.close();
    return true;
}

int main(int argc, char const *argv[])
{
    std::vector<Student> students;
    load(students);
    menuGetStudents(students);
    return 0;
}