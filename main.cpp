#include <SFML/Graphics.hpp>
#include <time.h> //Libreria utilizada para el spanwpoint de los jugadores

#define MAX_NUMBER_OF_ITEMS 3

using namespace sf;
// Definicion de resolucion del juego
const int w = 800;
const int h = 600;
// Velocidad de los jugadores
int speed = 3;
// Definicion de area de juego

// Colores de jugadores

Color c1(Color::Cyan);
Color c2(Color::Red);

// Definicion de valores de colores



Color R(Color::Red);
Color B(Color::Blue);
Color G(Color::Green);
Color Y(Color::Yellow);
Color C(Color::Cyan);
Color M(Color::Magenta);
Color W(Color::White);

bool field[w][h] = {0};
// Clase para crear jugadores

class Menu // Clase menu principal
{
public:
    Menu(float w, float h);
    ~Menu();

    void draw(RenderWindow &window);
    void moveUp();
    void moveDown();
    int getPressedItem() { return selectedItemIndex; }

private:
    int selectedItemIndex;
    Font font;
    Text menu[MAX_NUMBER_OF_ITEMS];
};

class player // Clase para jugadores
{
public:
    int x, y, dir;
    Color color;

    player(Color c)
    {
        x = rand() % w;
        y = rand() % h;
        color = c;
        dir = rand() % 4;
    }

    void tick()
    {
        if (dir == 0)
            y += 1;
        if (dir == 1)
            x -= 1;
        if (dir == 2)
            x += 1;
        if (dir == 3)
            y -= 1;

        if (x >= w)
            x = 0;
        if (x < 0)
            x = w - 1;
        if (y >= h)
            y = 0;
        if (y < 0)
            y = h - 1;
    }

    Vector3f getColor()
    {
        return Vector3f(color.r, color.g, color.b);
    }
};

void juego() // Funcion de juego de tron
{
    srand(time(0));
    RenderWindow window(VideoMode(w, h), "TRON");
    window.setFramerateLimit(60); // FPS MAX 60

    Texture texture;
    texture.loadFromFile("background.jpg");
    Sprite sBackground(texture);

    // creacion de jugadores
    player p1(c1), p2(c2);

    Sprite sprite;
    RenderTexture t;
    t.create(w, h);
    t.setSmooth(true);
    sprite.setTexture(t.getTexture());
    t.clear();
    t.draw(sBackground);

    Font font;
    font.loadFromFile("Warzone.ttf");

    Text text("YOU WIN", font, 35);
    text.setPosition(w / 2 - 80, 20);

    bool Game = 1;

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        // Input de jugadores

        // Input p1
        if (Keyboard::isKeyPressed(Keyboard::Left))
            if (p1.dir != 2)
                p1.dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right))
            if (p1.dir != 1)
                p1.dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::Up))
            if (p1.dir != 0)
                p1.dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down))
            if (p1.dir != 3)
                p1.dir = 0;

        // Input p2
        if (Keyboard::isKeyPressed(Keyboard::A))
            if (p2.dir != 2)
                p2.dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::D))
            if (p2.dir != 1)
                p2.dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::W))
            if (p2.dir != 0)
                p2.dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::S))
            if (p2.dir != 3)
                p2.dir = 0;

        if (!Game)
        {
            window.draw(text);
            window.display();
            continue;
        }
        // Instrucciones de colisión
        for (int i = 0; i < speed; i++)
        {
            p1.tick();
            p2.tick();
            if (field[p1.x][p1.y] == 1)
            {
                Game = 0;
                text.setFillColor(p2.color);
            }
            if (field[p2.x][p2.y] == 1)
            {
                Game = 0;
                text.setFillColor(p1.color);
            }
            field[p1.x][p1.y] = 1;
            field[p2.x][p2.y] = 1;

            // Creacion de "sprite" de jugadores
            CircleShape c(3);
            c.setPosition(p1.x, p1.y);
            c.setFillColor(p1.color);
            t.draw(c);
            c.setPosition(p2.x, p2.y);
            c.setFillColor(p2.color);
            t.draw(c);
            t.display();
        }

        // Dibujo del juego //
        window.clear();
        window.draw(sprite);
        window.display();
    }
}

void selectorColor()
{
    
}

int main()
{

    Font font; font.loadFromFile("Warzone.ttf");
    Text t("T", font, 100);
    t.setFillColor(Color::Cyan);
    t.setPosition(600, 40);

    Text r("R", font, 100);
    r.setFillColor(Color::Cyan);
    r.setPosition(600, 160);

    Text o("O", font, 100);
    o.setFillColor(Color::Cyan);
    o.setPosition(590, 280);

    Text n("N", font, 100);
    n.setFillColor(Color::Cyan);
    n.setPosition(600, 400);

    RenderWindow window(VideoMode(w, h), "MAIN MENU");

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
        menu.draw(window);
        window.display();
    }

    return 0;
}

Menu::Menu(float w, float h)
{
    if (!font.loadFromFile("Warzone.ttf"))
    {
        // handle error
    }

    menu[0].setFont(font);
    menu[0].setFillColor(Color::Cyan);
    menu[0].setString("PLAY");
    menu[0].setPosition(Vector2f(w/18, h / (MAX_NUMBER_OF_ITEMS + 1) * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(Color::White);
    menu[1].setString("OPTIONS");
    menu[1].setPosition(Vector2f(w/18, h / (MAX_NUMBER_OF_ITEMS + 1) * 2));

    menu[2].setFont(font);
    menu[2].setFillColor(Color::White);
    menu[2].setString("EXIT");
    menu[2].setPosition(Vector2f(w/18, h / (MAX_NUMBER_OF_ITEMS + 1) * 3));

    selectedItemIndex = 0;
}

Menu::~Menu()
{
}

void Menu::draw(RenderWindow &window)
{

    

    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::moveUp()
{

    if (selectedItemIndex - 1 >= 0)
    {
        menu[selectedItemIndex].setFillColor(Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(Color::Cyan);
    }
}

void Menu::moveDown()
{

    if(selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
    {
        menu[selectedItemIndex].setFillColor(Color:: White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(Color:: Cyan);
    }
}