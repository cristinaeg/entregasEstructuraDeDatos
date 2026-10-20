# entregasEstructuraDeDatos

## Diagrama

<img width="1233" height="726" alt="DiagramaParqueadero drawio" src="https://github.com/user-attachments/assets/f0fbd2eb-a38d-4634-af17-fe4cd8b9988f" />

## Parqueadero: cliente, servidor e interfaz

Simulación de un parqueadero de 100 celdas. Un cliente en C++ envía vehículos a un servidor en C++ por TCP. El servidor se expone a Python con SWIG y una interfaz en Tkinter muestra el estado de las celdas.

## Funcionamiento

1. El cliente (`client_while.cpp`) se conecta al servidor en el puerto 8080 y envía 3 mensajes, uno cada 5 segundos. Cada mensaje tiene una placa aleatoria, la hora actual y un espacio aleatorio entre 1 y 100:
   ```
   Placa: ABC-123 | Hora: 14:35 | Espacio: 27
   ```
2. El servidor (`server.cpp`) acepta la conexión, imprime cada mensaje recibido y responde al cliente. Cuando el cliente se desconecta, cierra los sockets.
3. `servidor.i` genera con SWIG el módulo de Python `servidor`, que expone la función `iniciar_servidor()`.
4. La interfaz (`interfaz.py`) ejecuta el servidor en un hilo y lo reinicia cuando el cliente se desconecta. Redirige la salida del servidor a un pipe, lee cada línea, extrae placa, hora y espacio con una expresión regular y actualiza la cuadrícula de 10 x 10.

Reglas de la interfaz:

- Si la placa no está registrada, el vehículo entra. Ocupa el espacio indicado o, si está ocupado, la primera celda libre. La celda se marca en rojo.
- Si la placa ya está registrada, el vehículo sale y la celda vuelve a verde.
- Si no hay celdas libres, se registra LLENO.
- Se muestran el conteo de celdas libres y ocupadas y el historial de entradas y salidas.

## Archivos

| Archivo | Descripción |
|---|---|
| `client_while.cpp` | Cliente TCP en C++ (Winsock) |
| `server.cpp` | Servidor TCP en C++ (Winsock) |
| `Servidor.h` | Declaración de `iniciar_servidor()` |
| `servidor.i` | Interfaz SWIG que genera el módulo `servidor` |
| `interfaz.py` | Interfaz gráfica en Python (Tkinter) |

## Estructuras de datos

- `placas` (diccionario): relaciona cada placa con su celda. Permite saber si un vehículo entra o sale.
- `celdas` (diccionario): relaciona cada número de celda con su elemento en pantalla.
- `lineas` (lista usada como cola): guarda las líneas leídas del pipe y se procesan en orden de llegada.
- `buffer` (arreglo `char[1024]`): almacena cada mensaje recibido por el socket.

## Requisitos

- Windows (cliente y servidor usan Winsock)
- g++ (MinGW-w64)
- SWIG
- Python 3 con Tkinter

## Compilación y ejecución

```bash
git clone https://github.com/cristinaeg/entregasEstructuraDeDatos.git
cd entregasEstructuraDeDatos

# Módulo de Python del servidor (ajustar ruta y versión de Python)
swig -c++ -python servidor.i
g++ -shared -o _servidor.pyd server.cpp servidor_wrap.cxx -I"C:\Python3X\include" -L"C:\Python3X\libs" -lpython3X -lws2_32

# Cliente
g++ client_while.cpp -o client_while.exe -lws2_32

# Ejecutar: primero la interfaz (inicia el servidor), luego el cliente en otra consola
python interfaz.py
client_while.exe
```

El cliente se conecta a la IP `10.2.10.200`. Para probar en un solo equipo, cambiarla por `127.0.0.1` en `client_while.cpp`.
