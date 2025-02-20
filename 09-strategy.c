#include <stdio.h>

// Definición de la interfaz de estrategia
// Esta estructura contiene un puntero a una función que representa la estrategia.
typedef struct Strategy {
    void (*execute)(void);  // Puntero a la función que ejecuta la estrategia
} Strategy;

// Implementación de la Estrategia Concreta A
// Esta función representa un comportamiento específico de la estrategia A.
void strategyA() {
    printf("Estrategia A ejecutada\n");
}

// Implementación de la Estrategia Concreta B
// Esta función representa un comportamiento específico de la estrategia B.
void strategyB() {
    printf("Estrategia B ejecutada\n");
}

// Definición del Contexto que utiliza la estrategia
// Esta estructura contiene un puntero a una estrategia, permitiendo cambiarla en tiempo de ejecución.
typedef struct Context {
    Strategy* strategy;  // Puntero a una estrategia actual
} Context;

// Función para establecer la estrategia en el contexto
// Permite cambiar la estrategia activa del contexto.
void setStrategy(Context* context, Strategy* strategy) {
    context->strategy = strategy;  // Asigna la nueva estrategia al contexto
}

// Función para ejecutar la estrategia actual en el contexto
// Verifica si hay una estrategia establecida y la ejecuta.
void executeStrategy(Context* context) {
    if (context->strategy && context->strategy->execute) {
        context->strategy->execute();  // Llama a la función de ejecución de la estrategia
    } else {
        printf("No hay estrategia establecida\n");  // Mensaje si no hay estrategia
    }
}

// Función principal del programa
int main() {
    // Crear instancias de las estrategias concretas
    Strategy strategy1 = { strategyA };  // Estrategia A
    Strategy strategy2 = { strategyB };  // Estrategia B

    // Crear el contexto que utilizará las estrategias
    Context context;

    // Establecer y ejecutar la Estrategia A
    setStrategy(&context, &strategy1);  // Cambia a Estrategia A en el contexto
    executeStrategy(&context);           // Ejecuta Estrategia A

    // Establecer y ejecutar la Estrategia B
    setStrategy(&context, &strategy2);  // Cambia a Estrategia B en el contexto
    executeStrategy(&context);           // Ejecuta Estrategia B

    return 0;  // Fin del programa
}
