#ifndef pong_hpp
#define pong_hpp

#include <SFML/Graphics.hpp>


using namespace sf;

    

void pong()
{       

    

    RenderWindow window(VideoMode(600, 480), "PONG");
    window.setFramerateLimit(60);

    auto image = sf::Image{};
    if (!image.loadFromFile("Assets/pong_logo.jfif"))
    {
    // Error handling...
    }

    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());


    Font font; font.loadFromFile("Assets/Warzone.ttf");
    Text text("COMING SOON :D", font, 50);
    text.setFillColor(Color(253,130,6));
    text.setPosition(40,200);

    while(window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if(e.type== Event::Closed)
            window.close();
        }
        
        window.clear();
        window.draw(text);
        window.display();
    }

}
    
    
    


#endif