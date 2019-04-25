function eigenvectors = optimized_classifier(d);

%
%
%

%% load mnist data set and set data up for use
mnist_file = 'scrambled_mnist10000.bin';
load_mnist;

%% store all of top d eigenvalues/-vectors for each class label
eigenvectors = [];
for i = 0:9
    indices = find(mnist_labels == i);
    digits = mnist_digits(:,:,indices);

    [m,n,p] = size(digits);
    digits = single(reshape(digits, [m*n, p]));

    %% average mnist data if necessary
    num = size(digits, 2);
    for i = 1:num
        image = digits(:, i);
        image = (image - mean(image)) / std(image);
        digits(:, i) = image;
    end
    
    %% Compute eigenvalues and eigenvectors using covariance matrix
    cov = digits * digits';
    [eig_vectors, eig_values] = eig(cov);
    
    %% grab only necessary eigenvalues/-vectors
    eig_values = diag(eig_values);
    [eig_values, indices] = sort(eig_values, 'descend');
    
    eig_vectors = eig_vectors(:, indices);
    eig_vectors = eig_vectors(:,1:d);

    %% append to final result
    eigenvectors = [eigenvectors, eig_vectors];
end


