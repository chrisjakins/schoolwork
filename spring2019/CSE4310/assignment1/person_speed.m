function [rows, cols] = person_speed(frame1, frame2)

% Determines the velocity of the person between frame1 and frame2
%
%

[name1, frame_id1] = parse_frame_name(frame1);
[name2, frame_id2] = parse_frame_name(frame2);

if frame_id1 > frame_id2
    [top1, bot1, left1, right1] = find_bounding_box(frame2);
    [top2, bot2, left2, right2] = find_bounding_box(frame1);
else
    [top1, bot1, left1, right1] = find_bounding_box(frame1);
    [top2, bot2, left2, right2] = find_bounding_box(frame2);
end

top = top2 - top1;
bot = bot2 - bot1;
left = left2 - left1;
right = right2 - right1;

rowAvg = (top + bot) / 2;
colAvg = (left + right) / 2;

rows = rowAvg / double(abs(frame_id2 - frame_id1));
cols = colAvg / double(abs(frame_id2 - frame_id1));