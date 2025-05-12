#include "iGraphics.h"
#include<iostream>
#include<string.h>
#include<math.h>
#include"imageLoader.h"
#include "Variables.h"
#include"score.h"
#include "music.h"
#include "menu.h"
using namespace std;
void resetGame();
class background{
public :
	int x, y;
};
class bomb{
public :
	int x, y;
	bool bomb_visible;
};
class box{
public :
	int x, y;
	bool box_visible;
};
class enemyBird{
public :
	int bird_x,bird_y,bird_index;
	bool bird_visible;
};
class enemyMonster{
public :
	int monster_x, monster_y,monster_index,monster_mellee_index;
	bool monster_visible,monster_mellee;
};
class enemyZombie{
public :
	int zombie_x, zombie_y, zombie_index, zombie_mellee_index,zombie_idle_index;
	bool zombie_visible, zombie_mellee,zombie_idle;
};
background upperbg_lvl1[10];
background lowerbg_lvl1[10];
background upperbg_lvl2[10];
background lowerbg_lvl2[10];
background upperbg_lvl3[10];
background lowerbg_lvl3[10];
background upperbg_lvl4[10];
background lowerbg_lvl4[10];
enemyBird birds[BIRDNUMBER];
enemyMonster monsters[MONSTERNUMBER];
enemyMonster monsters_level2[MONSTER_LEVEL2];
enemyMonster monsters_level3[MONSTER_LEVEL3];
enemyZombie zombies[ZOMBIENUMBER];
enemyZombie zombies_level2[ZOMBIE_LEVEL2];
enemyZombie zombies_level3[ZOMBIE_LEVEL3];
bomb level1_bomb[BOMBNUMBER];
box level2_box[BOXNUMBER];
void menuBar(){
	iShowImage(0, 0, WIDTH, HEIGHT, Menu);
	for (int i = 0; i < 5; i++){
		iShowBMP2(menu_buttons[i].x,menu_buttons[i].y,menubuttons[i],0);
	}
}
void lifeBar(){
	if (lifebarVisible){
		iShowBMP2(10, 740, life[life_index], 0);
	}
}
void bossLifeBar(){
	if (bossVisible){
		iShowBMP2(WIDTH - 350, 700, bossLife[bossLifeIndex], 0);
	}
}
void gamePause(){
	iShowBMP2((WIDTH / 2) - 140, (HEIGHT / 2) - 140, "images\\pausePlay.bmp", 0);
}
void Player1Movement(){
	if (player1Visible){
		if (jumping){
			if (jumpup){
				iShowBMP2(player1X, player1Y + playerJump, jump[0], 0);
			}
			else{
				iShowBMP2(player1X, player1Y + playerJump, jump[1], 0);
			}
		}
		if (firing&&front){
			iShowBMP2(fireX, fireY, fire[0], 0);
		}
		if (firing&&back){
			iShowBMP2(fireX, fireY, fire[1], 0);
		}
		if (standing){
			runningBackward = runningForward = false;
			iShowBMP2(player1X, player1Y, stand[stand_index], 0);
		}
		if (standRev){
			runningBackward = runningForward = false;
			iShowBMP2(player1X, player1Y, standingRev[stand_index], 0);
		}
		if (playerMellee&&front){
			iShowBMP2(melleeX, melleeY, player1_mellee[player1_mellee_index], 0);
		}
		if (runningForward){
			iShowBMP2(player1X, player1Y, run[run_index], 0);
			stand_counter++;
			if (stand_counter >= 25){
				stand_counter = 0; run_index = 0;
				standing = true;
				running = false;
			}
		}
		if (runningBackward){
			iShowBMP2(player1X, player1Y, rev[run_index], 0);
			stand_counter++;
			if (stand_counter >= 25){
				stand_counter = 0; run_index = 0;
				standRev = true;
				running = false;
			}
		}
	}
}
void player2Movement(){
	if (player2Visible){
		if (jumping){
			if (jumpup){
				iShowBMP2(player2X, player2Y + playerJump, jump_level2[0], 0);
			}
			else{
				iShowBMP2(player2X, player2Y + playerJump, jump_level2[1], 0);
			}
		}
		if (standing){
			runningBackward = runningForward = false;
			iShowBMP2(player2X, player2Y, stand_level2[stand_index], 0);
		}
		if (standRev){
			runningBackward = runningForward = false;
			iShowBMP2(player2X, player2Y, standrev_level2[stand_index], 0);
		}
		if (playerMellee&&front){
			iShowBMP2(melleeX, melleeY, player2_mellee[player2_mellee_index], 0);
		}
		if (firing&&front){
			iShowBMP2(fireX, fireY, fire[0], 0);
		}
		if (firing&&back){
			iShowBMP2(fireX, fireY, fire[1], 0);
		}
		if (runningForward){
			iShowBMP2(player2X, player2Y, run_level2[run_index], 0);
			stand_counter++;
			if (stand_counter >= 25){
				stand_counter = 0; run_index = 0;
				standing = true;
				running = false;
			}
		}
		if (runningBackward){
			iShowBMP2(player2X, player2Y, rev_level2[run_index], 0);
			stand_counter++;
			if (stand_counter >= 25){
				stand_counter = 0; run_index = 0;
				standRev = true;
				running = false;
			}
		}
	}
}
void player3Movement(){
	if (player3Visible){
		if (jumping){
			if (jumpup){
				iShowBMP2(player3X, player3Y + playerJump, jump_level3[0], 0);
			}
			else{
				iShowBMP2(player3X, player3Y + playerJump, jump_level3[1], 0);
			}
		}
		if (standing){
			runningBackward = runningForward = false;
			iShowBMP2(player3X, player3Y, stand_level3[stand_index], 0);
		}
		if (standRev){
			runningBackward = runningForward = false;
			iShowBMP2(player3X, player3Y, standrev_level3[stand_index], 0);
		}
		if (playerMellee&&front){
			iShowBMP2(melleeX, melleeY, player3_mellee[player3_mellee_index], 0);
		}
		if (firing&&front){
			iShowBMP2(fireX, fireY, fire[0], 0);
		}
		if (firing&&back){
			iShowBMP2(fireX, fireY, fire[1], 0);
		}
		if (runningForward){
			iShowBMP2(player3X, player3Y, run_level3[run_index], 0);
			stand_counter++;
			if (stand_counter >= 25){
				stand_counter = 0; run_index = 0;
				standing = true;
				running = false;
			}
		}
		if (runningBackward){
			iShowBMP2(player3X, player3Y, rev_level3[run_index], 0);
			stand_counter++;
			if (stand_counter >= 25){
				stand_counter = 0; run_index = 0;
				standRev = true;
				running = false;
			}
		}
	}
}
void bossMovement(){
	if (bossLevel){
		if (bossVisible){
			if (bossJumping){
				if (bossJumpUp){
					iShowBMP2(bossX, bossY + bossJump, boss_jump[0], 0);
				}
				else{
					iShowBMP2(bossX, bossY + bossJump, boss_jump[1], 0);
				}
			}
			if (bossRunForward){
				iShowBMP2(bossX, bossY, boss_run[bossRunIndex], 0);
			}
			if (bossRunBackward){
				iShowBMP2(bossX, bossY, boss_reverse[bossRunIndex], 0);
			}
			if (bossfiring&&bossRunForward){
				iShowBMP2(bossFireX, bossFireY, fire[1], 0);
			}
			if (bossfiring&&bossRunBackward){
				iShowBMP2(bossFireX, bossFireY, fire[0], 0);
			}
		}
	}
}
void monsterMovement(){
	for (int i = 0; i < MONSTERNUMBER; i++){
		if (monsters[i].monster_visible){
			if (monsters[i].monster_mellee){
				iShowBMP2(monsters[i].monster_x, monsters[i].monster_y, enemy2_mellee[monsters[i].monster_mellee_index], 0);
			}
			else{
				iShowBMP2(monsters[i].monster_x, monsters[i].monster_y, enemy2_lvl1[monsters[i].monster_index], 0);
			}
		}
	}
}
void zombieMovement(){
	for (int i = 0; i < ZOMBIENUMBER; i++){
		if (zombies[i].zombie_visible){
			if (zombies[i].zombie_idle) {
				iShowBMP2(zombies[i].zombie_x, zombies[i].zombie_y, enemy3_idle[zombies[i].zombie_idle_index], 0);
			}
			else if (zombies[i].zombie_mellee) {
				iShowBMP2(zombies[i].zombie_x, zombies[i].zombie_y, enemy3_mellee[zombies[i].zombie_mellee_index], 0);
			}
			else {
				iShowBMP2(zombies[i].zombie_x, zombies[i].zombie_y, enemy3_lvl1[zombies[i].zombie_index], 0);
			}
		}
	}
}
void bombRender(){
	for (int i = 0; i < BOMBNUMBER; i++){
		if (level1_bomb[i].bomb_visible){
			iShowBMP2(level1_bomb[i].x, level1_bomb[i].y, bomb_level1[0], 0);
		}
	}
}
void boxRender(){
	for (int i = 0; i < BOXNUMBER; i++){
		if (level2_box[i].box_visible){
			iShowBMP(level2_box[i].x, level2_box[i].y, box_level2[0]);
		}
	}
}
void monsterMovementlvl2(){
	for (int i = 0; i < MONSTER_LEVEL2; i++){
		if (monsters_level2[i].monster_visible){
			if (monsters_level2[i].monster_mellee){
				iShowBMP2(monsters_level2[i].monster_x, monsters_level2[i].monster_y, enemy1_level2_mellee[monsters_level2[i].monster_mellee_index], 0);
			}
			else{
				iShowBMP2(monsters_level2[i].monster_x, monsters_level2[i].monster_y, enemy1_level2[monsters_level2[i].monster_index], 0);
			}
		}
	}
}
void zombieMovementlvl2(){
	for (int i = 0; i < ZOMBIE_LEVEL2; i++){
		if (zombies_level2[i].zombie_visible){
			if (zombies_level2[i].zombie_idle){
				iShowBMP2(zombies_level2[i].zombie_x, zombies_level2[i].zombie_y, enemy2_level2_idle[zombies_level2[i].zombie_idle_index], 0);
			}
			else if (zombies_level2[i].zombie_mellee){
				iShowBMP2(zombies_level2[i].zombie_x,zombies_level2[i].zombie_y,enemy2_level2_mellee[zombies_level2[i].zombie_mellee_index],0);
			}
			else{
				iShowBMP2(zombies_level2[i].zombie_x, zombies_level2[i].zombie_y, enemy2_level2[zombies_level2[i].zombie_index], 0);
			}
		}
	}
}
void monsterMovementlvl3(){
	for (int i = 0; i < MONSTER_LEVEL3; i++){
		if (monsters_level3[i].monster_visible){
			if (monsters_level3[i].monster_mellee){
				iShowBMP2(monsters_level3[i].monster_x, monsters_level3[i].monster_y, enemy1_level3_mellee[monsters_level3[i].monster_mellee_index], 0);
			}
			else{
				iShowBMP2(monsters_level3[i].monster_x, monsters_level3[i].monster_y, enemy1_level3_run[monsters_level3[i].monster_index], 0);
			}
		}
	}
}
void zombieMovementlvl3(){
	for (int i = 0; i < ZOMBIE_LEVEL3; i++){
		if (zombies_level3[i].zombie_visible){
			if (zombies_level3[i].zombie_idle){
				iShowBMP2(zombies_level3[i].zombie_x, zombies_level3[i].zombie_y, enemy2_level3_idle[zombies_level3[i].zombie_idle_index], 0);
			}
			else if (zombies_level3[i].zombie_mellee){
				iShowBMP2(zombies_level3[i].zombie_x, zombies_level3[i].zombie_y, enemy2_level3_mellee[zombies_level3[i].zombie_mellee_index], 0);
			}
			else{
				iShowBMP2(zombies_level3[i].zombie_x, zombies_level3[i].zombie_y, enemy2_level3_run[zombies_level3[i].zombie_index], 0);
			}
		}
	}
}
void backGroundRender_level1(){
	for (int i = 0; i < 10; i++){
		//iShowBMP(upperbg_lvl1[i].x,upperbg_lvl1[i].y, upperbglvl1[i]);
		//iShowBMP(lowerbg_lvl1[i].x, lowerbg_lvl1[i].y, lowerbglvl1[i]);
		iShowImage(upperbg_lvl1[i].x,upperbg_lvl1[i].y,152,650,upperbackgroundlvl1[i]);
		iShowImage(lowerbg_lvl1[i].x, lowerbg_lvl1[i].y, 152, 150, lowerbackgroundlvl1[i]);
	}
}
void backgroundRender_level2(){
	for (int i = 0; i < 10; i++){
		iShowImage(upperbg_lvl2[i].x, upperbg_lvl2[i].y, 152, 673, upperbackgroundlvl2[i]);
		iShowImage(lowerbg_lvl2[i].x, lowerbg_lvl2[i].y, 152, 127, lowerbackgroundlvl2[i]);
	}
}
void backgroundREnder_level3(){
	for (int i = 0; i < 10; i++){
		iShowImage(upperbg_lvl3[i].x,upperbg_lvl3[i].y,152,550,upperbackgroundlvl3[i]);
		iShowImage(lowerbg_lvl3[i].x, lowerbg_lvl3[i].y, 152, 250, lowerbackgroundlvl3[i]);
	}
}
void backgroundRender_level4(){
	for (int i = 0; i < 10; i++){
		iShowImage(upperbg_lvl4[i].x, upperbg_lvl4[i].y, 152, HEIGHT-150, upperbackgroundlvl4[i]);
		iShowImage(lowerbg_lvl4[i].x, lowerbg_lvl4[i].y, 152, 150, lowerbackgroundlvl4[i]);
	}
}
void level1EndRender(){
	if (lvl1end_keyVisible){
		iShowBMP2(700, 150, level1_End[1], 0);
	}
		iShowBMP2(WIDTH-300,150,level1_End[0],0);
		if (player1X >= WIDTH - 300&&(lvl1end_keyVisible==false)){
			level++;
			playMusic(true);
			lifebarVisible = true;
			life_index = 0;
			player1Visible = false;
			player2Visible = true;
			level2Characters = true;
		}
}
void level2EndRender(){
	if (lvl2end_keyVisible){
		iShowBMP2(700,50,level2_End[1],0);
	}
	iShowBMP2(WIDTH-420,50,level2_End[0],0);
	if (player2X >= WIDTH - 420&&(lvl2end_keyVisible==false)){
		level++;
		playMusic(true);
		lifebarVisible = true;
		life_index = 0;
		player2Visible = false;
		player3Visible = true;
		level3Characters = true;
	}
}
void level3EndRender(){
	iShowBMP2(WIDTH-300,120,level3_End[0],0);
	if (player3X >= WIDTH - 300){
		level++;
		playMusic(true);
		//backgroundMusic = true;
		lifebarVisible = true;
		life_index = 0;
		bossLevel = true;
		bossVisible = true;
		player3Visible = false;
		player1Visible = true;
		player1X = player2X = player3X = 0;
		bossLevelTime = 10;
	}
}
void level4EndRender(){
	iShowBMP2(WIDTH - 300, 100, "images\\Level 4\\LevelEnd\\tressure.bmp", 0);
	if (player1Visible){
		if (player1X >= WIDTH - 300){
			completeGame = true;
			gameState = -2;
		}
	}
	else if (player2Visible){
		if (player2X >= WIDTH - 300){
			completeGame = true;
			gameState = -2;
		}
	}
	else if (player3Visible){
		if (player3X >= WIDTH - 300){
			completeGame = true;
			gameState = -2;
		}
	}
}
void collisionCheck(){
	if (!pause){
		if (level == 1 && level1Characters){
			for (int i = 0; i < MONSTERNUMBER; i++){
				if (monsters[i].monster_visible && player1Visible){
					if ((player1X + 115 >= monsters[i].monster_x&&player1X <= monsters[i].monster_x + 100) && (player1Y + playerJump >= monsters[i].monster_y&&player1Y + playerJump <= monsters[i].monster_y + 100)){
						life_index += 1;
						if (life_index >= 5){
							player1Visible = false;
							life_index = 5;
							lifebarVisible = false;
							monsters[i].monster_mellee = false;
							gameOver = true;
							playMusic(true);
							pause = true;
							gameState = -2;
							highscore(killScore);
						}
					}
				}
			}
			for (int i = 0; i < ZOMBIENUMBER; i++){
				if (zombies[i].zombie_visible && player1Visible){
					if ((player1X + 115 >= zombies[i].zombie_x&&player1X <= zombies[i].zombie_x + 100) && (player1Y + playerJump >= zombies[i].zombie_y&&player1Y + playerJump <= zombies[i].zombie_y + 100)){
						life_index += 1;
						if (life_index >= 5){
							player1Visible = false;
							life_index = 5;
							lifebarVisible = false;
							zombies[i].zombie_mellee = false;
							gameOver = true;
							playMusic(true);
							pause = true;
							gameState = -2;
							highscore(killScore);
						}
					}
				}
			}
			for (int i = 0; i < BOMBNUMBER; i++){
				if (level1_bomb[i].bomb_visible && player1Visible){
					if ((player1X + 115 >= level1_bomb[i].x&&player1X <= level1_bomb[i].x + 75) && (player1Y + playerJump >= level1_bomb[i].y&&player1Y + playerJump <= level1_bomb[i].y + 61)){
						life_index += 1;
						level1_bomb[i].bomb_visible = false;
						if (life_index >= 5){
							player1Visible = false;
							life_index = 5;
							lifebarVisible = false;
							gameOver = true;
							playMusic(true);
							pause = true;
							gameState = -2;
							highscore(killScore);
						}
					}
				}
			}
		}
		else if (level == 2 && level2Characters){
			for (int i = 0; i < MONSTER_LEVEL2; i++){
				if (monsters_level2[i].monster_visible && player2Visible){
					if ((player2X + 100 >= monsters_level2[i].monster_x&&player2X <= monsters_level2[i].monster_x + 125) && (player1Y + playerJump <= monsters_level2[i].monster_y + 204 && player1Y + playerJump >= monsters_level2[i].monster_y)){
						life_index += 1;
						if (life_index >= 5){
							lifebarVisible = false;
							player2Visible = false;
							life_index = 5;
							monsters_level2[i].monster_mellee = false;
							gameOver = true;
							playMusic(true);
							pause = true;
							gameState = -2;
							highscore(killScore);
						}
					}
				}
			}
			for (int i = 0; i < ZOMBIE_LEVEL2; i++){
				if (zombies_level2[i].zombie_visible && player2Visible){
					if ((player2X + 100 >= zombies_level2[i].zombie_x&&player2X <= zombies_level2[i].zombie_x + 99) && (player2Y + playerJump <= zombies_level2[i].zombie_y + 137 && player2Y + playerJump >= zombies_level2[i].zombie_y)){
						life_index += 1;
						if (life_index >= 5){
							lifebarVisible = false;
							player2Visible = false;
							life_index = 5;
							zombies_level2[i].zombie_mellee = false;
							gameOver = true;
							playMusic(true);
							pause = true;
							gameState = -2;
							highscore(killScore);
						}
					}
				}
			}
			for (int i = 0; i < BOXNUMBER; i++){
				if (level2_box[i].box_visible && player2Visible){
					if ((player2X + 100 >= level2_box[i].x&&player2X <= level2_box[i].x + 100) && (player2Y + playerJump <= level2_box[i].y + 100 && player2Y + playerJump >= level2_box[i].y)){
						life_index += 1;
						if (life_index >= 5){
							life_index = 5;
							lifebarVisible = false;
							player2Visible = false;
							level2_box[i].box_visible = false;
							gameOver = true;
							playMusic(true);
							pause = true;
							gameState = -2;
							highscore(killScore);
						}
					}
				}
			}
		}
		else if (level == 3 && level3Characters){
			for (int i = 0; i < MONSTERNUMBER; i++){
				if (monsters[i].monster_visible && player3Visible){
					if ((player3X + 112 >= monsters[i].monster_x&&player3X <= monsters[i].monster_x + 100) && (player3Y + playerJump >= monsters[i].monster_y&&player3Y + playerJump <= monsters[i].monster_y + 100)){
						life_index += 1;
						if (life_index >= 5){
							player1Visible = false;
							life_index = 5;
							lifebarVisible = false;
							monsters[i].monster_mellee = false;
							gameOver = true;
							playMusic(true);
							pause = true;
							gameState = -2;
							highscore(killScore);
						}
					}
				}
			}
			for (int i = 0; i < MONSTER_LEVEL3; i++){
				if (monsters_level3[i].monster_visible&&player3Visible){
					if ((player3X + 112 >= monsters_level3[i].monster_x&&player3X <= monsters_level3[i].monster_x + 83) && (player3Y + playerJump <= monsters_level3[i].monster_y + 117 && player3Y + playerJump >= monsters_level3[i].monster_y)){
						life_index += 1;
						if (life_index >= 5){
							life_index = 5;
							lifebarVisible = false;
							player3Visible = false;
							monsters_level3[i].monster_visible = false;
							gameOver = true;
							playMusic(true);
							pause = true;
							gameState = -2;
							highscore(killScore);
						}
					}
				}
			}
			for (int i = 0; i < ZOMBIE_LEVEL3; i++){
				if (zombies_level3[i].zombie_visible&&player3Visible){
					if ((player3X + 112 >= zombies_level3[i].zombie_x&&player3X <= zombies_level3[i].zombie_x + 80) && (player3Y + playerJump <= zombies_level3[i].zombie_y + 119 && player3Y + playerJump >= zombies_level3[i].zombie_y)){
						life_index += 1;
						if (life_index >= 5){
							life_index = 5;
							lifebarVisible = false;
							player3Visible = false;
							monsters_level3[i].monster_visible = false;
							gameOver = true;
							playMusic(true);
							pause = true;
							gameState = -2;
							highscore(killScore);
						}
					}
				}
			}
		}
		else if (level == 4 && bossLevel){
			if (player1Visible){
				for (int i = 0; i < BOMBNUMBER; i++){
					if (level1_bomb[i].bomb_visible){
						if ((player1X + 115 >= level1_bomb[i].x&&player1X <= level1_bomb[i].x + 75) && (player1Y + playerJump >= level1_bomb[i].y&&player1Y + playerJump <= level1_bomb[i].y + 61)){
							life_index += 1;
							level1_bomb[i].bomb_visible = false;
							if (life_index >= 5){
								life_index = 0;
								player1Visible = false;
								player2Visible = true;
							}
						}
					}
				}
			}
			else if (player2Visible){
				for (int i = 0; i < BOMBNUMBER; i++){
					if (level1_bomb[i].bomb_visible){
						if ((player2X + 100 >= level1_bomb[i].x&&player2X <= level1_bomb[i].x + 75) && (player2Y + playerJump >= level1_bomb[i].y&&player2Y + playerJump <= level1_bomb[i].y + 61)){
							life_index += 1;
							level1_bomb[i].bomb_visible = false;
							if (life_index >= 5){
								life_index = 0;
								player2Visible = false;
								player3Visible = true;
							}
						}
					}
				}
			}
			else if (player3Visible){
				for (int i = 0; i < BOMBNUMBER; i++){
					if (level1_bomb[i].bomb_visible){
						if ((player3X + 112 >= level1_bomb[i].x&&player3X <= level1_bomb[i].x + 75) && (player3Y + playerJump >= level1_bomb[i].y&&player3Y + playerJump <= level1_bomb[i].y + 61)){
							life_index += 1;
							level1_bomb[i].bomb_visible = false;
							if (life_index >= 5){
								life_index = 5;
								gameOver = true;
								//backgroundMusic = false;
								playMusic(true);
								pause = true;
								gameState = -2;
								player3Visible = false;
								lifebarVisible = false;
								highscore(killScore);
							}
						}
					}
				}
			}
		}
	}
}
void bossCollisionCheck(){
	if (!pause){
		if (level == 4 && bossLevel){
			if (player1Visible&&bossVisible&&bossfiring){
				if ((player1X <= bossFireX + 27 && player1X + 115 >= bossFireX) && (player1Y + playerJump <= bossFireY + 10 && player1Y + playerJump + 130 >= bossFireY)){
					if (player1Visible&&bossVisible) life_index += 1;
					bossfiring = false;
					random = 0;
					bossFireX = bossX + 10000000000000000000;
					if (life_index >= 5){
						life_index = 0;
						player1Visible = false;
						player2Visible = true;
					}
				}
			}
			else if (player2Visible&&bossVisible&&bossfiring){
				if ((player2X <= bossFireX + 27 && player2X + 100 >= bossFireX) && (player2Y + playerJump + 135 >= bossFireY&&player2Y + playerJump <= bossFireY + 10)){
					if (player2Visible&&bossVisible) life_index += 1;
					bossfiring = false;
					random = 0;
					bossFireX = bossX + 10000000000000000000;
					if (life_index >= 5){
						life_index = 0;
						player2Visible = false;
						player3Visible = true;
					}
				}
			}
			else if (player3Visible&&bossVisible&&bossfiring){
				if ((player3X <= bossFireX + 27 && player3X + 112 >= bossFireX) && (player3Y + playerJump + 135 >= bossFireY&&player3Y + playerJump <= bossFireY + 10)){
					if (player3Visible&&bossVisible) life_index += 1;
					bossfiring = false;
					random = 0;
					bossFireX = bossX + 10000000000000000000;
					if (life_index >= 5){
						life_index = 5;
						gameOver = true;
						//backgroundMusic = false;
						playMusic(true);
						pause = true;
						gameState = -2;
						player3Visible = false;
						lifebarVisible = false;
						highscore(killScore);
					}
				}
			}
		}
	}
}
void fireAndMelleeCollisionCheck(){
	if (!pause){
		if (firing){
			if (level == 1){
				for (int i = 0; i < MONSTERNUMBER; i++){
					if (monsters[i].monster_visible){
						if ((fireX + 27 >= monsters[i].monster_x&&fireX <= monsters[i].monster_x + 103) && (fireY <= monsters[i].monster_y + 100 && fireY + 19 >= monsters[i].monster_y)){
							monsters[i].monster_visible = false;
							firing = false;
							fireX = player1X + 10000000000000000000;
							enemyKilled++;
							killScore += 5;
						}
					}
				}
				for (int i = 0; i < ZOMBIENUMBER; i++){
					if (zombies[i].zombie_visible){
						if ((fireX + 27 >= zombies[i].zombie_x&&fireX <= (zombies[i].zombie_x + 100)) && (fireY <= zombies[i].zombie_y + 100)){
							zombies[i].zombie_visible = false;
							firing = false;
							fireX = player1X + 10000000000000000000;
							enemyKilled++;
							killScore += 5;
						}
					}
				}
			}
			else if (level == 2){
				for (int i = 0; i < MONSTER_LEVEL2; i++){
					if (monsters_level2[i].monster_visible){
						if ((fireX <= monsters_level2[i].monster_x + 125 && fireX + 27 >= monsters_level2[i].monster_x) && (fireY <= monsters_level2[i].monster_y + 204 && fireY + 19 >= monsters_level2[i].monster_y)){
							monsters_level2[i].monster_visible = false;
							firing = false;
							fireX = player2X + 10000000000000000000;
							enemyKilled++;
							killScore += 5;
						}
					}
				}
				for (int i = 0; i < ZOMBIE_LEVEL2; i++){
					if (zombies_level2[i].zombie_visible){
						if ((fireX + 27 >= zombies_level2[i].zombie_x&&fireX <= zombies_level2[i].zombie_x + 96) && (fireY + 19 >= zombies_level2[i].zombie_y&&fireY <= zombies_level2[i].zombie_y + 142)){
							zombies_level2[i].zombie_visible = false;
							firing = false;
							fireX = player2X + 10000000000000000000;
							enemyKilled++;
							killScore += 5;
						}
					}
				}
			}
			else if (level == 3){
				for (int i = 0; i < MONSTERNUMBER; i++){
					if (monsters[i].monster_visible){
						if ((fireX + 27 >= monsters[i].monster_x&&fireX <= monsters[i].monster_x + 103) && (fireY <= monsters[i].monster_y + 100 && fireY + 19 >= monsters[i].monster_y)){
							monsters[i].monster_visible = false;
							firing = false;
							fireX = player3X + 10000000000000000000;
							enemyKilled++;
							killScore += 5;
						}
					}
				}
				for (int i = 0; i < ZOMBIE_LEVEL3; i++){
					if (zombies_level3[i].zombie_visible){
						if ((fireX + 27 >= zombies_level3[i].zombie_x&&fireX <= zombies_level3[i].zombie_x + 80) && (fireY + 19 >= zombies_level3[i].zombie_y&&fireY <= zombies_level3[i].zombie_y + 119)){
							zombies_level3[i].zombie_visible = false;
							firing = false;
							fireX = player3X + 10000000000000000000;
							enemyKilled++;
							killScore += 5;
						}
					}
				}
				for (int i = 0; i < MONSTER_LEVEL3; i++){
					if (monsters_level3[i].monster_visible){
						if ((fireX <= monsters_level3[i].monster_x + 83 && fireX + 27 >= monsters_level3[i].monster_x) && (fireY <= monsters_level3[i].monster_y + 117 && fireY + 19 >= monsters_level3[i].monster_y)){
							monsters_level3[i].monster_visible = false;
							firing = false;
							fireX = player3X + 10000000000000000000;
							enemyKilled++;
							killScore += 5;
						}
					}
				}
			}
			else if (level == 4 && bossLevel){
				if ((player1Visible||player2Visible||player3Visible)&&bossVisible){
					if ((fireX + 27 >= bossX&&fireX <= bossX + 121) && (fireY <= bossY + 157 && fireY + 19 >= bossY)){
						bossLifeIndex += 1;
						firing = false;
						if (player1Visible) fireX = player1X + 10000000000000000000;
						else if (player2Visible) fireX = player2X + 10000000000000000000;
						else if(player3Visible) fireX = player3X + 10000000000000000000;
						killScore += 5;
						if (bossLifeIndex >= 7 && counts < 3){
							bossLifeIndex = 0;
							counts += 1;
						}
						else if(bossLifeIndex>=7 && counts == 3){
							bossLifeIndex = 7;
							bossVisible = false;
							bossLevel = false;
							highscore(killScore);
						}
					}
				}
			}
		}
		else if (playerMellee){
			if (level == 1){
				for (int i = 0; i < MONSTERNUMBER; i++){
					if (monsters[i].monster_visible){
						if ((melleeX + 108 >= monsters[i].monster_x&&melleeX <= monsters[i].monster_x + 110) && (melleeY + 100 <= monsters[i].monster_y + 100)){
							monsters[i].monster_visible = false;
							playerMellee = false;
							enemyKilled++;
							killScore += 5;
						}
					}
				}
				for (int i = 0; i < ZOMBIENUMBER; i++){
					if (zombies[i].zombie_visible){
						if ((melleeX + 108 >= zombies[i].zombie_x&&melleeX <= zombies[i].zombie_x + 98) && (melleeY + 100 <= zombies[i].zombie_y + 100)){
							zombies[i].zombie_visible = false;
							playerMellee = false;
							enemyKilled++;
							killScore += 5;
						}
					}
				}
			}
			else if (level == 2){
				for (int i = 0; i < MONSTER_LEVEL2; i++){
					if (monsters_level2[i].monster_visible){
						if ((melleeX + 110 >= monsters_level2[i].monster_x&&melleeX <= monsters_level2[i].monster_x + 125) && (melleeY + 100 <= monsters_level2[i].monster_y + 204)){
							monsters_level2[i].monster_visible = false;
							playerMellee = false;
							enemyKilled++;
							killScore += 5;
						}
					}
				}
				for (int i = 0; i < ZOMBIE_LEVEL2; i++){
					if (zombies_level2[i].zombie_visible){
						if ((melleeX + 110 >= zombies_level2[i].zombie_x&&melleeX <= zombies_level2[i].zombie_x + 99) && (melleeY + 100 <= zombies_level2[i].zombie_y + 137)){
							playerMellee = false;
							zombies_level2[i].zombie_visible = false;
							enemyKilled++;
							killScore += 5;
						}
					}
				}
			}
			else if (level == 3){
				for (int i = 0; i < MONSTERNUMBER; i++){
					if (monsters[i].monster_visible){
						if ((melleeX + 110 >= monsters[i].monster_x&&melleeX <= monsters[i].monster_x + 110) && (melleeY + 100 <= monsters[i].monster_y + 100 && melleeY + 100 >= monsters[i].monster_y)){
							monsters[i].monster_visible = false;
							playerMellee = false;
							enemyKilled++;
							killScore += 5;
						}
					}
				}
				for (int i = 0; i < MONSTER_LEVEL3; i++){
					if (monsters_level3[i].monster_visible){
						if ((melleeX + 110 >= monsters_level3[i].monster_x&&melleeX <= monsters_level3[i].monster_x + 83) && (melleeY + 100 <= monsters_level3[i].monster_y + 117 && melleeY + 100 >= monsters_level3[i].monster_y)){
							playerMellee = false;
							monsters_level3[i].monster_visible = false;
							enemyKilled++;
							killScore += 5;
						}
					}
				}
				for (int i = 0; i < ZOMBIE_LEVEL3; i++){
					if (zombies_level3[i].zombie_visible){
						if ((melleeX + 110 >= zombies_level3[i].zombie_x&&melleeX <= zombies_level3[i].zombie_x + 80) && (melleeY + 100 <= zombies_level3[i].zombie_y + 119 && melleeY + 100 >= zombies_level3[i].zombie_y)){
							playerMellee = false;
							zombies_level3[i].zombie_visible = false;
							enemyKilled++;
							killScore += 5;
						}
					}
				}
			}
		}
	}
}
void iDraw()
{
	iClear();
	if (gameState == -1){
		menuBar();
	}
	if (gameState == 0 && level == 1){
		if (level1Characters){
			backGroundRender_level1();
			scoreCounter();
			lifeBar();
			monsterMovement();
			zombieMovement();
			bombRender();
			Player1Movement();
			if (pause) gamePause();
			iShowImage(WIDTH/2-(155/2),HEIGHT-69,155,69,iLoadImage("images\\Level 1.png"));
		}
		else{
			backGroundRender_level1();
			Player1Movement();
			level1EndRender();
			if (pause) gamePause();
		}
	}
	else if (gameState == 0 && level == 2){
		if (level2Characters){
			backgroundRender_level2();
			scoreCounter();
			lifeBar();
			monsterMovementlvl2();
			zombieMovementlvl2();
			boxRender();
			player2Movement();
			if (pause) gamePause();
			iShowImage(WIDTH / 2 - (155/2), HEIGHT - 69, 155, 69, iLoadImage("images\\Level 2.png"));
		}
		else{
			backgroundRender_level2();
			player2Movement();
			level2EndRender();
			if (pause) gamePause();
		}
	}
	else if (gameState == 0 && level == 3){
		if (level3Characters){
			backgroundREnder_level3();
			scoreCounter();
			lifeBar();
			monsterMovement();
			monsterMovementlvl3();
			zombieMovementlvl3();
			player3Movement();
			if (pause) gamePause();
			iShowImage(WIDTH / 2 - (155/2), HEIGHT - 69, 155, 69, iLoadImage("images\\Level 3.png"));
		}
		else{
			backgroundREnder_level3();
			player3Movement();
			level3EndRender();
			if (pause) gamePause();
		}
	}
	else if (gameState == 0 && level == 4){
		if (bossLevel){
			backgroundRender_level4();
			scoreCounter();
			lifeBar();
			bossLifeBar();
			if (player1Visible){
				Player1Movement();
			}
			else if (player2Visible){
				player2Movement();
			}
			else if (player3Visible){
				player3Movement();
			}
			bossMovement();
			bombRender();
			if (pause) gamePause();
			iShowImage(WIDTH / 2 - (155/2) , HEIGHT - 69, 155, 69, iLoadImage("images\\Level 4.png"));
		}
		else{
			backgroundRender_level4();
			level4EndRender();
			if (player1Visible){
				Player1Movement();
			}
			else if (player2Visible){
				player2Movement();
			}
			else if (player3Visible){
				player3Movement();
			}
		}
	}
	else if (gameState == 1){
		iShowImage(0, 0, WIDTH, HEIGHT, iLoadImage("images\\help.png"));
	}
	else if(gameState == 2){
		iShowImage(0,0,WIDTH,HEIGHT,score);
		showScore();
	}
	else if (gameState == 3){
		iShowImage(0,0,WIDTH,HEIGHT,aboutUs);
	}
	else if (gameState == 4){
		exit(0);
	}
	else if (completeGame){
		iShowImage(0, 0, WIDTH, HEIGHT, iLoadImage("images\\CONGO.png"));
		resetGame();
	}
	else if (gameOver){
		/*iSetColor(0,0,0);
		iShowImage(0, 0, WIDTH, HEIGHT, userName);
		iText(550,415,username,GLUT_BITMAP_TIMES_ROMAN_24);*/
		iShowImage(0, 0, WIDTH, HEIGHT, gameover);
		resetGame();
	}
}

