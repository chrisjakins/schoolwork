% Chris Jakins 1000802309
% Assignment 1
% 2/1/2019

%
%
%

restoredefaultpath;
clear all;
close all;

addpath 'C:\Users\Chris Jakins\Desktop\schoolwork\spring2019\CSE4310\assignment1'
addpath 'C:\Users\Chris Jakins\Desktop\schoolwork\spring2019\CSE4310\assignment1\1_intro_data'
WALK_PATH = 'C:\Users\Chris Jakins\Desktop\schoolwork\spring2019\CSE4310\assignment1\1_intro_data\';
cd 'C:\Users\Chris Jakins\Desktop\schoolwork\spring2019\CSE4310\assignment1'

% for i = 15:109
%     i
%     find_bounding_box(make_frame_name('walkstraight\frame', i));
% end

%person_present('walkstraight\frame0110.tif');

person_speed('walkstraight\frame0030.tif', 'walkstraight\frame0090.tif');