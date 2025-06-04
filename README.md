# SISOP-ComunicacionClienteServidor
Repositorio para desarrollar el ejercicio 2 del trabajo practico. Comunicación Cliente-Servidor con Threads y Sockets  Proyecto desarrollado en lenguaje C

EJECUCION
-------------------------------------------------------------------------
Para la ejecucion del Servidor lo primero que se debe hacer es ubicarse en la carpea 'SISOP-ComunicacionClienteServidor/CASA_INTELIGENTE'.
Despues para la compilacion <gcc main.c Servidor.c Habitaciones.c Dispositivos.c Menu.c -o Servidor -lrt -pthread>
y se ejecuta con <./Servidor "Archivos/Habitaciones.txt">

Para el cliente se debe ir a la carpeta 'SISOP-ComunicacionClienteServidor/CLIENTE'
Despes para compilar <gcc Cliente.c -o Cliente>
y se ejecuta con <./Cliente>


HERRAMIENTAS
-------------------------------------------------------------------------
Una ves que el servidor esta en funcionamiento, y al menos un cliente ser conecto podemos monitorear.

SOCKETS
-------
Para ver los sockets vamos a utilizar el comando <lsof -i> para ver los sockets de la computadora local, los que estan en 'escucha' y los que no. 
Tambien mostrara el ID del proceoso que lo llamó, el usuario, tipo, el numero de sock, su protocolo de red, y su nombre. Aca podemos ver el puerto donde esta el socket de escucha.
Tambien vamos a usar algo algo mas especifico que nos permite ver unicamente los sockets que se generaron a traves del puerto que está en escucha. 
El comando es <lsof -i :mi_puerto>.

THREADS
-------
Para monitorear los hilos de ejecucion usamos <htop>. Este comando mustra los procesos en ejecucion de la PC local. En la columna PPID nos indica cual es el proceso padre. Para poder visualizar mejor los procesos filtramos por el usuario, y ademas buscamos el nombre de la carpteta donde esta el servidor: 'CASA_INTELIGENTE'.
Otro comando que usamos para visualizar los threads es lldb, que no es estandar y por lo tando la descargamos con <sudo apt install lldb>.
Ejecutamos <lldb -p PID_CASA> donde <PID_CASA> es el ID del proceso padre que ejecta el servidor.Luego ejecutamos (lldb) <thread list> Este comando pontra en pusar el servidor y listará todos los hilos que estan en ejecucion. Para salir se escribe el comando <quit>.
Otro comando que usamos (y es estandar) para ver si el hilo principal del servidor se esta ejecutando. Ejectamos <pgrep -fl CASA> donde <CASA> es el nombre del programa, en nuetro caso el servidor de casa Inteligente.