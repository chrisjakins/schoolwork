function soccer_analysis(image);

%
%
%

color = double(image);
r = color(:,:,1);
g = color(:,:,2);
b = color(:,:,3);

g_thresh = 10;
green = (g - r > g_thresh & g - b > g_thresh);
field = get_component(green, 1);
field_final = remove_holes(field);
figure(1); imshow(field_final);

r_thresh = 5;
red = ((r - g > r_thresh) & (r - b > r_thresh)) & field_final;
[red_labels, red_number] = bwlabel(red, 4);
for i = 1:red_number
    comp_image = (red_labels == i);
    number_pix = sum(comp_image(:));
    if number_pix < 15
       red(find(comp_image)) = 0; 
    end
end
figure(2); imshow(red);

b_thresh = 5;
blue = ((b - g > b_thresh) & (b - r > b_thresh)) & field_final;
[blue_labels, blue_number] = bwlabel(blue, 4);
for i = 1:blue_number
    comp_image = (blue_labels == i);
    number_pix = sum(comp_image(:));
    if number_pix < 7
        blue(find(comp_image)) = 0;
    end
end
figure(3); imshow(blue);