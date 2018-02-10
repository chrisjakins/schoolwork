#include <string>
#include <vector>

class Student
{
    public:
        Student(std::string name) 
            : student_name{name}
        { } 

        std::string name()
        {   return student_name; }

        double get_homework(int index)
        {   return homework_grades[index]; }

        double get_exam(int index)
        {   return exam_grades[index]; }

        int num_homeworks()
        {   return homework_grades.size(); }

        int num_exams()
        {   return exam_grades.size(); }

        void homework(double grade)
        {   homework_grades.push_back(grade); }

        void exam(double grade)
        {   exam_grades.push_back(grade); }

        /* if either no exam grades or no homework grades were input
           then student's average is 100 (thinking positive here) */
        double average()
        {
            if (exam_grades.size() == 0 || homework_grades.size() == 0)
                return 100;
            else
            {
                /* .4, .6 == respective weights for exam and homework grades */
                double exam_average = (sum(exam_grades) / exam_grades.size()) * .4;
                double homework_average = (sum(homework_grades) / homework_grades.size()) * .6; 
                return exam_average + homework_average;
            }
        }

    private:
        std::string student_name;
        std::vector<double> exam_grades;
        std::vector<double> homework_grades;

        double sum(std::vector<double> vals)
        {
            double total;
            for (int i = 0; i < vals.size(); i++)
                total += vals[i];
            return total;
        }
};
