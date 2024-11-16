#define Up Vector2D(0, -1)
#define Down Vector2D(0, 1)
#define Left Vector2D(-1, 0)
#define Right Vector2D(1, 0)
#define Zero Vector2D(0, 0)

class Vector2D{
public:
    float x;
    float y;
    
    Vector2D();
    Vector2D(float, float);

    Vector2D operator= (Vector2D);
    Vector2D operator + (Vector2D) const;
    Vector2D operator += (Vector2D);
    Vector2D operator - (Vector2D) const;
    Vector2D operator -= (Vector2D);
    Vector2D operator * (float) const;
    Vector2D operator / (float) const;
    bool operator == (Vector2D) const;
};

Vector2D multiply (Vector2D, Vector2D);
Vector2D divide (Vector2D, Vector2D);
Vector2D floorf(Vector2D);
Vector2D fabsf(Vector2D);