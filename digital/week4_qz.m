q3a = [1 1 2 2; 1 1 2 2; 2 2 3 4; 2 2 5 6];
q3b = [2 2 1 1; 2 2 2 2; 2 2 6 4; 2 2 5 3];
[m, n] = size(q3b);
mse = 1/(m*n)* sum((q3b - q3a).^2, "all")

q4a = [10 20 10 10; 20 40 10 10; 30 40 20 20; 50 60 20 20];

q4a1 = [10 20 10 10; 20 40 10 10; 20 20 30 40; 20 20 50 60];
q4a2 = [20 30 20 20; 30 50 20 20; 40 50 30 30; 60 70 30 30];
q4a3 = [10 20 30 40; 20 40 50 60; 10 10 20 20; 10 10 20 20];
q4a4 = [1 2 1 1; 2 4 1 1; 3 4 2 2; 5 6 2 2];

% the function below is implemented in another file to be reused in the
% next exercise
mae1 = calculateMAE(q4a1, q4a)
mae2 = calculateMAE(q4a2, q4a)
mae3 = calculateMAE(q4a3, q4a)
mae4 = calculateMAE(q4a4, q4a)
