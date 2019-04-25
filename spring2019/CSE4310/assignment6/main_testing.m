restoredefaultpath;
clear all;
close all;

addpath 'C:\Users\Chris Jakins\Desktop\schoolwork\spring2019\CSE4310\all_code\00_images\';
addpath 'C:\Users\Chris Jakins\Desktop\schoolwork\spring2019\CSE4310\assignment6';
addpath 'C:\Users\Chris Jakins\Desktop\schoolwork\spring2019\CSE4310\assignment6\mnist\';
addpath 'C:\Users\Chris Jakins\Desktop\schoolwork\spring2019\CSE4310\assignment6\digits_test\';
cd 'C:\Users\Chris Jakins\Desktop\schoolwork\spring2019\CSE4310\assignment6';


%%%%%%%%%

[vec, val] = mnist_pca('scrambled_mnist10000.bin', 2, 3);

%%%%%%%%%%

% image = imread('label0_test5.png');
% label = pca_classifier(image, 100);

%%%%%%%%%%

% accuracies = zeros(784, 1);
% for i = 1:30
%     [acc, con_mat] = pca_classifier_stats(i * 10);
%     accuracies(i, 1) = acc;
% end
% 
% maximum = max(accuracies);
% index = find(accuracies == maximum);

% [acc, con_mat] = pca_classifier_stats(1);

%%%%%%%%%%

% image = read_gray('Picture2.jpg');
% sc1 = shape_context_feature(image, 20, 20, 1);
% sc2 = shape_context_feature(image, 20, 20, 1);
% 
% %%%%%%%%%%
% 
% result = chi_squared(sc1, sc2);

%%%%%%%%%%

image = imread('Picture1.jpg');
result = hog_feature(image, 400, 100, 30);

%%%%%%%%%%