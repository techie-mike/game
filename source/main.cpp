

#include "autosimulator.h"

int main()
{
/*
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);

    sf::Texture texture;
    if (!texture.loadFromFile("car.png"))
    {
        abort();
        // error...
    }
    texture.setSmooth (true);

    sf::Sprite sprite;
    sprite.setTexture (texture);
    sprite.setScale(sf::Vector2f(0.5f, 0.5f));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
//        window.draw(shape);
        window.draw (sprite);
        window.display();
    }

*/


//    controller();
    AutosimController sim;
    sim.startProgram();
    return 0;
}
