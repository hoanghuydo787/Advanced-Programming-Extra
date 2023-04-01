#include "Engine.h"

const int windowHeight = 600;
const int windowWidth = 800;
const int frameRate = 60;

Engine::Engine()
{
    // create the window
    window.create(VideoMode(windowWidth, windowHeight), "Snake game");
    window.setFramerateLimit(frameRate);
    startGame();
}

void Engine::startGame()
{
    directionQueue.clear();
    timeElapsedSinceLastMove = Time::Zero;
    speed = 2;
    snake.resetSnake();
    moveFood();
    currentGameState = GameState::Running;
    baseWall.clear();
    //start the base wall
    int n_x = windowWidth / 20;
    int n_y = windowHeight / 20;
    for (int i = 0; i < n_x; i++)
    {
        baseWall.push_back(WallSection(Vector2f(i * 20, 0)));
        baseWall.push_back(WallSection(Vector2f(i * 20, windowHeight - 20)));
    }
    for (int i = 0; i < n_y; i++)
    {
        baseWall.push_back(WallSection(Vector2f(0, i * 20)));
        baseWall.push_back(WallSection(Vector2f(windowWidth - 20, i * 20)));
    }
}

void Engine::run()
{
    Clock clock;
    // game loop
    // run the program as long as the window is open
    while (window.isOpen())
    {
        if (currentGameState == GameState::GameOver)
        {
            input();
            draw();
            continue;
        }
        if (currentGameState == GameState::Paused)
        {
            input();
            continue;
        }

        Time elapsedTime = clock.restart();
        timeElapsedSinceLastMove += elapsedTime;

        input();
        update();
        draw();
    }
}

void Engine::input()
{
    // check all the window's events that were triggered since the last iteration of the loop
    Event event;
    while (window.pollEvent(event))
    {
        // "close requested" event: we close the window
        if (event.type == Event::Closed)
            window.close();
    }
    if (currentGameState == GameState::GameOver)
    {
        if (event.key.code == Keyboard::Enter)
            startGame();
    }
    switch (event.key.code)
    {
    case Keyboard::Up:
        addDirection(Direction::Up);
        break;
    case Keyboard::Down:
        addDirection(Direction::Down);
        break;
    case Keyboard::Left:
        addDirection(Direction::Left);
        break;
    case Keyboard::Right:
        addDirection(Direction::Right);
        break;
    case Keyboard::Space:
        togglePauseState();
        break;
    default:
        break;
    }
}

void Engine::togglePauseState()
{
    if (currentGameState == GameState::Running)
        currentGameState = GameState::Paused;
    else if (currentGameState == GameState::Paused)
        currentGameState = GameState::Running;
}

void Engine::draw()
{
    // clear last state
    window.clear(Color::Black);
    for (auto& s : snake.vsnake)
    {
        window.draw(s.getShape());
    }
    for (auto& w : baseWall)
    {
        window.draw(w.getShape());
    }
    window.draw(apple.getShape());
    // end the current frame
    window.display();
}

void Engine::addDirection(Direction d)
{
    if ( directionQueue.empty() || directionQueue.back() != d)
    {
        directionQueue.push_back(d);
    }
    
}

void Engine::update()
{
    //for every time slice we update the game
    if (timeElapsedSinceLastMove.asSeconds() > seconds( 1.f / (float)speed ).asSeconds())
    {
        if (!directionQueue.empty())
        {
            switch (directionQueue.front())
            {
            case Direction::Up:
                if (snake.direction != Direction::Down) snake.direction = directionQueue.front();
                break;
            case Direction::Down:
                if (snake.direction != Direction::Up) snake.direction = directionQueue.front();
                break;
            case Direction::Left:
                if (snake.direction != Direction::Right) snake.direction = directionQueue.front();
                break;
            case Direction::Right:
                if (snake.direction != Direction::Left) snake.direction = directionQueue.front();
                break;
            }
            directionQueue.pop_front();
        }
        if (snake.sectionToAdd > 0)
        {
            snake.addSnakeSection();
            snake.sectionToAdd--;
        }
        updateSnakePosition(snake.direction);

        if (snake.vsnake[0].getShape().getGlobalBounds().intersects(apple.getShape().getGlobalBounds()))
        {
            snake.sectionToAdd += 4;
            speed++;
            moveFood();
        }

        for (int i = 1; i < snake.vsnake.size(); i++)
        {
            if (snake.vsnake[0].getShape().getGlobalBounds().intersects(snake.vsnake[i].getShape().getGlobalBounds()))
                currentGameState = GameState::GameOver;
        }
        for (auto &w : baseWall)
        {
            if (snake.vsnake[0].getShape().getGlobalBounds().intersects(w.getShape().getGlobalBounds()))
                currentGameState = GameState::GameOver;
        }
        timeElapsedSinceLastMove = Time::Zero;
    }
}

void Engine::updateSnakePosition(Direction d)
{
    Vector2f currentSectionPosition = snake.vsnake[0].getPosition();
    Vector2f lastSectionPosition = currentSectionPosition;

    switch (d)
    {
    case Direction::Up:
        snake.vsnake[0].setPosition(Vector2f(currentSectionPosition.x, currentSectionPosition.y - 20));
        break;
    case Direction::Down:
        snake.vsnake[0].setPosition(Vector2f(currentSectionPosition.x, currentSectionPosition.y + 20));
        break;
    case Direction::Left:
        snake.vsnake[0].setPosition(Vector2f(currentSectionPosition.x - 20, currentSectionPosition.y));
        break;
    case Direction::Right:
        snake.vsnake[0].setPosition(Vector2f(currentSectionPosition.x + 20, currentSectionPosition.y));
        break;
    }
    
    for (int i = 1; i < snake.vsnake.size(); i++)
    {
        currentSectionPosition = snake.vsnake[i].getPosition();
        snake.vsnake[i].setPosition(lastSectionPosition);
        lastSectionPosition = currentSectionPosition;
    }
}

void Engine::moveFood()
{
    Vector2f foodPositionRange = Vector2f(windowWidth / 20 - 1, windowHeight / 20 - 1);
    Vector2f newFoodPosition;
    //bad position is position that in the wall or in the snake
    bool badPosition = true;
    uniform_int_distribution<int> dist_x(1, (int)foodPositionRange.x - 1);
    uniform_int_distribution<int> dist_y(1, (int)foodPositionRange.y - 1);
    while (badPosition)
    {
        badPosition = false;
        newFoodPosition.x = dist_x(mt) * 20;
        newFoodPosition.y = dist_y(mt) * 20;
        for (auto& s : snake.vsnake)
        {
            if (s.getShape().getGlobalBounds().intersects(Rect<float>(newFoodPosition.x, newFoodPosition.y, 20, 20)))
            {
                badPosition = true;
                break;
            }
        }
    }
    apple.setPosition(newFoodPosition);
}