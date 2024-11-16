namespace Key{
    const int ESCAPE = 27;
    const int ARROW_UP = 72;
    const int ARROW_DOWN = 80;
    const int ARROW_RIGHT = 77;
    const int ARROW_LEFT = 75;
    const int ENTER = 13;
    const int SHIFT = 16;
    const int CTRL = 17;
    const int TAB = 9;
    const int CAPSLOCK = 20;
    const int SPACE = 32;
    const int DELETE = 46;
}

class Input{
public:
    Input();

    void event();
    bool anykey();
    bool keyPressed(int);
    int get_curentkey();
private:
    int curentKey;
};