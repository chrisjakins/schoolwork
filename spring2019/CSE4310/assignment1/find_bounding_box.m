function [top, bottom, left, right] = find_bounding_box(img_string)

% finds the bounding box of provided image.
%
%

%%
% I/O and conversions to grayscale
%

[name, frame] = parse_frame_name(img_string);
if frame < 15 || frame > 109
    return;
end
one_name = make_frame_name(name, frame-15);
two_name = make_frame_name(name, frame+15);

color_image = imread(img_string);
gray_A = read_gray(one_name);
gray_B = read_gray(two_name);

double_image_M = double(color_image);
% double_image_A = double(color_image_A);
% double_image_B = double(color_image_B);

gray_M = (double_image_M(:,:,1) + double_image_M(:,:,2) + double_image_M(:,:,3)) / 3;
% gray_A = (double_image_A(:,:,1) + double_image_A(:,:,2) + double_image_A(:,:,3)) / 3;
% gray_B = (double_image_B(:,:,1) + double_image_B(:,:,2) + double_image_B(:,:,3)) / 3;

% main_image = read_gray(img_string);
% before_image = read_gray(two_name);
% after_image = read_gray(one_name);

% figure(1); imshow(gray_M, [0 255]);
% norm = read_gray(img_string);
% figure(2); imshow(norm, [0 255]);
% 
% check = (norm ~= gray_M)
%%
% Finding the motion and connected components
%

diff1 = abs(gray_B - gray_M);
diff2 = abs(gray_A - gray_M);
motion = min(diff1, diff2);
%figure(1); imshow(motion, [0 255]);
% diff1 = abs(before_image - main_image);
% diff2 = abs(after_image - main_image);
%motion = min(diff1, diff2);

threshold = 10;
thresholded = (motion > threshold);

[labels, number] = bwlabel(thresholded, 4);
%figure(2); imshow(labels, [0 255]);

counters = zeros(1, number);
for i = 1:number
    component_image = (labels == i);
    counters(i) = sum(component_image(:));
end

[area, id] = max(counters);
person = (labels == id);

%figure(2); imshow(person, []);

dim = size(person);

top = 0;
for i = 1:dim(1)
    for j = 1:dim(2)
        if 1 == person(i,j)
            top = i;
        end
    end
    if top ~= 0
        break;
    end
end

bottom = 0;
for i = dim(1):-1:1
    for j = 1:dim(2)
        if 1 == person(i,j)
            bottom = i;
        end
    end
    if bottom ~= 0
        break;
    end
end

left = 0;
for j = 1:dim(2)
    for i = 1:dim(1)
        if 1 == person(i,j)
            left = j;
        end
    end
    if left ~= 0
        break;
    end
end

right = 0;
for j = dim(2):-1:1
    for i = 1:dim(1)
        if 1 == person(i,j)
            right = j;
        end
    end
    if right ~= 0
        break;
    end
end

final = draw_rectangle(color_image, [255,255,0], top, bottom, left, right);

figure(3); 
imshow(final);
pause;
