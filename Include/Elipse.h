class Elipse : public Shape{
public:
	Elipse();
	Elipse(Vector2D, Vector2D);
	Elipse(Vector2D, Vector2D, char);

	void draw(Scene&) override;
};