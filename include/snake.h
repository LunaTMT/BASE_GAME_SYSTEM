#include <SFML/Graphics.hpp>

struct SnakeSegment {
    SnakeSegment(int x, int y) : position(x, y){}
    sf::Vector2i position;
};


enum Direction {
    None, UP, LEFT, RIGHT, DOWN
};

class Snake {
public:

    Snake();
    ~Snake();
    
    Direction    GetDirection();
    int          GetSpeed();
    int          GetLives();
    int          GetScore();
    sf::Vector2i GetPosition();


    void IncreaseScore();
    bool HasLost();

    void Lose();
    void ToggleLose();


    void SetDirection(Direction l_dir);


private:
    using SnakeContainer = std::vector<SnakeSegment>;

};


