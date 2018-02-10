#include <string>

class Student
{
    public:
        Student(std::string name) 
            : student_name{name},
              exam_sum{0},
              exam_num_grades{0}
        { } 

        std::string name()
        { return student_name; }

        void exam(double grade)
        {
            exam_sum += grade;
            exam_num_grades++;
        }

        double average()
        {
            if (exam_num_grades == 0)
                return 100;
            else
                return exam_sum / exam_num_grades;
        }

    private:
        std::string student_name;
        double exam_sum;
        double exam_num_grades;

};
