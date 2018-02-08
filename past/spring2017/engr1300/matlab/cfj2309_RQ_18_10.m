%{
    Chris Jakins 1000802309
    ENGR1300-001
    3/29/2017

    Problem Summary: plot braking times at certain speeds as a function
                    of reaction times and braking times
    Inputs: velocity (v) [mph]
%}

clear
clc
close all

% CONSTANTS
METERS_PER_MILE = 1609.34;
SECONDS_PER_HR = 3600;

% INPUTS
velocity = [20:10:70] * METERS_PER_MILE / SECONDS_PER_HR; % m/s
reactionDistance = [6: 3: 21]; % m
brakingDistance = [6 14 24 38 55 75];

% PLOTTING
figure('color', 'w')
hold on
plot(velocity, reactionDistance, 'x b', 'MarkerSize', 10)
plot(velocity, brakingDistance, 'o r', 'MarkerSize', 10)
plot(velocity, (reactionDistance + brakingDistance), 's k', 'MarkerSize', 10)
grid 
grid minor
axis([0 35 0 100])
xlabel('Velocity (V) [m/s]', 'FontWeight', 'bold', 'FontSize', 12)
ylabel('Distance (d) [m]', 'FontWeight', 'bold', 'FontSize', 12)
legend('Reaction Distance', 'Braking Distance', 'Total Distance', 'Location', 'Best')
title('How far will I travel when I hit the brakes?', 'FontSize', 12)
