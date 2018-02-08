%{
    Chris Jakins 1000802309
    4/7/2017

    ICA 18-15

    Problem Summary: plot the experimental data
    Input:  Current vector [A]
            Power vector [W]
%}

clear
clc
close all

% INPUTS
current = [.5 1.25 1.5 2.25 3.0 3.2 3.5]; % [A]
power = [1.2 7.5 11.25 25.0 45.0 50.0 65.0]; % [W]

figure('color', 'white')
plot(current, power, 'o b', 'MarkerSize', 9, 'MarkerFaceColor', 'b');
grid
grid minor
axis([0 4 0 70])
xlabel('Current (I) [A]', 'FontWeight', 'bold', 'FontSize', 13);
ylabel('Power (P) [W]', 'FontWeight', 'bold', 'FontSize', 13);
title('Joule''s First Law', 'FontSize', 16);