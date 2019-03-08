function class_label = nnc_euclidean(test_image);

%
%
%

% distances guaranteed to be positive
class_label = 0;
min = intmax;

for label = 0:9
    for sample_num = 1:15
        filename = sprintf('digits_training/label%d_training%d.png', label, sample_num);
        im = imread(filename);
        residual = euclidean_distance(test_image, im);
        if residual == min
            'ties'
        end
        
        if residual <= min
            min = residual;
            class_label = label;
        end
    end
end
