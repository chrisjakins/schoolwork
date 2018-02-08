%{
    Chris Jakins 1000802309
    4/7/2017

    RQ 18-18

    Problem Summary: experimental plot of power versus diameter
    Input:  power vectors hp
            diameter vector ft
    Output: plot of the relationship 
%}

clear 
clc
close all

diameter = [.5 .75 1 1.5 2 2.25 2.5 2.75]; % ft
power = [.004 .04 .13 .65 3 8 18 22]; % hp

figure('color', 'white')
plot(diameter, power, 'o b', 'MarkerSize', 10, 'MarkerFaceColor', 'b');
grid
grid minor
axis([0 3 0 25])
xlabel('Diameter (D) [ft]', 'FontWeight', 'Bold', 'FontSize', 15);
ylabel('Power (P) [hp]', 'FontWeight', 'bold', 'FontSize', 15);
title('Wind Turbine Measurements', 'FontSize', 18, 'FontWeight', 'bold')
set(gca, 'YScale', 'log')