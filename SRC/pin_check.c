#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PIN "1234567890"  // Sostituisci con il PIN reale

void executeCommand(const char* command) {
    int result = system(command);
    if (result != 0) {
        printf("Errore nell'esecuzione del comando: %s\n", command);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <pin>\n", argv[0]);
        return 1;
    }

    const char* inputPin = argv[1];

    if (strcmp(inputPin, PIN) == 0) {
        char command[256];

        // Genera l'hash del file di testo
        snprintf(command, sizeof(command), "openssl dgst -sha256 request.txt > outputsha256.txt");
        executeCommand(command);

        // Firma il file hashato
        snprintf(command, sizeof(command), "openssl dgst -sign clientsec_key.pem -out signature.bin outputsha256.txt");
        executeCommand(command);

        printf("Firma digitale eseguita con successo.\n");
    } else {
        printf("PIN errato, reinserire il PIN.\n");
    }

    return 0;
}