3D Maze
This C++ program, utilizing OpenGL and GLUT, is an interactive 3D maze simulation with various features. Users navigate a maze, which includes walls, cubes, and a projectile, providing an engaging experience.

Features
User Navigation: You can control your position within the maze using arrow keys. Turn left or right, and move forward or backward.

Wall Collision: Toggle wall collision on and off to control whether the user can move through walls.

Projection: Launch a blue, spinning, bouncing cube forward by pressing the space bar.

Maze Elements:

Walls: Walls are rendered in either yellow or green, based on user settings.
Spinning Red Cubes: Red cubes rotate in the maze.
Spinning Green Cubes: Green cubes appear when all red cubes are hit.
Visual Style: Choose between solid and wireframe (line) rendering for the maze walls by pressing 'q'.

Lighting: The maze is illuminated with ambient, diffuse, and specular lighting.

Controls
Use arrow keys to navigate the maze.
Press 'q' to toggle between wireframe and solid wall rendering.
Press 'w' to toggle wall collision on and off.
Press the space bar to launch the blue cube (projection).
The program also provides a timer for cube rotation.
Maze Layout
The maze layout is represented using a 2D array. It includes walls ('1'), empty spaces ('0'), and red cubes ('2'). When red cubes are hit, they turn green ('3'). When all red cubes are hit, the walls turn green.

Usage
Compile and run the program.
Use the arrow keys to navigate the maze.
Press 'q' to change the wall rendering style.
Press 'w' to toggle wall collision.
Launch a blue cube using the space bar.
Explore and enjoy the 3D maze!