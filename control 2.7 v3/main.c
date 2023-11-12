#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_JUGADAS 100 // Número máximo de jugadas que se pueden almacenar
#define NOMBRE_ARCHIVO "historial.txt" // Nombre del archivo para almacenar el historial

enum TipoJugada {
    NUMERO,
    PALE,
    TRIPLETA
};

struct Jugada {
    enum TipoJugada tipo;
    int numeros[3];
    int monto; // Cantidad de dinero apostada
    int cantidadAciertos; // Cantidad de números acertados
    time_t hora;
};

struct Jugada historialJugadas[MAX_JUGADAS]; // Arreglo para almacenar las jugadas
int numeroJugadas = 0; // Variable para rastrear la cantidad actual de jugadas realizadas

// Función para guardar el historial en el archivo
void guardarHistorial() {
    FILE *archivo = fopen(NOMBRE_ARCHIVO, "w");

    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numeroJugadas; ++i) {
        fprintf(archivo, "%d %d %d %d %d %ld\n", historialJugadas[i].tipo, historialJugadas[i].numeros[0], historialJugadas[i].numeros[1], historialJugadas[i].numeros[2], historialJugadas[i].monto, historialJugadas[i].hora);
    }

    fclose(archivo);
}

// Función para cargar el historial desde el archivo
void cargarHistorial() {
    FILE *archivo = fopen(NOMBRE_ARCHIVO, "r");

    if (archivo == NULL) {
        // No hay historial previo
        return;
    }

    while (fscanf(archivo, "%d %d %d %d %d %ld", &historialJugadas[numeroJugadas].tipo, &historialJugadas[numeroJugadas].numeros[0], &historialJugadas[numeroJugadas].numeros[1], &historialJugadas[numeroJugadas].numeros[2], &historialJugadas[numeroJugadas].monto, &historialJugadas[numeroJugadas].hora) == 6) {
        numeroJugadas++;
        if (numeroJugadas >= MAX_JUGADAS) {
            break;
        }
    }

    fclose(archivo);
}

// Función para generar automáticamente números, pales y tripleta
void generarAutomatico() {
    historialJugadas[numeroJugadas].tipo = rand() % 3; // Tipo de jugada aleatorio

    for (int i = 0; i < 3; ++i) {
        historialJugadas[numeroJugadas].numeros[i] = rand() % 10; // Números aleatorios
    }

    // Obtener la hora actual y almacenarla en la jugada
    time(&historialJugadas[numeroJugadas].hora);

    // Incrementar el número de jugadas realizadas
    numeroJugadas++;

    // Guardar el historial en el archivo después de cada jugada
    guardarHistorial();
}

// Función para verificar si se ganó la lotería
int verificarGanador(int numerosGanadores[3]) {
    // Verificar si se ganó la lotería (criterio: al menos un número coincide)
    int coincidencias = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (historialJugadas[numeroJugadas - 1].numeros[i] == numerosGanadores[j]) {
                coincidencias++;
                break;
            }
        }
    }

    return coincidencias;
}

