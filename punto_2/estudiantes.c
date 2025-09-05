#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura optimizada con bitfields para ahorrar memoria
typedef struct {
    char *nombre;                // Memoria dinámica para nombre
    char *apellido;              // Memoria dinámica para apellido
    float *calificaciones;       // Array dinámico de calificaciones
    unsigned int id : 24;        // 24 bits para ID (hasta 16 millones)
    unsigned int edad : 7;       // 7 bits para edad (0-127 años)
    unsigned int num_materias : 8; // 8 bits para número de materias (0-255)
} Estudiante;

// Estructura para manejar array dinámico de estudiantes
typedef struct {
    Estudiante *estudiantes;
    int capacidad;
    int cantidad;
} SistemaEstudiantes;

// Inicializar sistema
SistemaEstudiantes* inicializar_sistema() {
    SistemaEstudiantes *sistema = malloc(sizeof(SistemaEstudiantes));
    sistema->estudiantes = NULL;
    sistema->capacidad = 0;
    sistema->cantidad = 0;
    return sistema;
}


// Agregar estudiante al sistema
void agregar_estudiante(SistemaEstudiantes *sistema, const char *nombre, const char *apellido, 
                       unsigned int edad, unsigned int id, float *calificaciones, unsigned int num_materias) {
    // Redimensionar array si es necesario
    if (sistema->cantidad >= sistema->capacidad) {
        sistema->capacidad = sistema->capacidad == 0 ? 2 : sistema->capacidad * 2;
        sistema->estudiantes = realloc(sistema->estudiantes, 
                                     sistema->capacidad * sizeof(Estudiante));
    }
    
    // Asignar memoria exacta para nombre
    sistema->estudiantes[sistema->cantidad].nombre = malloc((strlen(nombre) + 1) * sizeof(char));
    strcpy(sistema->estudiantes[sistema->cantidad].nombre, nombre);
    
    // Asignar memoria exacta para apellido
    sistema->estudiantes[sistema->cantidad].apellido = malloc((strlen(apellido) + 1) * sizeof(char));
    strcpy(sistema->estudiantes[sistema->cantidad].apellido, apellido);
    
    // Asignar memoria exacta para calificaciones
    sistema->estudiantes[sistema->cantidad].calificaciones = malloc(num_materias * sizeof(float));
    memcpy(sistema->estudiantes[sistema->cantidad].calificaciones, calificaciones, num_materias * sizeof(float));
    
    // Asignar campos con bitfields
    sistema->estudiantes[sistema->cantidad].edad = edad;
    sistema->estudiantes[sistema->cantidad].id = id;
    sistema->estudiantes[sistema->cantidad].num_materias = num_materias;
    
    sistema->cantidad++;
}

// Eliminar estudiante por ID
int eliminar_estudiante(SistemaEstudiantes *sistema, unsigned int id) {
    for (int i = 0; i < sistema->cantidad; i++) {
        if (sistema->estudiantes[i].id == id) {
            // Liberar memoria del estudiante
            free(sistema->estudiantes[i].nombre);
            free(sistema->estudiantes[i].apellido);
            free(sistema->estudiantes[i].calificaciones);
            
            // Mover elementos hacia la izquierda
            for (int j = i; j < sistema->cantidad - 1; j++) {
                sistema->estudiantes[j] = sistema->estudiantes[j + 1];
            }
            
            sistema->cantidad--;
            return 1; // Éxito
        }
    }
    return 0; // No encontrado
}

// Mostrar información de un estudiante
void mostrar_estudiante(const Estudiante *est) {
    printf("ID: %u, Nombre: %s %s, Edad: %u\n", 
           est->id, est->nombre, est->apellido, est->edad);
    printf("Calificaciones (%u materias): ", est->num_materias);
    for (int i = 0; i < est->num_materias; i++) {
        printf("%.2f ", est->calificaciones[i]);
    }
    printf("\n\n");
}

// Liberar todo el sistema
void liberar_sistema(SistemaEstudiantes *sistema) {
    for (int i = 0; i < sistema->cantidad; i++) {
        free(sistema->estudiantes[i].nombre);
        free(sistema->estudiantes[i].apellido);
        free(sistema->estudiantes[i].calificaciones);
    }
    free(sistema->estudiantes);
    free(sistema);
}

// Función principal de demostración
int main() {
    SistemaEstudiantes *sistema = inicializar_sistema();
    
    // Datos de prueba
    float califs1[] = {4.5, 4.8, 4.2, 4.9};
    float califs2[] = {3.8, 4.0, 3.5};
    
    // Agregar estudiantes directamente al sistema
    printf("Agregando estudiantes...\n");
    agregar_estudiante(sistema, "Juan", "Pérez", 20, 12345, califs1, 4);
    agregar_estudiante(sistema, "María", "García", 19, 12346, califs2, 3);
    
    // Mostrar estudiantes registrados
    printf("=== ESTUDIANTES REGISTRADOS ===\n");
    for (int i = 0; i < sistema->cantidad; i++) {
        mostrar_estudiante(&sistema->estudiantes[i]);
    }
    
    // Eliminar un estudiante
    printf("Eliminando estudiante con ID 12346...\n");
    if (eliminar_estudiante(sistema, 12346)) {
        printf("Estudiante eliminado correctamente.\n");
    } else {
        printf("Estudiante no encontrado.\n");
    }
    
    // Mostrar estudiantes restantes
    printf("\n=== ESTUDIANTES RESTANTES ===\n");
    for (int i = 0; i < sistema->cantidad; i++) {
        mostrar_estudiante(&sistema->estudiantes[i]);
    }
    
    // Liberar todo el sistema
    liberar_sistema(sistema);
    printf("Sistema liberado correctamente.\n");
    
    return 0;
}