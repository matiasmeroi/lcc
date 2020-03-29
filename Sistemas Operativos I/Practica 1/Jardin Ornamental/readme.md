# Jardin Ornamental

 1. Como la instrucción counter++ no es atómica, lo que en realidad se está haciendo es: cargar el valor de la variable counter en un registro, incrementar el registro y finalmente guardar el valor en memoria. Al ejecutarse los dos hilos concurrentemente, puede pasar que un hilo cargue el valor de counter a un registro, lo incremente y luego se produzca un cambio de contexto, haciendo que el siguiente hilo que se ejecuta lea un valor incorrecto de la memoria.
 2. Si el programa da el resultado correcto puede ser porque todos los cambios de contexto se produjeron despues de que se ejecute counter++ completamente, o porque un thread terminó antes de que empiece el otro.
 3. El mínimo valor es 2:
	- Hilo 1: carga 0 en registro (CC: cambio de contexto)
	- Hilo 2: carga 0 en registro (CC)
	- Hilo 1: incrementa registro hasta N - 1
	- Hilo 1: guarda N - 1 (CC)
	- Hilo 2: incrementa registro a 1
	- Hilo 2: guarda 1 (CC)
	- Hilo 1: carga 1
	- Hilo 1: incrementa a 2 (CC)
	- Hilo 2: incrementa hasta N
	- Hilo 2: guarda N (CC)
	- Hilo 1: incrementa a 2
	- Hilo 1: guarda 2	
