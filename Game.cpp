#include "Game.h"

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
    //cout << "(" << statSnake->x << ", " << statSnake->y << ")\n";
    if (action == GLFW_PRESS) {

            switch (key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                break;
            case GLFW_KEY_W:
                //statSnake->incY();
                statSnake->dir = Top;
                break;
            case GLFW_KEY_S:
                //statSnake->decY();
                statSnake->dir = Bottom;
                break;
            case GLFW_KEY_A:
                //statSnake->decX();
                statSnake->dir = West;
                break;
            case GLFW_KEY_D:
                //statSnake->incX();
                statSnake->dir = East;
                break;
            case GLFW_KEY_SPACE:
                break;
            }
        }
}

Game::Game(int width, int height, string name) : width(width), height(height)
{
    cout << "Initializing the game" << endl;
	if (!glfwInit())
		exit(EXIT_FAILURE);

    window = glfwCreateWindow(width,height, name.c_str(), NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    /* Make the window's context current */
    squareA = (float)1/cells;
    vector<vector<GLfloat>> colors;
    colors.push_back(vector<GLfloat>{142 / 255.0f, 204 / 255.0f, 57 / 255.0f});//142, 204, 57
    colors.push_back(vector<GLfloat>{167 / 255.0f, 217 / 255.0f, 72 / 255.0f});//167, 217, 72
    for (int y = 0 ,i =0; y < cells; y++) {
        for (int x = 0; x < cells; x++) {
            field.push_back(Cell(x, y, colors[i++%2]));
        }
        i++;
    }
    snake = Snake(0,0, cells, 3);
    statSnake = &snake;
    srand(time(NULL));
    setKeyCallBack();
    glfwMakeContextCurrent(window);
    timer = lastTime = glfwGetTime();
    delta = 0;
    cout << "End of init" << endl;
}



Game::~Game()
{
    glfwTerminate();
}

bool Game::gameShouldClose()
{
    return glfwWindowShouldClose(window);
}

void Game::render()
{
    glClearColor(74 / 255.0f, 194 / 255.0f, 68 / 255.0f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (auto cell = field.begin(); cell != field.end(); cell++) {
        drawSquare(cell->x, cell->y, squareA,  cell->color);
        if (cell->isFoodHere)
            drawBall(cell->x, cell->y, squareA-0.01f, cell->food->color);
        if (cell->isSnakeHere)
            drawSnake(cell->x, cell->y, snakeColor, float(snake.length - cell->length)/snake.length * 0.3137);
    }
    /* Swap front and back buffers */
    glfwSwapBuffers(window);

}

void Game::run()
{
    double frameLimit = 1.0f / UPS;
    double nowTime = glfwGetTime();
    delta += (nowTime - lastTime) / frameLimit;
    lastTime = nowTime;

    while (delta >= 1.0 ) {
        update();
        delta--;
    }
    render();
    frames++;

    if (glfwGetTime() - timer > 1.0) {
        timer++;
        if(!stop)
            cout << "FPS: " << frames<<endl;
        frames = 0;
    }
}

void Game::update()
{
    /* Poll for and process events */
    glfwPollEvents();

    if (!stop) {
        snake.update();
        if (snake.x == cells || snake.x == -1 || snake.y == cells || snake.y == -1) {
            stop = true;
            cout << "Game Over" << endl << "Score: " << snake.length << endl;
            return;
        }
        for (auto cell = field.begin(); cell != field.end(); cell++) {
            if (cell->x == snake.x && cell->y == snake.y){
                if (cell->isFoodHere) {
                    snake.length++;
                    cell->isFoodHere = false;
                    foodNumber--;
                    delete cell->food;
                }
                cell->isSnakeHere = true;
                cell->length = snake.length;
            }
            else
                cell->update();
            while (foodNumber < totalFoodNumber) {
                int random;
                do {
                    random = rand() % 255;
                } while (field[random].isSnakeHere);
                if (random % 4 < 3)
                    field[random].food = new Apple();
                else
                    field[random].food = new Lemon();
                field[random].isFoodHere = true;
                foodNumber++;
            }

        }
    }
}

void Game::drawSnake(int x, int y, vector<GLfloat> &color, float gradient){

    drawSquare(x, y,squareA, color, gradient);
}

void Game::goToCords(int x, int y)
{
    glTranslatef(squareA-1+x*2*squareA, squareA-1+y*2*squareA, 0);
    //cout << squareA - 1 + x * 2 * squareA << ", " << squareA - 1 + y * 2 * squareA << endl;
}


void Game::setKeyCallBack()
{
    glfwSetKeyCallback(window, keyCallBack);
}

void Game::drawSquare(int x, int y, float a,  vector<GLfloat>& color, float gradient)
{
    glPushMatrix();
        goToCords(x, y);
        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(color[0]-gradient, color[1]-gradient, color[2]-gradient);
            glVertex2d(-a, a);
            glVertex2d(a, a);
            glVertex2d(a, -a);
            glVertex2d(-a, -a);
            glVertex2d(-a, a);
        glEnd();
    glPopMatrix();
}

void Game::drawBall(int x, int y, float ballRadius, vector<GLfloat>& color)
{
    glPushMatrix();
        goToCords(x, y);
        glBegin(GL_TRIANGLE_FAN);
            glColor3f(color[0], color[1], color[2]);
            glVertex2f(0.0f, 0.0f);       // Center of circle
            int numSegments = 100;
            GLfloat angle;
            for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
                angle = i * 2.0f * 3.1416 / numSegments;  // 360 deg for all segments
                glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
            }
        glEnd();
    glPopMatrix();
    
}