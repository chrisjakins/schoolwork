% Chris Jakins 1000802309
% Assignment 1
% 2/1/2019

%
%
%

restoredefaultpath;
clear all;
close all;

addpath 'C:\Users\Chris Jakins\Desktop\schoolwork\spring2019\CSE4310\assignment2'
addpath 'C:\Users\Chris Jakins\Desktop\schoolwork\spring2019\CSE4310\assignment2\data'
cd 'C:\Users\Chris Jakins\Desktop\schoolwork\spring2019\CSE4310\assignment2'

% image = imread('data\zebra_with_holes.gif', 'gif');
% test_image = imread('data\zebra_without_holes.gif', 'gif');
% result = remove_holes(image);
% 
% isequal(result, test_image)
% 
% image = imread('data\soccer_field4.jpg', 'jpg');
% soccer_analysis(image);

image = read_gray('data\ocean2.jpg');
ocean_segmentation(image);