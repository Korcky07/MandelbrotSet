#include "ComplexPlane.h"
#include <iostream>
#include <cmath> //maybe remove later if zoom in/out doesn't use exponents
#include <sstream>
#include <iomanip>
#include <complex>

using namespace sf;
ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_pixel_size = Vector2f(pixelWidth, pixelHeight);
	m_aspectRatio = pixelHeight / float(pixelWidth);
	m_plane_center = Vector2f(0, 0);
	m_plane_size = Vector2f(BASE_WIDTH, BASE_HEIGHT * m_aspectRatio);
	std::cout << m_plane_size.x << " ";
	std::cout << m_plane_size.y;
	m_state = State::CALCULATING;
	m_vArray = VertexArray(Points, pixelWidth * pixelHeight);
	m_mouseLocation = Vector2f(0, 0);
	m_zoomCount = 0;
	int x = MAX_ITER / 5;

	for (int i = 1; i < 5; i++)
	{
		regions.push_back(x * i);
	}
	for (int j = 1; j < 3; j++)
	{
		subregions.push_back((x / 3) * j);
	}
}

void ComplexPlane::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_vArray, states);
}
void ComplexPlane::updateRender()
{
	if (m_state == State::CALCULATING)
	{
		int rows = 0;
		int threadLimit = std::thread::hardware_concurrency();
		if (threadLimit < 10)
		{
			threadLimit = 10;
		}
		while (rows < m_pixel_size.y)
		{
			for (int y = 0; y < threadLimit && rows < m_pixel_size.y; y++)
			{
				std::thread* t = new std::thread(&ComplexPlane::updateRenderHelper, this, rows);
				threads.push_back(t);
				rows++;
			}
		}	
		for (int i = 0; i < threadLimit; i++)
		{
			threads.at(i)->join();
			delete threads.at(i);
		}
		threads.clear();
		m_state = DISPLAYING;
	}
}
/*void ComplexPlane::updateRender()
{
	if (m_state == State::CALCULATING)
	{
		for (int y = 0; y < m_pixel_size.y; y++)
		{
			for (int x = 0; x < m_pixel_size.x; x++)
			{
				size_t index = x + y * m_pixel_size.x;
				m_vArray[index].position = Vector2f(float(x), float(y));
				Vector2f coord = mapPixelToCoords(Vector2i(x, y));
				size_t iterations = countIterations(coord);
				Color color;
				iterationsToRGB(iterations, color.r, color.g, color.b);
				m_vArray[index].color = color;
			}
		}
		m_state = DISPLAYING;
	}
}*/
void ComplexPlane::updateRenderHelper(int y)
{
	for (int x = 0; x < m_pixel_size.x; x++)
	{
		size_t index = x + y * m_pixel_size.x;
		m_vArray[index].position = Vector2f(float(x), float(y));
		Vector2f coord = mapPixelToCoords(Vector2i(x, y));
		size_t iterations = countIterations(coord);
		Color color;
		iterationsToRGB(iterations, color.r, color.g, color.b);
		m_vArray[index].color = color;
	}
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	m_plane_size.x = BASE_WIDTH * std::pow(BASE_ZOOM, m_zoomCount);
	m_plane_size.y = BASE_HEIGHT * m_aspectRatio * std::pow(BASE_ZOOM, m_zoomCount);
	m_state = State::CALCULATING;
}
void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	m_plane_size.x = BASE_WIDTH * std::pow(BASE_ZOOM, m_zoomCount);
	m_plane_size.y = BASE_HEIGHT * m_aspectRatio * std::pow(BASE_ZOOM, m_zoomCount);
	m_state = State::CALCULATING;
}
void ComplexPlane::setCenter(sf::Vector2i mousePixel)
{
	m_plane_center = mapPixelToCoords(mousePixel);

	m_state = CALCULATING;
}
void ComplexPlane::setMouseLocation(sf::Vector2i mousePixel)
{
	m_mouseLocation = mapPixelToCoords(mousePixel);
}
void ComplexPlane::loadText(sf::Text& text)
{

	std::ostringstream strmOut;

	strmOut << "Mandelbrot Set" << std::endl << 
		"Center: (" << std::fixed << std::setprecision(5) << m_plane_center.x << ", " << m_plane_center.y << ")" << std::endl <<
		"Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")" << std::endl <<
		"Left-Click to Zoom In" << std::endl <<
		"Right-Click to Zoom Out";

	text.setPosition(0, 0);
	text.setString(strmOut.str());

}

size_t ComplexPlane::countIterations(sf::Vector2f coord)
{
	std::complex<double> c(coord.x,coord.y);
	std::complex<double> z(0,0);

	for (int i = 1; i < MAX_ITER; i++)
	{
		z = z * z + c;
		if (abs(z) > 2)
		{
			return i;
		}
	}
	return MAX_ITER;
}
void ComplexPlane::iterationsToRGB(size_t count, sf::Uint8& r, sf::Uint8& g, sf::Uint8& b)
{
	/* std::vector<int> regions;
	std::vector<int> subregions;
	int x = MAX_ITER / 5;

	for (int i = 1; i < 5; i++)
	{
		regions.push_back(x * i);
	}
	for (int j = 1; j < 3; j++)
	{
		subregions.push_back((x / 3) * j);
	}*/
	if (count == MAX_ITER)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	else if (count >= regions.at(3))
	{
		r = 251;
		g = 249;
		b = 204;
	}
	else if (count >= regions.at(2))
	{
		r = 204;
		g = 251;
		b = 209;
	}
	else if (count >= regions.at(1))
	{
		r = 204;
		g = 244;
		b = 251;
	}
	else if (count >= regions.at(0))
	{
		r = 233;
		g = 204;
		b = 251;
	}
	else
	{
		if (count >= subregions.at(1))
		{
			r = 251;
			g = 204;
			b = 215;
		}
		else if (count >= subregions.at(0))
		{
			r = 225;
			g = 138;
			b = 158;
		}
		else
		{
			r = 222;
			g = 87;
			b = 118;
		}
		

	}
}
sf::Vector2f ComplexPlane::mapPixelToCoords(sf::Vector2i mousePixel)
{
	Vector2f result;
	result.x = (mousePixel.x / m_pixel_size.x) * m_plane_size.x + (m_plane_center.x - m_plane_size.x / 2.0);
	result.y = ((m_pixel_size.y - mousePixel.y) / m_pixel_size.y) * m_plane_size.y + (m_plane_center.y - m_plane_size.y / 2.0);
	return result;
}