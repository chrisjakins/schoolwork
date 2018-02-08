%{
    Chris Jakins
    4/12/2017
    graphical analysis
%}


clear
clc
close all

x = [0:5E04:3.0E+05];
y = 6*x + 4E05;
y1 = 10 * x + 0;
figure('color', 'white')
plot(x, y, '- r', 'LineWidth', 2)
hold on
plot(x, y1, '-- g', 'LineWidth', 2)