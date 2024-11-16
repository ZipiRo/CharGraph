#include <ctime>
#include <cstring>
#include <cstdlib>
#include <CharGraph.h>

class Player{
public:
    int score = 0;
    int lives = 3;

    Player(int x, int boardSize, char boardChar){
        this->x = x;
        this->boardSize = boardSize;
        this->boardChar = boardChar;
        board = Line(Vector2D(x, 3), Vector2D(x, boardSize + 2), boardChar);
    }

    void setYPosition(int y){
        this->board.origin.y += y;
        this->board.range.y += y;
    }

    int getYTopPosition(){ return this->board.origin.y; }
    int getYBottomPosition(){ return this->board.range.y; }
    int getXPosition(){ return this->board.origin.x; }

    void draw(Scene& scene){
        this->board.draw(scene);
    }

    void bounderies(int top, int bottom){
        if(this->board.origin.y <= top)
            this->setYPosition(1);
        if(this->board.origin.y > bottom - this->boardSize)
            this->setYPosition(-1);
    }
private:
    Line board;
    char boardChar;
    int x;
    int boardSize;
};

class Ball{
public:
    Vector2D Velocity;
    float velocity = 1.5;

    Ball(Vector2D position, char ballChar){
        this->ballChar = ballChar;
        ball = Point(position, ballChar);
    }

    void setPosition(Vector2D position){
        this->ball.position = position;
    }

    Vector2D getPosition(){ return this->ball.position; }

    void draw(Scene& scene){
        ball.draw(scene);
    }
private:
    Point ball;
    char ballChar;
};

Scene Canvas = Scene(70, 23);
Input KeyInput;
time_t TICK;

Rectangle border(Vector2D(0, 0), Vector2D(Canvas.width - 1, Canvas.height), '#');
Line line(Vector2D(Canvas.width / 2, 0), Vector2D(Canvas.width / 2, Canvas.height) , '|');

Text UIText(Zero, ' ');
char player1Lives[5] = "LLL\0";
char player2Lives[5] = "LLL\0";

Player player1(2, 4, ')');
Player player2(Canvas.width - 5, 4, '(');

Ball ball(Vector2D(Canvas.width, Canvas.height) / 2, 'O');

bool running = true;
bool pause = false;

bool serve = true;

float tick = 0.1f;
float utime = 0;

void Draw();

void MatchFinished(char*, char*);

