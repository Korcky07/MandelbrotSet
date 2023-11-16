#include <iostream> 
#include <complex> 
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int main()
{
	int pixelWidth = VideoMode::getDesktopMode().width / 2;
	int pixelHeight = VideoMode::getDesktopMode().height / 2;

	VideoMode vm(pixelWidth, pixelHeight);

	RenderWindow window(vm, "Mandelbrot", Style::Default);

	ComplexPlane plane(pixelWidth, pixelHeight);

    Font font;
    if (!font.loadFromFile("ComicSans.ttf"))
    {
        throw runtime_error("Could not open file");
    }

    Text text;

    text.setPosition(529, 127);

    text.setString("Hello! Welcome to the Mandelbrot! Press anywhere on the screen to start!");

    text.setCharacterSize(35);
    text.setFillColor(sf::Color::White);
    text.setFont(font);

	bool updateLeft = true;
	bool updateRight = true;

	while (window.isOpen())
	{

		/*
		****************************************
		Handle the players input
		****************************************
		*/

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					cout << "the left button was pressed" << std::endl;
					cout << "mouse x: " << event.mouseButton.x << std::endl;
					cout << "mouse y: " << event.mouseButton.y << std::endl;



					updateLeft = true;
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					cout << "the left button was pressed" << std::endl;
					cout << "mouse x: " << event.mouseButton.x << std::endl;
					cout << "mouse y: " << event.mouseButton.y << std::endl;



					updateRight = true;
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*
		****************************************
		Update the scene
		****************************************
		*/
		if (updateLeft)
		{
			zoomOut();


		}

		/*
		****************************************
		Draw the scene
		****************************************
		*/

		window.clear();
		
		window.display();
	}


}