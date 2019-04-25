function result = hog_feature(image, top, left, block_size);

%
%
%

%% setup
image = image(top:top+block_size - 1, left:left+block_size - 1);

%% loop over blocks and compute histograms

sub1 = orientation_histogram(image(1:block_size / 2, 1:block_size / 2));
sub2 = orientation_histogram(image(1:block_size / 2, 1 + block_size / 2:block_size));
sub3 = orientation_histogram(image(1 + block_size / 2:block_size, 1:block_size / 2));
sub4 = orientation_histogram(image(1 + block_size / 2:block_size, 1 + block_size / 2:block_size));


result = [sub1; sub2; sub3; sub4];
