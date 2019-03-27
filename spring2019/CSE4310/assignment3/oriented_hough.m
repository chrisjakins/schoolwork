function votes = oriented_hough(grayscale, thetas, rhos, thr1, thr2);

%

edge_image = canny(grayscale, thr1);
%figure(1); imshow(edge_image);

[m, n] = size(rhos);
num_rhos = m * n;
[m, n] = size(thetas);
num_thetas = m * n;

votes = zeros(num_rhos, num_thetas);

[rows, cols] = size(grayscale);
orientations = gradient_orientations(grayscale);

for j = 1:cols
    for i = 1:rows
        if edge_image(i,j) == 1
            o = orientations(i, j);
            for k = 1:num_thetas
                if orientation_difference(o, thetas(k)) <= thr2
                   rho = find_rho(i, j, thetas(k));
                   p = closest_rho(rhos, rho);
                   votes(p, k) = votes(p, k) + 1;
                end
            end
        end
    end
end