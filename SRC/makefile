all: compile execute

certificates: ipzs client credca server

credential_certificate: credca2 client2

clean:
	rm -rf ./demoCA
	rm -rf ./client_authority
	rm -rf ./Trusted
	rm -f clientcert.pem
	rm -f clientpub_key.pem
	rm -f clientrequest.pem
	rm -f clientsec_key.pem
	rm -f credcacert.pem
	rm -f credcapub_key.pem
	rm -f credcarequest.pem
	rm -f credcasec_key.pem
	rm -f IPZScert.pem
	rm -f IPZSsec_key.pem
	rm -f iv.txt
	rm -f servercert.pem
	rm -f serverpub_key.pem
	rm -f serverrequest.pem
	rm -f serversec_key.pem
	rm -f signature.bin

ecparam:
	#generates the paramteters from the elliptic curve prime256v1
	openssl ecparam -name prime256v1 -out prime256v1.pem

configuration:
	#ipzs
	#creates the secret key of the ipzs
	openssl genpkey -paramfile prime256v1.pem -out IPZSsec_key.pem
	
	
	#client
	#creates the secret key of the client
	openssl genpkey -paramfile prime256v1.pem -out clientsec_key.pem
	
	#extracts the public key of the client from the previous file
	openssl pkey -in clientsec_key.pem -pubout -out clientpub_key.pem
	
	
	#credential authority
	#creates the secret key of the credentials authority
	openssl genpkey -paramfile prime256v1.pem -out credcasec_key.pem
	
	#extracts the public key of the credentials authority from the previous file
	openssl pkey -in credcasec_key.pem -pubout -out credcapub_key.pem
	
	
	#server
	#creates the secret key of the server
	openssl genpkey -paramfile prime256v1.pem -out serversec_key.pem
	
	#extracts the public key of the server from the previous file
	openssl pkey -in clientsec_key.pem -pubout -out serverpub_key.pem

ipzs:
	@echo "-----CERTIFICATE OF THE IPZS-----";
	openssl req -new -x509 -days 365 -key IPZSsec_key.pem -out IPZScert.pem -config openssl.cnf
	
	#section used to organize the file
	mkdir demoCA
	mkdir demoCA/private
	mkdir demoCA/newcerts
	touch demoCA/index.txt demoCA/serial
	echo "00" >> demoCA/serial
	cp IPZScert.pem demoCA
	cp IPZSsec_key.pem demoCA/private
	
	#changes the name of the file containing the secret key of the IPZS
	mv demoCA/private/IPZSsec_key.pem demoCA/private/cakey.pem
	
	#same for the certificate of the IPZS
	mv demoCA/IPZScert.pem demoCA/cacert.pem

client:
	#creates the request of a digital certificate
	@echo "-----CERTIFICATE REQUEST OF THE CLIENT-----";
	openssl req -new -key clientsec_key.pem -out clientrequest.pem -config clientconfig.cnf
	
	#reads the previosus file
	openssl req -in clientrequest.pem -text
	
	#allows the IPZS to sign the certificate of the client
	openssl ca -in clientrequest.pem -out clientcert.pem -policy policy_anything -config openssl.cnf

client2:
	#in this section the client will make another request for obtaining the credentials certificate from the 
	#credentials authority
	cp clientsec_key.pem client_authority
	@echo "-----CERTIFICATE REQUEST OF THE CLIENT FOR OBTAINING CREDENTIALS-----";
	openssl req -new -key client_authority/clientsec_key.pem -out client_authority/clientrequest2.pem -config client_authority/clientconfig.cnf
	
	#reads the previosus file
	openssl req -in client_authority/clientrequest2.pem -text
	
	#allows the credentials authority to sign the certificate of the client
	openssl ca -in client_authority/clientrequest2.pem -out client_authority/clientcert2.pem -policy policy_anything -config client_authority/autocredcaconfig.cnf

credca:
	#this section is used to make the credentials authority a reliable authority whose task is to sign the 
	#credential certificates of the clients
	#creates the request of a digital certificate
	@echo "-----CERTIFICATE REQUEST OF THE CREDENTIAL AUTHORITY-----";
	openssl req -new -key credcasec_key.pem -out credcarequest.pem -config caconfig.cnf
	
	#allows the IPZS to sign the certificate of the client
	openssl ca -in credcarequest.pem -out credcacert.pem -policy policy_anything -config openssl.cnf

