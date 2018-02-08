%{
    Chris Jakins 1000802309
    4/7/2017
    
    ICA 18-13

    Problem Summary: Determine the age difference between you and your BFF
    Input:  user's age
            best friend's name
            best friend's age
    Output: the age difference between user and best friend
%}

clc
clear
close all

% USER INPUT
userAge = input('Enter your age: ');
bffName = input('Enter the name of your BFF: ', 's');
bffAge = input('Enter the age of your BFF: ');

% CALCULATION
ageDiff = abs(userAge - bffAge);

% OUTPUT
fprintf('My age is %d years.\n', userAge);
fprintf('%s is my BFF. My friend''s age is %d years.\n', bffName, bffAge);
fprintf('The difference in our age is %d years.\n', ageDiff);
