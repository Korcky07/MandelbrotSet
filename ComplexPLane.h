#ifndef COMPLEX_PLANE
#define COMPLEX_PLANE

#include <SFML/Graphics.hpp>
const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

enum State { CALCULATING, DISPLAYING };

class ComplexPlane : public sf::Drawable
{
public:

private:
	int m_vArray;
	State m_state;
	sf::Vector2f m_mouseLocation;
	sf::Vector2f m_pixel_size;
	sf::Vector2f m_plane_center;
	sf::Vector2f m_plane_size;
	int m_zoomCount;
	float m_aspectRatio;

};
#endif // !COMPLEX_PLANE
