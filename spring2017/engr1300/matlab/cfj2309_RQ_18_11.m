%{
    Chris Jakins 1000802309
    4/7/2017
    
    RQ 18-11

    Problem Summary: Plot the experimental temperature change versus heat
        applied
    Input:  Change in temp vector [K]
            Heat Applied vector [J]
    Output: plot of m * Cp
%}

clear
clc
close all

heatApplied = [12 17 25 40 50 58]; % J
tempChange = [1.5 2.0 3.25 5.0 6.25 7.0]; % K

figure('color', 'white')
plot(heatApplied, tempChange, 'o r', 'MarkerSize', 10, 'MarkerFaceColor', 'r');
grid 
grid minor
axis([0 60 0 8])
xlabel('Heat Applied (Q) [J]', 'FontWeight', 'bold', 'FontSize', 14);
ylabel('Change in Temperature (\DeltaT) [K]', 'FontWeight', 'bold', 'FontSize', 14);
title('Observing Thermal Energy', 'FontSize', 16)