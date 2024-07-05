# APS Project: Tennis Table: Obtaining credentials via Electronic Identity Card and access to servers

## Group 03

- **Ciaravola Giosuè**
  - Email: g.ciaravola3@studenti.unisa.it
  - Student ID: 0622702177

- **Conato Christian**
  - Email: c.conato@studenti.unisa.it
  - Student ID: 0622702273

- **Del Gaudio Nunzio**
  - Email: n.delgaudio5@studenti.unisa.it
  - Student ID: 0622702277

- **Garofalo Mariachiara**
  - Email: m.garofalo38@studenti.unisa.it
  - Student ID: 0622702173


## HOW TO USE:

### Premises
Is highly recommended to do a backup folder before doing tests!!
In the folder there're already the digital certificates to do the tests so it's not necessary to create them again.

### How to run
1.	Navigate to the project folder containing the makefile

2.	To clear previously file and folders, enter the command
make clean

3. To configure the main files such us the ecparam, the public keys and the secret keys of ipzs, client, credential authority and server, enter the command
make configuration

4. To configure the main files and to run the scripts useful for the simulation of the CIE, for releasing the credentials and decrypting the credential, enter the command
make all

5. To create a certificate request and to sign them from a trusted authority (ipzs), enter the command
make certificates

6. To start a client server TLS connection between client and credentials authority from the pov of a server, enter the command
make clicaconnection_server

7. (A SECOND TERMINAL IS NEEDEED) To start a client server TLS connection between client and credentials authority from the pov of a client, enter the command
make clicaconnection_client

8. To start a client server TLS connection between client and server from the pov of a server, enter the command
make cliserconnection_server

9. (A SECOND TERMINAL IS NEEDEED) To start a client server TLS connection between client and server from the pov of a client, enter the command
make cliserconnection_client

After have runned this command is necessary to go to browser and type the following url:

https://127.0.0.1:8899/resource.html

to get the resource.


## File Descriptions

### IPZS

- **prime256v1.pem**: file for parameter generation using elliptic curve prime256v1;
- **IPZSsec key.pem**: file containing the secret key of IPZS;
- **IPZScert.pem**: digital certificate of IPZS;
- **openssl.cnf**: configuration file useful as a template for creating a certificate;
- **caconfig.cnf**: configuration file useful as a template for creating the certificate for the credential issuing authority;
- **serverconfig.cnf**: configuration file useful as a template for creating the server certificate;
- **demoCA**: folder containing all the necessary files for IPZS to issue certificates;
  - **newcerts**: folder containing all digital certificates ordered by serial number;
  - **private**: folder containing the copy of the secret key of IPZS;
  - **cacert.pem**: file of the digital certificate of IPZS;
  - **serial**: file that keeps track of the progression of serial numbers;
  - **index.txt**: "database" file that contains the history of all certificates issued by IPZS.

### Client

- **clientsec key.pem**: file containing the secret key of the client;
- **clientpub key.pem**: file containing the public key of the client;
- **clientrequest.pem**: digital certificate request of the client;
- **clientcert.pem**: digital certificate of the client approved by IPZS.

### CA:

- **credcasec key.pem**: file containing the secret key of the authority;
- **credcapub key.pem**: file containing the public key of the authority;
- **credcarequest.pem**: digital certificate request of the authority;
- **credcacert.pem**: digital certificate of the authority approved by IPZS.

### CIE: 

- **pin check.c**: script in C that simulates the CIE;
- **request.txt**: credential acquisition request message;
- **outputsha256.txt**: credential acquisition request message hashed with sha256;
- **signature.bin**: ECDSA signature.

### Issuing and obtaining credentials:

- **credentials release.c**: script in C that performs the credential release by the authority;
- **decrypting.c**: script in C that decrypts the credentials obtained from the credential issuing authority;
- **iv.txt**: initialization vector used to encrypt and decrypt a message with a symmetric key;
- **credentials.txt**: text file containing the credentials that the authority will release;
- **decrypted credentials.txt**: text file containing the credentials decrypted by the client;

### Server:

- **resource.html**: HTML page requested by the client