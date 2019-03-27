function result = resize_template(template, scale)

% function result = resize_template(template, scale)
%
% Resizes the template by the specific scale, calling imresize.
% It ensures that the number of rows and columns of the result are 
% both odd numbers.

[rows, cols] = size(template);
new_rows = floor(rows * scale);
if (mod(floor(new_rows), 2) == 0)
    new_rows = new_rows + 1;
end

new_cols = floor(cols * scale);
if (mod(floor(new_cols), 2) == 0)
    new_cols = new_cols + 1;
end

result = imresize(template, [new_rows, new_cols], 'bilinear');
