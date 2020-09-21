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
	int amountOfPoints=0;
	sf::Vector2f m_start;
	sf::Vector2f m_finish;
	sf::Vector2f* m_Points= nullptr;
	sf::ConvexShape semic;//создается своя фигура
	sf::Vertex* m_Line=new sf::Vertex[2];
	Line() :TOCHKA(0, 0) {}
	Line(sf::Vector2f Start, sf::Vector2f Finish, int Quality = 100) : TOCHKA(0, 0), amountOfPoints(Quality),m_start(Start),m_finish(Finish)
	{
		delete m_Points;
		m_Points = new sf::Vector2f[amountOfPoints];
		sf::Vector2f Length = Finish - Start;
		sf::Vector2f step =sf::Vector2f (Length.x/ amountOfPoints, Length.y / amountOfPoints);
		m_Points[0] = Start;
		for (int i = 1; i < amountOfPoints; i++)
		{
			m_Points[i]  =m_Points[i-1]+step;
		}

		m_Line[0] = sf::Vertex(m_Points[0]);
		m_Line[1] = sf::Vertex(m_Points[amountOfPoints-1]);

	
	}
};

class Figure : public TOCHKA {
public:
	float m_width, m_height;
	sf::ConvexShape m_shape;
	sf::Vector2f* m_points = nullptr;
	int m_amountOfPoints = 0;

	Figure(float n_Width, float n_Height) : TOCHKA(0,0),m_width(n_Width),m_height(n_Height)
	{
		
	}
	

};
class Triangle :public Figure
{

public:
	sf::ConvexShape m_shape;
	Triangle(Line* Lines):Figure(0,0)
	{
		m_amountOfPoints = Lines->amountOfPoints * 3;
		delete[] m_points;
		m_points = new sf::Vector2f[m_amountOfPoints];
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 100; j++)
				m_points[i * 100 + j] = Lines[i].m_Points[j];
		}
		m_shape.setPointCount(m_amountOfPoints);
		for (int i = 0; i < m_amountOfPoints; i++)
			m_shape.setPoint(i, m_points[i]);
		
	}

};

class SemiCircle: public Figure
{
	public:
	float b, a;
	SemiCircle(float A, float X, float Y, float B) : Figure(0,0) {
		a = A;
		b = B;
		m_amountOfPoints = 181;
		m_shape.setPointCount(m_amountOfPoints);
		for (int i = 0; i < m_amountOfPoints; i++)
		{
			m_shape.setPoint(i, sf::Vector2f(a * cos(M_PI / 180.0 * i), -a * sin(M_PI / 180.0 * i))); //формула полукруга
		}
		m_shape.setFillColor(sf::Color::Red);
		m_shape.setOrigin(-a/2,-a/2);

	}
	void move(sf::Vector2f newpos)
	{
		m_shape.setPosition(newpos);
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Semic and triangle");
	window.setFramerateLimit(60);
	
	
	SemiCircle MySemic(100, 300, 500, 25);
	MySemic.m_shape.setPosition(0,0);

	Line* TriangleLines = new Line[3];
	TriangleLines[0] = Line(sf::Vector2f(100, 200), sf::Vector2f(100, 300));
	TriangleLines[1] = Line(sf::Vector2f(100, 300), sf::Vector2f(500, 200));
	TriangleLines[2] = Line(sf::Vector2f(500, 200), sf::Vector2f(100, 200));
	Triangle MyTriangle(TriangleLines);
	int count = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//update
		MySemic.move(MyTriangle.m_points[count]);
		if (count == MyTriangle.m_amountOfPoints)		count = 0;
		else											count++;


		//clear
		window.clear();
		
		
		//draw
		
		//for (int i = 0; i < 3; i++)
			//window.draw(TriangleLines[i].m_Line, 2, sf::Lines);
		//window.draw(MyTriangle.m_shape, sf::RenderStates::Default);
		window.draw(MySemic.m_shape,sf::RenderStates::Default);
		window.display();

	}
	return 0;
}