function [tp, fp, fn] = dtw_spot_accuracy(ground_truth, gestures, iou_threshold);

%
%
%
%% setup
gt = importdata(ground_truth);
gt_labels = gt(:, 1);
gt = gt(:, 2:3);
gt = [gt gt_labels];
tp = 0;
fp = 0;
fn = 0;

[gt_m, gt_n] = size(gt);
[gest_m, gest_n] = size(gestures);
detected = zeros(gt_m, 1);

%%
for gest = 1:gest_m
    thresholds = zeros(gt_m, 1);
    
    for g = 1:gt_m
        % calc iou
        intersection = 0;
        s = max(gt(g,1), gestures(gest,1));
        e = min(gt(g,2), gestures(gest,2));
        if e > s
            intersection = e - s + 1;
            union = max(gt(g,2), gestures(gest,2)) - min(gt(g,1), gestures(gest,1)) + 1;
        else
            intersection = 0;
            union = gt(g,2) - gt(g,1) + gestures(gest,2) - gestures(gest,1);
        end
        
        iou = intersection / union;
        thresholds(g) = iou;
    end
    
    [value, ind] = max(thresholds);
    if gestures(gest, 3) == ind - 1 && value > iou_threshold
        tp = tp + 1;
        detected(gest) = 1;
    else
        fp = fp + 1;
    end
    
end

%%
fn = gt_m - sum(detected);
