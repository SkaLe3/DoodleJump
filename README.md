# Doodle Jump clone
![video placeholder]()

This is my implementation of a Doodle Jump clone, initially  created as a test task for a C++ game developer internship. The project was built in 5 days, and after some time, I revisited it to fix a couple of bugs, improve code quality, add features, enhance visuals, and polish it for public release. A significant portion of the assets, was created by me.
***

## Project Overview
This project is a basic clone of the popular mobile game Doodle Jump. The goal was to implement core game mechanics and several features under time constraints. The requirement was to work within a custom framework that provided only basic sprite rendering and input handling. Due to the limited functionality of the framework, I had to adapt and find creative solutions using the limited tools available, with some features being impossible to implement under these constraints.



## Features
### Core
* ECS
* Rendering System
* Collision System
* Scenes System
* Animation System
* Asset Manager
* Input bindings
* Serialization

### Game
* Doodle movement
* Doodle Animator
* Monsters
* Shooting
* Immunity ability
* Platform spawner
* UI widgets
    * Distance counter
    * Platform counter
    * Lifes counter
* Menu

## Getting Started
<ins>**1. Downloading the repository:**</ins>

Start by cloning the repository with `git clone https://github.com/SkaLe3/DoodleJump`.

<ins>**2. Configuring the dependencies:**</ins>

Run the [GenerateProjectFiles.bat](https://github.com/SkaLe3/DoodleJump/blob/master/Scripts/GenerateProjectFiles.bat) file found in `Scripts` folder. This will generate a Visual Studio solution file.

If changes are made, or if you want to regenerate project files, rerun the [GenerateProjectFiles.bat](https://github.com/SkaLe3/DoodleJump/blob/master/Scripts/GenerateProjectFiles.bat) script file found in `Scripts` folder.

<ins>**3. Building the project:**</ins>

After generating the project files, open the solution in Visual Studio 2022 and build the project.

<ins>**4. Copying framework dependencies:**</ins>

Once the project is built, you need to copy the framework dependencies. Copy the libraries from `ThirdParty/Framework/bin` to the `Build/Binaries/%{buildcfg-system-architecture}/DoodleJump` directory, where:
- `buildcfg` refers to your build configuration (e.g., `Debug`, `Release`).
- `system` refers to your operating system (e.g., `windows`).
- `architecture` refers to your system architecture (e.g., `x64`).

These libraries are provided with the framework and are mandatory for the project to run.

### Requirements
- [Visual Studio 2022](https://visualstudio.com) (required to automatically set up the project, otherwise you will have to set up the project yourself)

## Showcase
<p>
  <img src="/Resources/menu.png" alt="Menu" style="width: 32%; display: inline-block;"/>
  <img src="/Resources/gameplay1.png" alt="Gameplay 2" style="width: 32%; display: inline-block;"/>
  <img src="/Resources/gameplay2.png" alt="Gameplay 2" style="width: 32%; display: inline-block;"/>
</p>

## Framework Information
The project was developed using a custom framework provided for the task, which offers only basic functionality. Below is the header file that outlines the available features:

```cpp
#pragma once
#if defined(_WINDOWS)
    #if defined(FRAMEWORK_PROJECT)
        #define FRAMEWORK_API extern "C" __declspec(dllexport)
    #else
        #define FRAMEWORK_API extern "C" __declspec(dllimport)
    #endif
#else
    #define FRAMEWORK_API 
#endif

class Sprite;

FRAMEWORK_API Sprite* createSprite(const char* path);
FRAMEWORK_API void drawSprite(Sprite*, int x, int y);
FRAMEWORK_API void getSpriteSize(Sprite* s, int& w, int &h);
FRAMEWORK_API void setSpriteSize(Sprite* s, int w, int h);
FRAMEWORK_API void destroySprite(Sprite* s);
FRAMEWORK_API void drawTestBackground();
FRAMEWORK_API void getScreenSize(int& w, int &h);
// Get the number of milliseconds since library initialization.
FRAMEWORK_API unsigned int getTickCount();
FRAMEWORK_API void showCursor(bool bShow);

enum class FRKey {
	RIGHT,
	LEFT,
	DOWN,
	UP,
	COUNT
};

enum class FRMouseButton {
	LEFT,
	MIDDLE,
	RIGHT,
	COUNT
};

class Framework {
public:

	// no function calls are available here, this function should only return width, height and fullscreen values
	virtual void PreInit(int& width, int& height, bool& fullscreen) = 0;
	// return : true - ok, false - failed, application will exit
	virtual bool Init() = 0;
	virtual void Close() = 0;
	// return value: if true will exit the application
	virtual bool Tick() = 0;
	// param: xrel, yrel: The relative motion in the X/Y direction 
	// param: x, y : coordinate, relative to window
	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) = 0;
	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) = 0;
	virtual void onKeyPressed(FRKey k) = 0;
	virtual void onKeyReleased(FRKey k) = 0;
	virtual const char* GetTitle() = 0;
	virtual ~Framework() {};
};
FRAMEWORK_API int run(Framework*);

```

Despite providing basic features, the framework imposed several limitations that required me to implement custom functionality and workarounds, and in some cases, made certain features impossible to achieve:

* Limited Input: Only a few keys (up, down, left, right) are available, limiting input options.
* Sprite Restrictions: Sprites can't be rotated, tinted, or made transparent, which restricts visual effects.
* No Text Rendering: There’s no built-in text rendering, so I had to create my own solution for scores and UI.
* Basic Rendering: The framework doesn't support advanced transformations or custom shaders.
* No Sound: There’s no audio support.


## Improvements
Several improvements have been made after the initial release, including:
* Fixed memory leak: Resolved issue caused by `shared_ptr` cycle dependencies.
* Scene switching bug: Fixed crashes during scene transitions.
* Custom assets: Created and integrated new selfmade assets for game objects.
* Code readability, maintainability and safety: Refactored the codebase for better structure and clarity, improved edge cases handling.
* Animation System: Refactored and improved animations code, created enhanced animation system
* Animations: Added and integrated jumping and shooting animations
* Project structure: Reorganized project structure
* Platfrom spawner: Imroved platform spawner logic 
* Assets: Created Asset Manager and asset handlers
* Adaptive scene aspect ratio: Implemented dynamic handling of various window sizes for better visual consistency
* Smart pointer optimization: Introduced `weak_from_this` and replaced some `shared_ptr` with `weak_ptr` to improve memory management and avoid cyclic dependencies.
* Projectile movement: Fixed direction calculation for better accuracy.
* GameInstance: Added to manage game state and handle score serialization across scenes and game sessions (with enctyption).
* Visuals: Reworked Main menu

### Plan
I plan to implement the following features and improvements in the future:
* Add Themes. Theme switch should load theme assets
* optimize performance
* Make all assets 128x128 size
* Remake UI managing and create new UI System
* Add game over screen
* Remake main menu
* Encrypt serialized data to avoid cheating
* Make moving platforms

### Possible Enhancements
* Optimize scenes logic to improve performance
