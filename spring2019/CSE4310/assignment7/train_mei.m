function training_mei = train_mei();


%% setup
training_filename = "digits_model_quan_ex3.avi";
training_frames = [ 22 91;     143 165;
                    220 300;   350 445;
                    495 544;   608 701;
                    763 850;   906 961;
                    1035 1150; 1206 1277 ];

[m,n] = size(read_gray_avi(training_filename, 1));
training_mei = zeros(10, m, n);

%% building training model
for i = 1:10
   training_mei(i, :, :) = mei_image(training_filename, training_frames(i,1), training_frames(i,2)); 
end

