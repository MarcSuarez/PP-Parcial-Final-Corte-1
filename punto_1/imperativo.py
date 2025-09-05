def ordenar_estudiantes(estudiantes):
    n = len(estudiantes)
    
    for i in range(n):
        for j in range(0, n - i - 1):
            # Si la calificación actual es menor que la siguiente
            if estudiantes[j][1] < estudiantes[j + 1][1]:
                estudiantes[j], estudiantes[j + 1] = estudiantes[j + 1], estudiantes[j]
            
            # Si tienen la misma calificación, ordenar alfabéticamente
            elif estudiantes[j][1] == estudiantes[j + 1][1]:
                if estudiantes[j][0] > estudiantes[j + 1][0]:
                    estudiantes[j], estudiantes[j + 1] = estudiantes[j + 1], estudiantes[j]
    
    return estudiantes

estudiantes = [
    ["Ana García", 85.5],
    ["Carlos López", 92.0],
    ["María Rodríguez", 88.5],
    ["Juan Pérez", 92.0],
    ["Sofia Martín", 76.5],
    ["Diego Torres", 88.5],
    ["Elena Vargas", 95.0],
    ["Pablo Ruiz", 82.0],
    ["Carmen Silva", 90.5],
    ["Fernando Castro", 85.5]
]

print("Lista original:")
for estudiante in estudiantes:
    print(f"{estudiante[0]} - {estudiante[1]}")

print("\nLista ordenada:")
estudiantes_ordenados = ordenar_estudiantes(estudiantes)
for estudiante in estudiantes_ordenados:
    print(f"{estudiante[0]} - {estudiante[1]}")