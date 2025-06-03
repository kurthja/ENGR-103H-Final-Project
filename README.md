Jack Kurth
ENGR 103H
Udell
11 June, 2025
ENGR 103H Final Project - Reaction Game

Rules:
Game start: 2 second timer
A RANDOM light lights up. If it is on the right side of the board, flip the board to the right. If it is on the left side of the board, flip the board to the left.
If this is not completed in 2 seconds, the time expires and the board will flash red entirely and a MIDI tone will play. The game is over, flip the switch to restart the game. 

After every successful response to the random event, the timer will decrease by 10 milliseconds.


Key Mappings:
Inputs: 
Accelerometer X-values (0-10, scaled -90 - 90): Allows user to reset timer by flipping CPX board in specified direction by game. 
Switch (pin 7): Allows user to restart timer if game ends
Outputs:
Pixels (ALL) (0-9) (0-255 range): Used for random pixel generation, ending game by flashing red pixels
Speaker (A0) (vol 250): Outputs high/low MIDI pitches (60) which indicate that the game is over

