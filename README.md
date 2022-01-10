# T3_AOOP_A5

A5: FSM Part 2 (due June 13th)
Marking breakdown:

50% for logic and clarity of code
25% for clear and concise commenting throughout
25% for completion
Instructions
Use you ArcadeGame of previous assignment or download "ArcadeGame.zip" and extract the project;
Create a new enemy Actor called AlienShip;
Implement the AlienShip behaviour as a FSM following the FSM diagram attached.
AlienShip starts the game with 3 HP.
AlienShip shots a bullet downwards while it is in the Shot state (shot cooldown is 1.5 seconds).
AlienShip randomly and slowly moves sideways while in Search state (it doesn't collide with asteroid, the collision shouldn't be accounted);
AlienShip is born outside of screen at the top edge, it descends up to 10% of game screen then starts Searching.
AlienShip runs away by moving upwards.
After an alien ship runs away, a new one is reborn after 5 seconds.
Submission

ZIP the ENTIRE PROJECT FOLDER, not just the .cpp or .h files
Only upload via Moodle, no email or external services submissions
Notes
Call your project anything you want - and submit a zip file with the following filename:
"PG##YourName_AOOP_a1.zip"

If you project is greater than 20MB, delete .vs and Obj folders before zipping it.
Back up your work! Whenever you work on your project, copy the entire project folder to your flash drive AND the network drive. Copying it to Dropbox or Google Drive isn’t a bad idea either
