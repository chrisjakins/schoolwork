function result = euclidean_distance(im1, im2);

%
%
%

diff = im1(:) - im2(:);
result = sqrt(sum(diff .* diff));