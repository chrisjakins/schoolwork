function result = person_present(img_string)

% Determines if a person is present in the frame or not
%
% Return values:
%   1 - person present
%   0 - person not present

[name, frame] = parse_frame_name(img_string);
zero_frame = make_frame_name(name, 0);

zero_image = read_gray(zero_frame);
image = read_gray(img_string);

diff = abs(zero_image - image);

threshold = 10;
t = (diff > threshold);
[labels, number] = bwlabel(t, 4);

counters = zeros(1, number);
for i = 1:number
    component_image = (labels == i);
    counters(i) = sum(component_image(:));
end

[area, id] = max(counters);

if area > 1000
    result = 1;
else
    result = 0;
end



