% Chris Jakins 1000802309
% Assignment 1
% 2/1/2019

%
%
%

restoredefaultpath;
clear all;
close all;

addpath 'C:\Users\Chris Jakins\Desktop\Spring2019\CSE4310\assignment1'
addpath 'C:\Users\Chris Jakins\Desktop\Spring2019\CSE4310\assignment1\walkstraight'
WALK_PATH = 'C:\Users\Chris Jakins\Desktop\Spring2019\CSE4310\1_intro_data\';

for i = 15:109
    i
    find_bounding_box(make_frame_name('walkstraight\frame', i));
end