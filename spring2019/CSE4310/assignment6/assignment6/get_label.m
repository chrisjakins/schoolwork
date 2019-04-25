function class_label = get_label(vectors, image, d);

%
%
%

%% smallest backprojection error
errors = zeros(10, 1);
for i = 0:9
    eig_vec = vectors(:, 1 + d * i : d + d * i);
    proj = eig_vec' * image(:);
    backproj = eig_vec * proj;
    
    diff = backproj - image(:);
    errors(i + 1, 1) = sum(diff .* diff);
end

m = min(errors);
class_label = find(errors == m) - 1;



