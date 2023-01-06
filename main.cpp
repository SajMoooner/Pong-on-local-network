#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
 
 
unsigned short PORT = 12345;
const int WIDTH = 800;
const int HEIGHT = 600;
 
int main() {
  // Create the window and the paddles and score
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Pong");
  sf::RectangleShape player1(sf::Vector2f(10, 50));
  sf::RectangleShape player2(sf::Vector2f(10, 50));
  player1.setFillColor(sf::Color::White);
  player2.setFillColor(sf::Color::White);
  player1.setPosition(10, HEIGHT / 2 - 25);
  player2.setPosition(WIDTH - 20, HEIGHT / 2 - 25);
 
 
  // Create the ball
  sf::CircleShape ball(10);
  ball.setFillColor(sf::Color::White);
  ball.setPosition(WIDTH / 2, HEIGHT / 2);
  sf::Vector2f ball_velocity(1, 1);
 
  // create the score
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
 
 
  // Initialize the network sockets
  sf::UdpSocket socket;
  socket.bind(PORT);
  sf::IpAddress partner_ip;
  bool is_server = false;
  std::cout << "Enter 's' to start a server, or enter the IP address of the server: ";
  std::string input;
  std::cin >> input;
 
 
  if (input == "s") {
    is_server = true;
  } else {
    partner_ip = input;
  }
 
  // Main game loop
  while (window.isOpen()) {
    // Handle events
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
 
    // Update the paddles based on user input 
    // w and s for player 1 server
    // up and down for player 2 client
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
 
 
    // Clamp the paddles to the screen
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
 
    // Update the ball
    ball.move(ball_velocity);
    if (ball.getPosition().y < 0 || ball.getPosition().y > HEIGHT - 20) {
      ball_velocity.y *= -1;
    }
 
    // Check for collisions with the paddles
    if (ball.getGlobalBounds().intersects(player1.getGlobalBounds())) {
      ball_velocity.x *= -1;
    }
 
    if (ball.getGlobalBounds().intersects(player2.getGlobalBounds())) {
      ball_velocity.x *= -1;
    }
 
    // Check for a goal
    if (ball.getPosition().x < 0) {
      ball.setPosition(WIDTH / 2, HEIGHT / 2);
        score2N++;
    }
 
    if (ball.getPosition().x > WIDTH) {
      ball.setPosition(WIDTH / 2, HEIGHT / 2);
        score1N++;
    }
 
    // Update the score
    score1.setString(std::to_string(score1N));
    score2.setString(std::to_string(score2N));
 
    // Send the paddle positions from server to client and vice versa
    sf::Packet packet;
    if (is_server) {
      packet << player1.getPosition().y;
    } else {
      packet << player2.getPosition().y;
    }
    socket.send(packet, partner_ip, PORT);


    // Receive the paddle positions from client and update the paddle positions on the server
    // and vice versa
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
 
    // Clear the window and draw the game objects
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
