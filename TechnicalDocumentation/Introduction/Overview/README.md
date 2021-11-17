# 2.5D Tile based game with Procedurally Generated Content and engine
This project aims to explore and create a tailored game engine for the purpose of creating a basic 2.5d tile-based game. The engine will be required to render 3-dimensional quads - a quadrilateral polygon with 4 vertices existing in 3-dimensional space - which are to be either colored of textured. The 2D/3D OpenGL graphics API will be utilized using a wrapper library (GLAD) to enable rendering graphics to screen. OpenGL Mathematics (GLM) library will be used for vector-matrix transformations of virtual world geometry. Other features required for the engine are an input event handling system, window context creation, camera facilities pertaining orthographic and perspective projections, texture caching, and a logging system to facilitate colour coded console messaging.

A basic 2.5D tile-based survival game will be developed utilizing the subsystems made in the engine. The game will consist of a character existing in a virtual world where the floor tiles will be projected in 3 dimensional space, flat with no height, and all game objects existing within the 3-dimensional world with no depth, only height, appearing 2-dimensional. Custom projection matrixes will be used for rendering the 2-dimensional sprites. Noise based procedural content generation (PCG) methods will be explored to create the virtual world and to populate the world with game content such as trees, shrubs, twigs, grass etc. The game-design will incorporate a game object model, such that each object existing in the world will inherit common data structures including texture packs, position vector, size vector, update methods, draw methods etc. Each game object will encapsulate the model matrix from the model-view-projection transformations, being responsible for updating the matrix when the objects position changes.

The game will be designed to simulate a survival based game where-by players will have to make use of materials gained within the world to construct items like armour, weapons, torches etc in order to survive in the world - akin to 'Don't Starve'[1], 'Grounded'[2], 'Sims'[3]. The gameplay aspects will be kept simple due to the large scope of the project.


# References
* [Don't Starve, Klei Entertainment](https://www.klei.com/games/dont-starve)
* [Grounded, Obsidian Entertainment](https://grounded.obsidian.net/)
* [Sims, EA Games](https://www.ea.com/en-gb/games/the-sims)
* [Readme.md template, Walton-Rivers, J.](https://cseegit.essex.ac.uk/snippets/8)
