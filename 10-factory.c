#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de la interfaz común para los sensores
typedef struct Sensor {
    // Puntero a función que permite leer datos del sensor
    double (*readData)(struct Sensor* self); 
} Sensor;

// Implementación del sensor de temperatura
double readTemperature(Sensor* self) {
    // Simulación de lectura de temperatura (valor fijo)
    return 25.0; 
}

// Función para crear un sensor de temperatura
Sensor* createTemperatureSensor() {
    // Asignar memoria para un nuevo sensor
    Sensor* sensor = (Sensor*)malloc(sizeof(Sensor)); 
    // Asignar la función de lectura de temperatura al puntero
    sensor->readData = readTemperature;              
    return sensor; // Devolver el nuevo sensor creado
}

// Implementación del sensor de humedad
double readHumidity(Sensor* self) {
    // Simulación de lectura de humedad (valor fijo)
    return 60.0; 
}

// Función para crear un sensor de humedad
Sensor* createHumiditySensor() {
    // Asignar memoria para un nuevo sensor
    Sensor* sensor = (Sensor*)malloc(sizeof(Sensor)); 
    // Asignar la función de lectura de humedad al puntero
    sensor->readData = readHumidity;                 
    return sensor; // Devolver el nuevo sensor creado
}

// Clase Factory para crear sensores según el tipo solicitado
Sensor* createSensor(const char* type) {
    // Comparar el tipo solicitado y crear el sensor correspondiente
    if (strcmp(type, "temperature") == 0) {
        return createTemperatureSensor(); // Crear y devolver un sensor de temperatura
    } else if (strcmp(type, "humidity") == 0) {
        return createHumiditySensor(); // Crear y devolver un sensor de humedad
    }
    return NULL; // Devolver NULL si el tipo no es reconocido
}

// Programa principal para demostrar el uso del patrón Factory
int main() {
    printf("Sistema de Sensores Inteligentes\n");
    
    // Crear un sensor de temperatura usando la fábrica
    Sensor* tempSensor = createSensor("temperature");
    
    // Crear un sensor de humedad usando la fábrica
    Sensor* humiditySensor = createSensor("humidity");

    // Leer datos del sensor de temperatura, si fue creado correctamente
    if (tempSensor != NULL) {
        printf("Lectura del Sensor de Temperatura: %.2f °C\n", tempSensor->readData(tempSensor));
        free(tempSensor); // Liberar memoria después de usar el sensor
    } else {
        printf("Error al crear el Sensor de Temperatura.\n");
    }

    // Leer datos del sensor de humedad, si fue creado correctamente
    if (humiditySensor != NULL) {
        printf("Lectura del Sensor de Humedad: %.2f %%\n", humiditySensor->readData(humiditySensor));
        free(humiditySensor); // Liberar memoria después de usar el sensor
    } else {
        printf("Error al crear el Sensor de Humedad.\n");
    }

    return 0; // Finalizar el programa exitosamente
}