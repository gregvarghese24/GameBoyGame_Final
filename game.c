#include <stdlib.h>
#include "myLib.h"
#include "game.h"
#include "bg.h"
#include "bg2.h"
#include "spritesheet.h"
#include "gamebg.h" 
#include "gamebg2.h"
#include<time.h>
#include "bimmerr.h"
#include "sound.h"


// Variables 
PLAYER player;
BULLET bullets[BULLETCOUNT];
BULLET ebullets[EBULLETCOUNT];
ALIEN greenAliens[GALIENCOUNT];
ALIEN blueAliens[BALIENCOUNT];
ALIEN redAliens[RALIENCOUNT];
int score;
int seed; 
int hOff;
int vOff;
int cheat;
int lives;
int collect; 

void initGame() {
    lives = 6;
    collect = 0;
    cheat = 0;
    initPlayer();
    //initBullets();
    //initEnemyBullets();
    initGreenAliens();
    initBlueAliens();
    initRedAliens();
    // loadPalette(bgPal);

    // DMANow(3, bgTiles, &CHARBLOCK[0], bgTilesLen/2);
    // DMANow(3, bgMap, &SCREENBLOCK[28], bgMapLen/2);

    // DMANow(3, bg2Tiles, &CHARBLOCK[1], bg2TilesLen/2);
    // DMANow(3, bg2Map, &SCREENBLOCK[24], bg2MapLen/2);

    // loadPalette(bgPal);
    // DMANow(3, spritesheetTiles, &CHARBLOCK[4], spritesheetTilesLen/2);
    // DMANow(3, spritesheetPal, SPRITEPALETTE, 256);

    hOff = 0;
    vOff = 0;

}
void updateGame() {
    updatePlayer();
    //updateBack();
    //for (int i = 0; i < BULLETCOUNT; i++) {
    //     updateBullets(&bullets[i]);
    // }
    // for (int i = 0; i < BULLETCOUNT; i++) {
    //      updateEBullets(&ebullets[i]);
    //  }
    for (int i = 0; i < GALIENCOUNT; i++) {
        updateGreenAliens(&greenAliens[i]);
    }
    for (int i = 0; i < BALIENCOUNT; i++) {
        updateBlueAliens(&blueAliens[i]);
    }
    for (int i = 0; i < RALIENCOUNT; i++) {
        updateRedAliens(&redAliens[i]);
    }
    if( collect == 15){
        goToWin();
        hOff = 0;
    }
    // if (lives == 0){
    //     goToLose();
    //     hOff = 0;
    // }
    if (BUTTON_PRESSED(BUTTON_B)){
        goToPause();
    }
    
    // while(1){
    //     hhOff++;
    //     //waitForVBlank();
    // }
    // if (seed % 30 == 0) {
    //     enemyFireBullets();
    //     srand(seed);
    // } else {
    //     srand(seed);
    // }
}

