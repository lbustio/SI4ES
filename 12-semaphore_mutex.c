#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 5 // Definimos el número de hilos que se crearán

// Variables compartidas
int contador = 0; // Contador que será modificado por los hilos
pthread_mutex_t mutex; // Mutex para proteger el acceso al contador
sem_t semaforo; // Semáforo para controlar el acceso a la sección crítica

// Función que será ejecutada por cada hilo
void* incrementar_contador(void* threadid) {
    long tid = (long)threadid; // Identificador del hilo

    // Esperar hasta que se pueda acceder al recurso (semáforo)
    sem_wait(&semaforo);
    
    // Bloquear el mutex antes de acceder al contador
    pthread_mutex_lock(&mutex);
    
    // Sección crítica: solo un hilo puede ejecutar esto a la vez
    printf("Hilo %ld: Accediendo al contador...\n", tid);
    
    int temp = contador; // Guardamos el valor actual del contador
    sleep(1); // Simulamos un trabajo que toma tiempo (1 segundo)
    
    contador = temp + 1; // Incrementamos el contador
    printf("Hilo %ld: Contador incrementado a %d\n", tid, contador);
    
    // Desbloquear el mutex después de modificar el contador
    pthread_mutex_unlock(&mutex);
    
    // Liberar el semáforo para permitir que otro hilo acceda
    sem_post(&semaforo);
    
    pthread_exit(NULL); // Terminar el hilo
}

int main() {
    pthread_t threads[NUM_THREADS]; // Array para almacenar los identificadores de los hilos
    
    // Inicializar el mutex y el semáforo
    pthread_mutex_init(&mutex, NULL); // Inicializa el mutex sin atributos específicos
    sem_init(&semaforo, 0, 1); // Inicializa el semáforo permitiendo solo un acceso (valor inicial 1)
    
    // Crear los hilos
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, incrementar_contador, (void*)i); // Crea un nuevo hilo
    }
    
    // Esperar a que todos los hilos terminen su ejecución
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL); // Espera a que cada hilo termine
    }
    
    // Imprimir el valor final del contador después de que todos los hilos han terminado
    printf("Valor final del contador: %d\n", contador);
    
    // Destruir el mutex y el semáforo para liberar recursos
    pthread_mutex_destroy(&mutex); 
    sem_destroy(&semaforo);
    
    return 0; // Finaliza la ejecución del programa con éxito
}