# StackShoot_public
This is a game that combines a block-falling puzzle with a shooting game!

---About This Game---
This game is kind a combination of a block-falling puzzle and a shooting game.

Your goal is to defeat the enemy as same as a general shooting game.
However, during the game, blocks are falling and gradually piling up.
When four or more blocks of the same type are connected, they will be erased like "Puyo Puyo".
You can gain temporary effects according to their types.
You can't move the blocks, but you can shoot and destroy the blocks to prevents them from stacking.
Determine which blocks to break and which not to break, and defeat the enemy with appropriate effects!

Good luck!!

**This game is made for only Windows PC**

---About Developing This Game---
I used the ”DxLib (https://dxlib.xsrv.jp/)” to develope this game. I would like to take this opportunity to express my appreciation.
As the enviroment of developing, I used Visual Studio 2022. 

In the root directory, ther are the source files(.cpp, .h) of this game. 
Please let me know if there is anything I can do to improve it.

---How To Play---
Download the "x64" folder to your local Windows PC. Then, execute "StackShoot.exe" which locates in "x64\Debug\" directory. Game will soon start then.
**This game is made for only Windows PC**

---Control Guide---
"up" key: move upward
"down" key: move downward
"right" key: move right
"left" key: move left.
"shift" key under the "enter" key: shoot  **"shift" key under the "caps lock" is not available**
"s" key: use a bomb. Bomb can erase the stacked blocks on the bottom row.
"Esc" key: finish the game

---Specification---
1. The enemy's HP is indicated on the left-up of the screen. Your goal is to reduce it to 0.
2. Your HP is indicated on the right-up of the screen. If it is reduced to 0, you lose.
3. The number of bombs you have is also indicated on the right-up of the screen. Bomb can erase the stacked blocks on the bottom row.
4. During the game, blocks fall from top to bottom of the screen. Blocks will stack  like "Tetris" or "Puyo Puyo".
5. You can't move the blocks yourself, but you can shoot and destroy falling blocks (not for stacked blocks).
6. When four or more blocks of the same type are connected, they will be erased. You can gain temporary effects according to their types. The effect you can gain is shown below.
  Normal block (gray color block): No effect
  Bomb block (bomb illustrated block): Get Bomb
  Heart block (heart illustrated block): Recover your HP
  Power block (P written block): Increse Damage you can inflict
  Speed block (S written block): Increse your movement speed
  Bubble block (bubble illustrated block): Provide a one-time barrier against enemy attacks
  Double block (W written block): Increase your shooting rate (x2)
  
