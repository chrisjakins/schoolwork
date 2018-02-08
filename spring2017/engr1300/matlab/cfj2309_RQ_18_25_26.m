%{
    Chris Jakins 1000802309
    4/28/2017
    
    RQ 18-25 & 18-26

    Problem Summary: Plot the experimental years versus gear size, then find a 
                     theoretical exponentional relationship and graph the
                     trendline
    Input:  years from 1967 (Y) [y]
            gear size (S) [mm]
    Output: plot of Y vs S
%}

clear 
clc 
close all

yearsFrom1987 = [0 5 7 16 25 31 37];
minGearSize = [.8 .4 .2 .09 .007 .0002 .000008];

figure('color', 'white')
plot(yearsFrom1987, minGearSize, 'o r', 'MarkerSize', 10, 'MarkerFaceColor', 'r');
grid 
grid minor
axis([0 40 0 1])
xlabel('Minimum gear size (S) [mm]', 'FontWeight', 'bold', 'FontSize', 14);
ylabel('Years from 1987 (Y) [y]', 'FontWeight', 'bold', 'FontSize', 14);
title('Limits of Nanotechnology', 'FontSize', 16)

hold on

c = polyfit(yearsFrom1987, log(minGearSize), 1);
m = c(1);
b = exp(c(2));

Yfp = [0:1:37];
Gfp = b .* exp(m*Yfp);
plot(Yfp, Gfp, '-- k', 'LineWidth' , 3);

equation = sprintf('G = %.2f * e^{%.2fY}', b, m);
text(22, .5, equation, 'FontSize', 12, 'EdgeColor', 'b')
