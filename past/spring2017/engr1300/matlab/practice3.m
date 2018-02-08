%{
Chris Jakins
ENGR1300-002
3/22

cell arrays, matrices
%}

% housekeeping
clear
clc
close all

% combining/working with vectors and matrices
b = [1 2 3];
d = [7 8 9; 
     4 5 6];
 
M = [d; b];
f1 = M(2);

% working with strings
f = 'dog';
g = 'bird';
h = [g, f];
f2 = h(1:4);

% cell arrays can combine any kind of data
J = {g, f};
f3 = J(1);
f4 = J{1};

firstInitial = f4(1);
f5 = J{1}(1);

% cell array work
M = {f, b};
N = {M, g};

% learning how to access elements of cell arrays
Person = {{'Skywalker', 'Luke'}, 'Jedi', 31, [5,10]};
x = Person{1};
x1 = Person{1}{2};
x2 = Person{4}(2);
x3 = Person{3};

% examples matrix math
r = 3;
H = 4;
V = pi*r^2*H
SA = 2 * pi * r * H + 2 * pi * r^2

r = [r 3.1 3.2];
H = [H 4.1 4.2];

V1 = pi * r.^2 .* H
SA1 = 2 * pi * r .* H + 2 * pi * r.^2

% functions
answer = input('How many are in your party: '); % numeric
rsvp = input('and your name: ', 's');           % string
kidMenu = input('How many kid''s menus: ');
seatArea = input('inside or outside (i/o/d): ', 's');