#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estructura para almacenar la información de cada juego
typedef struct {
    int numbers[3];
    int won;
    time_t timestamp;
} LotteryGame;

// Función para tirar 3 números aleatorios
void throwDice(int manual, int numbers[3]) {
    if (manual) {
        printf("Ingresa tus 3 números (separados por espacio): ");
        scanf("%d %d %d", &numbers[0], &numbers[1], &numbers[2]);
    } else {
        for (int i = 0; i < 3; ++i) {
            numbers[i] = rand() % 10 + 1;  // Números aleatorios del 1 al 10
        }
    }
}

// Función para verificar si el jugador ganó
int checkWin(int selectedNumbers[3], int drawnNumbers[3]) {
    for (int i = 0; i < 3; ++i) {
        if (selectedNumbers[i] == drawnNumbers[i]) {
            return 1;  // Ganó al menos uno
        }
    }
    return 0;  // No ganó
}

// Función principal
int main() {
    srand(time(NULL));  // Inicializar la semilla para números aleatorios

    int option;
    int historyCount = 0;
    LotteryGame history[100];  // Se puede ajustar según sea necesario

    do {
        printf("\n=== Menú Principal ===\n");
        printf("1. Tirar 3 números\n");
        printf("2. Imprimir resultados\n");
        printf("3. Salir\n");
        printf("Selecciona una opción: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("\n=== Tirar 3 números ===\n");
                printf("1. Tirar aleatoriamente\n");
                printf("2. Ingresar números manualmente\n");
                printf("Selecciona una opción: ");
                int throwOption;
                scanf("%d", &throwOption);

                if (throwOption == 1 || throwOption == 2) {
                    history[historyCount].timestamp = time(NULL);
                    throwDice(throwOption == 2, history[historyCount].numbers);

                    // Verificar si ganó
                    int drawnNumbers[3];
                    throwDice(1, drawnNumbers);
                    history[historyCount].won = checkWin(history[historyCount].numbers, drawnNumbers);

                    // Imprimir resultado
                    printf("\n=== Resultado ===\n");
                    printf("Fecha y hora: %s", ctime(&history[historyCount].timestamp));
                    printf("Tus números: %d %d %d\n", history[historyCount].numbers[0], history[historyCount].numbers[1], history[historyCount].numbers[2]);
                    printf("Números sorteados: %d %d %d\n", drawnNumbers[0], drawnNumbers[1], drawnNumbers[2]);

                    if (history[historyCount].won) {
                        printf("¡Felicidades! Ganaste al menos con un número.\n");
                    } else {
                        printf("Lo siento, no ganaste. ¡Inténtalo de nuevo!\n");
                    }

                    historyCount++;
                } else {
                    printf("Opción no válida.\n");
                }
                break;

            case 2:
                printf("\n=== Imprimir resultados ===\n");
                for (int i = 0; i < historyCount; ++i) {
                    printf("\n=== Juego %d ===\n", i + 1);
                    printf("Fecha y hora: %s", ctime(&history[i].timestamp));
                    printf("Tus números: %d %d %d\n", history[i].numbers[0], history[i].numbers[1], history[i].numbers[2]);

                    if (history[i].won) {
                        printf("¡Felicidades! Ganaste al menos con un número.\n");
                    } else {
                        printf("Lo siento, no ganaste. ¡Inténtalo de nuevo!\n");
                    }
                }
                break;

            case 3:
                printf("Saliendo del programa. Gracias por jugar.\n");
                break;

            default:
                printf("Opción no válida. Inténtalo de nuevo.\n");
                break;
        }

    } while (option != 3);

    return 0;
}
