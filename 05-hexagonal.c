#include <stdio.h>
#include <string.h>

// ------------------------------------------
// 1. Puerto (Interfaz de la Lógica de Negocio)
// ------------------------------------------

typedef struct {
    int user_id;
    char user_name[50];
} User;

// Definimos el "puerto" o interfaz del sistema. Este es el punto de entrada a la lógica de negocio.
typedef struct {
    void (*show_user_info)(User user);  // Función para mostrar los datos del usuario.
} BusinessLogicPort;

// ------------------------------------------
// 2. Adaptador de Presentación (Entrada)
// ------------------------------------------

// Este adaptador implementa el puerto de la capa de presentación (interfaz de usuario).
void show_user_info_console(User user) {
    printf("User ID: %d\n", user.user_id);
    printf("User Name: %s\n", user.user_name);
}

// Este es el adaptador para la capa de presentación que permite mostrar los datos de usuario.
BusinessLogicPort presentation_adapter() {
    BusinessLogicPort port;
    port.show_user_info = show_user_info_console;  // Asociamos la función de presentación a la interfaz.
    return port;
}

// ------------------------------------------
// 3. Adaptador de Datos (Salida)
// ------------------------------------------

// Este adaptador simula la obtención de los datos desde una base de datos o fuente externa.
User get_user_data_from_database() {
    User user;
    user.user_id = 1;  // ID simulado
    strcpy(user.user_name, "Juan Perez");  // Nombre simulado
    return user;
}

// ------------------------------------------
// 4. Lógica de Negocio (Aplicación)
// ------------------------------------------

// La capa de lógica de negocio utiliza los puertos para interactuar con los adaptadores.
void business_logic(BusinessLogicPort *port) {
    // Recuperar datos usando un adaptador de acceso a datos
    User user = get_user_data_from_database();

    // Llamar al puerto para mostrar la información del usuario
    port->show_user_info(user);
}

// ------------------------------------------
// 5. Función principal (Configuración del flujo de trabajo)
// ------------------------------------------

int main() {
    // Configuramos el adaptador de presentación (Interfaz de Usuario)
    BusinessLogicPort port = presentation_adapter();

    // Ejecutamos la lógica de negocio con el adaptador correspondiente
    business_logic(&port);

    return 0;
}