void updateBack(){
    for (int i = 0; i < GALIENCOUNT; i++) {
        hOff++;
    }

    waitForVBlank();

    // Update the offset registers with the actual offsets

    // TODO 5.0 - change to implement parallax
    REG_BG0HOFF = hhOff;
    REG_BG1HOFF = hhOff/2;
}
void drawGame() {
    drawPlayer();
    shadowOAM[104].attr0 = 7 | ATTR0_4BPP | ATTR0_WIDE; //gpa
    shadowOAM[104].attr1 = 175 | ATTR1_MEDIUM;
    shadowOAM[104].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(0,14);

    // shadowOAM[101].attr0 = 7 | ATTR0_4BPP | ATTR0_SQUARE; //0
    // shadowOAM[101].attr1 = 199 | ATTR1_SMALL;
    // shadowOAM[101].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(1,18);
    
    // shadowOAM[101].attr0 = 100 | ATTR0_4BPP | ATTR0_SQUARE; //0
    // shadowOAM[101].attr1 = 199 | ATTR1_SMALL;
    // shadowOAM[101].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(7,11);

    
    if (collect == 0) {
        //loadPalette(bg2Pal);
        shadowOAM[101].attr0 = 15 | ATTR0_4BPP | ATTR0_SQUARE; // . 0
        shadowOAM[101].attr1 = 205 | ATTR1_SMALL;
        shadowOAM[101].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(1,18);

        shadowOAM[103].attr0 = 15 | ATTR0_4BPP | ATTR0_SQUARE; //0
        shadowOAM[103].attr1 = 202 | ATTR1_TINY;
        shadowOAM[103].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(1,19);

        shadowOAM[102].attr0 = 25 | ATTR0_4BPP | ATTR0_SQUARE; //greg panic
        shadowOAM[102].attr1 = 182 | ATTR1_LARGE; 
        shadowOAM[102].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(23,0);

        shadowOAM[107].attr0 = 100 | ATTR0_4BPP | ATTR0_SQUARE; //app 0
        shadowOAM[107].attr1 = 182 | ATTR1_LARGE; 
        shadowOAM[107].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(7,10);

    } else if(collect == 1){
        shadowOAM[105].attr0 = 50 | ATTR0_4BPP | ATTR0_SQUARE; //0
        shadowOAM[105].attr1 = 202 | ATTR1_TINY;
        shadowOAM[105].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(3,17);

    }
    else if (collect == 2) {
        //loadPalette(bg2Pal);
        shadowOAM[103].attr0 = 15 | ATTR0_4BPP | ATTR0_SQUARE; //0
        shadowOAM[103].attr1 = 202 | ATTR1_TINY;
        shadowOAM[103].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(3,17);

        // shadowOAM[100].attr0 = 2 | ATTR0_4BPP | ATTR0_SQUARE;
        // shadowOAM[100].attr1 = 35 | ATTR1_TINY;
        // shadowOAM[100].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(4,0);

        shadowOAM[102].attr0 = 25 | ATTR0_4BPP | ATTR0_SQUARE; //greg
        shadowOAM[102].attr1 = 182 | ATTR1_LARGE; 
        shadowOAM[102].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(15,0);
 
    } else if (collect == 4){
        shadowOAM[103].attr0 = 15 | ATTR0_4BPP | ATTR0_SQUARE; //0
        shadowOAM[103].attr1 = 202 | ATTR1_TINY;
        shadowOAM[103].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(2,17);

        shadowOAM[107].attr0 = 100 | ATTR0_4BPP | ATTR0_SQUARE; //app 1
        shadowOAM[107].attr1 = 182 | ATTR1_LARGE; 
        shadowOAM[107].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(15,10);
    }
    else if (collect == 6){
        shadowOAM[107].attr0 = 100 | ATTR0_4BPP | ATTR0_SQUARE; //app 1
        shadowOAM[107].attr1 = 182 | ATTR1_LARGE; 
        shadowOAM[107].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(23,10);
    }
    else if (collect == 7){
        shadowOAM[103].attr0 = 15 | ATTR0_4BPP | ATTR0_SQUARE; //3.0
        shadowOAM[103].attr1 = 202 | ATTR1_TINY;
        shadowOAM[103].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(3,18);
    }
    else if (collect == 8) {
        //loadPalette(bg2Pal);
         shadowOAM[102].attr0 = 25 | ATTR0_4BPP | ATTR0_SQUARE;
         shadowOAM[102].attr1 = 182 | ATTR1_LARGE; 
         shadowOAM[102].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(7,1); 

    } else if (collect == 10){
        shadowOAM[103].attr0 = 15 | ATTR0_4BPP | ATTR0_SQUARE; //4.0
        shadowOAM[103].attr1 = 202 | ATTR1_TINY;
        shadowOAM[103].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(3,19);
    }
    else if(collect == 12){
        
    }
    // for (int i = 0; i < BULLETCOUNT; i++) {
    //     drawBullet(&bullets[i]);
    // }
    // for (int i = 0; i < BULLETCOUNT; i++) {
    //     drawEBullet(&ebullets[i]);
    // }
    for (int i = 0; i < GALIENCOUNT; i++) {
        drawGreenAliens(&greenAliens[i]);
    }
    for (int i = 0; i < BALIENCOUNT; i++) {
        drawBlueAliens(&blueAliens[i]);
    }
    for (int i = 0; i < RALIENCOUNT; i++) {
        drawRedAliens(&redAliens[i]);
    }
    DMANow(3, shadowOAM, OAM, 128*4);
}

