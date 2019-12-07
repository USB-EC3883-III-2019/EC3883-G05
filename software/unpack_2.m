function [message_recived] = unpack_2(data)
start = find(data >= 128,1);

syncData = data(start:end);

byte0 = syncData(1:4:end);
byte1 = syncData(2:4:end);

message_h = bitand(byte0, 15);
message_l = bitand(byte1, 15);

message_recived = message_h*16 + message_l;
end