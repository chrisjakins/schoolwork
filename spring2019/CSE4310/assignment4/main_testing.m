restoredefaultpath;
clear all;
close all;

addpath 'C:\Users\Chris Jakins\Desktop\schoolwork\spring2019\CSE4310\assignment4'
addpath 'C:\Users\Chris Jakins\Desktop\schoolwork\spring2019\CSE4310\assignment4\digits_test\';
cd 'C:\Users\Chris Jakins\Desktop\schoolwork\spring2019\CSE4310\assignment4'


%%%% 

% arr1 = [1 2 3;
%         4 5 6;
%         7 8 9];
% arr2 = [1 1 1;
%         1 1 1;
%         1 1 1];
%     
% res = euclidean_distance(arr1, arr2);
% res

%%%%%

% count = 0;
% for label = 0:9
%     for sample = 1:10
%         filename = sprintf('digits_test/label%d_test%d.png', label, sample);
%         im = imread(filename);
%         result = nnc_euclidean(im);
%         if result ~= label
%             count = count + 1;
%             label, sample, result
%         end
%     end
% end
% count

%%%%%%%

% [acc, con_mat] = nnc_euclidean_stats();

%%%%%%%%

% im1 = imread('digits_test/label0_test1.png');
% im2 = imread('digits_test/label0_test2.png');
% 
% chamfer_distance(im1, im2);

%%%%%%%

% im1 = imread('digits_test/label0_test1.png');
% 
% result = nnc_chamfer(im1);

%%%%%%%

[acc, con_mat] = nnc_chamfer_stats();