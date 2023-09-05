function mae = calculateMAE(a, b)
   [i, j]=size(a);
   mae = sum(abs(a-b), "all")/(i*j);
end