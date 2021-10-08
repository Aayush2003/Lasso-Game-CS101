NAME: AAYUSH RAJESH
ROLL NUMBER: 200070001
  
Help Document for game Lasso (Windows)
Video Demo:  https://drive.google.com/file/d/1f0jBvnGOsKsVRAcWs5aifQd5tXwxDm_F/view?usp=sharing


Total lives are 3. Run out of lives, game ends.
Click on initCanvas window after reading instructions to start game.
Level 1: One coin (yellow) is tossed vertically upwards. Catch 3 of these to progress.
Level 2: Coin, Bomb (black) and Mystery Box (green, randomized) are tossed in parabolic paths. Catching bomb decrements life count by 1. Catch 10 more coins to progress.
Level 3: This level runs for a limited period of time (countdown displayed on top right of screen). Only coins and bombs are tossed. Try to catch as many coins as possible.
Final score is displayed on the window with instructions.

Random number generator is implemented in this game to generate parabolic paths at random angles (coin angles between 95 and 105 degrees) as well as random properties of mystery boxes.
Implementation was learnt on the net from stackoverflow.com.

Properties of mystery boxes:
   1. No mystery box appears (probability roughly 0.33)
   2. Catching mystery box slows speed of lasso (probability roughly 0.2)
   3. Catching mystery box increases speed of lasso (probability roughly 0.2)
   4. Catching mystery box activates a coin magnet for a limited period of time that attracts the coin along the x-axis. The coin magnet fits into the empty slot on y-axis (probability roughly 0.13)
   5. Catching mystery box contributes a random bonus score that is added to the final score tally (probability roughly 0.13)
Last achieved enhancement will be diplayed on bottom-right of screen.

Controls:
   't'- throw lasso
   'l'- loop lasso
   'y'- yank lasso
   'q'- quit game
   ']'- angle of throw increases
   '['- angle of throw decreases
   In addition to these, there are 2 CHEAT CODES, whose sole use is to make it easier for a tester to operate the game. These are:
   '-'- decreases speed of lasso
   '='- increases speed of lasso 

NOTE: Time displayed on the top right is not actual time count, but in-game time count. This may vary from actual time count depending on compiler speeds, but are consistent within the game.

 