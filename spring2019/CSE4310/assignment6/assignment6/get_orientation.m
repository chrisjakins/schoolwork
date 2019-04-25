function angle_deg = get_orientation(r1, c1, r2, c2);

% returns angle in degrees
% clockwise from +x axis
%

delta_y = r2 - r1;
delta_x = c2 - c1;

slope = abs(delta_y / delta_x);
ang1 = atan(slope) / pi * 180;

if (r2 > r1 && c2 < c1)
    angle_deg = 180 - ang1;
    
elseif (r2 < r1 && c2 < c1)
    angle_deg = 270 - ang1;
    
elseif (r2 < r1 && c2 > c1)
    angle_deg = 360 - ang1;

else
    angle_deg = ang1;
    
end


    
    