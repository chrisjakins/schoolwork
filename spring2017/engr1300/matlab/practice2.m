%{
chris jakins
3/20/2017
engr1300-002
Examples built-in functions & string data types
%}

clear       % workspace
clc         % cmd window
close all   % open figures

%get/generate data
scalar1 = 5;
scalar2 = 3;

vector1 = [0: 15: 180];
vector2 = [0: 10];
vector3 = [vector2; 5*vector2];
vector4 = [0: 0.5: 5;
           0: 1: 10];

% math functions
d = sqrt(scalar1);
d2 = sqrt(vector2);
f = nthroot(vector2, scalar2);
F = power(vector2, 3);
AA = exp(scalar1); % e^scalar1
BB = log(scalar1); % ln(scalar1)
CC = log10(scalar1);

% matrix manipulation
g = length(scalar2);
[r c] = size(vector4);
G = sum(vector2);

% working with strings
myZipCode = '76006-XXXX';
myZip5digit = myZipCode(1:5); % INDEXING DOES NOT START AT 0
eqnLines = 'y = mx+b';
myName = 'Leonardo di Caprio';
firstInitial = myName(1);
lastName = myName(10:end);


% get input
SG = .79;
gravity = 9.8;
radiusMax = .25;

% conversions
radiusMax = radiusMax * 2.54 / 100;
density = SG * 1000;

% solve and output
surfaceTension = power(radiusMax, 2) * gravity * density