#include <stdio.h>
#include <stdlib.h>

// Definimos los posibles estados de la máquina como una enumeración.
// Cada estado representa una fase del ciclo de operación del sistema.
typedef enum {
    ESTADO_INICIAL,   // Estado donde el sistema se inicializa
    ESTADO_ESPERA,     // Estado de espera, esperando por algún evento
    ESTADO_TRABAJO,    // Estado donde el sistema realiza sus operaciones
    ESTADO_TERMINADO,   // Estado final, donde el sistema ha terminado sus tareas
    ESTADO_ERROR // Estado de error, utilizado cuando hay una transición incorrecta
} Estado;

// Definimos un tipo de función que manejará cada uno de los estados.
// Las funciones que manejarán los estados deben tener este tipo de firma.
typedef void (*EstadoHandler)();

// Prototipos de las funciones que manejan cada estado
void manejarEstadoInicial();  // Función que maneja el estado INICIAL
void manejarEstadoEspera();   // Función que maneja el estado de ESPERA
void manejarEstadoTrabajo();  // Función que maneja el estado de TRABAJO
void manejarEstadoTerminado(); // Función que maneja el estado de TERMINADO
void manejarEstadoError();    // Función que maneja el estado de ERROR

// Función para cambiar de estado. Recibe el estado actual y el nuevo estado al que se debe cambiar.
void cambiarEstado(Estado *estadoActual, Estado nuevoEstado);

int main() {
    // Estado inicial de la máquina
    Estado estadoActual = ESTADO_INICIAL;

    // Tabla de funciones que se utilizarán para manejar cada estado.
    // Cada posición en el arreglo contiene un puntero a la función correspondiente a un estado.
    EstadoHandler manejadoresEstados[] = {
        manejarEstadoInicial,   // Estado INICIAL
        manejarEstadoEspera,    // Estado ESPERA
        manejarEstadoTrabajo,   // Estado TRABAJO
        manejarEstadoTerminado, // Estado TERMINADO
        manejarEstadoError      // Estado ERROR (manejo de transiciones incorrectas)
    };

    // Bucle principal de la máquina de estados que simula el ciclo de ejecución del sistema.
    while (1) {
        // Llamamos a la función correspondiente al estado actual.
        manejadoresEstados[estadoActual]();
        
        // Transiciones de estado basadas en condiciones o eventos.
        // Después de ejecutar cada función de estado, el sistema pasa al siguiente estado.
        if (estadoActual == ESTADO_INICIAL) {
            cambiarEstado(&estadoActual, ESTADO_ESPERA);  // Transición al estado de espera
        } else if (estadoActual == ESTADO_ESPERA) {
            cambiarEstado(&estadoActual, ESTADO_TRABAJO); // Transición al estado de trabajo
        } else if (estadoActual == ESTADO_TRABAJO) {
            cambiarEstado(&estadoActual, ESTADO_TERMINADO); // Transición al estado terminado
        } else if (estadoActual == ESTADO_TERMINADO) {
            break;  // El sistema termina una vez que se ha alcanzado el estado terminado
        }
    }

    return 0;  // Aunque el programa nunca llega aquí debido al bucle infinito
}

// Función que maneja el estado INICIAL
void manejarEstadoInicial() {
    printf("Estado Inicial: Preparando el sistema...\n");
    // Aquí se pueden realizar las acciones de inicialización del sistema.
    // Esto podría incluir configurar hardware, inicializar variables, etc.
}

// Función que maneja el estado de ESPERA
void manejarEstadoEspera() {
    printf("Estado de Espera: Esperando la señal para continuar...\n");
    // Este estado espera algún tipo de evento o condición para proceder al siguiente estado.
    // En una implementación real, podría esperarse por una señal externa, como una interrupción de hardware o una entrada de usuario.
}

// Función que maneja el estado de TRABAJO
void manejarEstadoTrabajo() {
    printf("Estado de Trabajo: Realizando las operaciones...\n");
    // En este estado, el sistema ejecuta sus tareas principales.
    // Esto podría incluir la realización de cálculos, procesamiento de datos, o control de dispositivos.
}

// Función que maneja el estado de TERMINADO
void manejarEstadoTerminado() {
    printf("Estado Terminado: El proceso ha finalizado.\n");
    // Aquí se realizan las operaciones de finalización del proceso.
    // Esto puede incluir la limpieza de recursos, desactivación de dispositivos o almacenamiento de resultados.
}

// Función que maneja el estado de ERROR
void manejarEstadoError() {
    printf("Error: Estado desconocido o falla en la transición.\n");
    // Si se llega a un estado desconocido o una transición incorrecta, el sistema entra en un estado de error.
    // Esto puede ocurrir si el estado de transición no está definido correctamente.
    // Aquí se pueden realizar acciones de recuperación o resetear el sistema.
    exit(-1);  // Termina el programa en caso de error
}

// Función para cambiar de estado, mejorando la flexibilidad de la transición
// Este método recibe el puntero al estado actual y el nuevo estado al que se debe cambiar.
void cambiarEstado(Estado *estadoActual, Estado nuevoEstado) {
    // Comprobamos si el nuevo estado es válido. Si no lo es, cambiamos al estado de error.
    if (nuevoEstado < ESTADO_INICIAL || nuevoEstado > ESTADO_ERROR) {
        *estadoActual = ESTADO_ERROR;  // Si el nuevo estado es inválido, pasamos al estado de error
    } else {
        *estadoActual = nuevoEstado;  // Si el estado es válido, realizamos la transición
    }
}