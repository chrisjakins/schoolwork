/* Chris Jakins */
/* CSE1325 */
/* HW2 9/7 */
#include <iostream>
#include <string>
#include "student.cpp"

int main()
{
    std::string name;
    double grade;

    std::cout << "Enter the student's name: ";
    getline(std::cin, name);
    Student student{name};

    std::cout << "Enter exam grade (negative number to quit): ";
    std::cin >> grade;
    while (grade >= 0)
    {
        student.exam(grade);
        std::cout << "Enter exam grade (negative number to quit): ";
        std::cin >> grade;
    }

    std::cout << "Enter homework grade (negative number to quit): ";
    std::cin >> grade;
    while (grade >= 0)
    {
        student.homework(grade);
        std::cout << "Enter homework grade (negative number to quit): ";
        std::cin >> grade;
    }

    std::cout << "Student name: " << student.name() << std::endl
              << "Student average: " << student.average() << std::endl;

    return 0;
}
