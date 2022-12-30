# Data-Oriented Architecture Studies
This repo contains a collection of studies on data-oriented architecture using my own 3D game engine that uses OpenGL for rendering. The project features data-oriented, pooled and instantiated (not cached) objects that work seamlessly together.
![Demo](/docs/shooterdemo.gif  "Demo")

## Highlights
- Data-Oriented Architecture
- Object pooling
- EntityComponent System (ECS)

## Data Oriented Architecture
Relevant Files: 
* [GSpaceShooter.cpp](https://github.com/jsfoao/nata-engine/blob/main/nata/res/scripts/GSpaceShooter.cpp)
    Engine's GameMode: Similar to Unreal Engine's GameMode, it's executing most of the initial setups, game logic and instantiating objects.
* [dots.h](https://github.com/jsfoao/nata-engine/blob/main/nata/src/core/ecs/dots.h)
    Data-oriented Architure
* [NDAsteroidPool.h](https://github.com/jsfoao/nata-engine/blob/main/nata/res/scripts/NDAsteroidPool.h)
    Inherits from the class above and executes asteroid's logic. All asteroids are instatiated using this system.
* [ecs.h](https://github.com/jsfoao/nata-engine/blob/main/nata/src/core/ecs/ecs.h)
    Entity Component System: An object-oriented ECS. The ship and its components are objects from this system.
* [object_pool.h](https://github.com/jsfoao/nata-engine/blob/main/nata/src/core/ecs/object_pool.h)
    An object pool for the entities from ECS: The projectiles are cached using this system and enabled when necessary.


## Dependencies
 * [glfw](https://github.com/glfw/glfw) : A multi-platform library for OpenGL, OpenGL ES, Vulkan, window and input.
 * [glew](http://glew.sourceforge.net) : The OpenGL Extension Wrangler Library.
 * [glm](https://github.com/g-truc/glm) : OpenGL Mathematics (GLM) is a header only C++ mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications.
* [Assimp](https://www.assimp.org) : The Open Asset Import Library (short name: Assimp) is a portable Open-Source library to import various well-known 3D model formats in a uniform manner.
* [imgui](http://glew.sourceforge.net) : Graphical user interface library.

## Sources
- [Learn OpenGL](https://learnopengl.com/)
- [OpenGL Abstractions](https://github.com/Pikachuxxxx/OpenGL-Abstractions)
- [TheCherno's Sparky](https://github.com/TheCherno/Sparky)
- [Anax ECS](https://github.com/miguelmartin75/anax)
- David Ventura's Computer Technology lectures (Futuregames)
