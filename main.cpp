#include <string>
#include <iostream>
#include <vector>
#include <numeric>

struct Student
{
    std::string name;
    std::vector<short int> grades = {};
    double average;
};

std::vector<Student> addStudents(int studentCount)
{
    std::vector<Student> students;
    for (int i = 0; i < studentCount; i++)
    {
        Student student;
        std::cout << "Input student name: ";
        std::string name;
        std::cin >> name;
        std::cout << std::endl;
        student.name = name;
        std::cout << "Type -1 to stop inputing grades" << std::endl;
        int gradeInput = 0;
        while (!(gradeInput < 0))
        {
            std::cout << "Add grade: " << std::endl;
            std::cin >> gradeInput;
            if (gradeInput < 0)
                break;
            std::cout << std::endl;
            student.grades.push_back(gradeInput);
        }

        // calculate average
        int average = 0;
        for (auto grade : student.grades)
        {
            average += grade;
        }
        student.average = int(average / student.grades.size());

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

    std::cout << "Student Data:" << std::endl;
    for (auto student : students)
    {
        std::cout << "Name: " << student.name << std::endl;
        std::cout << "Average: " << student.average << std::endl;
        std::cout << std::endl;
    }
}

bool findMaxAndMin(std::vector<Student> students, Student &maxStudent, Student &minStudent)
{
    if (!students.empty())
    {
        maxStudent = students.at(0);
        minStudent = students.at(0);

        for (auto student : students)
        {
            if (student.average > maxStudent.average)
                maxStudent = student;
            if (student.average < minStudent.average)
                minStudent = student;
        }
        return true;
    }
    else
    {
        return false;
    }
}

int main(int argc, char const *argv[])
{
    int studentCount;
    std::cout << "How many students: ";
    std::cin >> studentCount;
    std::vector<Student> students = addStudents(studentCount);
    printStudents(students);
    Student maxStudent;
    Student minStudent;
    findMaxAndMin(students, maxStudent, minStudent);
    std::cout << "Max score: " << std::endl;
    std::cout << "Student name: " << maxStudent.name << std::endl;
    std::cout << "Student average : " << maxStudent.average << std::endl;
    return 0;
}
