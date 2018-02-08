%{
    Chris Jakins 1000802309
    ENGR1300-002
    4/10/2017

    Exam 2
%}

clear
clc 
close all

% CONSTANTS defined for later use %
DENSITY_OF_WATER = 1000; % kg / m^3
CENT_PER_METER = 100;
LBM_PER_KG = 2.205;

Cereal = {'Crazy Marshmallows', 'Cinnamonairs', 'Loopy Loops', 'Crunch Brunch'};
%        SG L  W  H
Specs = [.1 20 5 22;
         .168 20 4.5 24.5;
         .103 20 5.5 30.5
         .118 20 7 32];
UnitCostsPerCereal = [3 1.75 1.5 2.5]; % $/lbm
UnitCostsPerCereal = UnitCostsPerCereal * LBM_PER_KG; % $/kg

% USER INPUTS %
Choice = menu('What cereal would you like to order?', Cereal);
Box = input('Enter the number of boxes you would like: ');
Ship = menu('How would you like it shipped?', 'Regular', 'Expedited');

% CALCULATIONS %

% sg * density of water = density of cereal chosen
Dense = Specs(Choice, 1) * DENSITY_OF_WATER; % kg / m^3

Volume = (Specs(Choice, 2) / CENT_PER_METER) * (Specs(Choice, 3) / CENT_PER_METER) * (Specs(Choice, 4) / CENT_PER_METER);
% m^3

Mass = Dense * Volume; % kg

Cost = Mass * UnitCostsPerCereal(Choice); % $ 

TCost = Cost * Ship; % 1 for Regular or 2 for Expedited

% OUTPUT %

fprintf('You ordered %d boxes of %s cereal. With your selected shipping method, the total cost of your order is $%.2f', Box, Cereal{Choice}, TCost * Box);

VarBox = [0:5:100];
VarCost = TCost * VarBox; % Increments of 5 still

figure('Color', 'white')
plot(VarBox, VarCost, 'k --', 'LineWidth', 3);
xlabel('Number of Boxes (N) [#]' , 'FontWeight', 'bold', 'FontSize', 16);
ylabel('Total Cost (C) [$]' , 'FontWeight', 'bold', 'FontSize', 16);
grid
grid minor
