function [FusionSL] = Fusion(Sonar, Lidar)

aux = Sonar - Lidar;

if aux > -10 && aux < 10
    FusionSL = (Sonar+Lidar)/2;
    else
    if aux > 10
        FusionSL = Lidar;
    else
     if aux < -10
        FusionSL = Sonar;
     end
    end
end