credca2:
	mkdir client_authority
	cp credcasec_key.pem client_authority
	cp autocredcaconfig.cnf client_authority
	cp clientconfig.cnf client_authority
	
	@echo "-----AUTO-CERTIFICATION OF THE CREDENTIAL AUTHORITY-----";
	openssl req -new -x509 -days 365 -key client_authority/credcasec_key.pem -out client_authority/autocredcacert.pem -config client_authority/autocredcaconfig.cnf
	
	#section used to organize the file
	mkdir client_authority/demoCA
	mkdir client_authority/demoCA/private
	mkdir client_authority/demoCA/newcerts
	touch client_authority/demoCA/index.txt client_authority/demoCA/serial
	echo "00" >> client_authority/demoCA/serial
	cp client_authority/autocredcacert.pem client_authority/demoCA
	cp client_authority/credcasec_key.pem client_authority/demoCA/private
	
	#changes the name of the file containing the secret key of the credentials authority
	mv client_authority/demoCA/private/credcasec_key.pem client_authority/demoCA/private/cakey.pem
	
	#same for the certificate of the credentials authority
	mv client_authority/demoCA/autocredcacert.pem client_authority/demoCA/cacert.pem

server:
	#creates the request of a digital certificate
	@echo "-----CERTIFICATE REQUEST OF THE SERVER-----";
	openssl req -new -key serversec_key.pem -out serverrequest.pem -config serverconfig.cnf
	
	#allows the IPZS to sign the certificate of the client
	openssl ca -in serverrequest.pem -out servercert.pem -policy policy_anything -config openssl.cnf

clicaconnection_server:
	#Here there are some things to do: the first is creating a new folder named "Trusted" in which there will be
	#all the certificates that the authority considers reliable.
	#Since we have used Windows, the option -CApath doesn't work and the option -CAfile wants a single file
	#so we had to create a single file named "client_certbundle.pem" 
	#that contains all the certificates that proves that the client is reliable i.e. its own certificate and the certificate of the ipzs
	mkdir Trusted
	cat clientcert.pem IPZScert.pem > Trusted/client_certbundle.pem
	cat credcacert.pem IPZScert.pem > Trusted/credca_certbundle.pem
	#allows to credentials authority to operate as a server waiting the requests from the client
	openssl s_server -cert credcacert.pem -key credcasec_key.pem -port 8899 -Verify 5 -CAfile Trusted/client_certbundle.pem

clicaconnection_client:
	#to run the client another terminal is needed
	#allows the client to operate as a client
	openssl s_client -cert clientcert.pem -key clientsec_key.pem -connect 127.0.0.1:8899 -CAfile Trusted/credca_certbundle.pem -verify_return_error

compile:
	@echo "-----COMMUNICATION BETWEEN CLIENT - CREDENTIALS AUTHORITY (CREDENTIALS OBTAINMENT)-----";
	@gcc -o pin_check pin_check.c;
	@gcc -o credentials_release credentials_release.c;
	@gcc -o decrypting decrypting.c

execute:
	#In this file there are commands such:
	# - openssl dgst -sha256 request.txt > outputsha256.txt used to hash the message request of the client;
	# - openssl dgst -sign clientsec_key.pem -out signature.bin outputsha256.txt used to create the ECDSA sign
	@./pin_check.exe 1234567890;
	
	#In this file there are commands such:
	# - openssl dgst -verify clientpub_key.pem -signature signature.bin outputsha256.txt used to verify the sign
	# - openssl rand -hex 16 > iv.txt
	# - openssl enc -base64 -e -aes-256-ctr -in text.txt -pbkdf2 -pass pass:123456789goabcdef123456789goabcdef123456789goabcdef123456789goabcdef -iv iv.txt -out ciphertext.bin
	@./credentials_release;
	
	#In this file there is one command in particular:
	# - openssl enc -base64 -d -aes-256-ctr -pbkdf2 -pass pass:123456789goabcdef123456789goabcdef123456789goabcdef123456789goabcdef -iv iv.txt -in ciphertext.bin
	@./decrypting;

cliserconnection_server:
	#same as clicaconnection: a double terminal is needeed, one for the server and one for the client
	#the diffrence here is that we run the server with the option -WWW necessary for return a resource if the client connect to a browser
	#in this case the resource is a simple html file named resource.html
	cat clientcert.pem client_authority/clientcert2.pem IPZScert.pem > Trusted/client2_certbundle.pem
	cat servercert.pem IPZScert.pem > Trusted/server_certbundle.pem
	#allows the server to run as a server
	openssl s_server -cert servercert.pem -key serversec_key.pem -port 8899 -Verify 5 -CAfile Trusted/client2_certbundle.pem -WWW

cliserconnection_client:
	#allows the client to run as a client
	openssl s_client -cert clientcert.pem -key clientsec_key.pem -connect 127.0.0.1:8899 -CAfile Trusted/server_certbundle.pem -verify_return_error
