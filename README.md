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

- SOCKET: Como en los trabajos practicos anteriores, esta clase es un socket con los métodos necesarios para poder efectuar la comunicación entre cliente y servidor: abrir el socket, esperar a una conexión, aceptarla y finalmente cerrar el socket correctamente.

- SERVER: Representa al servidor en el juego. Inicia una conexion con el cliente y la realiza, tambien tiene la opcion de que si le escribe el comando 'q' este deja de aceptar conexiones de clientes nuevos y espera a que los que estan conectados terminen para realizar el cierre de este ordenado.

- GAME CONTAINER: Esta clase es la contenedora de todos los juegos que estan ejecutandose en el momento. Es, de manera camuflada, un *MapMonitor* ya que protege las operaciones que se hacen dentro del mapa que contiene a los juegos.

- PROTECTED MAP: Como se menciono anteriormente, este es el mapa que contiene a las partidas. Es un mapa de par *<string,TaTeTi>* y a este se le realizan todas las operaciones necesarias basicas para que pueda ejercer su responsabilidad.

- SERVER PROTOCOL: Una vez que entablece una conexion esta clase se encarga de recibir y enviar los mensajes al cliente respentando el protocolo propuesto, tambien de delegar las operaciones necesarias a cada juego en su instancia de `TaTeTi`.

- TATETI: Esta clase representa al juego en si. Tiene metodos para que todas las operaciones clasicas del juego puedan ser realizadas. Esta clase tambien esta protegida y es *thread safe* ya que hay siempre dos hilos que estan modificando esta de manera concurrente.

- THREAD: Esta clase contiene al hilo de la libreria estandar, que sera usado por *Thread Acceptor* y *Thread Client*, contiene tambien la sobrecarga de operadores para que se pueda realizar el trabajo de manera correcta.

- THREAD ACCEPTOR: Esta clase representa a un hilo *aceptador*, el cual es el encargado de realizar la aceptacion de nuevos jugadores al programa. Esta clase es una clase hija de la clase *Thread* y tiene el metodo `run` que es el que ejecuta el algoritmo mencionado anteriormente.

- THREAD CLIENT: Al igual que la clase anterior, esta clase hereda de *Thread*. Esta clase es la representacion de un jugador para el servidor en la algoritmia del juego.

# IMPLEMENTACIÓN

Para la implementacion se busco siempre cumplir con el paradigma de programacion orientada a objetos. En todo momento se intento no romper con el encapsulamiento y delegar comportamientos. Asimismo tambien cumplir con los principios SOLID.

# PROBLEMAS EN PRIMERA ENTREGA.

Para esta entrega se encontro el siguiente problema:

- El programa en la computadora se ejecuta de manera correcta. Es decir siguiendo el *schedule* de las pruebas se obtiene el resultado adecuado y buscado, agregando que todos los recursos son liberados correctamente y no se pierde memoria. El problema ocurre cuando se quiere subir el programa a la plataforma de pruebas provisto por la catedra *sercom*. Aqui se arroja `El programa 'Server' termino con un codigo de error '124' muy posiblemente por timeout.`, lo cual no permite la ejecucion de las pruebas debido a que el programa se queda colgado en alguna parte y debe ejecutarse el cierre forzdo. Mostrando, que los mensajes no fueron enviados correctamente y se quedan en la mitad. Lo cual eso en mi computadora no ocurre (corriendo el programa con y sin valgrind). De hecho, cuando se ejecuta *tiburoncin* las salidas de este son tal cual a las esperadas en los casos de prueba. Lo cual me hace notar que esta sucediendo algo raro. 
Mi hipotesis sobre el mal funcionamiento del programa en el sercom es que debe haber una *race condition* en algun lado. Pero eso cuando lo pruebo localmente no lo puedo ver, ya que mi programa se ejecuta bien. Seguramente sea debido a que cuando se introducen los comandos manualmente se hacen de manera mas lenta que cuando se ejecuta el *script* del sercom, haciendo asi que ocurra la situacion no deseada y generando el mal comportamiento del programa. 
Adjunto imagenes que comprueban que en la computadora personal los programas se ejecutan correctamente:}

Caso 02 - One Match
![Prueba numero 1 funciona OK](https://user-images.githubusercontent.com/45469722/120196018-bdc6c200-c1f5-11eb-9f2a-9afb96cd9c2f.png)

Caso 03 - Two Concurrent Ties
![caso 02 anda Ok](https://user-images.githubusercontent.com/45469722/120196033-c0c1b280-c1f5-11eb-99d4-c465710cb77f.png)

*ACLARACION:* La 'q' se ejecuto en el servidor en el medio de las partidas. Para que nadie pueda conectarse y el servidor deba esperar a que los clientes terminen para cerrarse. Tambien como aclaracion, corri con tsan el servidor y no me genero en ningun momento una race condition, en ambos casos.


# Diagrama de clases representativo de la solución final:
*ACLARACION:* En este diagrama, y como primera entrega. Se muestran solamente las clases y como se relacionan entre ellas para que pueda verse un mayor entendimiento del programa.

