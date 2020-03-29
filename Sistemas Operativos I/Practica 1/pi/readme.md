# Aproximación de \pi

El programa genera una cantidad NPuntos de puntos al azar usando una cantidad NHilos de pthreads por lo que cada uno de los cuales genera NPuntos / NHilos puntos.
Cada hilo cuenta cuántos de estos puntos están dentro de la circunferencia y guarda el valor en la dirección que se le pasa como argumento.

