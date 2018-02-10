/* Chris Jakins */
/* CSE1325 */
/* HW2 9/7 */
#include <iostream>
#include <string>
#include <vector>
#include "student.cpp"

int main()
{
    std::vector<Student> students;
    std::string name;
    double grade;
    
    getline(std::cin, name);
    while (name != "exit")
    {
        students.push_back(name); 

        std::cin >> grade;
        while (grade >= 0)
        {
            students[students.size() - 1].exam(grade);
            std::cin >> grade;
        }

        std::cin >> grade;
        while (grade >= 0)
        {
            students[students.size() - 1].homework(grade);
            std::cin >> grade;
        }

        std::cin.ignore();
        getline(std::cin, name);
    }
    std::cout << "\n";

    /*  outputs student information in this format :
        Name
        Exam grades (terminated by -1)
        Homework grades (terminated by -1)
        Average
    */
    for (int i = 0; i < students.size(); i++)
    {
        std::cout << students[i].name() << std::endl;

        for (int j = 0; j < students[i].num_exams(); j++)
            std::cout << students[i].get_exam(j) << " ";
        std::cout << "-1" << std::endl;

        for (int j = 0; j < students[i].num_homeworks(); j++)
            std::cout << students[i].get_homework(j) << " ";
        std::cout << "-1" << std::endl;

        std::cout << students[i].average() << std::endl;
    }

    std::cout << "exit" << std::endl;
    return 0;
}
