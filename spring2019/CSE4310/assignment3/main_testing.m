%%% Chris Jakins 1000802309

restoredefaultpath;
clear all;
close all;

addpath 'C:\Users\Chris Jakins\Desktop\schoolwork\spring2019\CSE4310\assignment3'
addpath 'C:\Users\Chris Jakins\Desktop\schoolwork\spring2019\CSE4310\assignment3\data\';
cd 'C:\Users\Chris Jakins\Desktop\schoolwork\spring2019\CSE4310\assignment3'

%%%%%%%%%%

image = read_gray('data\road9.jpg');
thetas = -90:5:85;
thetas = thetas';
rhos = -250:1:250;
rhos = rhos';
thr1 = 4;
thr2 = 5;
votes = oriented_hough(image, thetas, rhos, thr1, thr2);

maximum = max(max(votes));
[x, y] = find(votes == maximum);
rho = rhos(x);
theta = thetas(y);
hough_image = draw_line2(image, rho, theta);

figure(4); imshow(hough_image, []);

%%%%%%%%

% image = read_gray('data\athitsos1.jpg');
% temp = read_gray('data\template.jpg');
% result = ssd_search(image, temp);
% 
% [x,y] = find(result == min(min(result(result>-1))));
% 
% final = draw_line(image, [x - 44, y - 44], [x + 44, y + 44]);
% figure(3); imshow(final, []);
%%%%%%%%%%%

% image = read_gray('data\athitsos_bright.jpg');
% image = int8(image);
% temp = read_gray('data\template.jpg');
% temp = int8(temp);
% result = ssd_bn_search(image, temp);
% 
% [x, y] = find(result == min(min(result(result > -1))));
% final = draw_line(image, [x - 44, y - 44], [x + 44, y + 44]);
% figure(4); imshow(final, []);

%%%%%%%%%%%

% small = read_gray('data\athitsos_small.jpg');
% big = read_gray('data\athitsos_big.jpg');
% temp = read_gray('data\template.jpg');
% 
% [scores, scales] = ssd_bn_multiscale(big, temp, [1.06, 1.53, 2.03, 2.52, 3.02]);
% 
% [x, y] = find(scores == min(min(scores(scores > -1))));
% scale = scales(x,y);
% image = imresize(big, 1/scale, 'bilinear');
% final = draw_line(image, [x - 44, y - 44], [x + 44, y + 44]);
% figure(5); imshow(final, []);