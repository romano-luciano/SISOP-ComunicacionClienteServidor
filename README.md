# SISOP-ComunicacionClienteServidor
Repositorio para desarrollar el ejercicio 2 del trabajo practico. Comunicación Cliente-Servidor con Threads y Sockets  Proyecto desarrollado en lenguaje C

EJECUCION
-------------------------------------------------------------------------
Para la ejecución del Servidor lo primero que se debe hacer es ubicarse en la carpeta 'SISOP-ComunicacionClienteServidor/CASA_INTELIGENTE'.
Después para la compilación <gcc main.c Servidor.c Habitaciones.c Dispositivos.c Menu.c -o Servidor -lrt -pthread>
y se ejecuta con <./Servidor "Archivos/Habitaciones.txt">

Para el cliente se debe ir a la carpeta 'SISOP-ComunicacionClienteServidor/CLIENTE'
Después para compilar <gcc Cliente.c -o Cliente>
y se ejecuta con <./Cliente>


HERRAMIENTAS
-------------------------------------------------------------------------
Una ves que el servidor esta en funcionamiento, y al menos un cliente ser conecto podemos monitorear.

SOCKETS
-------
Para ver los sockets vamos a utilizar el comando <lsof -i> para ver los sockets de la computadora local, los que están en 'escucha' y los que no. 
También mostrara el ID del proceso que lo llamó, el usuario, tipo, el numero de sock, su protocolo de red, y su nombre. Acá podemos ver el puerto donde esta el socket de escucha.
También vamos a usar algo mas especifico que nos permite ver únicamente los sockets que se generaron a través del puerto que está en escucha. 
El comando es <lsof -i :mi_puerto>.

THREADS
-------
Para monitorear los hilos de ejecución usamos <htop>. Este comando muestra los procesos en ejecución de la PC local. En la columna PPID nos indica cual es el proceso padre. Para poder visualizar mejor los procesos filtramos por el usuario, y además buscamos el nombre de la carpeta donde esta el servidor: 'CASA_INTELIGENTE'.
Otro comando que usamos para visualizar los threads es lldb, que no es estándar y por lo tanto la descargamos con <sudo apt install lldb>.
Ejecutamos <lldb -p PID_CASA> donde <PID_CASA> es el ID del proceso padre que ejecuta el servidor. Luego ejecutamos (lldb) <thread list> Este comando pondrá en pausa el servidor y listará todos los hilos que están en ejecución. Para salir se escribe el comando <quit>.
Otro comando que usamos (y es estándar) para ver si el hilo principal del servidor se esta ejecutando. Ejecutamos <pgrep -fl CASA> donde <CASA> es el nombre del programa, en nuestro caso el servidor de casa Inteligente.