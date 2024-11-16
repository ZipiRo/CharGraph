#include <ctime>
#include <random>
#include <cstring>
#include <CharGraph.h>

class Part{
public:
    Point point;

    Part(){
        this->point = Point(Zero, '*');
    }
};

time_t gameTime;
Scene scene(30, 20);
Input input;

bool running = true;
bool gameRunning = false;
bool pause = false;
bool dead = false;
float tick = 0.1;
int table[31 * 21];

Rectangle border(Vector2D(0, 0), Vector2D(scene.width - 1, scene.height), '#');
Text text;
Point point;

Part snake[500];
Vector2D headPosition(scene.width / 2, scene.height / 2);
Vector2D snakeDirection = Zero;
int snakeLength = 2;
int score = 0;

int RandPoint(int range){
    srand(time(0));
    return rand() % range - 1;
}

void PlacePoint(int type){
    Vector2D randPos(RandPoint(scene.width), RandPoint(scene.height));
    while(table[1 + int(randPos.x) + int(randPos.y) * scene.width])
        randPos = Vector2D(RandPoint(scene.width), RandPoint(scene.height));

    table[1 + int(randPos.x) + int(randPos.y) * scene.width] = type;
}

void HeadColide(){
    if(headPosition.x >= border.transform.getScale().x - 1
    || headPosition.x < 1
    || headPosition.y >= border.transform.getScale().y
    || headPosition.y <= 0){
        dead = true;
    }

    if(snakeDirection.x != 0){
        if(strchr("*%", scene.canvasBuffer[1 + int(headPosition.x + snakeDirection.x) + int(headPosition.y) * scene.width]))
            dead = true;
    }

    if(snakeDirection.y != 0){
        if(strchr("*%", scene.canvasBuffer[1 + int(headPosition.x) + int(headPosition.y + snakeDirection.y) * scene.width]))
            dead = true;
    }
}

void PointColide(){
    if(table[1 + int(headPosition.x) + int(headPosition.y) * scene.width] == 1){
        score++;
        table[1 + int(headPosition.x) + int(headPosition.y) * scene.width] = 0;
        snakeLength++;
    }
    if(table[1 + int(headPosition.x) + int(headPosition.y) * scene.width] == 2){
        score+=3;
        table[1 + int(headPosition.x) + int(headPosition.y) * scene.width] = 0;
        snakeLength+=3;
    }
}

void DrawScoreText(){
    char buffer[100];
    char scoretext[100] = "Score: ";
    itoa(score, buffer, 10);

    strcat(scoretext, buffer);

    text.position = Vector2D(3, 0);
    text.set(scoretext);
    text.draw(scene);
}

void DrawSnake(){
    for (int i = snakeLength - 1; i >= 0; i--){
        if(i % 2 != 0) snake[i].point.cchar = '%';
        snake[i].point.draw(scene);
    }
}

void DrawPoints(){
    for(int i = 2; i < scene.height; i++){
        for(int j = 2; j < scene.width; j++){
            if(table[1 + j + i * scene.width] == 1){
                point = Point(Vector2D(j, i), 'o');
                point.draw(scene);
            }
            if(table[1 + j + i * scene.width] == 2){
                point = Point(Vector2D(j, i), 'O');
                point.draw(scene);
            }
        }
    }
}

void GameLogic(){
    HeadColide();
    PointColide();

    headPosition += snakeDirection;

    snake[0].point.position = headPosition;
    for (int i = snakeLength - 1; i >= 1; i--)
        snake[i].point.position = snake[i - 1].point.position;
}

void GameDraw(){
    scene.clear();

    DrawPoints();
    DrawSnake();
    border.draw(scene);
    DrawScoreText();

    scene.paint();
}

void DeathScreen(){
    char buffer[30];
    char scoretext[30] = "Score: ";
    char deathtext[10] = "You Suck";

    itoa(score, buffer, 10);

    scene.clear();

    text.set(deathtext);
    text.position = Vector2D(scene.width / 2 - strlen(deathtext) / 2, scene.height / 2 - 2);
    text.draw(scene);
    strcat(scoretext, buffer);
    text.set(scoretext);
    text.position = Vector2D(scene.width / 2 - strlen(scoretext) / 2, scene.height / 2);
    text.draw(scene);

    border.draw(scene);

    scene.paint();
}

int main(void){
	time_t startTime = time(0);
	time_t pastTime = startTime;
	float utime = 0, ptime = 0, pptime = 0, dtime = 0;

    for(int i = 0; i < 250; i++)
        snake[i] = Part();

    snake[0].point.cchar = '@';

    for(int i = 1; i < snakeLength; i++)
        snake[i] = Part();

    while (running){
        pause ? tick = 0 : tick = 0.1;

		gameTime = time(0) - pastTime;
		if(gameTime != 1){
			utime += tick;
            if(gameRunning){
                ptime += tick;
                pptime += tick;
            }
		}
        else{
			gameTime = 0;
			pastTime = time(0);
		}

        if(ptime >= 4000){
            PlacePoint(1);
            ptime = 0;
        }
        if(pptime >= 50000){
            PlacePoint(2);
            pptime = 0;
        }

        if(utime >= 400){
            if(!dead){
                GameLogic();
                GameDraw();
            }else{
                DeathScreen();
                if(dtime == 1)
                    pause = 1;
                dtime++;
            }

            utime = 0;
        }


        input.event();
        if(dead)
            if(input.keyPressed(Key::ESCAPE))
                running = 0;

        if(input.keyPressed(Key::ESCAPE))
            pause = !pause;

        if(!gameRunning);
            if(input.keyPressed(Key::ARROW_UP) || input.keyPressed(Key::ARROW_DOWN) || input.keyPressed(Key::ARROW_LEFT) || input.keyPressed(Key::ARROW_RIGHT))
                gameRunning = true;


        if(input.keyPressed(Key::ARROW_LEFT))
            if(snakeDirection.x != 1){
                snakeDirection = Left;
            }

        if(input.keyPressed(Key::ARROW_RIGHT))
            if(snakeDirection.x != -1){
                snakeDirection = Right;
            }

        if(input.keyPressed(Key::ARROW_UP))
            if(snakeDirection.y != 1){
                snakeDirection = Up;
            }

        if(input.keyPressed(Key::ARROW_DOWN))
            if(snakeDirection.y != -1){
                snakeDirection = Down;
            }
    }

    return 0;
}