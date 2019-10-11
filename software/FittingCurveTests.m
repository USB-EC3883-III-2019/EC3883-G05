p8 = polyfit(Lidar.volts_real, Lidar.distance_real, 8);

y8 = polyval(p8, Lidar.volts_real);

p8_error = Lidar.distance_real - y8;
% Fitting Curves
subplot(2,1,1);
title('Distance vs Volts');
plot(Lidar.volts_real, Lidar.distance_real, 'LineWidth', 2);
hold on;
plot(Lidar.volts_real, y8, 'LineWidth', 2);
legend('Original', 'p8');
xlabel('Volts (V)');
ylabel('Distance (cm)');
grid on;
% Error Plot
subplot(2,1,2);
title('Error');
plot(Lidar.volts_real, p8_error, 'LineWidth', 2);
grid on;
legend('p8');
xlabel('Volts (V)');
ylabel('Distance (cm)');