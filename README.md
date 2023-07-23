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
