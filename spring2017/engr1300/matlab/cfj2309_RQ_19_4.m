%{
    Chris Jakins
    ENGR1300-002
    5/5/2017
    Review Question, Chapter 19 #4

    Problem Summary: Find the distance in kilometers
    Variables: 
        Input:  mpg [miles per gallon]
                mass [g] (user defined)
                density_ethanol [g/ml]
        Output: total_km [km]
    Assumptions:
%}

clear 
clc
close all

% defined input values
mpg = 10705;
%mass = 100; % g ethanol (test case)
density_ethanol = .789; %g/ml
milliliters_per_liter = 1000;
gallons_per_liter = .264;
miles_per_kilometer = .621; 

% user input
mass = input('Enter the mass of ethanol in grams (between 0 and 500): ');

if (mass < 0 || mass > 500)
    error('Mass must be between 0 and 500')
end

% calculations and conversions
density_ethanol = (density_ethanol * milliliters_per_liter) / gallons_per_liter; % g/ml -> g/L -> g/gal
volume = mass / density_ethanol; % gal
total_miles = mpg * volume; % mi
total_km = total_miles / miles_per_kilometer;

% output
fprintf('The distance the Microjoule traveled is %.0f kilometers.\n', total_km)


