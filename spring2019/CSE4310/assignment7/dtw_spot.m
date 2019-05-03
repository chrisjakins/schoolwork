function result = dtw_spot(input_video, class_thresholds);

%
%
%
%% setup 
hand_size = [30 40];
tr_filename = 'digits_model_quan_ex3.avi';
tr_frames = [ 22 91;     143 165;
              220 300;   350 445;
              495 544;   608 701;
              763 850;   906 961;
              1035 1150; 1206 1277 ];

scores = cell(10, 1);
for i = 1:10
    % + 2 because of the added 0 row
    scores{i} = Inf(tr_frames(i, 2) - tr_frames(i, 1) + 2, 1);
end

%% get trajectory of each training example
tr_trajectories = cell(10, 1);
for i = 1:10
    tr_trajectories{i, 1} = green_hand_trajectory(tr_filename, tr_frames(i, 1), tr_frames(i, 2));
end

%% get trajectory of whole input video
v = VideoReader(input_video);
num_frames = v.NumberOfFrames;
trajectory = green_hand_trajectory(input_video, 2, num_frames - 1);

%% spotting
result = [];
spotted = false;
frame_count = 0;
for frame = 1:num_frames - 2
    frame_count = frame_count + 1;
    bottom_row = zeros(10, 1);
    
    for class = 1:10
        % prealloc and append zeros to scores
        scores{class} = [scores{class} zeros(tr_frames(class, 2) - tr_frames(class, 1) + 2, 1)];
        [m, n] = size(scores{class});
        %compute column
        for i = 2:(tr_frames(class, 2) - tr_frames(class, 1) + 2)
            scores{class}(i, n) = l2norm(trajectory(frame, :) - tr_trajectories{class}(i - 1, :)) + min([scores{class}(i - 1, n) scores{class}(i, n - 1), scores{class}(i - 1, n - 1)]);
        end
        bottom_row(class) = scores{class}(m, n);
    end
    %check if normalized scores under threshold
    bottom_row = bottom_row / frame_count;
    for class = 1:10
        if bottom_row(class) <= class_thresholds(class)
            % start frame is incorrect, approximation hardcoded here
            result = [result; frame - 40, frame, class-1 ];
            frame_count = 0;
            scores = cell(10, 1);
            for i = 1:10
                % + 2 because of the added 0 row
                scores{i} = Inf(tr_frames(i, 2) - tr_frames(i, 1) + 2, 1);
            end
        end
    end
end

