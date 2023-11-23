#include <iostream> 
#include <complex> 
#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"
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

    text.setCharacterSize(15);
    text.setFillColor(sf::Color::White);
    text.setFont(font);

	Vector2i mousePixelRight;
	Vector2i mousePixelLeft;
	Vector2i mousePixelLocation;

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
					;
					mousePixelLeft.x = event.mouseButton.x;
					mousePixelLeft.y = event.mouseButton.y;

					plane.setCenter(mousePixelLeft);
					plane.zoomIn();
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					cout << "the right button was pressed" << std::endl;
					cout << "mouse x: " << event.mouseButton.x << std::endl;
					cout << "mouse y: " << event.mouseButton.y << std::endl;

					mousePixelRight.x = event.mouseButton.x;
					mousePixelRight.y = event.mouseButton.y;

					plane.setCenter(mousePixelRight);
					plane.zoomOut();


				}

			}
			if (event.type == sf::Event::MouseMoved)
				{
					mousePixelLocation.x = event.mouseMove.x;
					mousePixelLocation.y = event.mouseMove.y;

					plane.setMouseLocation(mousePixelLocation);
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
		
		
		plane.loadText(text);
		plane.updateRender();


		/*
		****************************************
		Draw the scene
		****************************************
		*/

		window.clear();
		window.draw(plane);
		window.draw(text);
		window.display();
	}


}