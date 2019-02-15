function ocean_segmentation(image);

%
sky = image > 189;
sky = imerode(sky, ones(7,7));
sky = imdilate(sky, ones(5,5));
figure(1); imshow(sky);

ocean = image < 164 & image > 122;
neighbor = [0 1 0; 1 1 1; 0 1 0];
ocean = imerode(ocean, neighbor);
[labels, number] = bwlabel(ocean, 4);
ocean = labels == 1;
ocean = imdilate(ocean, ones(3,3));
figure(2); imshow(ocean);