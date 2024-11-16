#include <ctime>
#include <CharGraph.h>

time_t TICK;
Scene Canvas = Scene(60, 40);
Input KeyInput;

int scale = 20;
Rectangle border = Rectangle(Vector2D(Canvas.width / 2 - 40 / 2, Canvas.height / 2 - scale / 2), Vector2D(40, scale), '#');
Line line1 = Line(border.transform.getPosition() + Vector2D(4, 4), border.transform.getPosition() + Vector2D(4, 15), 'O');
Line line2 = Line(border.transform.getPosition() + Vector2D(17, 4), border.transform.getPosition() + Vector2D(17, 15), 'O');
Line line3 = Line(border.transform.getPosition() + Vector2D(11, 6), border.transform.getPosition() + Vector2D(18, 6), 'O');
Point point[10000];
int lenP = 1;

bool running = true;
bool startAlgorithm = false;
bool pauseAlgorithm = false;

float tick = 0.1f;
float utime = 0;

Vector2D start(Canvas.width / 2, Canvas.height / 2);
Vector2D queue[10000];
int front = 0, rear = 1;

void LeeFloodFill(Vector2D start);

void Draw();

int main(){
    time_t StartTICK = time(0);
    time_t PastTICK = StartTICK;

    queue[rear] = start;

    while (running){
        pauseAlgorithm ? tick = 0 : tick = 0.1f;

		TICK = time(0) - PastTICK;
        if(TICK <= 1){
            utime += tick;
        }else{
            TICK = 0;
            PastTICK = time(0);
        }

        if(utime >= 1){
            if(rear < front) pauseAlgorithm = true; 
            if(startAlgorithm){
                LeeFloodFill(queue[rear]);
                LeeFloodFill(queue[rear]);
                LeeFloodFill(queue[rear]);
                LeeFloodFill(queue[rear]);
                LeeFloodFill(queue[rear]);
                LeeFloodFill(queue[rear]);
                LeeFloodFill(queue[rear]);
            }

            Draw();
            utime = 0;
        }

        KeyInput.event();
        if(KeyInput.keyPressed(Key::ESCAPE))
            pauseAlgorithm = !pauseAlgorithm;

        if(KeyInput.keyPressed(Key::SPACE))
            startAlgorithm = true;
    }
    

    return 0;
}

void LeeFloodFill(Vector2D start){
    Vector2D direction[5] = {Right, Left, Up, Down};

    Vector2D position = queue[front++];

    for(int i = 0; i < 4; i++){
        Vector2D new_position = position + direction[i];

        if(new_position.x > 1 && new_position.x < Canvas.width &&
            new_position.y > 1 && new_position.y < Canvas.height &&
            Canvas.canvasBuffer[1 + int(new_position.x) + int(new_position.y) * Canvas.width]== ' '){
                point[++lenP] = Point(new_position, '*');
                queue[rear++] = new_position;
        }
    }
}

void Draw(){
    Canvas.clear();

    border.draw(Canvas);
    line1.draw(Canvas);
    line2.draw(Canvas);
    line3.draw(Canvas);

    for(int i = 0; i < lenP; i++)
        point[i].draw(Canvas);

    Canvas.paint();
}