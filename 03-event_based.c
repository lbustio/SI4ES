#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Estructura que representa un evento
typedef struct {
    int evento_id;             // Identificador único del evento
    char descripcion[100];     // Descripción del evento
} Evento;

// Estructura que representa un canal de eventos
typedef struct {
    Evento eventos[10];        // Canal con capacidad para almacenar hasta 10 eventos
    int count;                 // Contador de eventos en el canal
    pthread_mutex_t lock;      // Mutex para asegurar acceso seguro al canal desde múltiples hilos
} CanalDeEventos;

// Función para inicializar el canal de eventos
void init_canal(CanalDeEventos *canal) {
    canal->count = 0;                               // Inicializa el contador de eventos en 0
    pthread_mutex_init(&canal->lock, NULL);         // Inicializa el mutex para proteger el acceso concurrente
}

// Función para enviar un evento al canal
void enviar_evento(CanalDeEventos *canal, Evento evento) {
    pthread_mutex_lock(&canal->lock);               // Bloquea el mutex para evitar acceso concurrente al canal
    if (canal->count < 10) {                        // Si hay espacio en el canal
        canal->eventos[canal->count] = evento;      // Agrega el evento al canal
        canal->count++;                              // Incrementa el contador de eventos
        printf("Evento enviado: %s\n", evento.descripcion);  // Imprime un mensaje indicando que el evento fue enviado
    } else {
        printf("Canal lleno. No se pudo enviar el evento.\n");  // Si el canal está lleno
    }
    pthread_mutex_unlock(&canal->lock);             // Desbloquea el mutex después de agregar el evento
}

// Función que un consumidor usa para procesar eventos del canal
void procesar_eventos(CanalDeEventos *canal) {
    while (1) {  // Bucle infinito donde el consumidor procesa eventos
        pthread_mutex_lock(&canal->lock);  // Bloquea el mutex para acceso seguro al canal
        if (canal->count > 0) {            // Si hay eventos para procesar
            Evento evento = canal->eventos[0];  // Toma el primer evento del canal
            // Desplaza los eventos restantes para que el siguiente evento quede en la primera posición
            for (int i = 1; i < canal->count; i++) {
                canal->eventos[i - 1] = canal->eventos[i];
            }
            canal->count--;  // Decrementa el contador de eventos en el canal
            printf("Evento procesado: %s\n", evento.descripcion);  // Imprime un mensaje indicando que el evento fue procesado
        } else {
            printf("No hay eventos para procesar.\n");  // Si no hay eventos en el canal
        }
        pthread_mutex_unlock(&canal->lock);  // Desbloquea el mutex después de procesar el evento
        sleep(1);  // Espera 1 segundo antes de intentar procesar otro evento
    }
}

// Función que simula un productor que genera eventos
void *productor(void *arg) {
    CanalDeEventos *canal = (CanalDeEventos *)arg;  // Toma el canal de eventos como argumento
    int id = 1;

    while (1) {  // Bucle infinito donde el productor genera eventos continuamente
        Evento evento;  // Declaración de un nuevo evento
        evento.evento_id = id++;  // Asigna un ID único para el evento
        snprintf(evento.descripcion, sizeof(evento.descripcion), "Evento #%d", evento.evento_id);  // Define una descripción para el evento
        enviar_evento(canal, evento);  // Envia el evento al canal
        sleep(2);  // Espera 2 segundos antes de generar un nuevo evento
    }

    return NULL;
}

// Función principal que crea los hilos y ejecuta la arquitectura basada en eventos
int main() {
    CanalDeEventos canal;   // Declaración de un canal de eventos
    init_canal(&canal);     // Inicializa el canal de eventos

    // Crear un hilo para el consumidor que procesa los eventos
    pthread_t consumidor_thread;
    pthread_create(&consumidor_thread, NULL, (void *)procesar_eventos, (void *)&canal);

    // Crear un hilo para el productor que genera eventos
    pthread_t productor_thread;
    pthread_create(&productor_thread, NULL, productor, (void *)&canal);

    // Esperamos a que ambos hilos finalicen (aunque en este caso no lo hacen, ya que están en un bucle infinito)
    pthread_join(productor_thread, NULL);
    pthread_join(consumidor_thread, NULL);

    // Liberamos recursos antes de salir (esto no se alcanzará en este ejemplo, debido al bucle infinito)
    pthread_mutex_destroy(&canal.lock);

    return 0;
}