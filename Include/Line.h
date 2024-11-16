class Line{
public: 
	Vector2D origin;
	Vector2D range;
	char cchar;

	Line();
	Line(Vector2D, Vector2D, char);

	void draw(Scene&);
};