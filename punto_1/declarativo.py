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
print('\n'.join(f"{est[0]} - {est[1]}" for est in estudiantes))

estudiantes_ordenados = sorted(estudiantes, key=lambda est: (-est[1], est[0]))

print("\nLista ordenada:")
print('\n'.join(f"{est[0]} - {est[1]}" for est in estudiantes_ordenados))