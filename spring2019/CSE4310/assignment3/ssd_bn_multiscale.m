function [scores, max_scales] = ssd_bn_multiscale(grayscale, template, scales)

%
[m, n] = size(grayscale);

scores = ones(m,n) * -1;
max_scales = ones(m,n) * -1;

for scale = scales
    if scales >= 1
        scaled_image = resize_template(grayscale, 1/scale);
        nt_scores = ssd_bn_search(scaled_image, template);
        nt_scores = imresize(nt_scores, size(grayscale), 'bilinear');
    else
        scaled_temp = resize_template(template, scale);
        nt_scores = ssd_bn_search(grayscale, scaled_temp);
    end
    
    if scale == scales(1)
        max_scales(nt_scores ~= -1) = scale;
        scores(nt_scores ~= -1) = nt_scores(nt_scores ~= -1);
    else
        higher_maxes = nt_scores < scores;
        max_scales(higher_maxes) = scale;
        scores(higher_maxes) = nt_scores(higher_maxes);

    end
end