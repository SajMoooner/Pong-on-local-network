# Pong-on-local-network

The purpose of this project was to create pong game on local network.

The proces of making game was not simple bacause we program it in c++ :D
The step by step proces : 
  - make clean pong game using SFML library -> sfml library was easy to use, thats why we use it
  - understand movement of player and how is calculated 
  - add rules for pong game 
  - when we have pong game we can start making comunication on local network
  - to make comunication possible we use sfml library and udp protocol
  - udp is best cause game is 60fps so if 4 frames drop we dont notice
  - to comunicate and get data between 2 local computers we use socket 
  
  
Server : 


![image](https://user-images.githubusercontent.com/70257823/211001926-d186d537-e2b8-4d23-b72f-dd5f826ffc38.png)

Client : 


![image](https://user-images.githubusercontent.com/70257823/211001987-854f137b-d697-493a-a778-06239f59a781.png)
