% Data test
DataTest = importdata('DataTest.mat');

% Random data
PositionRAW = [[0:24] [24:-1:-24] [-24:0]];
LidarRAW = randi([512, 4095], 1, length(PositionRAW));
SonarRAW = randi([0, 512], 1, length(PositionRAW));

% Unpack and convert data
%[PositionRAW, LidarRAW, SonarRAW] = unpack(DataTest);
[Position, Lidar, Sonar] = ConvertData(PositionRAW, LidarRAW, SonarRAW);


% Create polaraxes object
pax = polaraxes;

% Customize the polar axes
pax.NextPlot = 'add';
pax.ThetaZeroLocation = 'top';
pax.ThetaDir = 'clockwise';
pax.ThetaTickLabel = {'0', '30', '60', '90', '120', '150', '180', '-150', '-120', '-90', '-60', '-30'};
pax.RLim = [0 200];
pax.RTick = 0:50:200;
pax.ThetaMinorGrid = 'on';

% First plot and get the chart line object for Lidar and Sonar
LidarPlot = polarscatter(pax, Position, Lidar, 'filled');
SonarPlot = polarscatter(pax, Position, Sonar, 'filled');
RadarField = polarhistogram(pax, repelem(0.1,200), 'NumBins', 2, 'BinWidth', pi()/48);
legend('Lidar','Sonar');


% To update the plot...
for i = 1:length(Position)
    LidarPlot.ThetaData = Position(i);   % Update the theta
    SonarPlot.ThetaData = Position(i);

    LidarPlot.RData = Lidar(i);          % Update the Lidar data
    SonarPlot.RData = Sonar(i);          % Update the Sonar data
    pause(0.1);
end