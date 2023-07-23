To Run the project:

1. Open up 2 terminals, one for the echo server, and one for the client.
  
2. For echo server terminal:
   
   command 1. 先透過GCC編譯server.c這支程式 (-o means to specify the output file as the name "server")

       gcc server.c -o server
   
    command 2. 執行該支程式 (執行後，應該要出現"Server listening on 127.0.0.1:12345"的訊息，代表server開始等待client連接。)
   
       ./server 
   
3. For client terminal:
   
   command 1. (如果沒用 -o，預設的初出檔名為 a.out)

       gcc client.c -o client  
   
   command 2.

       ./client
   
5. After the above steps, you should see logs like "Received message from client: Hello, server! Attempt 1" on the server terminal, and echo message log like "Received echo message: Hello, server! Attempt 1" on the client terminal.


Explain the code:

1. The assignment was accomplished by two programs, the "server.c", and the "client.c".

2. In the program for the server:

   First, create a socket object (using socket()) sockfd into a UDP socket (using SOCK_DGRAM), and assigned IPv4 by using PF_INET or AF_INET.

   Then, configure the server address by defining the SERVER_IP to "127.0.0.1" and the SERVER_PORT 12345.

   Bind the socket to the server address.

   If bind() returns a negative value, it means an error occurred during the binding process, and the server terminates with an error message.

   Now, the server should be waiting for the client to send an UDP socket.

3. In the client program:

   I wrote a function exponential_backoff() for implementing the exponential backoff algorithm that was asked to add in the ASSIGNMENT for the Support max-retry option.

   In the main function for the client, first, create a UDP socket and then configure the server address similar to the server.c.

   Later on, may send the UDP message to the server. Here, I added an additional function for the client to type the message content through the terminal, so I clear the data buffer before getting the input message in case there's wrong message already exists in the data buffer.

   At last, there's the function for the Support max-retry option, in which the max-retry was set to 10 times according to the ASSIGNMENT, and the interval waiting time between each retry will be set according to the exponential backoff algorithm.

4. I added one additional function(mentioned above), for the client to type in the message that will be sent to the server, you may see the modified code in the commit history on GitHub (modified files include server.c and client.c).
