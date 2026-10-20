#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h> // Para la función Sleep()
#include <ctime>     // Para obtener la hora actual
#include <cstdlib>   // Para rand() y srand()

#pragma comment(lib, "ws2_32.lib")  // Enlaza la librería Winsock

#define PORT 8080

int main() {
    WSADATA wsaData;
    SOCKET sock = INVALID_SOCKET;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    const char* mensaje = "nuevo mensaje desde el cliente";

    // Inicializar Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Fallo al inicializar Winsock. Código de error: " << WSAGetLastError() << std::endl;
        return 1;
    }

    // Crear socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Fallo en socket. Código de error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convertir dirección IP
    serv_addr.sin_addr.s_addr = inet_addr("10.2.10.200");
	if (serv_addr.sin_addr.s_addr == INADDR_NONE) {
	    std::cerr << "Dirección inválida o no soportada" << std::endl;
	    closesocket(sock);
	    WSACleanup();
	    return 1;
	}

    // Conectar al servidor
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        std::cerr << "Fallo en connect. Código de error: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }
	
	
	//char buffer[1024];
	std::string input;
	
	// Inicializar la semilla aleatoria usando la hora actual
    srand(time(0)); 

    int total_mensajes = 3; // "x" cantidad de veces que se enviará el mensaje

    std::cout << "Iniciando simulacion de parqueadero...\n\n";

    for (int i = 0; i < total_mensajes; i++) {
        
        // 1. Generar Placa aleatoria (Ejemplo: ABC-123)
        char plate[8];
        snprintf(plate, sizeof(plate), "%c%c%c-%03d", 
                 'A' + rand() % 26, 'A' + rand() % 26, 'A' + rand() % 26, 
                 rand() % 1000);

        // 2. Obtener hora actual en formato HH:MM
        time_t now = time(0);
        tm *ltm = localtime(&now);
        char timeStr[10];
        snprintf(timeStr, sizeof(timeStr), "%02d:%02d", ltm->tm_hour, ltm->tm_min);

        // 3. Generar ID de espacio aleatorio (Del 1 al 100)
        int spot = rand() % 100 + 1;

        // 4. Formatear el mensaje final
        char mensaje[256];
        snprintf(mensaje, sizeof(mensaje), "Placa: %s | Hora: %s | Espacio: %d", plate, timeStr, spot);

        std::cout << "[Mensaje " << (i + 1) << "/" << total_mensajes << "] Enviando...\n";
        std::cout << "Datos: " << mensaje << "\n";

        // 5. Enviar al servidor
        int sendResult = send(sock, mensaje, strlen(mensaje), 0);
        if (sendResult == SOCKET_ERROR) {
            std::cout << "Error al enviar. Codigo: " << WSAGetLastError() << "\n";
            break;
        }

        // 6. Recibir respuesta del servidor
        char buffer[1024];
        int valread = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (valread > 0) {
            buffer[valread] = '\0';
            std::cout << "Servidor: " << buffer << "\n\n";
        } else {
            std::cout << "Conexion cerrada por el servidor o error en la red.\n";
            break;
        }

        // 7. Esperar 5 segundos antes del siguiente envio (excepto en el ultimo ciclo)
        if (i < total_mensajes - 1) {
            Sleep(5000); // Sleep() toma milisegundos (5000 ms = 5 segundos)
        }
    }

    std::cout << "Simulacion terminada. Cerrando conexion...\n";

    // Cerrar el socket al terminar
    closesocket(sock);
    WSACleanup();
    return 0;
}