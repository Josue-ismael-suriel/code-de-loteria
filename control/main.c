#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estructura para almacenar la informaci�n de cada juego
typedef struct {
    int numbers[3];
    int won;
    time_t timestamp;
} LotteryGame;

// Funci�n para tirar 3 n�meros aleatorios
void throwDice(int manual, int numbers[3]) {
    if (manual) {
        printf("Ingresa tus 3 n�meros (separados por espacio): ");
        scanf("%d %d %d", &numbers[0], &numbers[1], &numbers[2]);
    } else {
        for (int i = 0; i < 3; ++i) {
            numbers[i] = rand() % 10 + 1;  // N�meros aleatorios del 1 al 10
        }
    }
}

// Funci�n para verificar si el jugador gan�
int checkWin(int selectedNumbers[3], int drawnNumbers[3]) {
    for (int i = 0; i < 3; ++i) {
        if (selectedNumbers[i] == drawnNumbers[i]) {
            return 1;  // Gan� al menos uno
        }
    }
    return 0;  // No gan�
}

// Funci�n principal
int main() {
    srand(time(NULL));  // Inicializar la semilla para n�meros aleatorios

    int option;
    int historyCount = 0;
    LotteryGame history[100];  // Se puede ajustar seg�n sea necesario

    do {
        printf("\n=== Men� Principal ===\n");
        printf("1. Tirar 3 n�meros\n");
        printf("2. Imprimir resultados\n");
        printf("3. Salir\n");
        printf("Selecciona una opci�n: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("\n=== Tirar 3 n�meros ===\n");
                printf("1. Tirar aleatoriamente\n");
                printf("2. Ingresar n�meros manualmente\n");
                printf("Selecciona una opci�n: ");
                int throwOption;
                scanf("%d", &throwOption);

                if (throwOption == 1 || throwOption == 2) {
                    history[historyCount].timestamp = time(NULL);
                    throwDice(throwOption == 2, history[historyCount].numbers);

                    // Verificar si gan�
                    int drawnNumbers[3];
                    throwDice(1, drawnNumbers);
                    history[historyCount].won = checkWin(history[historyCount].numbers, drawnNumbers);

                    // Imprimir resultado
                    printf("\n=== Resultado ===\n");
                    printf("Fecha y hora: %s", ctime(&history[historyCount].timestamp));
                    printf("Tus n�meros: %d %d %d\n", history[historyCount].numbers[0], history[historyCount].numbers[1], history[historyCount].numbers[2]);
                    printf("N�meros sorteados: %d %d %d\n", drawnNumbers[0], drawnNumbers[1], drawnNumbers[2]);

                    if (history[historyCount].won) {
                        printf("�Felicidades! Ganaste al menos con un n�mero.\n");
                    } else {
                        printf("Lo siento, no ganaste. �Int�ntalo de nuevo!\n");
                    }

                    historyCount++;
                } else {
                    printf("Opci�n no v�lida.\n");
                }
                break;

            case 2:
                printf("\n=== Imprimir resultados ===\n");
                for (int i = 0; i < historyCount; ++i) {
                    printf("\n=== Juego %d ===\n", i + 1);
                    printf("Fecha y hora: %s", ctime(&history[i].timestamp));
                    printf("Tus n�meros: %d %d %d\n", history[i].numbers[0], history[i].numbers[1], history[i].numbers[2]);

                    if (history[i].won) {
                        printf("�Felicidades! Ganaste al menos con un n�mero.\n");
                    } else {
                        printf("Lo siento, no ganaste. �Int�ntalo de nuevo!\n");
                    }
                }
                break;

            case 3:
                printf("Saliendo del programa. Gracias por jugar.\n");
                break;

            default:
                printf("Opci�n no v�lida. Int�ntalo de nuevo.\n");
                break;
        }

    } while (option != 3);

    return 0;
}
