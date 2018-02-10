/* Chris Jakins */
/* CSE1325 */
/* Hw2 9/7 */
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

    std::cout << "Enter exam grade (-1 to quit): ";
    std::cin >> grade;
    while (grade >= 0)
    {
        student.exam(grade);
        std::cout << "Enter exam grade (-1 to quit): ";
        std::cin >> grade;
    }

    std::cout << "Student name: " << student.name() << std::endl
              << "Student average: " << student.average() << std::endl;

    return 0;
}
