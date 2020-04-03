
# Ejercicio clase de deadlocks
	
Un deadlock puede ocurrir si:
- Un hilo intenta hacer una transferencia de la cuenta a a la cuenta b
- Otro hilo intenta una transferencia de la cuenta b a la cuenta a

En este caso si el hilo 1 obtiene el lock de la cuenta a y el hilo 2 obtiene
el lock de la cuenta b, ambos se quedaran bloqueados.


- Otra solución sería primero obtener el lock de la cuenta con el menor indice. En este caso, si se produce la situación de arriba el hilo 2 no  obtendrá ningún lock hasta que el hilo 1 complete su ejecución.


- Uno solución puede ser utilizar la función pthread_mutex_trylock al intentar conseguir el segundo lock, si no es posible, liberar el primer lock, llamar a la función sleep y intentar nuevamente.

