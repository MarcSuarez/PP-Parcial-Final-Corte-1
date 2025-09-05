# Parcial 1. Paradigmas de programación

## Punto 1: Análisis Comparativo entre Programación Imperativa y Declarativa

### Código Imperativo vs Declarativo

**Imperativo:** 15 líneas con bucles anidados y lógica de intercambio
**Declarativo:** 1 línea con `sorted(estudiantes, key=lambda est: (-est[1], est[0]))`

### Análisis Comparativo

#### Claridad y legibilidad
- **Imperativo:** Requiere entender algoritmo Bubble Sort
- **Declarativo:** Intención clara en una línea
- **Ganador:** Declarativo

#### Expresividad y abstracción
- **Imperativo:** Especifica CÓMO ordenar (bajo nivel)
- **Declarativo:** Especifica QUÉ ordenar (alto nivel)
- **Ganador:** Declarativo

#### Mutabilidad
- **Imperativo:** Modifica lista original (mutable)
- **Declarativo:** Crea nueva lista (inmutable)
- **Ganador:** Empate, depende de lo que busques hay un ganador

#### Manejo de estado
- **Imperativo:** Variables de control explícitas (i, j, n)
- **Declarativo:** Sin estado explícito
- **Ganador:** Declarativo

#### Mantenimiento
- **Imperativo:** Difícil modificar, propenso a errores
- **Declarativo:** Fácil cambiar criterios de ordenamiento
- **Ganador:** Declarativo

#### Eficiencia
- **Imperativo:** O(n²) - Bubble Sort, O(1) espacio
- **Declarativo:** O(n log n) - Timsort, O(n) espacio
- **Ganador:** Declarativo (mejor tiempo)

### Conclusión
El enfoque **declarativo** es superior: más legible, mantenible y eficiente. El **imperativo** solo aventaja en control de memoria.

## Punto 2: Sistema de Gestión de Estudiantes en C

### Compilación
```bash
gcc -o estudiantes estudiantes.c
./estudiantes
```

### Funcionamiento

El programa implementa un sistema de gestión de estudiantes optimizado para el uso eficiente de memoria mediante:

#### Estructura optimizada con bitfields
- **ID**: 24 bits (hasta 16 millones)
- **Edad**: 7 bits (0-127 años)
- **Materias**: 8 bits (0-255 materias)

#### Memoria dinámica
- **Nombres y apellidos**: Se asigna exactamente la memoria necesaria usando `malloc`
- **Calificaciones**: Array dinámico que se ajusta al número real de materias
- **Lista de estudiantes**: Crece automáticamente con `realloc`

#### Funciones principales
- `crear_estudiante()`: Asigna memoria exacta para cada campo
- `agregar_estudiante()`: Redimensiona el sistema automáticamente
- `eliminar_estudiante()`: Libera memoria y compacta el array
- `compactar_memoria()`: Reduce la capacidad cuando hay mucho espacio sin usar
- `mostrar_estadisticas()`: Muestra el uso actual de memoria

#### Gestión de memoria
- Previene memory leaks liberando toda la memoria asignada
- Compacta automáticamente cuando la eficiencia baja del 50%
- Usa solo la memoria estrictamente necesaria para cada estudiante

El programa demuestra técnicas avanzadas de optimización de memoria en C, garantizando eficiencia sin desperdicios.

# Punto 3: Cálculo Lambda - Implementación del Promedio

## Código Haskell Original
```haskell
promedio xs = realToFrac (sum xs) / genericLength xs
main :: IO ()
main = do
    putStrLn "Ingrese una lista de números separados por espacios:"
    entrada <- getLine
    let numeros = map read (words entrada) :: [Double]
    if null numeros
        then putStrLn "La lista está vacía, no se puede calcular el promedio."
        else putStrLn $ "El promedio es: " ++ show (promedio numeros)
```

## Notación de Cálculo Lambda

```
promedio = λxs. realToFrac (sum xs) / genericLength xs

main = λ(). putStrLn "Ingrese una lista de números separados por espacios:" >>
           getLine >>= λentrada.
           (λnumeros. if null numeros 
                     then putStrLn "La lista está vacía, no se puede calcular el promedio."
                     else putStrLn ("El promedio es: " ++ show (promedio numeros))
           ) (map read (words entrada))
```

## Explicación de la Notación

La notación lambda convierte cada función en una expresión anónima:
- `promedio xs = ...` se convierte en `promedio = λxs. ...`
- El `do` de Haskell se traduce usando `>>=` para encadenar operaciones monádicas
- `let numeros = ...` se transforma en una aplicación directa `(λnumeros. ...) (expresión)`
- Cada variable capturada se convierte en un parámetro lambda explícito