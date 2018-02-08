%{
Chris Jakins
3/29/2017

Abscissa (x axis)
    independent variable controlled param
Ordinate (y axis)
    dependent variable measured param

FORMATTING
label axes to include variable, (symbol), [units]
title at the top as descriptive as possible
gridlines (horiz and vert)
experimental - just the points
theoretical - line
2+ data sets - include a legend
%}

clear
clc 
close all

voltage = [18 30 40 45];
rectA = [5 18 24 30];
rectB = [15 26 34 50];

% PLOTTING
figure('color', 'white')
% plot(voltage, rectA, 'r o', voltage, rectB, 'x b')
% plot(voltage, rectA, 'r o', voltage, rectB, 'x b', 'MarkerSize', 10, 'MarkerFaceColor', 'r')
plot(voltage, rectA, 'r o', 'MarkerSize', 10, 'MarkerFaceColor', 'r')
hold on
plot(voltage, rectB, 'b s', 'MarkerSize', 10, 'MarkerFaceColor', 'b')
grid
grid minor
axis([0 50 0 60])
xlabel('Voltage (V) [V]', 'FontWeight', 'bold', 'FontSize', 13)
ylabel('Current (I) [mA]', 'FontWeight', 'bold', 'FontSize', 13)
legend('Rectifier A', 'Rectifier B', 'Location', 'Best')
title('Measuring Current Across Two Rectifiers')

helloWorld = 'Hello World';
text(10, 40, helloWorld, 'BackgroundColor', 'w', 'EdgeColor', 'k','FontSize', 10)

% advanced 

% grid spacing
set(gca, 'XTick', 0:5:50)
% legend
L = legend('Rectifier A', 'Rectifier B', 'Location', 'Best');
set(L, 'FontSize', 12, 'TextColor', 'b')