void initPlayer() {

    player.width = 16;
    player.height = 16;
    player.rdel = 1;
    player.cdel = 1;
    player.row = 140;
    player.col = 90;


}
void updatePlayer() {
if (BUTTON_HELD(BUTTON_LEFT)
        && player.col >= player.cdel && player.col >= 1) {

        player.col -= player.cdel;
        player.cDirection = -1;

    } else if (BUTTON_HELD(BUTTON_RIGHT)
         && player.col <=119) {

        player.col += player.cdel;  
        player.cDirection = 1;

    } else {
        player.cDirection = 0;
    } 

    // Fire bullets
    if (BUTTON_PRESSED(BUTTON_A) && player.bulletTimer >= 13) {

        fireBullets();
        player.bulletTimer = 0;
    }

    player.bulletTimer++;
    for (int i = 0; i < RALIENCOUNT; i++) {
        if (redAliens[i].active && collision(player.row, player.col, player.height, player.width,
            redAliens[i].row, redAliens[i].col, redAliens[i].height, redAliens[i].width)) {

                // Put ball back in the pool
            //ebullets[i].active = 0;

                // Update the score
            collect++;
        }
    }
}

void drawPlayer() {
    if (BUTTON_HELD(BUTTON_LEFT)) { 

        shadowOAM[0].attr0 = player.row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[0].attr1 = player.col | ATTR1_SMALL;
        shadowOAM[0].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(2,2);

    } else if (BUTTON_HELD(BUTTON_RIGHT)) {
        shadowOAM[0].attr0 = player.row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[0].attr1 = player.col | ATTR1_SMALL;
        shadowOAM[0].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(4,0);

    } else {
        shadowOAM[0].attr0 = player.row | ATTR0_4BPP | ATTR0_SQUARE; 
        shadowOAM[0].attr1 = player.col | ATTR1_SMALL;
        shadowOAM[0].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(0,0);

    }
}
void initBullets() { 
    for (int i = 0; i < BULLETCOUNT; i++) {

        bullets[i].height = 1;
        bullets[i].width = 1;
        bullets[i].row = -bullets[i].height;
        bullets[i].col = 0;
        bullets[i].rdel = -2;
        bullets[i].cdel = 0;
        bullets[i].active = 0;
        bullets[i].index = i+1;
    }
}
void fireBullets() {

     for (int i = 0; i < BULLETCOUNT; i++) {
        if (!bullets[i].active) {

            // Position the new bullet
            bullets[i].row = player.row;
            bullets[i].col = player.col + player.width/2
                - bullets[i].width/2;

            // Slant it in the direction of player movement
            bullets[i].cdel = player.cDirection;

            // Take the bullet out of the pool
            bullets[i].active = 1;

            // Break out of the loop
            break;
        }
    }
}

void drawBullet(BULLET* b){
    if(b-> active) {
        shadowOAM[b->index].attr0 = (b->row & ROWMASK) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[b->index].attr1 = (b->col & COLMASK) | ATTR1_TINY;
        // Bullet sizes are different rows on sprite sheet
        shadowOAM[b->index].attr2 = ATTR2_PALROW(0)| ATTR2_TILEID(0, 10);
    }else {
       shadowOAM[b->index].attr0 = ATTR0_HIDE;
    }
}
void updateBullets(BULLET* b) {
    if (b->active) {
        if (b->row + b->height-1 >= 0
            && b->col + b->cdel > 0
            && b->col + b->cdel < SCREENWIDTH-1) {

            b->row += b->rdel;
            b->col += b->cdel;
        } else {
            b->active = 0;
        }
    }
}

void initGreenAliens() {
        for (int i = 0; i < GALIENCOUNT; i++) {
            greenAliens[i].width = 16;
            greenAliens[i].height = 16;
            greenAliens[i].rdel = 1;
            greenAliens[i].cdel = 1;
            greenAliens[i].row = 40;
            greenAliens[i].col = 20 + (i * 20);
            greenAliens[i].active = 1;
            greenAliens[i].index = i+1+GALIENCOUNT;
    }
}

