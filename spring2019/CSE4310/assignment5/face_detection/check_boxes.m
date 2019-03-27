function [tp, fp, fn] = check_boxes(boxes, gt, iou_thr);

% Input arguments:
% boxes: This is a matrix of N rows and 6 columns, where each row specifies the bounding box of a detection result.
% Each row has the format [top, bottom, left, right, score, scale]. In this function, the score and scale do not matter.
% ground_truth: This is a matrix of M rows and 4 columns, where each row specifies the bounding box of a real
% face location that is specified by the ground truth. Each row has the format [top, bottom, left, right].
% iou_thr: The IoU threshold that should be used to determine if a detection result matches a ground truth location or not.
%
% Return values:
% tp: The number of true positives in the detection results.
% fp: The number of false positives in the detection results.
% fn: The number of false negatives in the ground truth locations.
