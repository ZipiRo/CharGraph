class Point{
public:
	Vector2D position;
	char cchar;

	Point();
	Point(Vector2D, char);

	void draw(Scene&);
};