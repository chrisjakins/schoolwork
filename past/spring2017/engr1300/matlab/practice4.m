%{
    Chris Jakins
    ENGR1300-002
    Classwork 3/27/2017

    Built-in functions, input(), menu(), fprintf()
%}

clear
clc
close all

% oil change example showcasing input()
lastOil = input('How long ago was last oil change [mm yyyy]: ');
carType = input('Make and Model: ', 's');
longLine = input('How many people are in line: ');
waitTime = input('How long is the wait (minutes): ');
techName = input('What is the tech''s name: ', 's');

% drink strings showcasing menu()
drinks = {'Dew', 'Iced Tea', 'Water', 'Coffee', 'Rockstar', 'Beer'};
drinkChoice = menu('Choose a drink', drinks);
myDrink = drinks{drinkChoice};

depts = {'Billing', 'Manager', 'Parts', 'Service'};
deptInput = menu('Which department: ', depts);
deptToSee = depts{deptInput};

% fprintf
% f - float, s - string, e/E - exponent
fprintf('My Tech''s name is \t%s.\n', techName);
fprintf('I waited too long, %0.0f minutes, for my car.\n', waitTime);

