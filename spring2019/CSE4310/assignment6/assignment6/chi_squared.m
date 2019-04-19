function result = chi_squared(sc1, sc2);

%
%
%

result = 0;

for j = 1:12
    for i = 1:5
        numer = (sc1(i,j) - sc2(i,j))^2;
        denom = sc1(i,j) + sc2(i,j);
        result = result + (numer / denom);
    end
end

result = result / 2;