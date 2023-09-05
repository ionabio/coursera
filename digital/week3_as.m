clear all;

week_3 = double(imread('week3.jpg'));
lpfilter = 1/9*ones(3,3);
week_3lf = imfilter(week_3, lpfilter, "replicate");
cols = size(week_3, 1);
rows = size(week_3, 2);
week_3ds = week_3lf(1:2:end, 1:2:end); 
week_3us = zeros(cols, rows);
week_3us(1:2:end, 1:2:end) = week_3ds;
filter2 = [0.25 0.5 0.25; 0.5 1 0.5; 0.25 0.5 0.25];
week_3us = imfilter(week_3us, filter2);

figure()
imshow(uint8(week_3));
figure()
imshow(uint8(week_3ds));
figure()
imshow(uint8(week_3us));

sum = 0;
for i = 1:cols
    for j = 1:rows
      sum = sum + (week_3us(i,j) - week_3(i,j))^2;
    end
end
mse = sum/(cols*rows);
psr = 10*log10(255^2/mse)
psnr(week_3us, week_3, 255)