void updateGreenAliens(ALIEN* b) { //4.0
    if (b->active) {

        // Bounce the ball off the sides of the box
        //if (b->row <= 1 || b->row + b->height-1 >= 119)
            //b->rdel *= -1;
        //if (b->col <= 1 || b->col + b->width-1 >= SCREENWIDTH-2)
            //b->cdel *= -1;

        // Move the ball
        //b->row += b->rdel;
        //b->col += b->cdel;

        if (b->col <= 160 || b->col + b->height-1 >= 119 || b->row + b->height-1 <=10)
            b->cdel = -1;
            if (b->row >= 160 || b->col + b->width-1 >= SCREENHEIGHT-2){
                b->active = 0;
            }
            b->row += b->rdel;
        // Handle ball-bullet collisions
        for (int i = 0; i < BULLETCOUNT; i++) {
            if (bullets[i].active && collision(b->row, b->col, b->height, b->width,
                bullets[i].row, bullets[i].col, bullets[i].height, bullets[i].width)) {

                // Put ball back in the pool
                bullets[i].active = 0;
                b->active = 0;

                // Update the score
                score++;
            }
        }
        if (collision(b->row, b->col, b->height, b->width,
                player.row, player.col, player.height, player.width)) {

                // Put ball back in the pool
                //bullets[i].active = 0;
                b->active = 0;
                collect++;

                // Update the score
                //ballsRemaining = ballsRemaining + 1; 
                //slifeRemaining = lifeRemaining - 1;
            }

    }
    if(b->active == 0){
        b->row = 10;
        b->col = rand() % 100;
        b->active = 1;
        }
    }


void drawGreenAliens(ALIEN* b) { //weed
    if(b->active) {
        shadowOAM[b->index].attr0 = (b->row & ROWMASK) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[b->index].attr1 = (b->col & COLMASK) | ATTR1_SMALL;
        shadowOAM[b->index].attr2 = ATTR2_PALROW(2)| ATTR2_TILEID(0, 2);
    } else {
        shadowOAM[b->index].attr0 = ATTR0_HIDE;
    }
}
void initBlueAliens() {
        for (int i = 0; i < BALIENCOUNT; i++) {
            blueAliens[i].width = 16;
            blueAliens[i].height = 16;
            blueAliens[i].rdel = 1;
            blueAliens[i].cdel = 1;
            blueAliens[i].row = 60;
            blueAliens[i].col = 20 + (i * 20);
            blueAliens[i].active = 1;
            blueAliens[i].index = i+1+BALIENCOUNT;
    }
}

void updateBlueAliens(ALIEN* b) {
    if (b->active) {

        // Bounce the ball off the sides of the box
        //if (b->row <= 1 || b->row + b->height-1 >= 119)
            //b->rdel *= -1;
        //if (b->col <= 1 || b->col + b->width-1 >= SCREENWIDTH-2)
            //b->cdel *= -1;

        // Move the ball
        //b->row += b->rdel;
        //b->col += b->cdel;

        if (b->col <= 160 || b->col + b->height-1 >= 119 || b->row + b->height-1 <=10)
            b->cdel = -1;
            if (b->row >= 160 || b->col + b->width-1 >= SCREENHEIGHT-2){
                b->active = 0;
            }
            b->row += b->rdel;
        // Handle ball-bullet collisions
        for (int i = 0; i < BULLETCOUNT; i++) {
            if (bullets[i].active && collision(b->row, b->col, b->height, b->width,
                bullets[i].row, bullets[i].col, bullets[i].height, bullets[i].width)) {

                // Put ball back in the pool
                bullets[i].active = 0;
                b->active = 0;

                // Update the score
                score++;
            }
        }
        if (collision(b->row, b->col, b->height, b->width,
                player.row, player.col, player.height, player.width)) {

                // Put ball back in the pool
                //bullets[i].active = 0;
                b->active = 0;
                //goToLose();
                if(collect >= 0){                
                    collect--;}
                // Update the score
                //ballsRemaining = ballsRemaining + 1; 
                //slifeRemaining = lifeRemaining - 1;
            }

    }
    if (BUTTON_PRESSED(BUTTON_A)){
                cheat = 1;
                b->active = 0;

            }
    //srand(time(0));
    if(b->active == 0 && cheat == 0){
        b->row = 10;
        b->col = rand() % 110;
        b->active = 1;
        }
    }

void drawBlueAliens(ALIEN* b) {
    if(b->active) {
        shadowOAM[b->index].attr0 = (b->row & ROWMASK) | ATTR0_4BPP | ATTR0_WIDE;
        shadowOAM[b->index].attr1 = (b->col & COLMASK) | ATTR1_MEDIUM;
        shadowOAM[b->index].attr2 = ATTR2_PALROW(0)| ATTR2_TILEID(0, 4);
    } else {
        shadowOAM[b->index].attr0 = ATTR0_HIDE;
    }
}
void initRedAliens() {
        for (int i = 0; i < RALIENCOUNT; i++) {
            redAliens[i].width = 8;
            redAliens[i].height = 8;
            redAliens[i].rdel = 1;
            redAliens[i].cdel = 1;
            redAliens[i].row = 10;
            redAliens[i].col = 20 + (i * 10);
            redAliens[i].active = 1;
            redAliens[i].index = i+1+RALIENCOUNT;
    }
}

