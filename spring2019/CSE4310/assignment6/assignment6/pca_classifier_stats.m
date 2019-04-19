function [accuracy, confusion_matrix] = pca_classifier_stats(d);

%
%
%
eigenvectors = optimized_classifier(d);
confusion_matrix = zeros(10,10);
acc = 0;

for i = 0:9
    if (i == 0)
        ind = 10;
    else
        ind = i;
    end
    
    for j = 1:10
        filename = sprintf('label%d_test%d.png', i, j);
        image = imread(filename);
        label = get_label(eigenvectors, image, d);
        
        if (i == label)
            acc = acc + 1;
        end
        
        if (label == 0)
            label = 10;
        end
        
        confusion_matrix(ind, label) = confusion_matrix(ind, label) + 1;
    end
end

accuracy = acc * .01;
confusion_matrix = confusion_matrix * .1;