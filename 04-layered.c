#include <stdio.h>
#include <string.h>
#include <ctype.h>  // Para la función toupper()

// Capa de Acceso a Datos
// Esta capa se encarga de interactuar con los datos. En este caso, simulamos obtener los datos desde una "base de datos".

typedef struct {
    int user_id;
    char user_name[50];
} User;

// Función para obtener los datos (simulación de una consulta a base de datos)
User get_user_data() {
    User user;
    user.user_id = 1;  // ID de usuario simulado
    strcpy(user.user_name, "Juan Perez");  // Nombre de usuario simulado
    return user;
}

// Capa de Lógica de Negocio
// Esta capa procesa los datos obtenidos desde la capa de acceso a datos.
typedef struct {
    User user_data;
} BusinessLogic;

// Función para procesar los datos (ejemplo de lógica de negocio)
void process_user_data(BusinessLogic *bl) {
    // Convertimos el nombre de usuario a mayúsculas (simulando procesamiento)
    for (int i = 0; bl->user_data.user_name[i]; i++) {
        bl->user_data.user_name[i] = toupper(bl->user_data.user_name[i]);
    }
}

// Capa de Presentación
// Esta capa es responsable de mostrar los datos procesados al usuario.
void display_user_data(BusinessLogic *bl) {
    // Mostramos los datos al usuario
    printf("User ID: %d\n", bl->user_data.user_id);
    printf("User Name: %s\n", bl->user_data.user_name);
}

// Función principal que orquesta el flujo de las capas
int main() {
    // Capa de Acceso a Datos
    User user = get_user_data();  // Obtener datos del "almacenamiento"

    // Capa de Lógica de Negocio
    BusinessLogic bl;
    bl.user_data = user;  // Enviamos los datos a la capa de negocio
    process_user_data(&bl);  // Procesamos los datos

    // Capa de Presentación
    display_user_data(&bl);  // Mostramos los datos procesados

    return 0;
}