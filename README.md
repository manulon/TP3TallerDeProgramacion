# TP3TallerDeProgramacion
# TP3 - TaTeTi
# Alumno: Manuel Longo Elia
# Padrón: 102425

En este trabajo se implementa un programa que emula un *TaTeTi* pero de manera distribuida: Habrá un servidor con la lógica del juego, y los clientes podrán crear partidas o unirse a partidas existentes para desafiar a otros jugadores.El programa soporta múltiples partidas al mismo tiempo.

# DISEÑO

Antes de implementar la solución, se empezó por diseñarla, planteando las diferentes estructuras del programa y cómo iban a relacionarse entre sí. 

El diseño se pensó usando como base la programación orientada a objetos.

Se plantearon los siguientes:

- CLIENT: Representa al cliente en el juego, es decir al jugador. Este inicia una conexion con el servidor y la realiza.

- CLIENT PROTOCOL: Una vez que entablece una conexion esta clase se encarga de enviar los mensajes al servidor respentando el protocolo propuesto, enviando los mensajes necesarios leidos por la entrada estandar. 

- COMMUNICATION PROTOCOL: Esta clase es la clase comun del protocolo de comunicacion, se conecta con el protocolo cliente y servidor para poder realizar los envios a traves de un socket.

- SOCKET: Como en los trabajos practicos anteriores, esta clase es un socket con los métodos necesarios para poder efectuar la comunicación entre cliente y servidor: abrir el socket, esperar a una conexión, aceptarla , enviar, recibir y finalmente cerrar el socket correctamente.

- SERVER: Representa al servidor en el juego. Inicia una conexion con el cliente y la realiza, tambien tiene la opcion de que si le escribe el comando 'q' este deja de aceptar conexiones de clientes nuevos y espera a que los que estan conectados terminen para realizar el cierre de este ordenado.

- GAME CONTAINER: Esta clase es la contenedora de todos los juegos que estan ejecutandose en el momento. Es, de manera camuflada, un *MapMonitor* ya que protege las operaciones que se hacen dentro del mapa que contiene a los juegos.

- SERVER PROTOCOL: Una vez que entablece una conexion esta clase se encarga de recibir y enviar los mensajes al cliente respentando el protocolo propuesto, tambien de delegar las operaciones necesarias a cada juego en su instancia de `TaTeTi`.

- TATETI: Esta clase representa al juego en si. Tiene metodos para que todas las operaciones clasicas del juego puedan ser realizadas.

- TATETI WRAPPER: Esta clase es un *wrapper* de la clase TaTeTi, para hacerse cargo de que el juego sea *thread safe* y que el TaTeTi solo tenga en su interior la logica de juego. En esta clase siempre hay dos hilos que estan modificando un TaTeTi de manera concurrente.

- THREAD: Esta clase contiene al hilo de la libreria estandar, que sera usado por *Thread Acceptor* y *Thread Client*, contiene tambien la sobrecarga de operadores para que se pueda realizar el trabajo de manera correcta.

- THREAD ACCEPTOR: Esta clase representa a un hilo *aceptador*, el cual es el encargado de realizar la aceptacion de nuevos jugadores al programa. Esta clase es una clase hija de la clase *Thread* y tiene el metodo `run` que es el que ejecuta el algoritmo mencionado anteriormente.

- THREAD CLIENT: Al igual que la clase anterior, esta clase hereda de *Thread*. Esta clase es la representacion de un jugador para el servidor en la algoritmia del juego.

# IMPLEMENTACIÓN

Para la implementacion se busco siempre cumplir con el paradigma de programacion orientada a objetos. En todo momento se intento no romper con el encapsulamiento y delegar comportamientos. Asimismo tambien cumplir con los principios SOLID.

# CAMBIOS EN LA REENTREGA.

- Se sacaron los metodos `init` de clases como `CommunicationProtocol`, `ClientProtocol` o `ServerProtocol`.
- Se cambiaron nombres de algunos metodos ya que estos no eran descriptivos o no representaban lo que estos hacian.
- Se solucionaron varios problemas de performance, por ejemplo buffers (cada vez que se creaba uno se creaban de un tamaño mayor en una unidad al requerido), concatenaciones de strings e inicializaciones.
- Las constantes que representan a las key se hicieron char, para simplificar tambien el codigo.
- Se hizo uso de simetria cuando se encodea y des-encodea la posicion de la jugada realizada por el usuario, ya que antes esas logicas estaban sueltas por el codigo.
- Se removio el const& de los tipos nativos.
- Cuando se hizo uso de excepciones, se utilizo stdout para informar el error.
- Se crearon los metodos `socket_send` y `socket_receive` para que sea responsabilidad del socket el envio y recepcion de bytes. Ya no se rompe mas el encapsulamiento del *file descriptor*
- Se hizo el socket *movible pero no copiable*. En las demas clases esto no fue necesario ya que en ningun momento se necesito.
- Se arreglo el "hack" de `get_board`, ahora las jugadas son las que retornan el tablero para evitar race conditions
- Se hizo uso de `std::stringstream` para no copiar el tablero cada vez que se usaba +=.
- Se creo el metodo `garbage_collector` que lo que hace es "limpiar" a los clientes que ya se fueron.
- Se creo la clase `TaTeTiWrapper` para que el TaTeTi tenga solamente logica de juego y esta clase sea la encargada de manejar el acceso concurrente al juego.


# Diagrama de clases representativo de la solución final:
*ACLARACION:* En este diagrama, y como primera entrega. Se muestran solamente las clases y como se relacionan entre ellas para que pueda verse un mayor entendimiento del programa.
