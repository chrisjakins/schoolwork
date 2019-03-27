function distance = chamfer_distance(im1, im2);

%
% Inputs are assumed to be logical images
%

distance = directed_chamfer(im1, im2) + directed_chamfer(im2, im1);