#include <iostream>
#include "student.cpp"

int main()
{
    /* test 1 */
    Student student{"Bjarne Stroustrup"};
    student.exam(100.0);
    student.exam(90.0);
    student.exam(80.0);
    student.homework(100);
    student.homework(90);
    student.homework(80);
    student.homework(70);
    student.homework(60);

    if (student.name() != "Bjarne Stroustrup")
        std::cout << "Bad. Improper initialization of 'student' object..." << std::endl;
    if (student.average() != 84.0)
        std::cout << "Bad! Incorrect values entered for exam and homework grades..." << std::endl;

    /* test 2*/
    Student nada{"Rob Stark"};
    if (nada.average() != 100.0)
        std::cout << "Bad! Incorrect handling of edge cases..." << std::endl;

    return 0;
}
