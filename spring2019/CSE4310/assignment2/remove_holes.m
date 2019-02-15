function result = remove_holes(image);

% Takes an image with or without holes and returns 
% the same image with the holes removed
% Holes defined in the asssignment instructions

opp_image = ~image;
[labels, number] = bwlabel(opp_image, 4);
bg_label = labels(1,1);
opp_image(labels ~= 0 & labels ~= bg_label) = 0;
result = ~opp_image * 255;