function [labels, images] = load_mnist_selection(filename, indices)

% function [labels, images] = load_mnist_selection(filename, indices)
%
% Loads only a subset of MNIST labels and images, from the specified
% filename. The desired subset is specified by the indices argument.

fid = fopen(filename, 'r');

[total_number, count] = fread(fid, 1, 'int32');
if count ~= 1
    disp('failed to read number');
end

number = numel(indices);
labels = zeros(number, 1);
images = zeros(28, 28, number, 'uint8');

first_offset = 4 + total_number*4;
second_offset = 4 + total_number*5;

for counter = 1:number
    index = indices(counter);
    
    offset = first_offset + (index - 1);
    fseek(fid, offset, 'bof');
    labels(counter) = fread(fid, 1, 'uint8');
    
    offset = second_offset + 28*28*(index - 1);
    fseek(fid, offset, 'bof');
    images(:,:,counter) = fread(fid, [28, 28], 'uint8');
end

fclose(fid);
