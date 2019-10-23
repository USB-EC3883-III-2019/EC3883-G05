function [PositionRAW, LidarRAW, SonarRAW] = unpack(data)
databyte = int8(data);
start = find(databyte > 0, 1);

syncData = databyte(start:end-mod((8-start),4)-1);
syncData = typecast(syncData, 'uint8');
blocksize = length(syncData)/4;

byte0 = syncData(1:4:end);
byte1 = syncData(2:4:end);
byte2 = syncData(3:4:end);
byte3 = syncData(4:4:end);

Mask_position(1:blocksize,1) = uint8(63);
Mask_Position2(1:blocksize,1) = uint8(192);
Mask_sonar_l(1:blocksize,1)  = uint8(127);
Mask_sonar_h(1:blocksize,1)  = uint8(96);
Mask_lidar_l(1:blocksize,1)  = uint8(31);
Mask_lidar_h(1:blocksize,1)  = uint8(127);

sonar_l     = single(bitand(byte1, Mask_sonar_l));
sonar_h     = single(bitand(byte2, Mask_sonar_h));
lidar_l     = single(bitand(byte2, Mask_lidar_l));
lidar_h     = single(bitand(byte3, Mask_lidar_h));
PositionRAW = bitand(byte0, Mask_position);
if PositionRAW >= 32
   PositionRAW = bitor(PositionRAW, Mask_Position2);
   PositionRAW = -1.*single(bitcmp(PositionRAW) + 1);
end
PositionRAW = single(PositionRAW);
    
SonarRAW = sonar_h/32+ sonar_l*4;
LidarRAW = lidar_h + lidar_l*128;
end

