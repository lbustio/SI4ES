#include <stdio.h>       // Para funciones de entrada/salida estándar (printf, perror)
#include <stdlib.h>      // Para funciones de utilidad general (exit)
#include <string.h>      // Para funciones de manipulación de cadenas (strlen)
#include <unistd.h>      // Para funciones del sistema operativo (read, write, close)
#include <arpa/inet.h>   // Para funciones de manipulación de direcciones de red (htons, inet_addr)

#define PORT 8080    // Define el puerto en el que el servidor escuchará las conexiones
#define BUFFER_SIZE 1024  // Define el tamaño del buffer para recibir datos

int main() {
    int server_fd, new_socket;  // Descriptores de archivo para el socket del servidor y la nueva conexión
    struct sockaddr_in address;  // Estructura para almacenar la dirección del servidor
    int opt = 1;                 // Opción para reutilizar la dirección del socket
    int addrlen = sizeof(address); // Tamaño de la estructura de dirección
    char buffer[BUFFER_SIZE] = {0}; // Buffer para almacenar los datos recibidos del cliente, inicializado a cero

    // 1. Crear el socket del servidor
    // socket(dominio, tipo, protocolo)
    // AF_INET: Familia de direcciones IPv4
    // SOCK_STREAM: Tipo de socket para TCP (conexión orientada a flujo)
    // 0: Protocolo predeterminado (TCP para SOCK_STREAM)
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Error al crear el socket"); // Imprime un mensaje de error en stderr
        exit(EXIT_FAILURE);              // Termina el programa con un código de error
    }

    // 2. Opciones del socket (opcional, pero útil para evitar errores de "Address already in use")
    // setsockopt(socket, nivel, opción, valor, longitud_valor)
    // SOL_SOCKET: Nivel de la opción (socket)
    // SO_REUSEADDR: Permite reutilizar la dirección local cuando el servidor se reinicia rápidamente
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Error al establecer opciones del socket");
        exit(EXIT_FAILURE);
    }

    // 3. Definir la dirección del servidor
    address.sin_family = AF_INET;       // Familia de direcciones IPv4
    address.sin_addr.s_addr = INADDR_ANY; // Aceptar conexiones en cualquier dirección IP de la máquina
    address.sin_port = htons(PORT);      // Puerto en formato de red (big-endian)

    // 4. Enlazar el socket a la dirección y puerto especificados
    // bind(socket, direccion, longitud_direccion)
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Error al enlazar el socket");
        exit(EXIT_FAILURE);
    }

    // 5. Escuchar conexiones entrantes
    // listen(socket, backlog)
    // backlog: Número máximo de conexiones en cola
    if (listen(server_fd, 3) < 0) {
        perror("Error al escuchar");
        exit(EXIT_FAILURE);
    }

    printf("Servidor escuchando en el puerto %d...\n", PORT);

    // 6. Aceptar una conexión entrante
    // accept(socket, direccion_cliente, longitud_direccion_cliente)
    // Devuelve un nuevo descriptor de archivo para la conexión aceptada
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Error al aceptar la conexión");
        exit(EXIT_FAILURE);
    }

    // 7. Leer datos del cliente
    // read(socket, buffer, tamaño)
    // Lee hasta tamaño bytes del socket y los almacena en el buffer
    read(new_socket, buffer, BUFFER_SIZE);
    printf("Mensaje recibido: %s\n", buffer);

    // 8. Enviar respuesta al cliente
    const char *response = "Hola desde el servidor!";
    // send(socket, mensaje, longitud_mensaje, flags)
    // Envía longitud_mensaje bytes del mensaje a través del socket
    send(new_socket, response, strlen(response), 0);
    
    // 9. Cerrar los sockets
    close(new_socket); // Cierra el socket de la conexión con el cliente
    close(server_fd);  // Cierra el socket del servidor
    
    return 0;  // El programa termina exitosamente
}