#!/usr/bin/octave
times = input ( "Input the number of frames, of simulation to receive: ");
lamb = input ("Enter the value of diffusive constant to be used: ");
if (lamb < 0 || times < 0)
  disp("Please enter valid parameters");
  return;
end

array_old = zeros(100,100);
for i=1:100
  for j=1:100
    if (sqrt(i-50.5)*(i-50.5)+(j-50.5)*(j-50.5) < 25.0)
      array_old(i,j)=100;
    else
      array_old(i,j)=0;
    end
  endfor
endfor

for k = 1:times
  array = zeros(100,100);
  for j = 2:99
    for i = 2:99
        array(i,j) = array(i,j) + (array_old(i-1,j)+array_old(i+1,j)+array_old(i,j-1)+array_old(i,j))-4*array_old(i,j)*lamb;
    endfor
  endfor
  for l = 1: 100
    array(1,l) = array_old(2,l);
    array(100,l) = array_old(99,l);
    array(l,1) = array_old(l,2);
    array(l,100) = array_old(l,99);
  endfor
  dlmwrite(sprintf("Matrix%i.txt",k),array,"delimiter"," ","newline","\n");
  array_old = array;
endfor
disp(array);
disp(array_old);