// Función para imprimir el resultado del sorteo
void imprimirResultado(int numerosGanadores[3]) {
    printf("¡Has seleccionado imprimir!\n");

    // Obtener la hora y fecha actual
    struct tm *infoTiempo;
    time_t tiempoActual;
    time(&tiempoActual);
    infoTiempo = localtime(&tiempoActual);

    // Imprimir la hora y fecha de la jugada
    printf("Hora del sorteo: %02d:%02d:%02d, Fecha: %02d/%02d/%04d\n",
           infoTiempo->tm_hour, infoTiempo->tm_min, infoTiempo->tm_sec,
           infoTiempo->tm_mday, infoTiempo->tm_mon + 1, infoTiempo->tm_year + 1900);

    // Mostrar el tipo de jugada y los números generados
    switch (historialJugadas[numeroJugadas - 1].tipo) {
        case NUMERO:
            printf("Tipo de jugada: Número\n");
            break;
        case PALE:
            printf("Tipo de jugada: Pale\n");
            break;
        case TRIPLETA:
            printf("Tipo de jugada: Tripleta\n");
            break;
        default:
            break;
    }

    printf("Números seleccionados: %d %d %d\n", historialJugadas[numeroJugadas - 1].numeros[0], historialJugadas[numeroJugadas - 1].numeros[1], historialJugadas[numeroJugadas - 1].numeros[2]);

    // Mostrar los números ganadores
    printf("Números ganadores: %d %d %d\n", numerosGanadores[0], numerosGanadores[1], numerosGanadores[2]);

    // Verificar si se ganó la lotería
    int coincidencias = verificarGanador(numerosGanadores);

    if (coincidencias > 0) {
        int montoGanado = historialJugadas[numeroJugadas - 1].monto * coincidencias;
        printf("¡Felicidades! Has ganado la lotería. Cantidad ganada: $%d\n", montoGanado);

        // Sumar la cantidad ganada al monto total
        historialJugadas[numeroJugadas - 1].monto += montoGanado;
        printf("Nuevo monto total: $%d\n", historialJugadas[numeroJugadas - 1].monto);
    } else {
        printf("Lo siento, no has ganado esta vez. ¡Mejor suerte la próxima vez!\n");
    }
}

// Función principal del juego
void jugar() {
    printf("¡Has seleccionado jugar manualmente!\n");

    if (numeroJugadas >= MAX_JUGADAS) {
        printf("Se ha alcanzado el límite máximo de jugadas. No se pueden almacenar más.\n");
        return;
    }

    int opcionTipoJugada;
    printf("¿Qué tipo de jugada deseas realizar?\n");
    printf("1. Número\n");
    printf("2. Pale\n");
    printf("3. Tripleta\n");
    printf("Seleccione una opción: ");
    scanf("%d", &opcionTipoJugada);

    if (opcionTipoJugada < 1 || opcionTipoJugada > 3) {
        printf("Opción no válida. Volviendo al menú principal.\n");
        return;
    }

    historialJugadas[numeroJugadas].tipo = opcionTipoJugada - 1; // Ajustamos para que coincida con el enum

    // Permitir al usuario ingresar números según el tipo de jugada
    if (historialJugadas[numeroJugadas].tipo == PALE) {
        // Para Pale, permitir al usuario ingresar tres números
        for (int i = 0; i < 3; ++i) {
            printf("Ingrese el número %d: ", i + 1);
            scanf("%d", &historialJugadas[numeroJugadas].numeros[i]);
        }
    } else {
        // Para Número y Tripleta, permitir al usuario ingresar tres números
        for (int i = 0; i < 3; ++i) {
            printf("Ingrese el número %d: ", i + 1);
            scanf("%d", &historialJugadas[numeroJugadas].numeros[i]);
        }
    }

    // Solicitar la cantidad de dinero para apostar
    printf("Ingrese la cantidad de dinero para apostar: ");
    scanf("%d", &historialJugadas[numeroJugadas].monto);

    // Obtener la hora actual y almacenarla en la jugada
    time(&historialJugadas[numeroJugadas].hora);

    // Incrementar el número de jugadas realizadas
    numeroJugadas++;

    // Guardar el historial en el archivo después de cada jugada
    guardarHistorial();
}

// Función principal del programa
int main() {
    // Cargar el historial al inicio del programa
    cargarHistorial();

    int opcion;

    do {
        printf("----- Menu Loteria -----\n");
        printf("1. Jugar automático\n");
        printf("2. Jugar manualmente\n");
        printf("3. Imprimir resultado\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                generarAutomatico();
                break;
            case 2:
                jugar();
                break;
            case 3: {
                // Generar números ganadores aleatorios
                int numerosGanadores[3];
                srand(time(NULL));
                for (int i = 0; i < 3; ++i) {
                    numerosGanadores[i] = rand() % 10;
                }
                imprimirResultado(numerosGanadores);
                break;
            }
            case 0:
                printf("Saliendo del programa. ¡Hasta luego!\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }

    } while (opcion != 0);

    // Guardar el historial al salir del programa
    guardarHistorial();

    return 0;
}
