function class_label = dtw_classifier_green(filename, start_frame, end_frame);

%
%
%
%% get test trajectory
traj = green_hand_trajectory(filename, start_frame, end_frame);
n = end_frame - start_frame;

%% setup training
tr_filename = "digits_model_quan_ex3.avi";
tr_frames = [ 22 91;     143 165;
              220 300;   350 445;
              495 544;   608 701;
              763 850;   906 961;
              1035 1150; 1206 1277 ];

          
%% do training
% get test trajectory
% calculate DTW alignment
% performance measure
alignment_scores = zeros(10, 1);
for i = 1:10
    tr_traj = green_hand_trajectory(tr_filename, tr_frames(i, 1), tr_frames(i, 2));
    m = tr_frames(i, 2) - tr_frames(i, 1);
    scores = zeros(m, n);
   
    scores(1, 1) = l2norm(tr_traj(1, :) - traj(1, :));
   
    for j = 2:m
      scores(j, 1) = scores(j - 1, 1) + l2norm(tr_traj(j, :) - traj(1, :));
    end
   
    for j = 2:n
        scores(1, j) = scores(1, j - 1) + l2norm(tr_traj(1, :) - traj(j, :));
    end
    
    for j = 2:m
        for k = 2:n
            scores(j, k) = l2norm(tr_traj(j, :) - traj(k, :)) + min([scores(j-1,k) scores(j,k-1), scores(j-1,k-1)]);
        end
    end

    alignment_scores(i, 1) = scores(m, n);
end
%%

[value, class_label] = min(alignment_scores);
class_label = class_label - 1;
