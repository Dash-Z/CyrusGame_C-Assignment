Hello there, I'm Muktikanta Dash
I made this small FPS game in UE5 using C++ as part of an assignment submission to Cyrus365.

The following targets were achieved successfully --
- Spawning boxes of different colors with different health and score values
- Using projectile system to shoot the boxes and reduce their health and eventually destroy them
- Updating player's score depending on which box they shoot at
- Showing the player's updated score on the screen using a Widget

The following features are still WIP --
- Fetching data from a JSON File online to spawn the boxes based on the specified parameters

The project was built completely using unreal C++ where Blueprint instances were used where necessary to spawn the classes into the game world.
The major challenges are/were :
- Getting the JSON fetch feature to work properly using C++
- Using the Data fetched from JSON file to create a dynamic material and spawn boxes with that material applied.