void change(){
	if (!pause){
		if (level == 1){
			if (standing || standRev){
				stand_index++;
				if (stand_index > 3) stand_index = 0;
			}
			if (jumping){
				if (jumpup){
					playerJump += 5;
					if (playerJump >= JUMPLIMIT){
						jumpup = false;
					}
				}
				else{
					playerJump -= 5;
					if (playerJump < 0){
						playerJump = 0;
						jumping = false;
					}
				}
			}
			if (level1Characters == false){
				if ((player1X + 115 >= 700 && player1X <= 700 + 112) && (player1Y + playerJump <= 150 + 200 && player1Y + playerJump >= 115)){
					lvl1end_keyVisible = false;
				}
			}
			if (level1Characters){
				for (int i = 0; i < BOMBNUMBER; i++){
					level1_bomb[i].x -= 10;
					if (level1_bomb[i].x < 0) level1_bomb[i].x = WIDTH + rand() % 40000;
					if (level1_bomb[i].bomb_visible == false){
						level1_bomb[i].bomb_visible = true;
						level1_bomb[i].x = WIDTH + rand() % 40000;
					}
				}
				for (int i = 0; i < MONSTERNUMBER; i++){
					if (monsters[i].monster_visible){
						if (monsters[i].monster_mellee){
							monsters[i].monster_mellee_index++;
							if (monsters[i].monster_mellee_index >= 3) monsters[i].monster_mellee_index = 0;
							if (monsters[i].monster_x < player1X) monsters[i].monster_mellee = false;
						}
						else{
							monsters[i].monster_x -= 10;
							monsters[i].monster_index++;
							if (player1Visible){
								if (abs(monsters[i].monster_x - (player1X + 50)) <= 5) {
									monsters[i].monster_mellee = true;
								}
							}
							if (monsters[i].monster_x <= 0) monsters[i].monster_x = WIDTH + rand() % 80000 + rand() % 6;
							if (monsters[i].monster_index >= 5) monsters[i].monster_index = 0;
						}
					}
					if (monsters[i].monster_visible == false){
						monsters[i].monster_x = WIDTH + rand() % 100000 + rand() % 8;
						monsters[i].monster_y = 150;
						monsters[i].monster_visible = true;
					}
				}
				for (int i = 0; i < ZOMBIENUMBER; i++){
					if (zombies[i].zombie_visible){
						if (zombies[i].zombie_mellee){
							zombies[i].zombie_mellee_index++;
							if (zombies[i].zombie_mellee_index >= 5) zombies[i].zombie_mellee_index = 0;
							if (zombies[i].zombie_x < player1X) zombies[i].zombie_mellee = false;
						}
						else{
							zombies[i].zombie_x -= 5;
							if (zombies[i].zombie_x <= WIDTH - 150) zombies[i].zombie_idle = false;
							if (zombies[i].zombie_idle) zombies[i].zombie_idle_index++;
							else zombies[i].zombie_index++;
							if (player1Visible){
								if (abs(zombies[i].zombie_x - (player1X + 50)) <= 5){
									zombies[i].zombie_mellee = true;
								}
							}
							if (zombies[i].zombie_x <= 0) zombies[i].zombie_x = WIDTH + rand() % 60000 + rand() % 5;
							if (zombies[i].zombie_index >= 5) zombies[i].zombie_index = 0;
							if (zombies[i].zombie_idle_index >= 3) zombies[i].zombie_idle_index = 0;
						}
					}
					if (zombies[i].zombie_visible == false){
						zombies[i].zombie_x = WIDTH + rand() % 80000 + rand() % 5;
						zombies[i].zombie_y = 150;
						zombies[i].zombie_visible = true;
						zombies[i].zombie_idle = true;
					}
				}
			}
		}
		else if (level == 2){
			if (standing || standRev){
				stand_index++;
				if (stand_index > 3) stand_index = 0;
			}
			if (jumping){
				if (jumpup){
					playerJump += 5;
					if (playerJump >= JUMPLIMIT){
						jumpup = false;
					}
				}
				else{
					playerJump -= 5;
					if (playerJump < 0){
						playerJump = 0;
						jumping = false;
					}
				}
			}
			if (level2Characters == false){
				if ((player2X + 115 >= 700 && player2X <= 700 + 100) && (player2Y + playerJump <= 50 + 70 && player2Y + playerJump >= 50)){
					lvl2end_keyVisible = false;
				}
			}
			if (level2Characters){
				for (int i = 0; i < BOXNUMBER; i++){
					level2_box[i].x -= 10;
					if (level2_box[i].x < 0) level2_box[i].x = WIDTH + rand() % 50000;
					if (level2_box[i].box_visible == false){
						level2_box[i].box_visible = true;
						level2_box[i].x = WIDTH + rand() % 50000;
					}
				}
				for (int i = 0; i < MONSTER_LEVEL2; i++){
					if (monsters_level2[i].monster_visible){
						if (monsters_level2[i].monster_mellee){
							monsters_level2[i].monster_mellee_index++;
							if (monsters_level2[i].monster_mellee_index >= 3) monsters_level2[i].monster_mellee_index = 0;
							if (monsters_level2[i].monster_x < player2X) monsters_level2[i].monster_mellee = false;
						}
						else{
							monsters_level2[i].monster_x -= 10;
							monsters_level2[i].monster_index++;
							if (player2Visible){
								if (abs(monsters_level2[i].monster_x - (player2X + 60)) <= 5) {
									monsters_level2[i].monster_mellee = true;
								}
							}
							if (monsters_level2[i].monster_x <= 0) monsters_level2[i].monster_x = WIDTH + rand() % 60000 + rand() % 9;
							if (monsters_level2[i].monster_index >= 5) monsters_level2[i].monster_index = 0;
						}
					}
					if (monsters_level2[i].monster_visible == false){
						monsters_level2[i].monster_x = WIDTH + rand() % 100000 + rand() % 4;
						monsters_level2[i].monster_y = 50;
						monsters_level2[i].monster_visible = true;
					}
				}
				for (int i = 0; i < ZOMBIE_LEVEL2; i++){
					if (zombies_level2[i].zombie_visible){
						if (zombies_level2[i].zombie_mellee){
							zombies_level2[i].zombie_mellee_index++;
							if (zombies_level2[i].zombie_mellee_index >= 5) zombies_level2[i].zombie_mellee_index = 0;
							if (zombies_level2[i].zombie_x < player2X) zombies_level2[i].zombie_mellee = false;
						}
						else{
							zombies_level2[i].zombie_x -= 5;
							if (zombies_level2[i].zombie_x <= WIDTH - 150) zombies_level2[i].zombie_idle = false;
							if (zombies_level2[i].zombie_idle) zombies_level2[i].zombie_idle_index++;
							else zombies_level2[i].zombie_index++;
							if (player2Visible){
								if (abs(zombies_level2[i].zombie_x - (player2X + 60)) <= 5) {
									zombies_level2[i].zombie_mellee = true;
								}
							}
							if (zombies_level2[i].zombie_x <= 0) zombies_level2[i].zombie_x = zombies_level2[i].zombie_x = WIDTH + rand() % 60000 + rand() % 6;
							if (zombies_level2[i].zombie_index >= 4) zombies_level2[i].zombie_index = 0;
							if (zombies_level2[i].zombie_idle_index >= 3) zombies_level2[i].zombie_idle_index = 0;
						}
					}
					if (zombies_level2[i].zombie_visible == false){
						zombies_level2[i].zombie_x = WIDTH + rand() % 60000 + rand() % 7;
						zombies_level2[i].zombie_y = 50;
						zombies_level2[i].zombie_visible = true;
					}
				}
			}
		}
		else if (level == 3){
			if (standing || standRev){
				stand_index++;
				if (stand_index > 3) stand_index = 0;
			}
			if (jumping){
				if (jumpup){
					playerJump += 5;
					if (playerJump >= JUMPLIMIT){
						jumpup = false;
					}
				}
				else{
					playerJump -= 5;
					if (playerJump < 0){
						playerJump = 0;
						jumping = false;
					}
				}
			}
			if (level3Characters){
				for (int i = 0; i < MONSTERNUMBER; i++){
					if (monsters[i].monster_visible){
						if (monsters[i].monster_mellee){
							monsters[i].monster_mellee_index++;
							if (monsters[i].monster_mellee_index >= 3) monsters[i].monster_mellee_index = 0;
							if (monsters[i].monster_x < player3X) monsters[i].monster_mellee = false;
						}
						else{
							monsters[i].monster_y = 120;
							monsters[i].monster_x -= 10;
							monsters[i].monster_index++;
							if (player3Visible){
								if (abs(monsters[i].monster_x - (player3X + 50)) <= 5) {
									monsters[i].monster_mellee = true;
								}
							}
							if (monsters[i].monster_x <= 0) monsters[i].monster_x = WIDTH + rand() % 80000 + rand() % 6;
							if (monsters[i].monster_index >= 5) monsters[i].monster_index = 0;
						}
					}
					if (monsters[i].monster_visible == false){
						monsters[i].monster_x = WIDTH + rand() % 100000 + rand() % 8;
						monsters[i].monster_y = 150;
						monsters[i].monster_visible = true;
					}
				}
				for (int i = 0; i < MONSTER_LEVEL3; i++){
					if (monsters_level3[i].monster_visible){
						if (monsters_level3[i].monster_mellee){
							monsters_level3[i].monster_mellee_index++;
							if (monsters_level3[i].monster_mellee_index >= 5) monsters_level3[i].monster_mellee_index = 0;
							if (monsters_level3[i].monster_x < player3X) monsters_level3[i].monster_mellee = false;
						}
						else{
							monsters_level3[i].monster_x -= 10;
							monsters_level3[i].monster_index++;
							if (player3Visible){
								if (abs(monsters_level3[i].monster_x - (player3X + 70)) <= 5) {
									monsters_level3[i].monster_mellee = true;
								}
							}
							if (monsters_level3[i].monster_x <= 0) monsters_level3[i].monster_x = WIDTH + rand() % 65000 + rand() % 5;
							if (monsters_level3[i].monster_index >= 5) monsters_level3[i].monster_index = 0;
						}
					}
					if (monsters_level3[i].monster_visible == false){
						monsters_level3[i].monster_x = WIDTH + rand() % 80000 + rand() % 8;
						monsters_level3[i].monster_y = 120;
						monsters_level3[i].monster_visible = true;
					}
				}
				for (int i = 0; i < ZOMBIE_LEVEL3; i++){
					if (zombies_level3[i].zombie_visible){
						if (zombies_level3[i].zombie_mellee){
							zombies_level3[i].zombie_mellee_index++;
							if (zombies_level3[i].zombie_mellee_index >= 5) zombies_level3[i].zombie_mellee_index = 0;
							if (zombies_level3[i].zombie_x < player3X) zombies_level3[i].zombie_mellee = false;
						}
						else{
							zombies_level3[i].zombie_x -= 5;
							if (zombies_level3[i].zombie_x <= WIDTH - 150) zombies_level3[i].zombie_idle = false;
							if (zombies_level3[i].zombie_idle) zombies_level3[i].zombie_idle_index++;
							else zombies_level3[i].zombie_index++;
							if (player3Visible){
								if (abs(zombies_level3[i].zombie_x - (player3X + 70)) <= 5){
									zombies_level3[i].zombie_mellee = true;
								}
							}
							if (zombies_level3[i].zombie_x <= 0) zombies_level3[i].zombie_x = WIDTH + rand() % 50000 + rand() % 6;
							if (zombies_level3[i].zombie_index >= 4) zombies_level3[i].zombie_index = 0;
							if (zombies_level3[i].zombie_idle_index >= 3) zombies_level3[i].zombie_idle_index = 0;
						}
					}
					if (zombies_level3[i].zombie_visible == false){
						zombies_level3[i].zombie_x = WIDTH + rand() % 60000 + rand() % 5;
						zombies_level3[i].zombie_y = 120;
						zombies_level3[i].zombie_visible = true;
						zombies_level3[i].zombie_idle = true;
					}
				}
			}
		}
		else if (level == 4){
			if (standing || standRev){
				stand_index++;
				if (stand_index > 3) stand_index = 0;
			}
			if (jumping){
				if (jumpup){
					playerJump += 5;
					if (playerJump >= JUMPLIMIT){
						jumpup = false;
					}
				}
				else{
					playerJump -= 5;
					if (playerJump < 0){
						playerJump = 0;
						jumping = false;
					}
				}
			}
			if (bossVisible&&bossLevel){
				for (int i = 0; i < BOMBNUMBER; i++){
					level1_bomb[i].y = 120;
					level1_bomb[i].x -= 10;
					if (level1_bomb[i].x < 0) level1_bomb[i].x = WIDTH + rand() % 20000;
					if (level1_bomb[i].bomb_visible == false){
						level1_bomb[i].bomb_visible = true;
						level1_bomb[i].x = WIDTH + rand() % 30000;
					}
				}
			}
		}
	}
}
void bossMovements(){
	if (!pause){
		if (bossLevel && level==4){
			if (bossVisible){
				if (bossRunForward){
					bossX -= (rand() % 3 + 1);
				}
				if (bossRunBackward){
					bossX += (rand() % 3 + 1);
				}
				if (player1Visible){
					if (player1X > bossX) {
						bossRunBackward = true;
						bossRunForward = false;
					}
					else{
						bossRunBackward = false;
						bossRunForward = true;
					}
				}
				if (player2Visible){
					if (player2X > bossX) {
						bossRunBackward = true;
						bossRunForward = false;
					}
					else{
						bossRunBackward = false;
						bossRunForward = true;
					}
				}
				if (player3Visible){
					if (player3X > bossX) {
						bossRunBackward = true;
						bossRunForward = false;
					}
					else{
						bossRunBackward = false;
						bossRunForward = true;
					}
				}
				bossRunIndex++;
				if (bossRunIndex >= 5) bossRunIndex = 0;
				if (bossX >= WIDTH - 115) bossX = WIDTH - 115;
				if (bossX <= WIDTH / 2) bossX = WIDTH / 2;
				if (bossfiring == false){
					random++;
					if (random >= (rand()%70+1)){
						bossfiring = true;
						bossFireX = bossX;
						//if (bossJumping) bossFireY = bossJump + bossY + 100;
						bossFireY = bossY + 100;
					}
				}
				if (bossfiring&&bossRunForward) {
					for (int i = 0; i < 35; i++) {
						bossFireX--;
						if (bossFireX < 0) {
							bossfiring = false;
							random = 0;
							bossFireX = bossX + 10000000000000000000;
						}
					}
				}
				else if (bossfiring&&bossRunBackward){
					for (int i = 0; i < 35; i++) {
						bossFireX++;
						if (bossFireX >= WIDTH) {
							bossfiring = false;
							random = 0;
							bossFireX = bossX + 10000000000000000000;
						}
					}
				}
			}
		}
	}
}
/*void bossfire_bullet(){
	if (!pause){
		if (bossVisible){

		}
	}
}*/
void playerMelleeAttack(){
	if (!pause){
		if (level == 1){
			player1_mellee_index++;
			if (player1_mellee_index >= 3) {
				player1_mellee_index = 0;
				playerMellee = false;
			}
		}
		else if (level == 2){
			player2_mellee_index++;
			if (player2_mellee_index >= 3) {
				player2_mellee_index = 0;
				playerMellee = false;
			}
		}
		else if (level == 3){
			player3_mellee_index++;
			if (player3_mellee_index >= 3) {
				player3_mellee_index = 0;
				playerMellee = false;
			}
		}
		else if (level == 4){
			if (bossLevel){
				if (player1Visible){
					player1_mellee_index++;
					if (player1_mellee_index >= 3) {
						player1_mellee_index = 0;
						playerMellee = false;
					}
				}
				else if (player2Visible){
					player2_mellee_index++;
					if (player2_mellee_index >= 3) {
						player2_mellee_index = 0;
						playerMellee = false;
					}
				}
				else if (player3Visible){
					player3_mellee_index++;
					if (player3_mellee_index >= 3) {
						player3_mellee_index = 0;
						playerMellee = false;
					}
				}
			}
		}
	}
}
void fire_bullet(){
	if (!pause){
		if (firing&&front){
			for (int i = 0; i < 152; i++) {
				fireX++;
				if (fireX > WIDTH) {
					firing = false;
					if (level == 1) fireX = player1X + 10000000000000000000;
					else if (level == 2) fireX = player2X + 10000000000000000000;
					else if (level == 3) fireX = player3X + 10000000000000000000;
					else if (level == 4){
						if (player1Visible) fireX = player1X + 10000000000000000000;
						else if (player2Visible) fireX = player2X + 10000000000000000000;
						else if (player3Visible) fireX = player3X + 10000000000000000000;
					}
				}
			}
		}
		else if (firing&&back){
			for (int i = 0; i < 152; i++) {
				fireX--;
				if (fireX < 0) {
					firing = false;
					if (level == 1) fireX = player1X + 10000000000000000000;
					else if (level == 2) fireX = player2X + 10000000000000000000;
					else if (level == 3) fireX = player3X + 10000000000000000000;
					else if (level == 4){
						if (player1Visible) fireX = player1X + 10000000000000000000;
						else if (player2Visible) fireX = player2X + 10000000000000000000;
						else if (player3Visible) fireX = player3X + 10000000000000000000;
					}
				}
			}
		}
	}
}
void ending_Level_logic(){
	if (level == 1){
		if (enemyKilled == 3){
			enemyKilled = 0;
			level1Characters = false;
			//backgroundMusic = false;
			lvl1end_keyVisible = true;
		}
	}
	else if (level == 2){
		if (enemyKilled == 2){
			enemyKilled = 0;
			level2Characters = false;
			//backgroundMusic = false;
			lvl2end_keyVisible = true;
		}
	}
	else if (level == 3){
		if (enemyKilled == 4){
			enemyKilled = 0;
			level3Characters = false;
			//backgroundMusic = false;
		}
	}
	else if (level == 4){
		if (player1Visible) player1Y = 100;
		else if (player2Visible) player2Y = 100;
		else if (player3Visible) player3Y = 100;
	}
}
void changeBackground()
{
	if (!pause){
		if (level == 1){
			if (running){
				if (front){
					for (int i = 0; i < 10; i++){
						upperbg_lvl1[i].x -= upperbgspeed;
						if (upperbg_lvl1[i].x < 0) upperbg_lvl1[i].x = WIDTH - 152;
						lowerbg_lvl1[i].x -= lowerbgspeed;
						if (lowerbg_lvl1[i].x < 0) lowerbg_lvl1[i].x = WIDTH - 152;
					}
				}
				else if(back){
					for (int i = 0; i < 10; i++){
						upperbg_lvl1[i].x += upperbgspeed;
						if (upperbg_lvl1[i].x >= WIDTH) upperbg_lvl1[i].x = 0;
						lowerbg_lvl1[i].x += lowerbgspeed;
						if (lowerbg_lvl1[i].x >= WIDTH) lowerbg_lvl1[i].x = 0;
					}
				}
			}
		}
		else if (level == 2){
			if (running){
				if (front){
					for (int i = 0; i < 10; i++){
						upperbg_lvl2[i].x -= upperbgspeed;
						if (upperbg_lvl2[i].x < 0) upperbg_lvl2[i].x = WIDTH - 152;
						lowerbg_lvl2[i].x -= lowerbgspeed;
						if (lowerbg_lvl2[i].x < 0) lowerbg_lvl2[i].x = WIDTH - 152;
					}
				}
				else if(back){
					for (int i = 0; i < 10; i++){
						upperbg_lvl2[i].x += upperbgspeed;
						if (upperbg_lvl2[i].x >= WIDTH) upperbg_lvl2[i].x = 0;
						lowerbg_lvl2[i].x += lowerbgspeed;
						if (lowerbg_lvl2[i].x >= WIDTH) lowerbg_lvl2[i].x = 0;
					}
				}
			}
		}
		else if (level == 3){
			if (running){
				if (front){
					for (int i = 0; i < 10; i++){
						upperbg_lvl3[i].x -= upperbgspeed;
						if (upperbg_lvl3[i].x < 0) upperbg_lvl3[i].x = WIDTH - 152;
						lowerbg_lvl3[i].x -= lowerbgspeed;
						if (lowerbg_lvl3[i].x < 0) lowerbg_lvl3[i].x = WIDTH - 152;
					}
				}
				else if(back){
					for (int i = 0; i < 10; i++){
						upperbg_lvl3[i].x += upperbgspeed;
						if (upperbg_lvl3[i].x >= WIDTH) upperbg_lvl3[i].x = 0;
						lowerbg_lvl3[i].x += lowerbgspeed;
						if (lowerbg_lvl3[i].x >= WIDTH) lowerbg_lvl3[i].x = 0;
					}
				}
			}
		}
		/*else if (level == 4 && bossLevel){
			for (int i = 0; i < 10; i++){
				upperbg_lvl4[i].x -= upperbgspeed;
				if (upperbg_lvl4[i].x < 0) upperbg_lvl4[i].x = WIDTH - 152;
				lowerbg_lvl4[i].x -= lowerbgspeed;
				if (lowerbg_lvl4[i].x < 0) lowerbg_lvl4[i].x = WIDTH - 152;
			}
		}*/
	}
}
void setBomb_level1(){
	for (int i = 0; i < BOMBNUMBER; i++){
		level1_bomb[i].x = WIDTH + rand() % 30000;
		level1_bomb[i].y = 150;
		level1_bomb[i].bomb_visible = true;
	}
}
void setBox_level2(){
	for (int i = 0; i < BOXNUMBER; i++){
		level2_box[i].x = WIDTH + rand() % 40000;
		level2_box[i].y = 50;
		level2_box[i].box_visible = true;
	}
}
void setBackgroundVariables_level1(){
	int sum = 0;
	for (int i = 0; i < 10; i++){
		upperbg_lvl1[i].y = 150;
		lowerbg_lvl1[i].y = 0;
		upperbg_lvl1[i].x = sum;
		lowerbg_lvl1[i].x = sum;
		sum += 152;
	}
}
void setBackgroundVariables_level2(){
	int sum = 0;
	for (int i = 0; i < 10; i++){
		upperbg_lvl2[i].y = 127;
		lowerbg_lvl2[i].y = 0;
		upperbg_lvl2[i].x = sum;
		lowerbg_lvl2[i].x = sum;
		sum += 152;
	}
}
void setBackgroundVariables_level3(){
	int sum = 0;
	for (int i = 0; i < 10; i++){
		upperbg_lvl3[i].y = 250;
		lowerbg_lvl3[i].y = 0;
		upperbg_lvl3[i].x = sum;
		lowerbg_lvl3[i].x = sum;
		sum += 152;
	}
}
void setBackgroundVariables_level4(){
	int sum = 0;
	for (int i = 0; i < 10; i++){
		upperbg_lvl4[i].y = 150;
		lowerbg_lvl4[i].y = 0;
		upperbg_lvl4[i].x = sum;
		lowerbg_lvl4[i].x = sum;
		sum += 152;
	}
}
void setEnemyMonsterVariables_level1(){
	for (int i = 0; i < MONSTERNUMBER; i++){
		monsters[i].monster_x = WIDTH + rand() % 100000;
		monsters[i].monster_y = 150;
		monsters[i].monster_index = rand() % 6;
		monsters[i].monster_mellee_index = rand() % 4;
		monsters[i].monster_visible = true;
		monsters[i].monster_mellee = false;
	}
}
void setEnemyZombieVariables_level1(){
	for (int i = 0; i < ZOMBIENUMBER; i++){
		zombies[i].zombie_x = WIDTH + rand() % 80000;
		zombies[i].zombie_y = 150;
		zombies[i].zombie_index = rand() % 6;
		zombies[i].zombie_mellee_index = rand() % 6;
		zombies[i].zombie_idle_index = rand() % 4;
		zombies[i].zombie_mellee = false;
		zombies[i].zombie_visible = true;
		zombies[i].zombie_idle = true;
	}
}
void setEnemyMonsterVariables_level2(){
	for (int i = 0; i < MONSTER_LEVEL2; i++){
		monsters_level2[i].monster_x = WIDTH + rand() % 100000;
		monsters_level2[i].monster_y = 50;
		monsters_level2[i].monster_index = rand() % 6;
		monsters_level2[i].monster_mellee_index = 0;
		monsters_level2[i].monster_visible = true;
		monsters_level2[i].monster_mellee = false;
	}
}
void setEnemyZombieVariables_level2(){
	for (int i = 0; i < ZOMBIE_LEVEL2; i++){
		zombies_level2[i].zombie_x = WIDTH + rand() % 60000;
		zombies_level2[i].zombie_y = 50;
		zombies_level2[i].zombie_index = rand() % 5;
		zombies_level2[i].zombie_mellee_index = 0;
		zombies_level2[i].zombie_idle_index = 0;
		zombies_level2[i].zombie_mellee = false;
		zombies_level2[i].zombie_visible = true;
		zombies_level2[i].zombie_idle = true;
	}
}
void setEnemyMonsterVariables_level3(){
	for (int i = 0; i < MONSTER_LEVEL3; i++){
		monsters_level3[i].monster_x = WIDTH + rand() % 80000;
		monsters_level3[i].monster_y = 120;
		monsters_level3[i].monster_index = rand() % 6;
		monsters_level3[i].monster_mellee_index = rand() % 6;
		monsters_level3[i].monster_visible = true;
		monsters_level3[i].monster_mellee = false;
	}
}
void setEnemyZombieVariables_level3(){
	for (int i = 0; i < ZOMBIE_LEVEL2; i++){
		zombies_level3[i].zombie_x = WIDTH + rand() % 60000;
		zombies_level3[i].zombie_y = 120;
		zombies_level3[i].zombie_index = rand() % 5;
		zombies_level3[i].zombie_mellee_index = 0;
		zombies_level3[i].zombie_idle_index = 0;
		zombies_level3[i].zombie_mellee = false;
		zombies_level3[i].zombie_visible = true;
		zombies_level3[i].zombie_idle = true;
	}
}
void setMenu(){
	int sum = 50;
	for (int i = 4; i >= 0; i--){
		menu_buttons[i].x = 1000;
		menu_buttons[i].y = sum;
		sum += 120;
	}
}
void resetGame(){
	setEnemyMonsterVariables_level1();
	setEnemyZombieVariables_level1();
	setBomb_level1();
	setBackgroundVariables_level1();
	setBox_level2();
	setBackgroundVariables_level2();
	setBackgroundVariables_level3();
	setBackgroundVariables_level4();
	setEnemyMonsterVariables_level2();
	setEnemyZombieVariables_level2();
	setEnemyMonsterVariables_level3();
	setEnemyZombieVariables_level3();
	if (level1Characters == false){
		level1Characters = true; 
		level2Characters = level3Characters = false;
	}
	else if (level1Characters == false && level2Characters == false){
		level1Characters = true;
		level2Characters = level3Characters = false;
	}
	if (player1Visible == false) {
		player1X = 0;
		player1Y = 150;
		player1Visible = true;
	}
	else if (player2Visible == false) {
		player2X = player1X = 0;
		player1Y = 150; player2Y = 50;
		player2Visible = false;
		player1Visible = true;
	}
	else if (player3Visible == false) {
		player3X = player2X = player1X = 0;
		player1Y = 150; player2Y = 50; player3Y = 120;
		player3Visible = player2Visible = false;
		player1Visible = true;
	}
	level = 1;
	killScore = 0;
	enemyKilled = 0;
	life_index = 0;
	lifebarVisible = true;
	bossRunForward = true; bossRunBackward = false; bossfiring = false;
	bossVisible = true; counts = 0; bossRunIndex = 0; bossLifeIndex = 0; bossX = WIDTH - 115; bossY = 100;
	random = 0;
}
/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/

