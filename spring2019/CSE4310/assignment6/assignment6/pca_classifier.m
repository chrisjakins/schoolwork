function class_label = pca_classifier(image, d);

%
%
%

errors = zeros(10, 1);
for i = 0:9
    [eig_vec, eig_val] = mnist_pca('scrambled_mnist10000.bin', i, d);
    proj = eig_vec' * image(:);
    backproj = eig_vec * proj;
    
    diff = backproj - image(:);
    errors(i + 1, 1) = sum(diff .* diff);
end

m = min(errors);
class_label = find(errors == m) - 1;
