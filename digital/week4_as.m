clear all
i1 = double(imread("frame_1.jpg"));
i2 = double(imread("frame_2.jpg"));

delta = 32;
x0 = 65; x1 = x0+delta-1;
y0 = 81; y1 = y0 + delta -1;

B_target = i2(x0:x1, y0:y1);

initialShift = 2; %% I will start in a window of -32 respective to curren one and find the smallest in the grid of 3 x 3 (8 except the middle)

% 1 2 3
% 4 5 6
% 7 8 9
step = initialShift
[mae, new_x, new_y, newIndex] = findMinima(x0, y0, step, delta, i1, B_target)

step = step/2;
[mae, new_x, new_y, newIndex] = findMinima(new_x, new_y, step, delta, i1, B_target)

answer = new_x + new_y
answer2 = round(mae,2)

function [minmae, newX, newY, index] = findMinima(x_0, y_0, step, delta, i1, B_target)
  xys = {};
  mae = [];
  for(x = [x_0 - step, x_0, x_0 + step])
    for (y = [y_0 - step, y_0, y_0 + step])
        A_source = i1(x:x+delta-1, y:y+delta-1);
        mae = [mae calculateMAE(A_source, B_target)];
        xys{end+1} = [x y];
    end
  end
  [minmae, index] = min(mae);
  newX = xys{index}(1);
  newY = xys{index}(2);
end
    
   
