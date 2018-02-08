%{
    Chris Jakins
    ENGR1300-002
    3/24/2017
    Chapter 17, Review Question #8

    Problem Summary: find density of tribromoethylene in kg/m^3
%}


% housekeeping
clear
clc
close all

% conversion factors 
FEET_PER_METER = 3.28;
PASCALS_PER_ATM = 101325;

% input
height = 25; % ft
height = height / FEET_PER_METER; % m
pSurface = 3; % atm
pTotal = 5; % atm
gravity = 9.8; % m/s^2

% calculations and conversions
pHydro = pTotal - pSurface; % atm
pHydro = pHydro * PASCALS_PER_ATM; % Pa

% output
density = pHydro / (height * gravity) % kg/m^3