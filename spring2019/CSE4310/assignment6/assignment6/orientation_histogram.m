function histogram = orientation_histogram(image);

%
%
%


%% setup
[m,n] = size(image);

%% compute gradients and orientations
grad_dx = single(imfilter(image, [-1,0,1]));
grad_dy = single(imfilter(image, [-1,0,1]'));

orientations = zeros(size(image));
histogram = zeros(9,1);

for j = 1:n
    for i = 1:m
        orientations(i,j) = 360 * atan2(grad_dy(i,j), grad_dx(i,j)) / pi;
        
        angle = floor(orientations(i, j) / 22.5 + 1);
        
        weight = sqrt(grad_dx(i,j)^2 + grad_dy(i,j)^2);
        histogram(angle, 1) = histogram(angle, 1) + weight;
    end
end
