# Problema fumadores

 Puede ocurrir un deadlock si el agente entrega un par de elemntos y cada uno es tomado por un fumador distino
 Por ejemplo:

 Fumador 1: tabaco y papel
 Fumador 2: fosforos y tabaco
 Fumador 3: papel y fosforos

 Si el agente entrega tabaco y papel, se puede ejecutar la sig secuencia:

 Fumador 1 decrementa el semáforo tabaco 
 Fumador 3 decrementa el semáforo papel

 Ambos fumadores quedaran bloqueados esperando el siguiente elemento porque el semafóro otra_vez nunca llega a incrementase.


 Uno solución es tener un semáforo por cada combinación de elementos posibles, cada uno correspondiendo unicamente a un fumador.
