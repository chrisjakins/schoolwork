function result = mei_image(filename, start_frame, end_frame);

%
%
%

%%
prev = read_gray_avi(filename, start_frame);
result = zeros(size(prev));

for curr_frame = start_frame+1:end_frame
    curr = read_gray_avi(filename, curr_frame);
    diff = abs(curr - prev);
    result = result + diff;
    prev = curr;
end