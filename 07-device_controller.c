#include <stdio.h>  // Biblioteca estándar para entrada y salida (printf, etc.)
#include <stdlib.h> // Biblioteca estándar para funciones generales (opcional aquí)

// Definición de una estructura para representar un dispositivo
typedef struct {
    int id;           // Campo para almacenar el identificador único del dispositivo
    char name[50];    // Campo para almacenar el nombre del dispositivo (máximo 50 caracteres)
} Device;             // El nombre de esta estructura será "Device"

// Prototipos de funciones
// Estas son declaraciones de las funciones que se implementarán más adelante.
// Sirven para que el compilador conozca su existencia antes de usarlas.
void initializeDevice(Device *device, int id, const char *name); // Inicializa un dispositivo
void startDevice(Device *device);                                // Inicia un dispositivo
void stopDevice(Device *device);                                 // Detiene un dispositivo

// Función principal del programa
int main() {
    Device myDevice; // Declaración de una variable de tipo "Device" llamada "myDevice"

    // Llamamos a la función para inicializar el dispositivo.
    // Le pasamos la dirección (&) de "myDevice", un ID (1) y un nombre ("Mi Dispositivo").
    initializeDevice(&myDevice, 1, "Mi Dispositivo");

    // Llamamos a la función para iniciar el dispositivo.
    startDevice(&myDevice);

    // Llamamos a la función para detener el dispositivo.
    stopDevice(&myDevice);

    return 0; // Retornamos 0 indicando que el programa terminó exitosamente.
}

// Implementación de las funciones

// Función: initializeDevice
// Propósito: Configura los valores iniciales de un dispositivo (ID y nombre).
// Parámetros:
//   - device: Puntero al dispositivo que queremos inicializar.
//   - id: ID único del dispositivo.
//   - name: Nombre del dispositivo.
void initializeDevice(Device *device, int id, const char *name) {
    device->id = id; // Asignamos el ID al campo "id" del dispositivo.
    
    // Usamos snprintf para copiar el nombre al campo "name" del dispositivo,
    // asegurándonos de no exceder el tamaño máximo del arreglo.
    snprintf(device->name, sizeof(device->name), "%s", name);

    // Imprimimos un mensaje indicando que el dispositivo ha sido inicializado correctamente.
    printf("Dispositivo inicializado: ID=%d, Nombre=%s\n", device->id, device->name);
}

// Función: startDevice
// Propósito: Simula el inicio de un dispositivo.
// Parámetros:
//   - device: Puntero al dispositivo que queremos iniciar.
void startDevice(Device *device) {
    // Imprimimos un mensaje indicando que el dispositivo ha sido iniciado.
    printf("Dispositivo %s (ID: %d) iniciado.\n", device->name, device->id);
}

// Función: stopDevice
// Propósito: Simula la detención de un dispositivo.
// Parámetros:
//   - device: Puntero al dispositivo que queremos detener.
void stopDevice(Device *device) {
    // Imprimimos un mensaje indicando que el dispositivo ha sido detenido.
    printf("Dispositivo %s (ID: %d) detenido.\n", device->name, device->id);
}
