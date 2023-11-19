#include "ComplexPlane.h"
#include <iostream>
#include <cmath> //maybe remove later if zoom in/out doesn't use exponents

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
}

void ComplexPlane::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_vArray, states);
}
void ComplexPlane::updateRender()
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

}
void ComplexPlane::setMouseLocation(sf::Vector2i mousePixel)
{

}
void ComplexPlane::loadText(sf::Text& text)
{

}

size_t ComplexPlane::countIterations(sf::Vector2f coord)
{
	return 0;
}
void ComplexPlane::iterationsToRGB(size_t count, sf::Uint8& r, sf::Uint8& g, sf::Uint8& b)
{

}
sf::Vector2f ComplexPlane::mapPixelToCoords(sf::Vector2i mousePixel)
{
	Vector2f result;
	result.x = (mousePixel.x / m_pixel_size.x) * m_pixel_size.x + (m_plane_center.x - m_plane_size.x / 2.0);
	result.y = ((m_pixel_size.y - mousePixel.y) / m_pixel_size.y) * m_pixel_size.y + (m_plane_center.y - m_plane_size.y / 2.0);
	return result;
}