class Rectangle : public Shape{
public:
	Rectangle();
	Rectangle(Vector2D, Vector2D);
	Rectangle(Vector2D, Vector2D, char);

	void draw(Scene&) override;
};