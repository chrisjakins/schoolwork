function [scores, result, centers] = ...
    green_hands(filename, frame, hand_size)

% function [scores, result, centers] = ...
%     green_hands(filename, frame, hand_size)

v = VideoReader(filename);
current = read(v, frame);
green_scores = 2 * current(:, :, 2) - current(:, :, 1) - current(:, :, 3);
%green_scores = (current(:, :, 2) > current(:, :, 1)) & (current(:, :, 2) > current(:, :, 3));

previous_gray = double_gray(read(v, frame-1));
current_gray = double_gray(current);
next_gray = double_gray(read(v, frame+1));


frame_diff = min(abs(current_gray-previous_gray), abs(current_gray-next_gray));
green_motion_scores = double(green_scores) .* frame_diff;

scores = imfilter(green_motion_scores, ones(hand_size), 'same', 'symmetric');
[result, centers] = top_detection_results(current, scores, hand_size, ...
                                          1, 1);
