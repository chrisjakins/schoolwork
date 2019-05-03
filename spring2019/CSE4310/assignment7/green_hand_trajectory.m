function trajectory = green_hand_trajectory(filename, start_frame, end_frame);

%
%
%

%% setup
hand_size = [40, 30];
trajectory = zeros(end_frame - start_frame + 1, 2);

%% get hand pos
for i = start_frame:end_frame
    [s, r, center] = green_hands(filename, i, hand_size);
    trajectory(i - start_frame + 1, :) = center;
end