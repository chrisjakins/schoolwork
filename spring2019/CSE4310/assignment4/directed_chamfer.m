function distance = directed_chamfer(im_from, im_to);

%
%   Images asssumed to be logical, binary images.
%

% [from_row, from_col] = size(im_from);
% [to_row, to_col] = size(im_to);
% 
% num_conn = 0;
% 
% for j = 1:from_col
%     for i = 1:from_row
%         if im_from(i,j) == 1
%         
%         
%         
%         
%         end
%     end
% end
im1 = double(im_from);
im2 = double(im_to);

dt = bwdist(im2);

distance = sum(sum(im1 .* dt));