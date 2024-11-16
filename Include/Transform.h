class Transform{
public:
    Transform();

    void setPosition(Vector2D);
    void setScale(Vector2D);
    void setPivot(Vector2D);

    Vector2D getPosition();
    Vector2D getScale();
    Vector2D getPivot();
private:
    Vector2D position;
    Vector2D scale;
    Vector2D pivot;
};
