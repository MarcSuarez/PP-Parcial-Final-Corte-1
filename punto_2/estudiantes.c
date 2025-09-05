#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura optimizada con bitfields
typedef struct {
    char *nombre;
    char *apellido;
    float *calificaciones;
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

// Crear estudiante con memoria optimizada
Estudiante* crear_estudiante(const char *nombre, const char *apellido, 
                           unsigned int edad, unsigned int id, 
                           float *calificaciones, unsigned int num_materias) {
    Estudiante *est = malloc(sizeof(Estudiante));
    
    // Asignar memoria exacta para nombre
    est->nombre = malloc((strlen(nombre) + 1) * sizeof(char));
    strcpy(est->nombre, nombre);
    
    // Asignar memoria exacta para apellido
    est->apellido = malloc((strlen(apellido) + 1) * sizeof(char));
    strcpy(est->apellido, apellido);
    
    // Asignar memoria exacta para calificaciones
    est->calificaciones = malloc(num_materias * sizeof(float));
    memcpy(est->calificaciones, calificaciones, num_materias * sizeof(float));
    
    // Usar bitfields optimizados
    est->edad = edad;
    est->id = id;
    est->num_materias = num_materias;
    
    return est;
}

// Liberar memoria de un estudiante
void liberar_estudiante(Estudiante *est) {
    if (est != NULL) {
        free(est->nombre);
        free(est->apellido);
        free(est->calificaciones);
        free(est);
    }
}

// Agregar estudiante al sistema
void agregar_estudiante(SistemaEstudiantes *sistema, Estudiante *estudiante) {
    // Redimensionar array si es necesario
    if (sistema->cantidad >= sistema->capacidad) {
        sistema->capacidad = sistema->capacidad == 0 ? 2 : sistema->capacidad * 2;
        sistema->estudiantes = realloc(sistema->estudiantes, 
                                     sistema->capacidad * sizeof(Estudiante));
    }
    
    // Copiar datos del estudiante
    sistema->estudiantes[sistema->cantidad] = *estudiante;
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

// Compactar memoria del sistema
void compactar_memoria(SistemaEstudiantes *sistema) {
    if (sistema->cantidad < sistema->capacidad / 2 && sistema->capacidad > 2) {
        sistema->capacidad = sistema->cantidad == 0 ? 2 : sistema->cantidad;
        sistema->estudiantes = realloc(sistema->estudiantes, 
                                     sistema->capacidad * sizeof(Estudiante));
        printf("Memoria compactada. Nueva capacidad: %d\n", sistema->capacidad);
    }
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

// Mostrar estadísticas del sistema
void mostrar_estadisticas(const SistemaEstudiantes *sistema) {
    printf("\n=== ESTADÍSTICAS DEL SISTEMA ===\n");
    printf("Estudiantes registrados: %d\n", sistema->cantidad);
    printf("Capacidad del sistema: %d\n", sistema->capacidad);
    printf("Memoria usada por estudiantes: %zu bytes\n", 
           sistema->cantidad * sizeof(Estudiante));
    printf("Memoria total asignada: %zu bytes\n", 
           sistema->capacidad * sizeof(Estudiante));
    
    // Calcular memoria dinámica aproximada
    size_t memoria_dinamica = 0;
    for (int i = 0; i < sistema->cantidad; i++) {
        memoria_dinamica += strlen(sistema->estudiantes[i].nombre) + 1;
        memoria_dinamica += strlen(sistema->estudiantes[i].apellido) + 1;
        memoria_dinamica += sistema->estudiantes[i].num_materias * sizeof(float);
    }
    printf("Memoria dinámica (strings + calificaciones): %zu bytes\n", memoria_dinamica);
    printf("Eficiencia de memoria: %.2f%%\n", 
           sistema->cantidad > 0 ? (double)sistema->cantidad / sistema->capacidad * 100 : 0);
    printf("================================\n\n");
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
    float califs3[] = {4.9, 4.7, 4.8, 4.6, 4.3};
    
    // Crear estudiantes
    Estudiante *est1 = crear_estudiante("Juan", "Pérez", 20, 12345, califs1, 4);
    Estudiante *est2 = crear_estudiante("María", "García", 19, 12346, califs2, 3);
    Estudiante *est3 = crear_estudiante("Carlos", "López", 21, 12347, califs3, 5);
    
    // Agregar al sistema
    agregar_estudiante(sistema, est1);
    agregar_estudiante(sistema, est2);
    agregar_estudiante(sistema, est3);
    
    // Liberar estudiantes temporales (ya están copiados en el sistema)
    free(est1);
    free(est2);
    free(est3);
    
    printf("=== ESTUDIANTES REGISTRADOS ===\n");
    for (int i = 0; i < sistema->cantidad; i++) {
        mostrar_estudiante(&sistema->estudiantes[i]);
    }
    
    mostrar_estadisticas(sistema);
    
    // Eliminar un estudiante
    printf("Eliminando estudiante con ID 12346...\n");
    eliminar_estudiante(sistema, 12346);
    
    mostrar_estadisticas(sistema);
    
    // Compactar memoria
    printf("Compactando memoria...\n");
    compactar_memoria(sistema);
    
    mostrar_estadisticas(sistema);
    
    // Liberar todo el sistema
    liberar_sistema(sistema);
    
    printf("Sistema liberado correctamente.\n");
    
    return 0;
}