%{
    Chris Jakins
    ENGR1300-002
    5/5/2017
    Review Question, Chapter 19 #20

    Problem Summary: Output the grade based off of user input
    Variables: 
        Input:  numeric grade between 0 and 100
        Output: letter grade
%} 

clear
clc
close all

% input
studentGrade = input('Enter the grade of the student (between 0 and 100): ');

if (studentGrade < 0 || studentGrade > 100)
    error('Input invalid, not between 0 and 100. Program quitting...');
end

if (studentGrade < 60)
    letterGrade = 'F';
elseif (studentGrade < 70)
    letterGrade = 'D';
elseif (studentGrade < 80)
    letterGrade = 'C';
elseif (studentGrade < 90)
    letterGrade = 'B';
else
    letterGrade = 'A';
end

fprintf('Student has numeric grade: %.0f\nRecieves letter grade %s\n', studentGrade, letterGrade);
