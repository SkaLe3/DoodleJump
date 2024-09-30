# Doodle Jump clone
![video placeholder]()
This is my implementation of a Doodle Jump clone, initially  created as a test task for a C++ developer internship. The project was built in 5 days, and after some time, I revisited it to fix a couple of bugs, improve code quality, enhance visuals, and polish it for public release.
***

## Project Overview
This project is a basic clone of the popular mobile game Doodle Jump. The goal was to implement core game mechanic and several features under time constraints. The requirement was to work within their custom framework that provided only basic sprite rendering and  input handling.



## Features
### Core
* ECS
* Collision System
* Scenes System
* Animator
* Asset Manager
### Game
* Doodle movement
* Monsters
* Shooting
* Immunity ability
* Platform spawner
* UI widgets
    * Distance counter
    * Platform counter
    * Lifes counter

## Getting Started
<ins>**1. Downloading the repository:**</ins>

Start by cloning the repository with `git clone https://github.com/SkaLe3/DoodleJump`.

<ins>**2. Configuring the dependencies:**</ins>

Run the [GenerateProjectFiles.bat](https://github.com/SkaLe3/DoodleJump/blob/master/Scripts/GenerateProjectFiles.bat) file found in `Scripts` folder. This will generate a Visual Studio solution file.

If changes are made, or if you want to regenerate project files, rerun the [GenerateProjectFiles.bat](https://github.com/SkaLe3/DoodleJump/blob/master/Scripts/GenerateProjectFiles.bat) script file found in `Scripts` folder.

### Requirements
- [Visual Studio 2022](https://visualstudio.com) (required to automatically set up the project, otherwise you will have to set up the project yourself)

## Showcase
![Screenshots placeholder]()

## Improvements
Several improvements have been made after the initial release, including:
* Fixed memory leak: Resolved issue caused by shared_ptr cycle dependencies.
* Scene switching bug: Fixed crashes during scene transitions.
* Custom assets: Created and integrated new selfmade assets for game objects.
* Enhanced safety: Improved handling of edge cases.
* Code readability and maintainability: Refactored the codebase for better structure and clarity.
* Animation System: Refactored and improved animations code, created enhanced animation system
* Project structure: Reorganized project structure
* Platfrom spawner: Imroved platform spawner logic 
* Assets: Created Asset Manager and asset handlers
* Adaptive scene aspect ratio: Implemented dynamic handling of various window sized for better visual consistency
* Animations: Added jumping and shooting animations


### Plan
I plan to implement the following features and improvements in the future:
* Remake main menu with custom background, buttons, additional widgets
* Add Themes. Theme switch should load theme assets
* Add score serialization
* optimize performance
* Make all assets 128x128 size

### Possible Enhancements
* Make use of `weak_ptr`
* Get rid of smart pointers and write garbage collector. 
    The current use of smart pointers can lead to code like this:
    ```cpp 
    void MovementComponent::Destroy()
    {
        GetScene()->DestroyTickComponent(GetScene()->GetComponent(this));
    }
    ```
    Or consider using:
    ```cpp
    std::enable_shared_from_this<ThisClass>
    ```
* Optimize scenes logic to improve performance