void updateRedAliens(ALIEN* b) { 
    if (b->active) {

        // Bounce the ball off the sides of the box
        //if (b->row <= 1 || b->row + b->height-1 >= 119)
            //b->rdel *= -1;
        //if (b->col <= 1 || b->col + b->width-1 >= SCREENWIDTH-2)
            //b->cdel *= -1;

        // Move the ball
        //b->row += b->rdel;
        //b->col += b->cdel;

        if (b->col <= 160 || b->col + b->height-1 >= 240 || b->row + b->height-1 <=10)
            b->cdel = -1;
            if (b->row >= 160 || b->col + b->width-1 >= SCREENHEIGHT-2){
                b->active = 0;
            }
            b->row += b->rdel;
        // Handle ball-bullet collisions
        for (int i = 0; i < BULLETCOUNT; i++) {
            if (bullets[i].active && collision(b->row, b->col, b->height, b->width,
                bullets[i].row, bullets[i].col, bullets[i].height, bullets[i].width)) {

                // Put ball back in the pool
                bullets[i].active = 0;
                b->active = 0;

                // Update the score
                score++;
            } 
        }
        if (collision(b->row, b->col, b->height, b->width,
                player.row, player.col, player.height, player.width)) {  

                // Put ball back in the pool
                //bullets[i].active = 0;
                b->active = 0;
            if(collect >= 0){
                collect--;
            }
                lives--;
                //goToLose();

                // Update the score
                //ballsRemaining = ballsRemaining + 1; 
                //slifeRemaining = lifeRemaining - 1;
            }
            


    }

    if (BUTTON_PRESSED(BUTTON_A)){
                cheat = 1;
                b->active = 0;

            }
    if(b->active == 0 && cheat == 0){
        b->row = 10;
        b->col = rand() % 110;
        b->active = 1;
        }
    }

void drawRedAliens(ALIEN* b) {
    if(b->active) {
        shadowOAM[b->index].attr0 = (b->row & ROWMASK) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[b->index].attr1 = (b->col & COLMASK) | ATTR1_SMALL;
        shadowOAM[b->index].attr2 = ATTR2_PALROW(0)| ATTR2_TILEID(0, 8);
    } else {
        shadowOAM[b->index].attr0 = ATTR0_HIDE;
    }
}

void initEnemyBullets() {
    for (int i = 0; i < EBULLETCOUNT; i++) { 

        ebullets[i].height = 1;
        ebullets[i].width = 1;
        ebullets[i].row = -ebullets[i].height;
        ebullets[i].col = 0;
        ebullets[i].rdel = 2;
        ebullets[i].cdel = 0;
        ebullets[i].active = 0;
        ebullets[i].index = i+1 + GALIENCOUNT + BALIENCOUNT + RALIENCOUNT;
    }
}
void enemyFireBullets() {

     for (int i = 0; i < (EBULLETCOUNT); i++) {
        if (!ebullets[i].active & greenAliens[i].active) {

            // Position the new bullet
            ebullets[i].row = greenAliens[i].row;
            ebullets[i].col = greenAliens[i].col;


            // Slant it in the direction of player movement
            ebullets[i].cdel = player.cDirection;

            // Take the bullet out of the pool
            ebullets[i].active = 1;

            // Break out of the loop

            break;
        }
    }
}

void drawEBullet(BULLET* b){
    if(b-> active) {
        shadowOAM[b->index].attr0 = (b->row & ROWMASK) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[b->index].attr1 = (b->col & COLMASK) | ATTR1_TINY;
        // Bullet sizes are different rows on sprite sheet
        shadowOAM[b->index].attr2 = ATTR2_PALROW(0)| ATTR2_TILEID(0, 12);
    }else {
       shadowOAM[b->index].attr0 = ATTR0_HIDE;
    }
}
void updateEBullets(BULLET* b) {
    if (b->active) {
        if (b->row + b->height-1 >= 0
            && b->col + b->cdel > 0
            && b->col + b->cdel < SCREENWIDTH-1 &&
            b->row < 160) {

            b->row += b->rdel;
            b->col += b->cdel;
        } else {
            b->active = 0;
        }
    }
}

