%{
    Chris Jakins 1000802309
    4/28/2017
    
    RQ 18-14 & 18-15

    Problem Summary: Plot the experimental radius versus height, then find a 
                     theoretical power relationship and graph the
                     trendline
    Input:  radius (r) [cm]
            height (h) [cm]
    Output: plot of r vs h
%}

clear 
clc 
close all

radius = [.01 .05 .1 .2 .4 .5];
height = [14 3 1.5 .8 .4 .2];

figure('color', 'white')
plot(radius, height, 'o r', 'MarkerSize', 10, 'MarkerFaceColor', 'r');
grid 
grid minor
axis([0 .6 0 15])
xlabel('Radius (r) [cm]', 'FontWeight', 'bold', 'FontSize', 14);
ylabel('Height (H) [cm]', 'FontWeight', 'bold', 'FontSize', 14);
title('Capillary Action due to Surface Tension', 'FontSize', 16)

hold on

c = polyfit(log(radius), log(height), 1);
m = c(1);
b = exp(c(2));

rfp = [.01:.01:.5];
tfp = b * rfp .^ m;
plot(rfp, tfp, '-- k', 'LineWidth' , 3);

equation = sprintf('H = %.2fr^{%.2f}', b, m);
text(.3, 7, equation, 'FontSize', 12, 'EdgeColor', 'b')