#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <vector>
#include <string>
#include "Line.hpp"
#include <cmath>
#include "Editor.hpp"
#include "Object.hpp"
#include <fstream>

const float cell_side = 80.;

int main()
{
    int CELL = (int)cell_side;
    int WIDTH = 35 * CELL, HEIGHT = 22 * CELL;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Level Editor", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);
    sf::Event evnt;

    Editor editor(window, evnt);

    sf::Music soundtrack;
    soundtrack.openFromFile("editor_music.ogg");
    soundtrack.setLoop(true);
    soundtrack.setVolume(50);
    soundtrack.play();

    while (window.isOpen())
    {
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();

            case sf::Event::KeyPressed:
                if (evnt.key.code == sf::Keyboard::Tab)
                {
                    window.close();
                    editor.save();
                }
            }
        }

        window.clear(sf::Color(201, 220, 255));

        editor.update();

        window.display();
    }
}