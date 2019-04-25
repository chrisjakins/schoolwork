function labels = load_mnist_labels(filename)

% function labels = load_mnist_labels(filename)
%
% Loads the labels (not the images) of the MNIST data, from the specified
% filename. 

fid = fopen(filename, 'r');

[number, count] = fread(fid, 1, 'int32');
if count ~= 1
    disp('failed to read number');
end

[mnist_permutation, count] = fread(fid, number, 'int32');
if count ~= mnist_permutation
    disp('failed to read number');
end


labels = fread(fid, number, 'uchar');
if count ~= number
    disp('failed to read number');
end

fclose(fid);
