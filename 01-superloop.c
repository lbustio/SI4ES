#include <stdio.h>
#include <stdbool.h>

// ==============================
//        SUPER LOOP EN C
// ==============================
// Este programa implementa el patrón "Super Loop", común en sistemas embebidos.
// Se ejecutan tareas en un bucle infinito hasta que el usuario decide detener el sistema.

// ----------------------------
//       DECLARACIÓN DE TAREAS
// ----------------------------

// Cada tarea representa una operación dentro del sistema
void tarea1() { printf("Ejecutando tarea 1\n"); }
void tarea2() { printf("Ejecutando tarea 2\n"); }
void tarea3() { printf("Ejecutando tarea 3\n"); }

// ----------------------------
//      ARRAY DE TAREAS
// ----------------------------

// Usamos un array de punteros a funciones para almacenar las tareas.
// Esto permite mayor flexibilidad y escalabilidad en la ejecución de tareas.
void (*tareas[])() = {tarea1, tarea2, tarea3};

// Calculamos el número de tareas de manera automática
const int numTareas = sizeof(tareas) / sizeof(tareas[0]);

// ----------------------------
//    FUNCIÓN DE CONTROL
// ----------------------------

// Esta función pregunta al usuario si desea continuar con la ejecución del sistema.
// Devuelve `true` si el usuario elige continuar, o `false` si elige detener el sistema.
bool verificarContinuar() {
    char continuar;

    printf("¿Continuar ejecutando el sistema? (s/n): ");
    scanf(" %c", &continuar); // Leer la respuesta del usuario

    // Limpiar el buffer de entrada para evitar problemas con scanf
    while (getchar() != '\n');

    // Si el usuario ingresa 'n' o 'N', detenemos el sistema.
    return (continuar != 'n' && continuar != 'N');
}

// ----------------------------
//     FUNCIÓN PRINCIPAL
// ----------------------------

int main() {
    // Bucle principal del sistema (Super Loop)
    do {
        // Ejecutar todas las tareas de forma secuencial
        for (int i = 0; i < numTareas; i++) {
            tareas[i](); // Llamamos a cada función almacenada en el array de tareas
        }
    } while (verificarContinuar()); // Preguntar al usuario si desea continuar

    printf("Sistema detenido.\n");
    return 0;
}
