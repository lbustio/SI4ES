#include <stdio.h>      // Biblioteca para funciones de entrada/salida
#include <stdlib.h>     // Biblioteca para funciones de utilidad general
#include <time.h>       // Biblioteca para manejo de tiempo
#include <unistd.h>     // Biblioteca para funciones POSIX como sleep()

// Definimos un tiempo límite en segundos para la ejecución de la tarea
#define TIME_LIMIT 2 // Tiempo límite en segundos

// Función que simula una tarea que puede tardar un tiempo variable en completarse
void tarea() {
    // Generamos un tiempo de trabajo aleatorio entre 0 y 3 segundos
    int tiempoTrabajo = rand() % 4; // Genera un número aleatorio entre 0 y 3
    printf("Tarea comenzando, se espera que tarde %d segundos...\n", tiempoTrabajo);
    
    // Simulamos el tiempo de ejecución de la tarea
    sleep(tiempoTrabajo); // Pausa la ejecución durante el tiempo simulado
}

// Función que ejecuta la tarea con el patrón TimeGuard
void ejecutarConTimeGuard() {
    time_t inicio, fin; // Variables para almacenar el tiempo de inicio y fin
    
    // Obtener el tiempo de inicio
    inicio = time(NULL); // Captura el tiempo actual en segundos desde la época

    // Ejecutar la tarea
    tarea(); // Llamamos a la función que simula la tarea

    // Obtener el tiempo de fin
    fin = time(NULL); // Captura el tiempo actual después de ejecutar la tarea

    // Calcular el tiempo transcurrido en segundos
    double tiempoTranscurrido = difftime(fin, inicio); // Calcula la diferencia entre fin e inicio
    
    // Verificar si se excedió el tiempo límite definido
    if (tiempoTranscurrido > TIME_LIMIT) {
        printf("Error: La tarea excedió el tiempo límite de %d segundos. Tiempo transcurrido: %.2f segundos.\n", TIME_LIMIT, tiempoTranscurrido);
        
        // Manejo del error: reiniciar la tarea o tomar otra acción adecuada.
        printf("Reiniciando la tarea...\n");
        ejecutarConTimeGuard(); // Reinicia la ejecución como ejemplo de manejo de error
    } else {
        printf("La tarea se completó exitosamente en %.2f segundos.\n", tiempoTranscurrido);
    }
}

// Función principal del programa
int main() {
    srand(time(NULL)); // Inicializa la semilla para números aleatorios usando el tiempo actual
    ejecutarConTimeGuard(); // Llama a la función que implementa el patrón TimeGuard
    return 0; // Termina el programa exitosamente
}