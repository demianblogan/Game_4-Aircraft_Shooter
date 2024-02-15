[![en](https://img.shields.io/badge/Language-English-red.svg)](https://github.com/demianblogan/Game_4-Aircraft_Shooter/edit/main/README.md)
[![ru](https://img.shields.io/badge/Language-Russian-blue.svg)](https://github.com/demianblogan/Game_4-Aircraft_Shooter/edit/main/README.ru.md)
[![ua](https://img.shields.io/badge/Language-Ukrainian-green.svg)](https://github.com/demianblogan/Game_4-Aircraft_Shooter/edit/main/README.ua.md)

# **Overview**<br />
This is my 3rd game for my portfolio. This project is written in C++ with SFML. It's an aircraft shooter with a top-down camera. You control an aircraft with WASD keys (by default). You can shoot bullets and missiles (keys SPACE and M by default). Bullets fly straight up, missiles try to find an enemy aircraft and fly toward it. Every aircraft has health points (even yours). Your aircraft has a finite number of missiles. There are two types of enemy aircraft: the first one can shoot bullets, and the second one just flies. Enemies appear on the top of the window and fly down. If you run into one of the enemy aircraft, they'll be destroyed, but you'll get hit. Your goal is to reach the end of the level (you'll see a finish line at the end of it). If your health points fall below 0, you'll lose the game. The game has a few states - title screen state (the first one you'll see), main menu state (with items "Play", "Settings", and "Exit"), settings menu state (where you can bind keys with actions), game state (where you play actually), and pause state (press ESCAPE, when in the game state). When enemies are destroyed, they might drop pickups with a 33% chance.

![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/7861bf1a-6aed-4984-b622-1c11ea5dc7c2)

## **Game controls:**<br />
Arrow left -> Move aircraft left<br />
Arrow right -> Move aircraft right<br />
Arrow up -> Move aircraft up<br />
Arrow down -> Move aircraft down<br />
SPACE -> Shoot bullets<br />
M -> Launch missile<br />
ENTER -> Select menu item<br />
ESCAPE -> Pause game<br />

## **How to create and build this project in Visual Studio?**<br />
1. Download this repository as a .zip file and extract it:<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/536db98f-b1bd-40c9-983d-b31e1f2e235d)

2. Create an empty C++ project in Visual Studio:<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/f2da9908-e3c8-4840-bc92-62e61c981350)

3. Open the project's folder in File Explorer and move all files from the archive into it:<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/b01abf94-3866-45ca-86f6-a391e0669594)

4. Now you have to include these files to your project. At first, to make all those files visible in your project, click the button "Show all files" in Solution Explorer. After this select them, RMB on them and click "Include in Project":<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/cc97cdb1-4229-4360-a4e2-585e5eee5149)

5. In Project's Properties first set binaries location:<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/eb8f3659-4cc5-4ca4-af5e-f0b2745aeec8)

6. Connect SFML library to the project. Let's start from "include" folder. Go to the "C/C++" tab, find "Additional Include Directories", press the arrow on its right, and click "<Edit...>":<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/cb80df18-c8eb-45de-9b49-aba7b8734c6e)

7. Now do the same with "lib" folder: go to the tab "Linker", find "Additional Library Directories", press the arrow on its right, and click "<Edit...>":<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/dbaa2397-b082-433f-94de-e9ceeb1836f2)

8. Almost done. We only need to add .dll files to our project. Save your changes by clicking the "Apply" button at the bottom of the project's properties, change the configuration to "Debug", go to "Linker" -> "Input" tab, find "Additional Dependencies", click the arrow on its right, and click "<Edit...>".<br />
In the new window write the next lines:<br />
sfml-system-d.lib<br />
sfml-window-d.lib<br />
sfml-audio-d.lib<br />
sfml-graphics-d.lib<br />
sfml-network-d.lib<br />
and press "Ok" button.<br />
Do the same with "Release" configuration, but remove "-d" prefixes:<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/9d14f17b-bbf7-4705-81c1-8ef652ce94ea)
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/e87c4240-74da-4121-a74b-ba35a7bbc186)

9. Now you can compile the project.