void iMouseMove(int mx, int my)
{

}
//*******************************************************************ipassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my)
{

}

void iMouse(int button, int state, int mx, int my)
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		menu(mx, my);
	}
	
	
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
	}
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/


void iKeyboard(unsigned char key)
{
	if (key == 'x')
	{
		exit(0);
	}
	if (key == '\b'){
		if (gameState == 3 || gameState == 2 || gameState == 1) gameState = -1;
		/*(if (gameOver){
			if (charIndex <= 0) charIndex = 0;
			else charIndex--;
			username[charIndex] = '\0';
		}*/
		else if (gameOver){
			gameOver = false;
			gameState = -1;
		}
		else if (completeGame){
			completeGame = false; gameState = -1;
		}
	}
	if (key == 'A'||key=='a'){
		if (!pause){
			if (!firing){
				firing = true;
				playMusic(true);
				if (level == 1){
					fireX = player1X;
					if (jumping) fireY = player1Y + playerJump + 100;
					else fireY = player1Y + 100;
				}
				else if (level == 2){
					fireX = player2X;
					if (jumping) fireY = player2Y + playerJump + 100;
					else fireY = player2Y + 100;
				}
				else if (level == 3){
					fireX = player3X;
					if (jumping) fireY = player3Y + playerJump + 100;
					else fireY = player3Y + 100;
				}
				else if (level == 4){
					if (bossLevel){
						if (player1Visible){
							fireX = player1X;
							if (jumping) fireY = player1Y + playerJump + 100;
							else fireY = player1Y + 100;
						}
						else if (player2Visible){
							fireX = player2X;
							if (jumping) fireY = player2Y + playerJump + 100;
							else fireY = player2Y + 100;
						}
						else if (player3Visible){
							fireX = player3X;
							if (jumping) fireY = player3Y + playerJump + 100;
							else fireY = player3Y + 100;
						}
					}
				}
			}
		}
	}
	if (key == 's' || key == 'S'){
		if (!pause){
			if (!playerMellee){
				playerMellee = true;
				playMusic(true);
				if (level == 1){
					melleeX = player1X;
					if (jumping) melleeY = player1Y + playerJump;
					else melleeY = player1Y;
				}
				else if (level == 2){
					melleeX = player2X;
					if (jumping) melleeY = player2Y + playerJump;
					else melleeY = player2Y;
				}
				else if (level == 3){
					melleeX = player3X;
					if (jumping) melleeY = player3Y + playerJump;
					else melleeY = player3Y;
				}
				else if (level == 4){
					if (bossLevel){
						if (player1Visible){
							melleeX = player1X;
							if (jumping) melleeY = player1Y + playerJump;
							else melleeY = player1Y;
						}
						else if (player2Visible){
							melleeX = player2X;
							if (jumping) melleeY = player2Y + playerJump;
							else melleeY = player2Y;
						}
						else if (player3Visible){
							melleeX = player3X;
							if (jumping) melleeY = player3Y + playerJump;
							else melleeY = player3Y;
						}
					}
				}
			}
		}
	}
	if (key == 'm' || key == 'M'){
		if (!mute){
			mute = true;
			playMusic(false);
		}
		else{
			mute = false;
			playMusic(true);
		}
	}
	if (key == 'p' || key == 'P'){
		if (!pause){
			pause = true;
		}
		else{
			pause = false;
		}
	}
	/*if (gameOver){
		if (key != '\b'){
			username[charIndex] = key;
			charIndex++;
			username[charIndex] = '\0';
		}
		if (key == '\r'){
			highscore(killScore);
			killScore = 0;
			gameOver = false;
		}
	}*/

}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	
	if (key == GLUT_KEY_RIGHT)
	{
		if (!pause){
			running = true;
			runningForward = true;
			runningBackward = false;
			if (jumping) runningBackward = runningForward = false;
			if (level == 1){
				player1X += 5;
				if (player1X >= WIDTH) player1X = -10;
			}
			else if (level == 2){
				player2X += 5;
				if (player2X >= WIDTH) player2X = -10;
			}
			else if (level == 3){
				player3X += 5;
				if (player3X >= WIDTH) player3X = -10;
			}
			else if (level == 4){
				if (bossLevel){
					if (player1Visible){
						player1X += 5;
						if (player1X >= WIDTH) player1X = -10;
					}
					else if (player2Visible){
						player2X += 5;
						if (player2X >= WIDTH) player2X = -10;
					}
					else if (player3Visible){
						player3X += 5;
						if (player3X >= WIDTH) player3X = -10;
					}
				}
				else{
					if (player1Visible){
						player1X += 5;
						if (player1X >= WIDTH) player1X = -10;
					}
					else if (player2Visible){
						player2X += 5;
						if (player2X >= WIDTH) player2X = -10;
					}
					else if (player3Visible){
						player3X += 5;
						if (player3X >= WIDTH) player3X = -10;
					}
				}
			}
			if (runningBackward || runningForward) run_index++;
			if (run_index >= 5) run_index = 0;
			standing = standRev = false;
			front = true; back = false;
		}
	}
	if (key == GLUT_KEY_LEFT)
	{
		if (!pause){
			running = true;
			runningForward = false;
			runningBackward = true;
			if (jumping) runningBackward = runningForward = false;
			if (level == 1){
				player1X -= 5;
				if (player1X <= 0) player1X = 0;
			}
			else if (level == 2){
				player2X -= 5;
				if (player2X <= 0) player2X = 0;
			}
			else if (level == 3){
				player3X -= 5;
				if (player3X <= 0) player2X = 0;
			}
			else if (level == 4){
				if (bossLevel){
					if (player1Visible){
						player1X -= 5;
						if (player1X <= 0) player1X = 0;
					}
					else if (player2Visible){
						player2X -= 5;
						if (player2X <= 0) player2X = 0;
					}
					else if (player3Visible){
						player3X -= 5;
						if (player3X <= 0) player2X = 0;
					}
				}
				else{
					if (player1Visible){
						player1X -= 5;
						if (player1X <= 0) player1X = 0;
					}
					else if (player2Visible){
						player2X -= 5;
						if (player2X <= 0) player2X = 0;
					}
					else if (player3Visible){
						player3X -= 5;
						if (player3X <= 0) player2X = 0;
					}
				}
			}
			if (runningBackward || runningForward) run_index++;
			if (run_index >= 5) run_index = 0;
			standing = standRev = false;
			front = false; back = true;
		}
	}
	if (key == GLUT_KEY_UP)
	{
		if (!pause){
			if (!jumping){
				jumping = jumpup = true;
				runningBackward = runningForward = standing = standRev = false;
			}
		}
	}
	if (key == GLUT_KEY_DOWN)
	{

	}
	if (key == GLUT_KEY_INSERT)
	{

	}
	if (key == GLUT_KEY_HOME)
	{

	}
	if (key == GLUT_KEY_PAGE_UP)
	{

	}
}
int main()
{
	setMenu();
	resetGame();
	iSetTimer(1000,collisionCheck);
	iSetTimer(25, fireAndMelleeCollisionCheck);
	iSetTimer(165, bossCollisionCheck);
	endingLevel = iSetTimer(2, ending_Level_logic);
    iSetTimer(300, changeBackground);
	iSetTimer(50, change);
	iSetTimer(70,playerMelleeAttack);
	iSetTimer(10, fire_bullet);
	iSetTimer(40, bossMovements);
	///srand((unsigned)time(NULL));
	iInitialize(WIDTH, HEIGHT, "Rangers");
	imageLoader();//for loading image
	playMusic(true);
	iStart();
	return 0;
}