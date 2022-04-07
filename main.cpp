#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;
#include <math.h> 
#include <time.h>     

int main()
{
      srand (time(NULL));
    RenderWindow window(sf::VideoMode(800, 600), "Floppy bird!");
    Clock clock;
    /////////////////////// Variables
    Texture birdTexture; birdTexture.loadFromFile("./media/graphical/bird.png");

    Sprite bird; bird.setTexture(birdTexture);

    RectangleShape obs[2][3];
    int x = 200;
    for(int i = 0;i< 3;i++){
        int t = rand() % (600-x) + 1;
        obs[0][i] = RectangleShape(Vector2f(80, t));
        obs[0][i].setPosition(Vector2f(300 + 300*i, 0));
        obs[1][i] = RectangleShape(Vector2f(80, 600-x-t));
        obs[1][i].setPosition(Vector2f(300 + 300*i, x+t));
    }
    bool gameOver = false;
    float speedMultiplier = 160;
    float totalTime = 0;
    int nextObs = 0;
    int birdState = 0;
    float birdSpeed = 0;
    float gravity = 9.8;
    bird.setTextureRect(sf::IntRect(birdTexture.getSize().x/3 * birdState, 0, birdTexture.getSize().x / 3, birdTexture.getSize().y));
    bird.setOrigin(Vector2f(bird.getLocalBounds().width/2, bird.getLocalBounds().height/2));
    bird.setScale(Vector2f(0.2,0.2));
    bird.setPosition(Vector2f(100, 130));
    int score = 0;
    ///////////////////////
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    float dt = clock.getElapsedTime().asSeconds();
    totalTime += dt;
    if(!gameOver){

    
    speedMultiplier += dt;

    ////////////////////////////////// loop 
    ////////////////////////////////////// Bird movement
    birdState = 2;
    bird.setRotation(-10);
    if(birdSpeed > 0){
        birdState = 0;
        bird.setRotation(10);
    }
    if(Keyboard::isKeyPressed(Keyboard::Up)){
        birdState = (int)(totalTime*6) % 3;
        bird.setRotation(-10);
        birdSpeed -= dt*30;
    }


    if(bird.getPosition().x > obs[0][0].getPosition().x + 100){
        nextObs = 1;
    }
    else{
        nextObs = 0;
    }

    // if(obs[1][0].getPosition().y -50 < bird.getPosition().y && birdSpeed > -4 || birdSpeed > 4 ){
    //     birdState = (int)(totalTime*6) % 3;
    //     bird.setRotation(-10);
    //     birdSpeed -= dt*30;
    // }
    

    bird.setTextureRect(sf::IntRect(birdTexture.getSize().x/3 * birdState, 0, birdTexture.getSize().x / 3, birdTexture.getSize().y));
    bird.move(Vector2f(0, 0.5*(birdSpeed+=gravity*dt)*dt)*speedMultiplier);


    
    if(bird.getPosition().y - bird.getLocalBounds().height/12 < 0 ){
        bird.setPosition(bird.getPosition().x, bird.getLocalBounds().height/12);
        birdSpeed *= -0.4;
    }
    else if(bird.getPosition().y + bird.getLocalBounds().height/12 > 600){
        
        bird.setPosition(bird.getPosition().x, 600 - bird.getLocalBounds().height/12);
        birdSpeed *= -0.4;
    }
    ////////////////////////////////////// Obstacles

    if(obs[0][0].getPosition().x < -80){
        score++;
        cout << score <<endl;
        for(int i = 0; i<2;i++){
        obs[0][i] = obs[0][i+1];
        obs[1][i] = obs[1][i+1];
        obs[0][i].setPosition(Vector2f(300-80 + 300*i, 0));
        obs[1][i].setPosition(Vector2f(300-80 + 300*i, obs[1][i].getPosition().y));
        }
        int t = rand() % (600-x) + 1;
        obs[0][2] = RectangleShape(Vector2f(80, t));
        obs[1][2] = RectangleShape(Vector2f(80, 600-x-t));
        obs[0][2].setPosition(Vector2f(900-80, 0));
        obs[1][2].setPosition(Vector2f(900-80, x+t));

    }
    for(int i = 0; i<3;i++){
        obs[0][i].move(Vector2f(-dt*speedMultiplier, 0));
        obs[1][i].move(Vector2f(-dt*speedMultiplier, 0));
    }
        obs[0][0].setFillColor(Color(255,255,255,255));
        obs[1][0].setFillColor(Color(255,255,255,255));
        obs[0][1].setFillColor(Color(255,255,255,255));
        obs[1][1].setFillColor(Color(255,255,255,255));
        obs[0][2].setFillColor(Color(255,255,255,255));
        obs[1][2].setFillColor(Color(255,255,255,255));
        obs[0][nextObs].setFillColor(Color(0,255,0,255));
        obs[1][nextObs].setFillColor(Color(0,255,0,255));
    
    if(bird.getPosition().x + bird.getLocalBounds().width/12 > obs[0][0].getGlobalBounds().left && bird.getPosition().x - bird.getLocalBounds().width/12 < obs[0][0].getGlobalBounds().left + obs[0][1].getGlobalBounds().width){
        if(bird.getPosition().y - bird.getLocalBounds().width/16 < obs[0][0].getLocalBounds().height || bird.getPosition().y + bird.getLocalBounds().width/16 > obs[1][0].getPosition().y){
            obs[0][0].setFillColor(Color(0xff0000FF));
            obs[1][0].setFillColor(Color(0xff0000FF));
            bird.setColor(Color(0xaaaaaaaa));
            speedMultiplier = 0;
            gameOver = true;
        } 
    }
  

}


    ///////////////////////////////////// rendering
        clock.restart();//d
        cout << 1/dt << endl;
        
        sleep(seconds(1/30.f));
        window.clear();


        for(int i = 0;i<3;i++){
            window.draw(obs[0][i]);
            window.draw(obs[1][i]);
        }

        window.draw(bird);

        window.display();
    
    ///////////////////////////////////// loop
    }
    return 0;
}