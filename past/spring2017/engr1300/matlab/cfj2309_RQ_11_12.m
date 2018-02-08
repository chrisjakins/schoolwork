%{
    Chris Jakins 1000802309
    4/28/2017
    
    RQ 18-11 & 18-12

    Problem Summary: Plot the experimental temperature change versus heat
        applied, then find a theoretical linear relationship and graph the
        trendline
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

hold on
c = polyfit(heatApplied, tempChange, 1);
m = c(1);
b = c(2);

Hfp = [12:1:58];
Tfp = m * Hfp + b;

plot(Hfp, Tfp, ': b', 'LineWidth', 3);
equation = sprintf('T = %.2fQ + %.2f', m, b);
text(15, 6, equation, 'FontSize', 12, 'EdgeColor', 'k')