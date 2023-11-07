#ifdef _WIN32
#define M_PI 3.14159265358979323846
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

// Global variables for game state and user's position
double angle = 0;          // The angle of rotation for the cubes
double xloc = -7.5;        // The user's X position
double zloc = -21.5;       // The user's Z position
double userAngle = 0;      // The user's viewing angle

bool opaque = true;        // Toggle for drawing mode (filled or outlined walls)
bool checkproj = false;    // Determines if a projectile has been fired
double projY = 0;          // Projectile's Y position
double projZ = 0;          // Projectile's Z position
double dY = 0;            // Projectile's Y direction for bouncing
bool collisonBool = true;  // Toggle for wall collision

int gcube = 0;             // Counts the number of cubes that have been hit
bool greenWalls = false;   // Turns all of the walls green

// Represents the maze. 1 is a wall, 0 is empty, 2 is a cube
int maze[20][20] = {
    {'1', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '2', '0', '1', '1', '0', '0', '0', '1'},
    {'1', '0', '0', '0', '0', '2', '0', '0', '0', '1', '1', '0', '0', '0', '1', '1', '0', '0', '0', '1'},
    {'1', '1', '1', '1', '0', '0', '0', '0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '1', '1', '0', '0', '0', '0', '1', '1', '1', '1', '0', '0', '0', '0', '2', '0', '1'},
    {'1', '0', '0', '1', '1', '1', '1', '0', '0', '1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1', '0', '1', '1', '0', '0', '0', '1'},
    {'1', '1', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '0', '0', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1', '1', '0', '0', '0', '1', '1', '0', '0', '1'},
    {'1', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '1', '1', '0', '0', '1', '1'},
    {'1', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
    {'1', '0', '1', '1', '0', '0', '0', '0', '0', '0', '0', '2', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '1', '0', '0', '1', '1', '0', '1', '0', '0', '0', '0', '0', '1', '1', '0', '1', '1', '1'},
    {'1', '0', '0', '0', '0', '0', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1'},
    {'1', '0', '0', '0', '1', '0', '0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '1', '0', '0', '0', '0', '0', '2', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '0', '1'},
    {'1', '1', '0', '0', '1', '1', '0', '0', '0', '1', '1', '0', '0', '1', '1', '0', '0', '1', '0', '1'},
    {'1', '1', '0', '0', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1', '0', '1'},
    {'1', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '1'}
};

// Display function for rendering the scene
void display(void)
{
    // Set the drawing mode (filled or outlined walls)
    if (opaque)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Clear the screen with a black background
    glClearColor(0.0, 0.0, 0.0, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    // Iterate through the maze
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            glLoadIdentity();
            glRotatef(userAngle * 180, 0, 1, 0);
            glTranslatef(xloc, 0, zloc);
            glTranslatef(i, 0, j);

            if (maze[j][i] == '1')
            {
                if (greenWalls)
                {
                    // Set wall color to green
                    glColor3f(0.0, 1.0, 0.3);
                }
                else
                {
                    // Set wall color to default
                    glColor3f(0.8, 0.7, 0.5);
                    glutSolidCube(1.0);
                }
            }
            else if (maze[j][i] == '2')
            {
                // Set cube color to red
                glColor3f(1.0, 0.0, 0.0);
                glRotatef(angle, 0, 1, 0);
                glutSolidCube(0.5);
            }
            else if (maze[j][i] == '3')
            {
                // Set cube color to green
                glColor3f(0.0, 1.0, 0.0);
                glRotatef(angle, 0, 1, 0);
                glutSolidCube(0.5);
            }
        }
    }

    if (checkproj)
    {
        glLoadIdentity();
        glTranslatef(0, projY, -projZ - 3);
        glColor3f(0.0, 0.0, 1.0);
        glRotatef(angle * 40, 1, 1, 1);
        glutSolidCube(0.25);
    }

    // Flush the rendering commands and swap the buffer for double buffering
    glFlush();
    glutSwapBuffers();
}

// Function to enable necessary parameters for lighting and perspective

void enableParameters(void)
{
    // Enable depth testing to handle occlusion and hidden surfaces
    glEnable(GL_DEPTH_TEST);
    
    // Set the clear color for the background (black in this case)
    glClearColor(0.0, 0.0, 0.0, 0.0f);
    
    // Enable color material for material properties
    glEnable(GL_COLOR_MATERIAL);
    
    // Set up perspective projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.5, 1.0, 1.0, 1000);
}
// Function to create the light sources
void createLight(void)
{
    // Enable lighting and set up light sources
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Define the position and properties of the light source
    GLfloat lightPosition[] = {-0.5, 0.0, 5.0, 1.0};
    GLfloat ambientLight[] = {0.3, 0.3, 0.3, 1};
    GLfloat diffuseLight[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat specularLight[] = {0.5, 0.5, 0.5, 1.0};

    // Set the defined properties for the light source
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
}

// Function to check if moving the user/projectile forward results in a collision
bool checkCollision(double x, double z)
// Function to check if moving the user/projectile forward results in a collision
bool checkCollision(double x, double z)
{
    if (!collisonBool)  // If collision check is disabled, return false
        return false;
    else if (-abs(z) <= 0 && -abs(z) > -20 && -abs(x) <= 0 && -abs(x) > -20 && maze[int(round(-1 * z))][int(round(x * -1))] == '1')
        return true;  // Return true if a collision with a wall occurred
    else
        return false;  // Return false if no collision occurred
}

// Function to check if a firing cube hits a red cube or a wall
// Function to check if a firing cube hits a red cube or a wall
bool checkCubeCollision(double x, double z)
{
    if (-abs(z) <= 0 && -abs(z) > -20 && -abs(x) <= 0 && -abs(x) > -20 && maze[int(round(-1 * z))][int(round(x * -1))] == '2')
    {
        maze[int(round(-1 * z))][int(round(x * -1))] = '3';
        gcube++;

        if (gcube % 5 == 0)
        {
            for (int i = 0; i < 20; i++)
            {
                for (int j = 0; j < 20; j++)
                {
                    if (maze[i][j] == '3')
                        maze[i][j] = '2';
                }
            }
            // Toggle green walls after hitting every 5 cubes
            greenWalls = true;
        }

        return true;  // Return true if a collision occurred
    }
    else if (-abs(z) <= 0 && -abs(z) > -20 && -abs(x) <= 0 && -abs(x) > -20 && maze[int(round(-1 * z))][int(round(x * -1))] == 'w')
        return true;  // Return true if the projectile hit a wall
    else
        return false;  // Return false if no collision occurred
}

// Function for keyboard input
void handleKeyboardInput(unsigned char key, int x, int y)
{
    if (key == ' ')
    {
        if (!checkproj)
            checkproj = true;  // Toggle projectile firing on spacebar press
    }
    else if (key == 'q')
    {
        opaque = !opaque;  // Toggle between filled and outlined walls on 'q' key press
    }
    else if (key == 'w')
    {
        collisonBool = !collisonBool;  // Toggle wall collision on 'w' key press
    }
}

// Function for arrow key input
void handleArrowKeys(int key, int x, int y)
    {
        userAngle += 0.02; // Rotate the user to the right
        if (userAngle == 2.0)
            userAngle = 0; // Wrap around user angle (360 degrees)
    }
    else if (key == GLUT_KEY_LEFT)
    {
        userAngle -= 0.02; // Rotate the user to the left
        if (userAngle < 0)
            userAngle = 1.999; // Wrap around user angle (360 degrees)
    }
    else if (key == GLUT_KEY_DOWN && !checkCollision(xloc + sin(userAngle * M_PI), zloc - cos(userAngle * M_PI)))
    {
        // Move the user forward while checking for collisions
        xloc += sin(userAngle * M_PI) / 10;
        zloc -= cos(userAngle * M_PI) / 10;
    }
    else if (key == GLUT_KEY_UP && !checkCollision(xloc - sin(userAngle * M_PI), zloc + cos(userAngle * M_PI)))
    {
        // Move the user backward while checking for collisions
        xloc -= sin(userAngle * M_PI) / 5;
        zloc += cos(userAngle * M_PI) / 5;
    }
}

// Timer function
// Timer function for managing animations and updates
void timerFunction(int unused)
{
    // Update the rotation angle
    angle += 1;
    if (angle == 360)
        angle = 0;

    // Check if a projectile has been fired
    if (checkproj)
    {
        // Check for collisions with cubes or walls
        if (checkCubeCollision(xloc - projZ * sin(userAngle * M_PI), zloc + projZ * cos(userAngle * M_PI)) ||
            checkCubeCollision(xloc, zloc + projZ))
        {
            checkproj = false; // Disable the projectile
        }
        else
        {
            projZ += 0.1; // Move the projectile forward

            if (projY >= 0)
            {
                projY -= 0.025; // Apply vertical motion for bouncing effect
                projZ += 0.1;
            }

            projY += dY;

            // Check if the projectile is out of bounds
            if (-abs(zloc - projZ) > 21.5 || -abs(xloc + projZ * sin(userAngle * M_PI)) > 21.5 || -abs(xloc - projZ * cos(userAngle * M_PI)) > 21.5)
                checkproj = false; // Disable the projectile
        }
    }

    // Trigger a redisplay to update the scene
    glutPostRedisplay();
    
    // Set a timer for the next animation frame
    glutTimerFunc(25, timerFunction, 0);
}

// Main function for initializing and running the 3D Maze Game
int main(int argc, char **argv)
{
    // Initialize GLUT and create a window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("3D Maze Game");

    // Enable necessary OpenGL parameters
    enableParameters();

    // Create and configure the lighting for the scene
    createLight();

    // Set callback functions for various events
    glutDisplayFunc(display);           // Rendering function
    glutKeyboardFunc(handleKeyboardInput); // Keyboard input handler
    glutSpecialFunc(handleArrowKeys);     // Special key input handler
    glutTimerFunc(25, timerFunction, 0);  // Timer function for animations

    // Enter the main event loop
    glutMainLoop();

    return 0;
}