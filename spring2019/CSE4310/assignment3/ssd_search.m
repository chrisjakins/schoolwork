function result = ssd_search(grayscale, template)

%

[m, n] = size(grayscale);
[t_rows, t_cols] = size(template);
rh = floor(t_rows / 2);
ch = floor(t_cols / 2);
result = ones(m,n) * -1;

for j = 1 + ch : n - ch
    for i = 1 + rh : m - rh
        window = grayscale(i - rh : i + rh, j - ch : j + ch);
        diff = window(:) - template(:);
        result(i,j) = sum(diff .* diff);
    end
end