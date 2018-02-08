%{
    Chris Jakins        
    Sanjana Choudhary
    Erin Hollingsworth

    4/21/2017
    Group Project
    
    ENGR1300-002

    Problem Summary: Compute breakeven points based off of user input
    information for a material and its costs
%}

close all
clear
clc

%   **********
%   USER INPUT
%   **********

%   CONSTANTS FOR CONVERSIONS
LBM_PER_KG = 2.205;
GRAM_PER_KG = 1000;

%   WIDGET INPUT
widgetWeight = input('Enter the weight of one widget, in grams: ');
widgetSellingPrice = input('Enter the selling price of each widget, in dollars: ');

%   COST INPUT
equipmentName = input('Enter the name of the equipment option: ', 's');
initialPurchaseCost = input('Enter the initial purchase cost [$]: ');
energyCost = input('Enter the energy cost [$/widget]: ');
laborCost = input('Enter the labor cost [$/widget]: ');
maintenanceCost = input('Enter the maintenance cost [$/widget]: ');
landfillCost = input('Enter the landfill cost [$/widget]: ');
machineProduction = input('Enter the machine production [widget/day]: ');
materialCosts = input('Enter the material costs [$/lbm]: ');
materialCosts = materialCosts * LBM_PER_KG / GRAM_PER_KG;

%   PLANT OPERATION INPUT
numDays = input('Enter the number of days per week the plant will run: ');
numWeeks = input('Enter the number of weeks per year the plant will run: ');
numYears = input('Enter the number of years the analysis will include: ');

%   ************
%   CALCULATIONS
%   ************

%   TOTAL VARIABLE COST CALCULATIONS
numWidgetsProducedPerYear = machineProduction * numDays * numWeeks;
numWidgetsProducedTotal = numWidgetsProducedPerYear * numYears;
totalVariableCostOneWidget = (energyCost + laborCost + maintenanceCost + landfillCost + (materialCosts * widgetWeight));
variableCostOneYear = totalVariableCostOneWidget * numWidgetsProducedPerYear;
totalVariableCost = variableCostOneYear * numYears;

%   TOTAL COST CALCULATIONS
totalCostByYear = [0:numYears] * variableCostOneYear + initialPurchaseCost; % stored in vector as per year

%   TOTAL REVENUE CALCULATIONS
totalRevenueByYear = [0:numYears] * widgetSellingPrice * numWidgetsProducedPerYear; % vector as per year

%   TOTAL PROFIT CALCULATIONS
totalProfitByYear = totalRevenueByYear - totalCostByYear;

%	BREAKEVEN POINT CALCULATIONS
breakevenPointWidgets = initialPurchaseCost / (widgetSellingPrice - totalVariableCostOneWidget);
breakevenPointMonths = breakevenPointWidgets / (numWidgetsProducedPerYear / 12);

%   ******
%   OUTPUT
%   ******

fprintf('\nThe machine listed below will operate for %d days per year.\n\n', numDays * numWeeks);
fprintf('Option:    %s\n', equipmentName);
fprintf('\tProducing %d widgets each week will generate per year:\n', machineProduction * numDays);
fprintf('\t\tRevenue:\t$%.0f\n', totalRevenueByYear(2));
fprintf('\t\tCost:\t\t$%.0f\n', totalCostByYear(2));
fprintf('\tTotal number of widgets produced per year: %0.1e5\n', numWidgetsProducedPerYear);
fprintf('\tThe breakeven time is %d months or %d widgets.\n', round(breakevenPointMonths), round(breakevenPointWidgets));
fprintf('\tThe total profit after %d years is $%.0f\n', numYears, totalProfitByYear(numYears));

%   ****
%   PLOT
%   ****

% plot graph for widgets by dollars
widgetsVector = [0 : 10000 : numWidgetsProducedTotal / 4];
figure('color', 'white')

plot(widgetsVector, widgetsVector * widgetSellingPrice, 'b --', 'LineWidth', 2) % revenue
grid on
grid minor
hold on
plot(widgetsVector, widgetsVector * totalVariableCostOneWidget + initialPurchaseCost, 'k :', 'LineWidth', 2)    % cost
plot(breakevenPointWidgets, breakevenPointWidgets * widgetSellingPrice, 'r o', 'MarkerSize', 8, 'MarkerFaceColor', 'r')
xlabel('Widgets Produced [#]', 'FontWeight', 'bold', 'FontSize', 12)
ylabel('Dollars [$]', 'FontWeight', 'bold', 'FontSize', 12);
title('Determining the breakeven point of widgets', 'FontWeight', 'bold', 'FontSize', 14)
L = legend('Total Revenue', 'TotalCost', 'Breakeven Point', 'Location', 'best');
set(L, 'LineWidth', 2, 'FontSize', 8)

% plot graph for time by dollars
figure('color', 'white')

plot([0:numYears], (totalProfitByYear), 'k :', 'LineWidth', 2)
grid on
grid minor
hold on
plot(breakevenPointMonths / 12, 0, 'r o', 'MarkerFaceColor', 'r', 'MarkerSize', 8)
xlabel('Years [y]', 'FontWeight', 'bold', 'FontSize', 12)
ylabel('Profit [$]', 'FontWeight', 'bold', 'FontSize', 12)
title('Time to breakeven', 'FontWeight', 'bold', 'FontSize', 14)

%   END CODE

    
