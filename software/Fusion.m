function [FusionSL] = Fusion(Sonar, Lidar)

aux = Sonar(1) - Lidar(1);

if aux(1) > -10 && aux(1) < 10
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