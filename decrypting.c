#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funzione per eseguire un comando di sistema e ottenere l'uscita
int execute_command(const char *command) {
    int result = system(command);
    if (result == -1) {
        perror("Errore nell'esecuzione del comando");
        exit(EXIT_FAILURE);
    }
    // Controlla se il comando è terminato correttamente
    if (result == 0) {
        return 0;
    } else {
        return 1;
    }
}

int main() {
    // Nome del file contenente il vettore di inizializzazione
    const char *iv_file = "iv.txt";

    // Leggi l'IV dal file
    char iv[33];  // 32 caratteri hex + 1 per il terminatore nullo
    FILE *iv_fp = fopen(iv_file, "r");
    if (iv_fp == NULL) {
        perror("Errore nell'apertura del file IV");
        exit(EXIT_FAILURE);
    }
    if (fgets(iv, sizeof(iv), iv_fp) == NULL) {
        perror("Errore nella lettura del vettore di inizializzazione dal file");
        fclose(iv_fp);
        exit(EXIT_FAILURE);
    }
    fclose(iv_fp);

    // Rimuove il newline alla fine dell'iv
    iv[strcspn(iv, "\n")] = '\0';
    
    // Comando per decrittografare il file ciphertext.bin usando l'IV dal file
    char decrypt_command[512];
    snprintf(decrypt_command, sizeof(decrypt_command),
             "openssl enc -base64 -d -aes-256-ctr -pbkdf2 -pass pass:123456789goabcdef123456789goabcdef123456789goabcdef123456789goabcdef -iv %s -in ciphertext.bin -out decrypted_credentials.txt",
             iv);

    // Esegui il comando di decrittografia
    int decrypt_status = execute_command(decrypt_command);
    if (decrypt_status == 0) {
        printf("Credenziali ottenute con successo nel file decrypted_credentials.txt.\n");
    } else {
        printf("Errore nella decrittografia delle credenziali.\n");
    }
    return 0;
}









