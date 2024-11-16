#define WIDTH 200
#define HEIGHT 100

class Scene{
public:
	char canvasBuffer[WIDTH * HEIGHT];
	char cchar;
	int width;
	int height;

	Scene(int, int);

	void fill(char);
	void paint();
	void clear();
};