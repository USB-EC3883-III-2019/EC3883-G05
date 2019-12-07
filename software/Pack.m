function [message_sent] = Pack(message, position1, position2, position3, position4)

message_h = bitand(message, 240);
message_h = dec2bin(message_h, 8);
message_h = message_h(1:4);
message_h = strcat('1000',message_h);
byte0 = bin2dec(message_h);

message_l = bitand(message, 15);
message_l = dec2bin(message_l, 8);
message_l = message_l(5:8);
message_l = strcat('0000',message_l);
byte1 = bin2dec(message_l);

pos_1 = dec2bin(position1,3);
pos_2 = dec2bin(position2,3);
byte2 = strcat('00',pos_1,pos_2);
byte2 = bin2dec(byte2);

pos_3 = dec2bin(position3,3);
pos_4 = dec2bin(position4,3);
byte3 = strcat('00',pos_3,pos_4);
byte3 = bin2dec(byte3);

message_sent = [byte0,byte1,byte2,byte3];
end