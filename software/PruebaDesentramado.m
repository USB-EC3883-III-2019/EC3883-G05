databyte = int8(ans);
start = find(databyte > 0, 1);
syncData = databyte(start:end-mod((512-start),4)-1);
syncData = typecast(syncData, 'uint8');
blocksize = length(syncData)/4;
byte0 = syncData(1:4:end);
byte1 = syncData(2:4:end);
byte2 = syncData(3:4:end);
byte3 = syncData(4:4:end);
Mask_posicion(1:blocksize,1) = uint8(63);
Mask_sonar_l(1:blocksize,1) = uint8(127);
Mask_sonar_h(1:blocksize,1) = uint8(96);
Mask_lidar_l(1:blocksize,1) = uint8(31);
Mask_lidar_h(1:blocksize,1) = uint8(127);

posicion_d = bitand(byte0, Mask_posicion);
sonar_l = bitand(byte1, Mask_sonar_l);
sonar_h = bitand(byte2, Mask_sonar_h);
lidar_l = bitand(byte2, Mask_lidar_l);
lidar_h = bitand(byte3, Mask_lidar_h);

sonar = uint16(sonar_h)/32+ uint16(sonar_l)*4;
lidar = uint16(lidar_h) + uint16(lidar_l)*128;

