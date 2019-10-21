function [Position, Lidar, Sonar] = ConvertData(PositionRAW, LidarRAW, SonarRAW)
%ConvertData Function to convert the raw data from the microcontroller
%   It converts the raw data from the microcontroller and process it to get
%   the true values

% Position conversion
TotalSteps = 48;
PositionScale = (2*pi()/TotalSteps);
Position = PositionScale*PositionRAW;

% Lidar conversion
LidarPoly = [7.67526029129288 -108.134109245746 644.115225669854 -2113.71833279663 4175.24292278666 -5097.1909611203 3802.7451305835 -1649.81901283364 366.038219660162];
LidarScale = 3/4096;
LidarEval = polyval(LidarPoly, LidarScale*LidarRAW);
Lidar = LidarEval*100;

% Sonar conversion
SonarScale = 122.0703125/58.30;
Sonar = SonarScale*SonarRAW;
end

