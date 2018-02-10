#include <string>

class Student
{
    public:
        Student(std::string name) 
            : student_name{name}, exam_sum{0},
              exam_num_grades{0}, homework_sum{0},
              homework_num_grades{0}
        { } 

        std::string name()
        { return student_name; }

        void exam(double grade)
        {
            exam_sum += grade;
            exam_num_grades++;
        }

        double homework(double grade)
        {
            homework_sum += grade;
            homework_num_grades++;
        }

        double average()
        {
            if (exam_num_grades == 0 || homework_num_grades == 0)
                return 100;
            else
            {
                /* .4, .6 == respective weights for exam and homework grades */
                double exam_average = (exam_sum / exam_num_grades) * .4;
                double homework_average = (homework_sum / homework_num_grades) * .6; 
                return exam_average + homework_average;
            }
        }

    private:
        std::string student_name;
        double exam_sum;
        double exam_num_grades;
        double homework_sum;
        double homework_num_grades;
};
