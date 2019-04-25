function [eig_vectors, eig_values] = mnist_pca(data_file, class_label, d);

%
%
%

%%
mnist_file = data_file;
load_mnist;

%% pull appropriate data and vectorize
indices = find(mnist_labels == class_label);
digits = mnist_digits(:,:,indices);

[m,n,p] = size(digits);
digits = single(reshape(digits, [m*n, p]));

%% normalize for brightness and contrast and get covariance matrix
num = size(digits, 2);
for i = 1:num
    image = digits(:, i);
    image = (image - mean(image)) / std(image);
    digits(:, i) = image;
end

cov = digits * digits';

%% get top d eig-values/-vectors
[eig_vectors, eig_values] = eig(cov);
eig_values = diag(eig_values);

[eig_values, indices] = sort(eig_values, 'descend');
eig_vectors = eig_vectors(:, indices);

eig_values = eig_values(1:d);
eig_vectors = eig_vectors(:,1:d);

