%{
    Chris Jakins
    5/1/2017

    ENGR1300

    Conditionals
%}

clear 
close all
clc
%{
temp = input('Enter your temp (deg C): ');

if temp <= -273
    error('Invalid temp. Program quitting...');
end

if temp >= 0 && temp <= 100
    phase = 'liquid';
elseif temp < 0
    phase = 'solid';
else
    phase = 'gas';
end


% strcmp() and strcmpi()

x = input('Enter string1: ', 's');
y = input('Enter string2: ', 's');

if (x == y)         % don't use
    fprintf('Match\n')
end

if strcmp(x, y)     % case-sens
    fprintf('strc1: match\n')
end

if strcmpi(x, y)    % non-case-sens
    fprintf('strci: match\n')
end
%}
age = input('Enter age: ');
sysPress = input('Enter systolic pressure: ');
diasPress = input('Enter diastolic pressure: ');

if (age < 15 || age > 24)
    error('Age out of bounds. Program quitting...')
end

if (age >= 15 && age <= 19)
    if (sysPress > 120 || diasPress > 81)
        fprintf('HIGH BP!\n');
    else
        fprintf('NORMAL BP\n');
    end
else
    if (sysPress > 132 || diasPress > 83)
        fprintf('HIGH BP!\n');
    else
        fprintf('NORMAL BP\n');
    end
end


    
