## Premises
Is highly recommended to do a backup folder before doing tests!!
In the folder there're already the digital certificates to do the tests so it's not necessary to create them again.

## How to run
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
