#include <SFML/Graphics.hpp>
using namespace sf;
int main()
{
    srand (time(NULL));
    RenderWindow w(sf::VideoMode(800, 600), "Floppy bird!", Style::Close);
    Clock clock;
    CircleShape bird; bird.setRadius(20); bird.setOrigin(20,20); bird.setPosition(Vector2f(100,130));
    RectangleShape obs[2][3];
    float speed = 0;
    for(int i = 0;i<3;i++){
        int t = rand() % 400 +1;
        obs[0][i] = RectangleShape(Vector2f(80, t)); obs[0][i].setPosition(Vector2f(300 + 300*i, 0));
        obs[1][i] = RectangleShape(Vector2f(80, 400-t));obs[1][i].setPosition(Vector2f(300 + 300*i, 200+t));
    }
    while(true){
        Event e; while (w.pollEvent(e) && e.type == Event::Closed){w.close();}
        float dt = clock.getElapsedTime().asSeconds();
        speed+=dt*10;
        if(Keyboard::isKeyPressed(Keyboard::Up)){speed-=dt*30;} bird.move(Vector2f(0,speed*dt*100));
        if(bird.getPosition().y < 20){bird.setPosition(100, 20);speed*=-0.4;}
        else if(bird.getPosition().y > 580){bird.setPosition(100, 580);speed*=-0.4;}
        if(obs[0][0].getPosition().x < -80){
            for(int i = 0; i<2;i++){
                obs[0][i] = obs[0][i+1]; obs[0][i].setPosition(Vector2f(220 + 300*i, 0));
                obs[1][i] = obs[1][i+1]; obs[1][i].setPosition(Vector2f(220 + 300*i, obs[1][i].getPosition().y));
            }
            int t = rand() % 400 + 1;
            obs[0][2] = RectangleShape(Vector2f(80, t)); obs[0][2].setPosition(Vector2f(820, 0));
            obs[1][2] = RectangleShape(Vector2f(80, 400-t)); obs[1][2].setPosition(Vector2f(820, 200+t));   
        }
        for(int i = 0;i<6;i++){
            obs[i%2][i%3].move(Vector2f(-dt*100,0));
        }
        if(obs[0][0].getPosition().x < 120 && obs[0][0].getPosition().x > 20 && (bird.getPosition().y -20 < obs[0][0].getLocalBounds().height ||  bird.getPosition().y + 20 > obs[1][0].getPosition().y )){
            w.close();
            return 0;
        }
        clock.restart();
        sleep(seconds(1/30.f));
        w.clear();
        for(int i = 0;i<6;i++){
            w.draw(obs[i%2][i%3]);
        }
        w.draw(bird);
        w.display();
    }
    return 0;
}