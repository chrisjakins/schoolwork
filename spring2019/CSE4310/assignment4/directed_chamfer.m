function distance = directed_chamfer(im_from, im_to);

%
%   Images asssumed to be logical, binary images.
%

from_bin = (im_from ~= 0);
n1 = sum(sum(from_bin));
dt2 = bwdist(im_to);
distance = sum(sum(from_bin .* dt2)) / n1;