int main(){
    time_t StartTICK = time(0);
    time_t PastTICK = StartTICK;
    ball.Velocity = Zero;

    while (running){
        pause ? tick = 0 : tick = 0.1f;

		TICK = time(0) - PastTICK;
        if(TICK <= 1){
            utime += tick;
        }else{
            TICK = 0;
            PastTICK = time(0);
        }

        if(utime >= 100){
            Draw();
            
            // Match Decisions
            if(player1.lives <= 0 && player1.score < player2.score) {
                MatchFinished("Player1: LOST", "Player2: WON");
                pause = 1; 
            }else if(player1.lives <= 0 && player1.score > player2.score){
                MatchFinished("Player2: LOST", "Player1: WON");
                pause = 1; 
            }
            if(player2.lives <= 0 && player2.score < player1.score) {
                MatchFinished("Player2: LOST", "Player1: WON");
                pause = 1; 
            }else if(player2.lives <= 0 && player2.score > player1.score){
                MatchFinished("Player1: LOST", "Player2: WON");
                pause = 1; 
            }

            //Out
            if(ball.getPosition().x <= 0){
                serve = 1;
                ball.Velocity = Zero;
                ball.velocity = 1;
                ball.setPosition(Vector2D(Canvas.width, Canvas.height) / 2);
                player2.score += 3;
                player1Lives[--player1.lives] = '\0';
            }

            if(ball.getPosition().x >= Canvas.width){
                serve = 1;
                ball.Velocity = Zero;
                ball.velocity = -1;
                ball.setPosition(Vector2D(Canvas.width, Canvas.height) / 2);
                player1.score += 3;
                player2Lives[--player2.lives] = '\0';
            }

            // Physics
            if(ball.getPosition().y <= 2){
                ball.Velocity = multiply(Vector2D(1, -1), ball.Velocity);
            }
            if(ball.getPosition().y >= Canvas.height - 2){
                ball.Velocity = multiply(Vector2D(1, -1), ball.Velocity);
            }
            if((ball.getPosition().x <= player1.getXPosition() + 1 && ball.getPosition().x >= player1.getXPosition()) && 
                (ball.getPosition().y <= player1.getYBottomPosition() + 1 && ball.getPosition().y >= player1.getYTopPosition() - 1)){
                    ball.Velocity = multiply(Vector2D(-1, 1), ball.Velocity);
                    player1.score++;
            }
            if((ball.getPosition().x >= player2.getXPosition() - 1 && ball.getPosition().x <= player2.getXPosition()) && 
                (ball.getPosition().y <= player2.getYBottomPosition() + 1 && ball.getPosition().y >= player2.getYTopPosition() - 1)){
                    ball.Velocity = multiply(Vector2D(-1, 1), ball.Velocity);
                    player2.score++;
            }

            ball.setPosition(ball.getPosition() + ball.Velocity);

            utime = 0;
        }

        KeyInput.event();
        if(KeyInput.keyPressed(Key::ESCAPE))
            pause = !pause;

        if(!pause){    
            if(serve){
                if(KeyInput.keyPressed(Key::SPACE)){
                    ball.Velocity = Vector2D(ball.velocity, 1);
                    serve = false;
                }
            }

            if(KeyInput.keyPressed('w'))
                player1.setYPosition(-2);
            else if(KeyInput.keyPressed('s'))
                player1.setYPosition(2);
            
            if(KeyInput.keyPressed(Key::ARROW_UP))
                player2.setYPosition(-2);
            else if(KeyInput.keyPressed((Key::ARROW_DOWN))){
                player2.setYPosition(2);
            }

            player1.bounderies(0, Canvas.height - 1);
            player2.bounderies(0, Canvas.height - 1);
        }
    }
    
    return 0;
}

void MatchFinished(char* loser, char* winner){
    Canvas.clear();

    border.draw(Canvas);

    UIText.position = Vector2D(Canvas.width / 2 - 14 / 2, 4);
    UIText.set("Match Finished");
    UIText.draw(Canvas);

    UIText.position = Vector2D(Canvas.width / 2 - strlen(winner) / 2 - 1, 6);
    UIText.set(winner);
    UIText.draw(Canvas);

    UIText.position = Vector2D(Canvas.width / 2 - strlen(loser) / 2 - 1, 8);
    UIText.set(loser);
    UIText.draw(Canvas);

    char scoreP1T[10];
    char textP1[50] = "Player1 Score: ";
    strcat(textP1, itoa(player1.score, scoreP1T, 10));
    
    UIText.position = Vector2D(Canvas.width / 2 / 2 - strlen(textP1) / 2 + 1, Canvas.height / 2 + 5);
    UIText.set(textP1);
    UIText.draw(Canvas);


    char scoreP2T[10];
    char textP2[50] = "Player2 Score: ";
    strcat(textP2, itoa(player2.score, scoreP1T, 10));

    UIText.position = Vector2D((Canvas.width / 2) + (Canvas.width / 4) - strlen(textP2) / 2, Canvas.height / 2 + 5);
    UIText.set(textP2);
    UIText.draw(Canvas);

    Canvas.paint();
}

void Draw(){
    Canvas.clear();

    line.draw(Canvas);
    border.draw(Canvas);
    player1.draw(Canvas);
    player2.draw(Canvas);
    ball.draw(Canvas);

    UIText.position = Vector2D(3, 0);
    UIText.set(player1Lives);
    UIText.draw(Canvas);

    UIText.position = Vector2D(Canvas.width - 3 - 2, 0);
    UIText.set(player2Lives);
    UIText.draw(Canvas);

    UIText.position = Vector2D(Canvas.width / 2 - 2, 3);
    UIText.set(player1.score);
    UIText.draw(Canvas);

    UIText.position = Vector2D(Canvas.width / 2 + 4, 3);
    UIText.set(player2.score);
    UIText.draw(Canvas);

    Canvas.paint();
}