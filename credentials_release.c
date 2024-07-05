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
    // Comando per verificare la firma
    const char *verify_command = "openssl dgst -verify clientpub_key.pem -signature signature.bin outputsha256.txt";
    
    // Esegui il comando di verifica
    int verify_status = execute_command(verify_command);

    // Controlla se il comando di verifica è andato a buon fine
    if (verify_status == 0) {
        // Comando per generare il vettore di inizializzazione e salvarlo su un file
        const char *iv_file = "iv.txt";
        char generate_iv_command[64];
        snprintf(generate_iv_command, sizeof(generate_iv_command), "openssl rand -hex 16 > %s", iv_file);
        
        // Esegui il comando di generazione dell'IV
        int generate_iv_status = execute_command(generate_iv_command);
        if (generate_iv_status != 0) {
            perror("Errore nell'esecuzione del comando openssl rand");
            exit(EXIT_FAILURE);
        }
        
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
        
        // Comando per crittografare il file credentials.txt
        char encrypt_command[512];
        snprintf(encrypt_command, sizeof(encrypt_command),
                 "openssl enc -base64 -e -aes-256-ctr -in credentials.txt -pbkdf2 -pass pass:123456789goabcdef123456789goabcdef123456789goabcdef123456789goabcdef -iv %s -out ciphertext.bin",
                 iv);

        // Esegui il comando di crittografia
        int encrypt_status = execute_command(encrypt_command);
        if (encrypt_status == 0) {
            printf("Credenziali rilasciate con successo.\n");
        } else {
            printf("Errore nel rilascio delle credenziali.\n");
        }
    } else {
        printf("Errore nel rilascio delle credenziali.\n");
    }
    return 0;
}
