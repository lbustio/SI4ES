#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 10 // Definimos el número máximo de tareas que el planificador puede manejar

// Definición de un puntero a función que no recibe argumentos y no devuelve nada
typedef void (*TaskFunction)(void);

// Estructura que representa una tarea
typedef struct {
    TaskFunction function; // Puntero a la función que implementa la tarea
    char name[20];         // Nombre de la tarea
} Task;

// Estructura que representa el planificador
typedef struct {
    Task tasks[MAX_TASKS]; // Array de tareas
    int taskCount;         // Contador actual de tareas
} Scheduler;

// Función para inicializar el planificador
void initScheduler(Scheduler *scheduler) {
    scheduler->taskCount = 0; // Establece el contador de tareas a cero
}

// Función para agregar una tarea al planificador
int addTask(Scheduler *scheduler, TaskFunction function, const char *name) {
    // Verifica si se ha alcanzado el número máximo de tareas
    if (scheduler->taskCount >= MAX_TASKS) {
        return -1; // Retorna -1 si no se pueden agregar más tareas
    }
    
    // Asigna la función y el nombre a la nueva tarea
    scheduler->tasks[scheduler->taskCount].function = function;
    strncpy(scheduler->tasks[scheduler->taskCount].name, name, sizeof(scheduler->tasks[scheduler->taskCount].name) - 1);
    
    // Asegura que el nombre esté terminado en null
    scheduler->tasks[scheduler->taskCount].name[sizeof(scheduler->tasks[scheduler->taskCount].name) - 1] = '\0';
    
    scheduler->taskCount++; // Incrementa el contador de tareas
    return 0; // Retorna 0 si la tarea se agregó exitosamente
}

// Función para ejecutar todas las tareas en el planificador
void runScheduler(Scheduler *scheduler) {
    for (int i = 0; i < scheduler->taskCount; i++) {
        printf("Ejecutando tarea: %s\n", scheduler->tasks[i].name); // Muestra el nombre de la tarea que se está ejecutando
        
        // Llama a la función asociada a la tarea actual
        scheduler->tasks[i].function();
    }
}

// Ejemplo de funciones de tarea

// Tarea A: Imprime un mensaje al completar la tarea A
void taskA() {
    printf("Tarea A completada.\n");
}

// Tarea B: Imprime un mensaje al completar la tarea B
void taskB() {
    printf("Tarea B completada.\n");
}

// Programa principal
int main() {
    Scheduler scheduler; // Declara una variable del tipo Scheduler
    
    initScheduler(&scheduler); // Inicializa el planificador
    
    // Agrega tareas al planificador con sus respectivas funciones y nombres
    addTask(&scheduler, taskA, "Tarea A");
    addTask(&scheduler, taskB, "Tarea B");
    
    runScheduler(&scheduler); // Ejecuta todas las tareas registradas en el planificador
    
    return 0; // Finaliza el programa con éxito
}