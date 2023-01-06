/*
  Project : Pong Game
  Author :  SajMoooner a Marek
  Predmet : POS
  Stack : c++ , SFML, SFML-Network, SFML-graphics, SFML-system, SFML-window,

*/

#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <pthread.h>
 
 // Konštanty pre hru
unsigned short PORT = 12345;
const int WIDTH = 800;
const int HEIGHT = 600;

// Funkcia pre pridanie skore hracovi 1 pomocou vlakna
void *addScorePlayer1(void *arg) {
  int *score1N = (int *)arg;
  *score1N += 1;
  return NULL;
}

// Funkcia pre pridanie skore hracovi 2 pomocou vlakna
void *addScorePlayer2(void *arg) {
  int *score2N = (int *)arg;
  *score2N += 1;
  return NULL;
}
 
int main() {

  // Vytvor hlavné okno hry 
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Pong");

  // Vytvor hráčov 
  sf::RectangleShape player1(sf::Vector2f(10, 50));
  sf::RectangleShape player2(sf::Vector2f(10, 50));
  player1.setFillColor(sf::Color::White);
  player2.setFillColor(sf::Color::White);
  player1.setPosition(10, HEIGHT / 2 - 25);
  player2.setPosition(WIDTH - 20, HEIGHT / 2 - 25);
 
  // Vytvor loptu
  sf::CircleShape ball(10);
  ball.setFillColor(sf::Color::White);
  ball.setPosition(WIDTH / 2, HEIGHT / 2);
  sf::Vector2f ball_velocity(1, 1);
 
  // Vytvor skore ktoré sa zobrazuje na obrazovke
  sf::Font font;
  font.loadFromFile("arial.ttf");
  sf::Text score1;
  sf::Text score2;
  score1.setFont(font);
  score2.setFont(font);
  score1.setCharacterSize(24);
  score2.setCharacterSize(24);
  score1.setFillColor(sf::Color::White);
  score2.setFillColor(sf::Color::White);
  score1.setPosition(WIDTH / 2 - 50, 10);
  score2.setPosition(WIDTH / 2 + 50, 10);
  int score1N = 0;
  int score2N = 0;

  // Vytvor vlákno pre pridanie skore hracovi 1
  pthread_t thread1;
  pthread_create(&thread1, NULL, addScorePlayer1, &score1N);

  // Vytvor vlákno pre pridanie skore hracovi 2
  pthread_t thread2;
  pthread_create(&thread2, NULL, addScorePlayer2, &score2N);
 
  // Vytvor socket pre komunikáciu medzi serverom a klientom a bindni ho na port 
  sf::UdpSocket socket;
  socket.bind(PORT);

  // Vytvor IP adresu
  sf::IpAddress partner_ip;

  // Vypíš moju IP adresu 
  std::cout << "Tvoja IP adresa je : " << sf::IpAddress::getLocalAddress() << std::endl;

  // Zisti či je server alebo klient
  bool is_server = false;
  std::cout << "Ak chcec byt server napis s, ak chces byt klient napis IP adresu servera : ";
  std::string input;
  std::cin >> input;
 
 
  if (input == "s") {
    std::cout << "Cakam na pripojenie klienta..." << std::endl;
    is_server = true;
  } else {
    std::cout << "Pripajam sa na server..." << std::endl;
    partner_ip = input;
  }
  
  // Hlavný cyklus hry
  while (window.isOpen()) {

    // Event loop kym sa okno nezavrie
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    //Zisti polohu hráčov
    //SERVER stlačenie kláves W a S
    //CLIENT stlačenie kláves UP a DOWN

    if (is_server) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player1.move(0, -1);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player1.move(0, 1);
      }
    } else {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        player2.move(0, -1);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        player2.move(0, 1);
      }
    }
 
 
    // Vykresli hráčov a loptu

    if (player1.getPosition().y < 0) {
      player1.setPosition(10, 0);
    }
    if (player1.getPosition().y > HEIGHT - 50) {
      player1.setPosition(10, HEIGHT - 50);
    }
    if (player2.getPosition().y < 0) {
      player2.setPosition(WIDTH - 20, 0);
    }
    if (player2.getPosition().y > HEIGHT - 50) {
      player2.setPosition(WIDTH - 20, HEIGHT - 50);
    }
 
    // Updatni pozíciu lopty
    ball.move(ball_velocity);
    if (ball.getPosition().y < 0 || ball.getPosition().y > HEIGHT - 20) {
      ball_velocity.y *= -1;
    }
 
    // Zisti či bola lopta dotknutá hráčom 1
    if (ball.getGlobalBounds().intersects(player1.getGlobalBounds())) {
      ball_velocity.x *= -1;
    }

    // Zisti či bola lopta dotknutá hráčom 2
    if (ball.getGlobalBounds().intersects(player2.getGlobalBounds())) {
      ball_velocity.x *= -1;
    }
 
    // Zisti či lopta skorovala
    if (ball.getPosition().x < 0) {
      ball.setPosition(WIDTH / 2, HEIGHT / 2);
      score2N++;
    }
 
    if (ball.getPosition().x > WIDTH) {
      ball.setPosition(WIDTH / 2, HEIGHT / 2);
      score1N++;
    }
 
    // Updatni skore
    score1.setString(std::to_string(score1N));
    score2.setString(std::to_string(score2N));
 
    // Pošli pozíciu hráčov na server a klienta a updatni pozíciu hráčov na serveri a klientovi
    // server posiela pozíciu hráča 1 a klientovy 
    // klient posiela pozíciu hráča 2 a serveru

    sf::Packet packet;
    if (is_server) {
      packet << player1.getPosition().y;
    } else {
      packet << player2.getPosition().y;
    }
    socket.send(packet, partner_ip, PORT);


    // Prijmi pozíciu hráčov od servera a klienta a updatni pozíciu hráčov na serveri a klientovi
    // server prijíma pozíciu klienta
    // klient prijíma pozíciu servera
    // nastav pozíciu hráčov na pozíciu prijatú od servera a klienta
    sf::Packet packet2;
    if (is_server) {
      socket.receive(packet2, partner_ip, PORT);
      float y;
      packet2 >> y;
      player2.setPosition(WIDTH - 20, y);
    } else {
      socket.receive(packet2, partner_ip, PORT);
      float y;
      packet2 >> y;
      player1.setPosition(10, y);
    }
 
    // Vykresli pozadie
    // Vykresli skore, hráčov a loptu na okno
    window.clear();
   
    window.draw(score1);
    window.draw(score2);

    window.draw(player1);
    window.draw(player2);
    window.draw(ball);

    window.display();
  }
    return 0;
   
}
