posicion = [0.017 0.087 0.34 0.52 0.17 1.57 1.65 1.83 2.007 2.09 2.26 3.14]; %Genera vector de posicion de valores de 10 
distancia = randi([0 80],1,12); %Genera vector de distancia aleatorio con max de 80
polarscatter(posicion,distancia,'filled');
[posicionx,posiciony] = transformar(posicion,distancia);
128
function [posicionx,posiciony] = transformar(posicion, distancia)

posicionx = distancia.*cos(posicion);
posiciony = distancia.*sin(posicion);
end


