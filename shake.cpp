#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>
#include <vector>
using namespace std;

Color purple = { 138, 43, 226, 255 };
Color darkpur = { 75, 0, 130, 255 };

int cellsize = 35;
int cellCount = 15;
double lastUpdateTime = 0;

double Elementindeque(Vector2 element, deque<Vector2> deque)
{
    for (unsigned i = 0; i < deque.size(); i++)
    {
        if (Vector2Equals(deque[i], element))
        {
            return true;
        }
    }
    return false;
}

bool eventTriggered(double interval)
{
    double currenTime = GetTime();
    if (currenTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currenTime;
        return true;
    }
    return false;

}

class Snake
{
public:
    deque<Vector2> body = { Vector2{6,9}, Vector2 {5, 9} };
    Vector2 direction = { 1, 0 };
    bool addsnake = false;
    void Draw()
    {
        
      for (unsigned int i = 0; i < body.size(); i++)
        {
            float x = body[i].x;
            float  y = body[i].y;      Rectangle segment = Rectangle{ x * cellsize, y * cellsize, (float)cellsize, (float)cellsize };
            DrawRectangleRounded(segment,0.5, 6, darkpur);
            if (i == 0)
            {
                DrawCircle(x * cellsize + cellsize / 3, y * cellsize + cellsize / 3, 3, BLACK);
                DrawCircle(x * cellsize + 2 * cellsize / 3, y * cellsize + cellsize / 3, 3, BLACK);
            }



        }
    }
    void Update()
    {
        if (addsnake == true)
        {
            body.push_front(Vector2Add(body[0], direction));
            addsnake = false;
        }
        else
        {
            body.pop_back();
            body.push_front(Vector2Add(body[0], direction));
        }
    }
    void Reset()
    {
        body = { Vector2{6,9}, Vector2{5, 9} };
        direction = { 1, 0 };
    }
};
class Food {
public:
    Vector2 position;
    std::vector<Texture2D> textures;
    int currentFruitIndex = 0;

    Food(deque<Vector2> snakeBody) {
        Image image1 = LoadImage("assets/fruit.png");
        textures.push_back(LoadTextureFromImage(image1));
        UnloadImage(image1);

        Image image2 = LoadImage("assets/fruit2.png");
        textures.push_back(LoadTextureFromImage(image2));
        UnloadImage(image2);

        Image image3 = LoadImage("assets/fruit3.png");
        textures.push_back(LoadTextureFromImage(image3));
        UnloadImage(image3);

        position = GenerateRandomPos(snakeBody);
    }
    ~Food()
    {
        for (auto& texture : textures) {
            UnloadTexture(texture);
        }
    }
    void Draw()
    {
        DrawTexture(textures[currentFruitIndex], position.x * cellsize, position.y * cellsize, WHITE);
    }
    Vector2 GenerateRandomPos(deque<Vector2> snakeBody)
    {
        Vector2 position;
        do {
            position.x = GetRandomValue(0, cellCount - 1);
            position.y = GetRandomValue(0, cellCount - 1);
        } while (Elementindeque(position, snakeBody));
        return position;
    }
    void NextFruit() {
        currentFruitIndex = (currentFruitIndex + 1) % 3;
    }
};

class Game
{
public:
    Snake snake = Snake();
    Food food = Food(snake.body);
    bool running = true;
    int score = 0;

    void DrawGrid()
    {
        for (int i = 0; i < cellCount; i++)
        {
            for (int j = 0; j < cellCount; j++)
            {
                Color gridColor = { 148, 93, 226, 100 }; 
                DrawRectangleLines(i * cellsize, j * cellsize, cellsize, cellsize, gridColor);
            }
        }
    }

    void Draw()
    {
        food.Draw();
        snake.Draw();
    }
    void Update()
    { 
        if (running)
        {
            snake.Update();
            eat();
            Check();
            headtail();
        }
        
    }
    void eat()
    {
        if (Vector2Equals(snake.body[0], food.position))
        {
            food.position = food.GenerateRandomPos(snake.body);
            snake.addsnake = true;
            score ++;
            food.NextFruit();
        }
    }
    void Check()
    {
        if (snake.body[0].x >= cellCount)
        {
            snake.body[0].x = 0;
        }
        else if (snake.body[0].x < 0)
        {
            snake.body[0].x = cellCount - 1;
        }
        if (snake.body[0].y >= cellCount)
        {
            snake.body[0].y = 0;
        }
        else if (snake.body[0].y < 0)
        {
            snake.body[0].y = cellCount - 1;
        }
    
    }
    void headtail()
    {
        deque<Vector2> headlesBody = snake.body;
        headlesBody.pop_front();
        if (Elementindeque(snake.body[0], headlesBody))
        {
            snake.Reset();
            food.position = food.GenerateRandomPos(snake.body);
            running = false;
            score = 0;
        }
    }
 
    
};
int main() { 
    InitWindow(cellsize * cellCount, cellsize * cellCount, "SNAKE");
    SetTargetFPS(60);
    Game game = Game();
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        if (eventTriggered(0.2))
        {
            game.Update();
        }
        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1)
        {
            game.snake.direction = { 0, -1 };
            game.running = true;
        }
        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1 )
        {
            game.snake.direction = { 0, 1 };
            game.running = true;
        }
        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1)
        {
            game.snake.direction = { -1, 0 };
            game.running = true;
        }
        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1)
        {
            game.snake.direction = { 1, 0 };
            game.running = true;
        }
 

        ClearBackground(purple);
        game.DrawGrid();
        game.Draw();
        DrawText("Shake snake", 5, 26, 35, darkpur);
        DrawText(TextFormat("%i", game.score), 480, 26, 35, darkpur);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}