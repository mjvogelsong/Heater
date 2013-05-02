% Takes data from the Arduino to plot the user-inputted reference reflow
% curve as well as the actual reflow curve in real time.

% makes sure that arduino is closed and deleted
fclose(arduino)
delete(arduino)
clear all
clc

arduino = serial('COM3') % arduino is connected to computer through COM3
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
    inputTemps(counter - 6) = fscanf(arduino, '%d');
    counter=counter+1;
end    

% plots the ser inputted reference curve
figure(1), clf
plot(inputTimes, inputTemps, 'r-')
grid
xlabel('Time (s)')
ylabel('Temperature (C)')
title('Heating Curve')

% plots the real time curve on top of the reference curve
times = 0;
temps = 25;
hold on
h = plot(times, temps, 'b-', 'XDataSource', 'times', ...
    'YDataSource', 'temps');
dataRemaining = 1;

pauseNums = 0;
pauseLimit = round(.5/.005);
plotWait = 10;

endTime=(inputTimes(5));

while (arduino.BytesAvailable == 0)
    pause(.1);
end

while (times(end)<endTime)
        plotWait = plotWait - 1;
        data = fscanf(arduino,'%d %d');
        times = [times data(2)/1000];
        temps = [temps data(1)];
        % only plots 1 of every 10 data points
        if (plotWait == 0)
            refreshdata(h, 'caller');
            drawnow;
            plotWait = 10;
        end
end


% pauseLength = .005;
% plotWait = 1;
% iter = floor(plotWait/pauseLength);
% for z = 1:10
%     for k = 1:iter
%         t = [t t(end)+pauseLength];
%         y = [y y(end)+rand(1)-rand(1)];
%         pause(pauseLength)
%     end
%   refreshdata(h,'caller') % Evaluate y in the function workspace
% 	drawnow;
%     end
