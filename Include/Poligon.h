class Poligon : public Shape{
public:
	Poligon();
	Poligon(Vector2D[], int);
	Poligon(Vector2D[], int, char);

	void draw(Scene&) override;
private:
	Vector2D points[1000];
	int sides;
};