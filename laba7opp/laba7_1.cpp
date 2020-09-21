// Полукруг по треугольнику
//динамический объект
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <stdio.h>  
#include <iostream> 
#include <math.h>
class TOCHKA
{
public:
	float x, y;
	TOCHKA(float x1, float y1)
	{
		x = x1;
		y = y1;
	}
};

class Line : public TOCHKA {   //класс линия наследует класс точка
public:
	sf::ConvexShape semic;    //создается своя фигура
	Line() :TOCHKA(0, 0) {}
};

class Figure : public Line {
public:
	float b, a;
	Figure(float A, float X, float Y, float B) : Line() {
		x = X;
		y = Y;
		a = A;
		b = B;
		semic.setPointCount(181);
		for (int i = 0; i < 181; i++)
		{
			semic.setPoint(i, sf::Vector2f(a*cos(M_PI / 180.0*i), -a*sin(M_PI / 180.0*i))); //формула полукруга
		}
		semic.setFillColor(sf::Color::Red);
		semic.setOrigin(a / 2, b / 2);
		semic.setPosition(x, y);
	}
	void update() {
		    //ВЫЛЕТАЕТ
		
		x += 1;
		y -= 2;
		semic.setPosition(x, y);

	}

};

class Point : public Line {
public:
	float a, b, dx, dy;

	Point(float X, float Y, float A, float B) : Line() {
		x = X;
		y = Y;
		a = A;
		b = B;
		semic.setOrigin(a, b);
		semic.setPosition(x, y);
	}
};

int main()
{
	float x1, y1;
	sf::RenderWindow window(sf::VideoMode(1000, 600), "Semic and triangle");
	Figure MySemic(100, 300, 500, 25);
	x1 = MySemic.x; y1 = MySemic.y;
	Point **p = new Point*[10000];
	for (int i = 0; i < 10000; ++i)
	{
			    // ДА ТВОЮ МАТЬ
		
		x1 += 1;
		y1 -= 2;
		p[i] = new Point(x1, y1, 2, 2);

	}
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		MySemic.update();
		window.clear();
		for (int i = 0; i < 10000; ++i)
		{
			window.draw(p[i]->semic);
		}
		window.draw(MySemic.semic);
		window.display();

	}
	return 0;
}