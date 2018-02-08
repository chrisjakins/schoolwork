%{
    Chris Jakins
    3/29/2017
    Theoretical plotting - lines
%}

clear
clc 
close all

b_0 = 10; % initial Bacteria Concentration (BC) [#]
k1 = 0.2; % BC growth rate [per hr]
k2 = 0.3;
t = [0: 0.1: 5]; % Time (t) [hr]
B1 = b_0 * exp(k1*t);
B2 = b_0 * exp(k2*t);

figure('color', 'w')
plot(t, B1, '-- r', 'LineWidth', 1.5)
hold on
plot(t, B2, ': b', 'LineWidth', 1.5)
grid
grid minor
