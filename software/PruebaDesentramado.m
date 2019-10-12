% Data test
DataTest = importdata('DataTest.mat');

% Random data
%PositionRAW = [[0:40] [40:-1:0]];
%LidarRAW = randi([512, 4095], 1, length(PositionRAW));
%SonarRAW = randi([0, 512], 1, length(PositionRAW));

% Unpack and convert data
[PositionRAW, LidarRAW, SonarRAW] = unpack(DataTest);
[Position, Lidar, Sonar] = ConvertData(PositionRAW, LidarRAW, SonarRAW);


% Create polaraxes object
pax = polaraxes;

% First plot and get the chart line object for Lidar and Sonar
LidarPlot = polarscatter(pax, Position, Lidar, 'filled');
hold on;
SonarPlot = polarscatter(pax, Position, Sonar, 'filled');
legend('Lidar','Sonar');

% Customize the polar axes
pax.ThetaZeroLocation = 'top';
pax.ThetaDir = 'clockwise';
pax.ThetaTickLabel = {'0', '30', '60', '90', '120', '150', '180', '-150', '-120', '-90', '-60', '-30'};
pax.RLim = [0 200];
pax.RTick = 0:50:200;

% To update the plot...
LidarPlot.ThetaData = linspace(0,2*pi(),20);   % Update the theta
SonarPlot.ThetaData = linspace(0,2*pi(),20);

LidarPlot.RData = linspace(1,80,20);           % Update the Lidar data
SonarPlot.RData = linspace(150,50,20);         % Update the Sonar data