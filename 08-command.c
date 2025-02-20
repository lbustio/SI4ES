#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura Command (Interfaz del Comando)
typedef struct Command {
    void (*execute)(void*); // Puntero a función que ejecuta el comando
    void* receiver;          // Puntero genérico al receptor asociado al comando
} Command;

// Receptor (Lámpara)
typedef struct Light {
    // No se necesitan métodos dentro de la estructura, solo se usa como receptor
} Light;

// Función que enciende la lámpara
void light_on(void* receiver) {
    printf("La lámpara está encendida.\n"); // Mensaje al encender la lámpara
}

// Función que apaga la lámpara
void light_off(void* receiver) {
    printf("La lámpara está apagada.\n"); // Mensaje al apagar la lámpara
}

// Función para crear un comando genérico
Command* create_command(void (*execute)(void*), void* receiver) {
    Command* command = (Command*)malloc(sizeof(Command)); // Asignar memoria para el comando
    if (command != NULL) {
        command->execute = execute; // Asignar la función de ejecución
        command->receiver = receiver; // Asignar el receptor
    }
    return command; // Devolver el comando creado
}

// Invocador (Control Remoto)
typedef struct RemoteControl {
    Command* command; // Puntero al comando actual asignado
} RemoteControl;

// Función para asignar un comando al control remoto
void set_command(RemoteControl* remote, Command* command) {
    remote->command = command; // Asignar el comando al control remoto
}

// Función para presionar el botón y ejecutar el comando asignado
void press_button(RemoteControl* remote) {
    if (remote->command != NULL && remote->command->execute != NULL) { // Verificar si hay un comando asignado
        remote->command->execute(remote->command->receiver); // Ejecutar el comando con su receptor
    } else {
        printf("No hay comando asignado.\n"); // Mensaje si no hay ningún comando asignado
    }
}

// Función principal donde se ejecuta el programa
int main() {
    // Crear el receptor (lámpara)
    Light light;

    // Crear comandos para encender y apagar la lámpara usando la función de creación de comandos
    Command* lightOnCommand = create_command(light_on, &light);   // Comando para encender la lámpara
    Command* lightOffCommand = create_command(light_off, &light); // Comando para apagar la lámpara

    // Crear el invocador (control remoto)
    RemoteControl remote;

    // Asignar el comando de encender la lámpara al control remoto y ejecutarlo
    set_command(&remote, lightOnCommand); // Asignar el comando de encender
    press_button(&remote);                 // Presionar el botón para ejecutar

    // Asignar el comando de apagar la lámpara al control remoto y ejecutarlo
    set_command(&remote, lightOffCommand); // Asignar el comando de apagar
    press_button(&remote);                  // Presionar el botón para ejecutar

    // Liberar memoria asignada dinámicamente para los comandos creados
    free(lightOnCommand);
    free(lightOffCommand);

    return 0; // Fin del programa
}
