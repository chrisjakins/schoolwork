function [accuracy, confusion_matrix] = nnc_euclidean_stats()

%
%
%

num_correct = 0;
confusion_matrix = zeros(10,10);

for label = 0:9
    if label == 0
        i_label = 10;
    else
        i_label = label;
    end
    
    for sample = 1:10
        filename = sprintf('digits_test/label%d_test%d.png', label, sample);
        im = imread(filename);
        result = nnc_euclidean(im);
        if result == label
            num_correct = num_correct + 1;
        end
        
        if result == 0
            result = 10;
        end

        confusion_matrix(i_label, result) = confusion_matrix(i_label, result) + 1;
    end
end

accuracy = num_correct / 100;
confusion_matrix = confusion_matrix / 10;