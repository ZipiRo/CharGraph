class Text{
public:
	Vector2D position;

	Text();
	Text(int, int, int);
	Text(Vector2D, int);
	Text(int, int, char*);
	Text(Vector2D, char*);
	
	void draw(Scene&);
	void set(char*);
	void set(int);
private:
	int length;
	char* text;
};