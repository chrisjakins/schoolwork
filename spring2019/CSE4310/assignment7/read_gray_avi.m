function frame = read_gray_avi(filename, frame_number);


v = VideoReader(filename);
frame = read(v, frame_number);

frame = double(frame);
if size(frame, 3) == 3
    frame = 0.3*frame(:,:,1) + 0.59*frame(:,:,2) + 0.11*frame(:,:,3);
end
