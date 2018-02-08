%{
    Chris Jakins
    ENGR1300-002
    5/5/2017
    Review Question, Chapter 19 #9

    Problem Summary: Determine the spectral color the user-entered
                        wavelength falls
    Variables: 
        Input:  wavelength [nm]
        Output: spectral color
%}

clear
clc
close all

% input
wavelength = input('Enter your wavelength: ');

% decision tree 
if (wavelength < 400 || wavelength > 700)
    color = 'not in the visible spectrum';
elseif (wavelength < 450)
    color = 'violet';
elseif (wavelength < 490)
    color = 'blue';
elseif (wavelength < 560)
    color = 'green';
elseif (wavelength < 590)
    color = 'yellow';
elseif (wavelength < 635)
    color = 'orange';
else
    color = 'red';
end

% output
fprintf('Wavelength of %.0f nm is %s.\n', wavelength, color);
    