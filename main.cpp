#include <SFML/Graphics.hpp>
#include <time.h> //Libreria utilizada para el spanwpoint de los jugadores

const int w = 600;
const int h = 480;

#include "menu.hpp"
#include "tron.hpp"
#include "pong.hpp"


using namespace sf;

int main()
{

    Font font; font.loadFromFile("Warzone.ttf");
    Text t("T", font, 100);
    t.setFillColor(Color::Cyan);
    t.setPosition(450, 15);

    Text r("R", font, 100);
    r.setFillColor(Color::Cyan);
    r.setPosition(450, 140);

    Text o("O", font, 100);
    o.setFillColor(Color::Cyan);
    o.setPosition(450-20, 260);

    Text n("N", font, 100);
    n.setFillColor(Color::Cyan);
    n.setPosition(450, 370);

    Text p("P", font, 100);
    p.setFillColor(Color::White);
    p.setPosition(50, 15);

    Text O("o", font, 100);
    O.setFillColor(Color::White);
    O.setPosition(50-20, 140);

    Text N("N", font, 100);
    N.setFillColor(Color::White);
    N.setPosition(50, 260);

    Text g("g", font, 100);
    g.setFillColor(Color::White);
    g.setPosition(50-20, 370);

    RenderWindow window(VideoMode(w, h), "2 IN 1 VIDEOGAME");

    auto image = sf::Image{};
    if (!image.loadFromFile("laformula.jfif"))
    {
    // Error handling...
    }

    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

    Menu menu(window.getSize().x, window.getSize().y);

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {

            case Event::KeyReleased:
                switch (event.key.code)
                {
                case Keyboard::Up:
                    menu.moveUp();
                    break;
                case Keyboard::Down:
                    menu.moveDown();
                    break;

                case Keyboard::Return:
                    switch (menu.getPressedItem())
                    {
                    case 0:
                        window.clear();

                        juego();
                        break;
                    case 1:
                        pong();
                        break;
                    case 2:
                        window.close();
                    }

                    break;
                }

                break;
            case Event::Closed:
                window.close();
                break;
            }
        }

        window.clear();
        window.draw(t);
        window.draw(r);
        window.draw(o);
        window.draw(n);
        window.draw(p);
        window.draw(O);
        window.draw(N);
        window.draw(g);
        menu.draw(window);
        window.display();
    }

    return 0;
}

