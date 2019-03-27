function index = closest_rho(rhos, rho);

index = 1;
[m, n] = size(rhos);
el = m * n;
for i = 2:el
    if abs(rhos(i) - rho) <= abs(rhos(i - 1) - rho)
        index = i;
    end
end