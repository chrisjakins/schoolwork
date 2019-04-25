function result = shape_context_feature(edge_image, row, col, r1);

%
%
%

%% init
result = zeros(5, 12);

rad_bins = [r1];
for i = 1:4
    rad_bins = [rad_bins, 2 * rad_bins(i)];
end

[m, n] = size(edge_image);

%% loop over surrounding edge pixels
% can optimize loop bounds here to use max radius
for j = 1:n
    for i = 1:m
        % is edge pixel and is NOT center
        if (edge_image(i,j) ~= 0 && ~(i == row && j == col))
            % find proper distance index
            distance = sqrt((row-i)^2 + (col-j)^2);
            d_ind = 6;
            while d_ind ~= 1 && distance <= rad_bins(d_ind - 1)
                d_ind = d_ind - 1;
            end
            
            % find proper orientation index
            if (d_ind ~= 6)
                angle = get_orientation(row, col, i, j);
                o_ind = ceil(angle / 30);
                if (o_ind == 0)
                    o_ind = 1;
                end
                result(d_ind, o_ind) = result(d_ind, o_ind) + 1;
            end
        end
    end
end

%%
for j = 1:12
    for i = 1:5
        if (result(i,j) == 0)
            result(i,j) = 1;
        end
    end
end
