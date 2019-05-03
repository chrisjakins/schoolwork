restoredefaultpath;
clear all;
close all;

addpath 'C:\Users\Chris Jakins\Desktop\schoolwork\spring2019\CSE4310\all_code\00_images\';
addpath 'C:\Users\Chris Jakins\Desktop\schoolwork\spring2019\CSE4310\assignment7';
addpath 'C:\Users\Chris Jakins\Desktop\schoolwork\spring2019\CSE4310\assignment7\gesture_videos\';

cd 'C:\Users\Chris Jakins\Desktop\schoolwork\spring2019\CSE4310\assignment7';

avi_one = "digits_model_joni_ex3.avi";
avi_two = "digits_model_quan_ex3.avi";
avi_three = "digits_short_sleeves_michalis_ex4.avi";
avi_four = "digits_short_sleeves_tian_ex3.avi";

%%%%%%%%%%

% result = mei_image(avi_one, 183, 212);
% imshow(result, []);

%%%%%%%%%%
frame_numbers = [ 47 105;    183 212;
                  270 338;   399 467;
                  532 578;   650 738;
                  789 857;   915 964;
                  1022 1137; 1200 1277 ];
% % classified correctly:::
% % with 1-norm
% % 1,2,4,7,8,9
% % with 2-norm
% % none...
% for i = 1:10
%     label = mei_classifier(avi_one, frame_numbers(i, 1), frame_numbers(i, 2));
%     if label ~= i - 1
%         "I - 1 = "
%         disp(i - 1);
%         "Label = "
%         disp(label);
%     end
% end

%%%%%%%%%%

% traj = green_hand_trajectory(avi_one, 47, 105);

%%%%%%%%%%

% l2norm([3, 5]);
% Correct classifications -
% 0 1 2 4 8 9
% for i = 1:10
%     label = dtw_classifier_green(avi_one, frame_numbers(i, 1), frame_numbers(i, 2));
%     if label ~= i - 1
%         disp("I - 1 = ");
%         disp(i - 1);
%         disp("Label = ");
%         disp(label);
%     end
% end

%%%%%%%%%%

%result = dtw_spot(avi_one, [10 2 10 10 5 10 10 10 7 10]);

%%%%%%%%%%
frame_numbers = [ 47 85 0;    200 212 1;
                  290 328 2;   399 432 3;
                  532 555 4;   676 710 5;
                  789 857 6;   915 964 7;
                  1022 1137 8; 1200 1277 9 ];
[tp, fp, fn] = dtw_spot_accuracy('start_end_frames_model_joni_ex3.txt', frame_numbers, .8);

%%%%%%%%%%