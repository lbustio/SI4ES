#include <stdio.h>       // Para funciones de entrada/salida estándar (printf)
#include <stdlib.h>      // Para funciones de utilidad general (exit)
#include <string.h>      // Para funciones de manipulación de cadenas (strlen)
#include <unistd.h>      // Para funciones del sistema operativo (read, write, close)
#include <arpa/inet.h>   // Para funciones de manipulación de direcciones de red (htons, inet_pton)

#define PORT 8080    // Define el puerto al que el cliente se conectará
#define BUFFER_SIZE 1024  // Define el tamaño del buffer para recibir datos

int main() {
    int sock = 0;               // Descriptor de archivo para el socket del cliente
    struct sockaddr_in serv_addr; // Estructura para almacenar la dirección del servidor
    char *message = "Hola desde el cliente!"; // Mensaje que el cliente enviará al servidor
    char buffer[BUFFER_SIZE] = {0}; // Buffer para almacenar los datos recibidos del servidor, inicializado a cero

    // 1. Crear el socket del cliente
    // socket(dominio, tipo, protocolo)
    // AF_INET: Familia de direcciones IPv4
    // SOCK_STREAM: Tipo de socket para TCP (conexión orientada a flujo)
    // 0: Protocolo predeterminado (TCP para SOCK_STREAM)
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Error al crear el socket \n");
        return -1; // Termina el programa con un código de error
    }

    // 2. Configurar la dirección del servidor
    serv_addr.sin_family = AF_INET;  // Familia de direcciones IPv4
    serv_addr.sin_port = htons(PORT); // Puerto del servidor en formato de red (big-endian)

    // 3. Convertir la dirección IPv4 desde texto a formato binario
    // inet_pton(familia, dirección_texto, dirección_binaria)
    // AF_INET: Familia de direcciones IPv4
    // "127.0.0.1": Dirección IP del servidor (localhost)
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\n Dirección no válida/ Dirección no soportada \n");
        return -1; // Termina el programa con un código de error
    }

    // 4. Conectar al servidor
    // connect(socket, direccion_servidor, longitud_direccion)
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\n Error de conexión \n");
        return -1; // Termina el programa con un código de error
    }

    // 5. Enviar mensaje al servidor
    // send(socket, mensaje, longitud_mensaje, flags)
    // Envía longitud_mensaje bytes del mensaje a través del socket
    send(sock, message, strlen(message), 0);
    
    // 6. Leer respuesta del servidor
    // read(socket, buffer, tamaño)
    // Lee hasta tamaño bytes del socket y los almacena en el buffer
    read(sock, buffer, BUFFER_SIZE);
    
    printf("Respuesta del servidor: %s\n", buffer);

    // 7. Cerrar el socket
    close(sock); // Cierra el socket del cliente
    
    return 0;  // El programa termina exitosamente
}
