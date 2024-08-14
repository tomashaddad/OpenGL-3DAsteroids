# Asteroids 3D in OpenGL

Asteroids game demo using OpenGL (fixed function pipeline). WASD to move, space to shoot, click + move mouse to control the ship.

See video in **About** section.

Notable features:

- Skyboxes
- Directional and moving point lights
- Ship model (obj, loaded with tinyobjloader)
- Animated textures (bullets, explosions)
- Asteroid physics (elastic collisions)
- Quaternions used to control ship and camera rotation

See `README.pdf` for a detailed breakdown of the above.

----

Original README contents:

* Source files are in src folder.
* Visual studio solution is in vs folder.
* External libraries needed to compile OpenGL programs using visual studio are in libs.
* When creating new source files using visual studio, you should make sure they go in the src folder.
* Compiled executables are placed in this folder.
* Don't delete freeglut.dll, it's needed.
* Compile 64 bit versions only, as freeglut.dll is a 64 bit dll.