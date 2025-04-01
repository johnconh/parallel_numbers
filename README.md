# parallel_numbers

## Descripción  
Este programa genera números aleatorios en paralelo utilizando hilos (*threads*). Los números generados se dividen en dos listas enlazadas: una para números pares y otra para impares. La concurrencia se maneja con `pthread` y `mutex` para evitar condiciones de carrera.  

## Características  
✅ Implementación de listas enlazadas protegidas con `mutex`  
✅ Generación de números aleatorios únicos por hilo  
✅ Soporte para múltiples hilos con configuración flexible  
✅ Gestión eficiente de memoria para evitar *memory leaks*  
✅ Manejo seguro de errores y validaciones 


### 📜 Archivos principales  

- **`main.c`** → Punto de entrada del programa.  
- **`args.c/h`** → Manejo de argumentos de línea de comandos.  
- **`config.c/h`** → Lectura y validación del archivo de configuración.  
- **`list.c/h`** → Implementación de listas enlazadas con protección de `mutex`.  
- **`thread.c/h`** → Creación y gestión de hilos para la generación de números

## ⚙️ Instalación y Uso  

### 📌 Requisitos  
- `gcc` (GCC) con soporte para `pthread`  
- Sistema basado en UNIX (Linux o macOS)  
 
## 🔄 Opciones del Makefile  
| Comando         | Descripción                          |
|----------------|--------------------------------------|
| `make`        | Compila el programa                 |
| `make clean`  | Elimina archivos objeto             |
| `make fclean` | Borra ejecutables y archivos objeto |
| `make re`     | Limpia y recompila el proyecto      |
  