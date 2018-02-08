%{
    4/26/2017

    models
%}

clear
close all
clc 

% LINEAR model - polyfit()
T = [ 375 395 420 450 500]; % x's [K]
P = [2.2 2.3 2.5 2.6 2.9]; % y's [atm]

% experimental
figure('color', 'white')
plot(T, P, 'd r', 'MarkerSize', 10, 'MarkerFaceColor', 'r')
axis([350 550 2 3])
grid on
grid minor
xlabel('Temperature (T) [K]', 'FontWeight', 'bold', 'FontSize', 14)
ylabel('Pressure (P) [atm]', 'FontWeight', 'bold', 'FontSize', 14)

% generating
c = polyfit(T, P, 1);
m = c(1);
b = c(2);
Tpf = [375:5:500];
Ppf = m*Tpf + b; % y = mx + b with new values

hold on
plot(Tpf, Ppf, '-- k', 'LineWidth', 2)
eq = sprintf('P = %.2fT + %.3f', m, b);
text(450, 2.2, eq, 'FontSize', 12, 'EdgeColor', 'g');


close all

% POWER model
R = [.5 1 1.25 1.5 2];
V = [3 13 20 28 50];
plot(R, V, 'sb', 'MarkerFaceColor', 'b', 'MarkerSize', 14)

c = polyfit(log(R), log(V), 1);
m = c(1);
b = exp(c(2));

Rpf = [.5:.1:2];
Vpf = b * Rpf.^m;
hold on
grid on 
grid minor
plot (Rpf, Vpf, ': m', 'LineWidth', 3)
eq2 = sprintf('V = %.1fR^{%.0f}', b, m); % ^{exp}

text(1, 40, eq2, 'EdgeColor', 'b', 'FontSize', 18);


close all

% EXPONENTIAL model
t = [1 5 15 20 30];
V = [18.1 12.1 4.5 2.75 1];
figure('color', 'white')
plot(t, V, 'hg', 'MarkerFaceColor', 'g', 'MarkerSize', 14)
grid on
grid minor

c = polyfit(t, log(V), 1);
m = c(1);
b = exp(c(2));

hold on
tpf = [1:1:30];
vpf = b .* exp(m*tpf);

plot(tpf, vpf, '-. k', 'LineWidth', 3)

eq3 = sprintf('V = %.2f * e^{%.1f * t}', b, m)
text(15, 13, eq3, 'FontSize', 12, 'EdgeColor', 'k')
