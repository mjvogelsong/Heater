%% realTimeReflow.m
%% Virginia Chen
%% Michael Vogelsong

% Takes data from the Arduino to plot the user-inputted reference reflow
% curve as well as the actual reflow curve in real time.

% for reference:
% http://www.mathworks.com/help/matlab/serial-port-devices.html

% makes sure that previous port is closed and deleted
fclose(arduino)
delete(arduino)
clear all
clc

arduino = serial('COM3') % port may be different for different computers
fopen(arduino)

% waits until the user inputs a curve/selects the default curve
while (arduino.BytesAvailable == 0)
    pause(.1);
end

inputTimes = zeros(1,5);
inputTemps = zeros(1,5);
counter = 0;

% a string that says 'Time', not needed
fscanf(arduino,'%s');

% loads the input times
counter = counter + 1;
while (counter < 6)
    inputTimes(counter) = fscanf(arduino, '%d');
    counter = counter + 1;
end

% a string that says 'Temperature', not needed
fscanf(arduino,'%s');

% loads the input temperatures
counter = counter + 1;
while ( counter < 12 )
    inputTemps(counter - 6) = fscanf(arduino, '%f');
    counter=counter+1;
end    

% plots the inputted reference curve
figure(1), clf
plot(inputTimes, inputTemps, 'r-')
grid
xlabel('Time (s)')
ylabel('Temperature (C)')
title('Heating Curve')

% sets up the real time curve on top of the reference curve
times = 0;
temps = 25;
hold on
h = plot(times, temps, 'b-', 'XDataSource', 'times', ...
    'YDataSource', 'temps');

% Control parameters for real-time looping
dataRemaining = 1;
plotWait = 10;
endTime=(inputTimes(5));

% wait for user to start process
while (arduino.BytesAvailable == 0)
    pause(.1);
end

% load in data off of buffer as it comes in
while (times(end)<endTime)
        plotWait = plotWait - 1;
        data = fscanf(arduino,'%d %d');
        times = [times data(2)/1000];
        temps = [temps data(1)];
        % waits for 10 new data points before refreshing the plot
        if (plotWait == 0)
            refreshdata(h, 'caller');
            drawnow;
            plotWait = 10;
        end
end

fprintf('Target Peak Temperature: %f C\n\n', inputTemps(5))
fprintf('Actual Peak Temperature: %f C\n', max(temps))