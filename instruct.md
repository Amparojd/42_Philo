1º El problema está formado por:

-1 mesa redonda
-1 número X de filósofos (argv[1])
-1 tenedor por cada filósofo (aka mutex)


Por cada filósofo al que invitemos a nuestra mesa debe haber 1 tenedor.
Los filósofos tienen 3 tareas:

-Comer
-Dormir
-Pensar

El problema está en que para que un filósofo pueda comer necesita 2 tenedores, por lo que no pueden comer todos a la vez.

Existe también:

-X tiempo antes de morir de inanición(argv[2])
-X tiempo empleado para comer (argv[3])
-X tiempo empleado para dormir (argv[4])
-X número de comidas(argv[5])**

**También tenemos un argv opcional, que sería el número de comidas que queremos que realice cada filósofo. Una vez que todos hayan comido X veces, el programa finaliza.

El programa paso a paso:

1º Realizamos el parseo:
-¿Existen realmente el número de argumentos necesarios?
-Por cada error existe un mensaje de retorno diferente (número de argumentos inválido, vacíos o no son números)
-Si existe algún error, el programa retorna 1, lo que indica error.

2º Iniciamos nuestro entorno 



