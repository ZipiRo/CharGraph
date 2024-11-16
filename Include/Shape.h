class Shape{
public:
    Transform transform;
    char ochar;
    char fchar;

    virtual void draw(Scene&) = 0;
};