GE = [2007, 2010; 2008, 2315; 2009, 2474; 2010, 2748; 2011, 2791; 2012, 3282; 2013, 3508];

figure('color', 'white')
plot(GE(:,1), GE(:,2), 'x r', 'MarkerSize', 8)

c = polyfit(GE(:,1), GE(:,2), 1);
m = c(1);
b = c(2);

hold on
plot(GE(:,1), m*GE(:,1) + b, ': k', 'LineWidth', 3)

yearInput = input('Enter a prediction year, greater than 2013: ');
fprintf('In year %.0f, there will be %.0f students in General Engineering.\n', yearInput, (yearInput*m + b));