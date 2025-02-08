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

Working Logic -
- I made a C++ class that defines the basic properties of the boxes that are being spawned. It contains values like health and score points.
- Then, I exposed them to a blueprint. I set the specific health and score points values for that BP.
- I then made 2 other child blueprints from that box blubeprint to create the other 2 variants of the boxes.
- I then created 3 different materials with different colors for each BP and assigned them respectively
- Then I gave the boxes their attributes as per the mentioned info in the JSON file ( health and score points )
- Then I added a damage causing function in the projectile's class which damages the actor it contacts
- Then I made a damage receiving function in the box class to take damage and reduce health because of the projectile and destroy when health reaches zero
- I also addeda score variable to the player and incremented it each time a box was damaged, based on the score value of the box
- Finally, I created a widget class and fixed a text binding there which gets updated with each increment in the player's score 

The major challenges are/were :
- Getting the JSON fetch feature to work properly using C++ <b>( partial implementation done, The 'BoxSpawner' and 'SpawnedBox' classes are present, please take a look )</b>
- Using the Data fetched from JSON file to create a dynamic material and spawn boxes with that material applied.
