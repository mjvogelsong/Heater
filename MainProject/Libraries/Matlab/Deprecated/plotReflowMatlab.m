% Plots the actual reflow curve overlayed on top of the user-set reflow
% curve.
% Virginia Chen
% 4/29/13

% referenced this: http://www.xploreautomation.com/arduinomatlab-real-time-plot/

% need to first download Arduino IO package: http://www.mathworks.it/matlabcentral/fileexchange/32374
%   load pde>adiosrv>adiosrv.pde
%   open Matlab
%   run install_arduino.m
%   connect Arduino to computer

a=arduino('COM3'); % connect Matlab and arduino using port COM3

% input the user-inputted reference curve
totalSamples=; % total number of samples
step=;  % change in time per iteration
refTimes=;  % array of the reference times and temps
refTemps=;
figure(1)
plot(refTime,refTemp,'k--')
title('Reflow Curve: Ideal vs. Actual')
xlabel('Time (s)')
ylabel('Temperature (/circ C)')

hold on

% real time actual curve
t = 1 ; % starting time, increases by step
x = 0 ; % will become an array of all the temperatures
while ( t <totalSamples )
    b = a. analogRead ( 0 ) ; % data retrieved from analog port 0
    x = [ x, b ] ; % adds b to the array of temperatures
    plot ( x ) ;
    axis ( [ 0 , totalSamples, 0 , 300 ] ) ;
    grid
    t = t + step;
    drawNow ;
end