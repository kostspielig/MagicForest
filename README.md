
# Magic Forest SDL 

3D game developed with the SDL library.

## What happening?
You control the **goblin**, our main character. You will be searching for mushrooms in the forest, while dodging trees, that you should avoid touching as they collapse easily.
 
![ScreenShot](https://raw.github.com/kostspielig/MagicForest/master/mf5.png)

## Class structure

### Goblin

The main character of the game. This class is an entity and a keyboard listener, as we can control it via keyboard. This class also incorporates a camera that will follow the goblin.

### Camera
Basic functionality for the use of the camera

### Cone, Cube, Cylinder, Hemisphere, Sphere
3D definition of the different shapes

### Ground
Implementation of the ground of the scene

### Drawable
Interface used by all the game elements that can be drawn in the system. Draw() method should implement the OpenGL calls to draw the object.

### Entity
It represents any entity of the game, in this case the trees, the mushrooms and the goblin. Here you can find the basic needs for an entity off the game such as the radio of action (for collisions).

### EntityManager
Entity manager that consists of two different types: Static and dynamic entities. The need for two different types of entities is based on the need to improve the collisions efficiency.
Static entities are those that don't move, such as mushrooms or trees. Dynamic entities are those that move, therefore they will need extra functionality: checking for collisions

### KeyListener
Interface to control keyboard events, such as pressing a keyboard

### MouseListener
Interface to control mouse events, such as moving the mouse or pressing a button

### VideoListener
Interface to control video events, such as refresing or changing the window size
 
### EventManager
Event manager that includes tree lists of events (keyListener, mouseListener and videoListener). Registers event listeners so that EventManager can receive SDL events, and depending on the type, it can send the event to all the objects registered to it. 

### Game 
We define here the main elements of the game (goblin, mushrooms and tree), the fixed cameras andd the event listeners.

### Timer
It counts the system ticks and sets the refresing speed. The update() function updates the Timer counter, this function should be called once for every drawing cicle. 

### Mesh
Defined to save the mesh of points that make up a figure. We can set the color, material, brightness or transparency.

### PlyMesh
Type of mesh that allows you to get .ply objects

### SceneNode
Data structure based on a TreeNode. It allows us to structure the whole scene ased on a hierarchy.


### TreeEnt
Tree entity that defines its behaviour. The tree will remain on its position until a goblin hits him.

