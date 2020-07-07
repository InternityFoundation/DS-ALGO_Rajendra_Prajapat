# Client Server Program 

Install the OpenSSL library, for the ubuntu use the below command.
>sudo apt-get install -y libssl-dev

Generate certificate
>openssl req -x509 -nodes -days 365 -newkey rsa:1024 -keyout mycert.pem -out mycert.pem

Compile the programs
> gcc -Wall -o cli  client.c -L/usr/lib -lssl -lcrypto
> gcc -Wall -o ser  server.c -L/usr/lib -lssl -lcrypto -lpthread

run server
> sudo ./ser 8081

Run wireshark to capture the packets
> sudo wireshark -i lo

run client 
> ./client 127.0.0.1 8081

stop server and wireshark capturing and analyze the packets
