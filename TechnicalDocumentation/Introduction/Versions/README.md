# Versioning strategy  
**[Semantic versioning](https://semver.org/)** is used throughout of form *x.y.z* where:  
	* z - patch version number  
	* y - minor version  
	* x - major version  

# Published Versions  
  
All released versions are uploaded and stored in this directory. Executable versions can be found in the version folder specified. To run any of the versions one must simply copy all files and the 'res' directory locally, and then run the 'GameEngine.exe' executable.  
  
Source code is not included in the versions; however a git hash can be found below which contains the hash of the projects source code at the point in time the version was created  
  
## [final](https://cseegit.essex.ac.uk/ce301_2020/ce301_allport_michael_s/-/tree/master/PublishedVersions/final) - git hash f856540afa035b9d3b794008192a53ffb18f98e8  
Game developed( offering the player world generation utilities with ImGui overlay. Player can select parameterized world generation and object placement. Generate world generates new world, play starts the player in the game world.  
  
## [version 1.1.1](https://cseegit.essex.ac.uk/ce301_2020/ce301_allport_michael_s/-/tree/master/PublishedVersions/1.1.1) - git hash 7119b55b3d7f5dc7d5d7135f8cb04ffd203d84d5  
Test Environment:  
- Object Picker test, successful highlighting of objects under the mouse, with console message of the unique objects id  
   
**Changes to App::**
### StencilDrawer  
- Class with its own Renderer, responsible for drawing a colour on top of a given game object to highlight it with colour  
### ObjectPicker  
- Class with its own renderer  
- Responsible for encoding ObjectID's to RGB code using bit shifting  
- Draws objects to hidden game window in a solid colour of its encoded  
- Decodes any objects drawn under the mouse position and stores them in MouseState class   
### MouseState  
- Now stored object under mouse reference, either null or an object    
### ClickHandler  
- Responds to click events, if primary mouse click then gets character to move to object  
### CharacterObject  
- now contains members to move character to a given position  
- if moveTo position is not null, character will move towards the positions vector on update  
### Tests Added  
- ObjectPickerTest  
  
**Changes to GE::**  
### Window  
- now contains an extra hidden window which is not visible to user  
- contains member functions for switching between main window and hidden window (changes the OpenGL drawing context)    
  
## [version 1.1.0](https://cseegit.essex.ac.uk/ce301_2020/ce301_allport_michael_s/-/tree/master/PublishedVersions/1.0.1) - git hash 999daa4cb1b5ce2c89df19db89d0b18af43b9721    
Test Environment:  
- Improved world generator test, with visualisation of noise using white to black colour representation alongside tile representation  
- content placement, ability to place variable objects by clicking on mouse. Shows ray plane intersection picking up the mouse positions in world coordinate space  
- poisson disc sampling with red texture markers  
- object placement with poisson disc sampling  
  
**Changes to App::**  
#### Objects  
- CommonGameObject class created for vertically drawn sprites (no z depth)  
- CommonObjectEnum / CommonObjectMap created - Enum is used in the map and is the main parameter for CommonGameObject mapping to  
    - CommonObjectData created which stores data related to the actual objects size and  
    - TexturePack added which stores texture sizes, offsets for the centre (what to draw)  
- WorldGenerator namespace created mainly using  
    - PoissonGenerator, creates a list of points distributed with densities using PerlinNoise for point clustering   
    - ObjectGenerator, creates a list of randomly selected objects weighted by the density values of PerlinNoise with Stochastic properties  
  
## [version 1.0.1](https://cseegit.essex.ac.uk/ce301_2020/ce301_allport_michael_s/-/tree/master/PublishedVersions/1.0.1) - git hash 1927090838ddf2223edd031a029af6d84a8eaaac  
Test Environment:  
- Player in a procedurally generated map, camera controller responding to movements and player moving  
  
Functionality tested  
- GameObject class created for all in game objects i.e character, tile..   
- CharacterObject class created for main character   
- CameraHandler class now fixed onto characters position  
- Camera moves at a delayed response from characters movement  
- Sprite class created for storing the textures related to object, drawing methods, and the model transofrmation matrix for the sprite  
- Controller class created for associating key presses with actions i.e character movement, camera movement  
- Vector2D class created for standard vector math  
   
## [Version 0.9.9](https://cseegit.essex.ac.uk/ce301_2020/ce301_allport_michael_s/-/tree/master/PublishedVersions/0.9.9) - git hash 720975310031feb37168d4837cf789473fc09344  
Test Environment:  
- World Generation test, first version on PCG terrain generation providing parameterised test  
- Mesh Renderer, most basic quad rendering  
- New 3d Camera test, rendering of number of cubes with perspective projection. Up, Down, left and right key events working. Mouse scrolling to zoom in and out working.  
- 2d Camera test, first orthographic rendering of multi colours 2d quads  
- Old 3d camera test. very basic rendering of rotating cubes  
- Renderer Instanced, rendering of multiple 2d quads with batched rendering, one draw call for numerous quads  
- Renderer instanced with static geometry  
- Renderer batched with static geometry  
  
Functionality tested:-    
- PCG world generation, floor and tiles.  
- OpenGL functionality tested  
- rendering triangles/quads to screen  
- Orthographic (2D) projection  
- Perspective (3D) projection  
- Batched rendering (drawing multiple objects in as few draw calls as needed)  
- Instanced rendering ^ ^ similar  
- Event handling subsystem  
- Logging subsystem  
  
## Author  
* Michael Allport, ma18533, 1802882  
