clear all;
lena = double(imread('lena.gif'));
lpfilter = 1/9*ones(3,3);
lpfilter2 = 1/25*ones(5,5);
lena2 = imfilter(lena, lpfilter, "replicate");
lena3 = imfilter(lena, lpfilter2, "replicate");
imshow(uint8(lena2));
sum  = 0;
sum2 = 0;
for i = 1:256
    for j = 1:256
      sum = sum + (lena2(i,j)-lena(i,j))^2;
      sum2 = sum2 + (lena3(i,j) - lena(i,j))^2;
    end
end
mse = sum/(256.0*256);
psr = 10*log10(255^2/mse)

mse2 = sum2/(256.0*256);
psr2 = 10*log10(255^2/mse2)
