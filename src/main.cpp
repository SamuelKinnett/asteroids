#include "main.h"
using namespace std;

#define FPS 60
#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600

int windowHandle = 0;
int screenSize[2] = {DEFAULT_WIDTH, DEFAULT_HEIGHT};

vector<GameObject*> gameObjects;
Player* player;

int main (int argc, char* argv[]) {
	Initialise(argc, argv);
}

//Initialise the window and OpenGL
void Initialise(int argc, char* argv[]) {
	InitWindow(argc, argv);
	InitOpenGL();

	//Initialise the player
	player = new Player();
	//TESTING
	gameObjects.push_back(new Asteroid());
	gameObjects.push_back(new Asteroid(0.5f, 0.5f));
	gameObjects.push_back(new Asteroid(-0.5f, -0.5f));
	glutMainLoop();
}

void InitWindow(int argc, char* argv[]) {
	glutInit(&argc, argv);

	//Set the window size
	glutInitWindowSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	//Set the display mode to double buffered
	glutInitDisplayMode(GLUT_DOUBLE);
	//Create a window with the specified title
	windowHandle = glutCreateWindow("Asteroids");
	//Check for errors
	if (windowHandle < 1) {
		fprintf(stderr, "ERROR: Could not create a new rendering window.\n");
		exit(EXIT_FAILURE);
	}

	//Set the screen update function
	glutDisplayFunc(Render);
	//Set the MainLoop function to be called 60 times a second
	glutTimerFunc(1000 / FPS, MainLoop, 0);
	//Set the callback functions
	glutMouseFunc(HandleMouseClick);
	glutMotionFunc(HandleMouseMoving);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(HandleButtonPress);
	glutSpecialFunc(HandleSpecialButtonPress);
}

//Initialises OpenGL
bool InitOpenGL() {
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//Initialise blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

void Update() {
	for (int i = 0; i < (int) gameObjects.size(); ++i) {
		if (gameObjects[i]->gravAffected) {
			for (int c = 0; c < (int) gameObjects.size(); ++c) {
				if (c != i)
					gameObjects[i]->ApplyGravity(gameObjects[c]);
			}
		}
		gameObjects[i]->Update();
	}
}

void Render() {
	
	glClear(GL_COLOR_BUFFER_BIT);

	//Drawing code goes here
	for (int currentObject = 0; currentObject < (int)gameObjects.size(); ++currentObject) {
		gameObjects[currentObject]->Render();
	}	
	
	//Draw the player
	player->Render();
	
	//End drawing code
	
	glutSwapBuffers();
}

//The main program loop
void MainLoop(int val) {

	Update();
	Render();

	//Set the loop to be run again in 1/60th of a second
	glutTimerFunc(1000 / FPS, MainLoop, val);
}

//Handles mouse clicks
void HandleMouseClick(int button, int state, int x, int y) {

	y = screenSize[1] - y;	//Invert the y co-ordinate

}

//Handles the mouse moving while a button is pressed
void HandleMouseMoving(int x, int y) {

}

//Handles standard keyboard input
void HandleButtonPress(unsigned char key, int x, int y) {

}

//Handles special key input
void HandleSpecialButtonPress(int key, int x, int y) {

}

//Handles the window being resized
void Resize(int width, int height) {

	screenSize[0] = width;
	screenSize[1] = height;
}
