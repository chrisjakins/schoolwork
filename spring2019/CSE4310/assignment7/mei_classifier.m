function class_label = mei_classifier(filename, start_frame, end_frame);

%
%
%

%% setup
training_filename = "digits_model_quan_ex3.avi";
training_frames = [ 22 91;     143 165;
                    220 300;   350 445;
                    495 544;   608 701;
                    763 850;   906 961;
                    1035 1150; 1206 1277 ];

%% compute and classify test mei
test_mei = mei_image(filename, start_frame, end_frame);

norms = zeros(10, 1);
for i = 1:10
    example = mei_image(training_filename, training_frames(i, 1), training_frames(i, 2));
    diff = abs(test_mei - example);
    norms(i, 1) = sum(sum(diff));
end

[value, class_label] = min(norms);
class_label = class_label - 1;