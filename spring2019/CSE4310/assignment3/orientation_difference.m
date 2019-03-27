function result = orientation_difference(ang1, ang2);

while ang1 > 180
    ang1 = ang1 - 180;
end

while ang2 > 180
    ang2 = ang2 - 180;
end

result = abs(ang1 - ang2);
if result > (180 - result)
    result = abs(180 - result);
end
    