//Finished Background, sprites, and sound
//need to make story level
//need to integrate game 3 into the main game
// one bug is that the pause state doesnt want to work anymore last minute, it worked a couple 
// minutes before submission
// for the first mini game, you gotta collect as many 4.0s to win. The beers and drugs will hidner your win. there's an algorithm that
// determines if you get into the next level (like how you dont know how to get into tech because
// admission officers are random). I still need to implement the score board. 
// mini game 3 is in the works. the one in the current gba file isnt the one that is going to be used



#include <stdlib.h>
#include <stdio.h>
#include "myLib.h"
#include "game3.h"
#include "game.h"
#include "game2.h"
//#include "startop.h"

#include "bg2.h"
#include "bg.h"
#include "start.h"
#include "pause.h"
#include "win.h"
#include "lose.h"
#include "spritesheet.h"
#include "spritesheeter.h"
#include "startop.h"
#include "gamebg.h"
#include "gamebg2.h"
#include "gamebg4.h"
#include "trees.h"
#include "furtherTrees.h"
#include "house.h"
#include "collisionmap.h"
#include "instruction.h"  
#include "gamebg3.h"
#include "sound.h"
#include "bimmerr.h"
#include "abelly.h"
#include "spriter.h"

// Prototypes
void initialize();

// State Prototypes
void goToStart();
void start();
//Instructions
void goToInstruct();
void instruct(); 

void goToMenu();
void menu();
void goToMenu2();
void menu2();
void goToGame();
void game();
void goToPause();
void pause();
void goToWin();
void win();
void goToLose();
void lose();

//game 2
void goToGame2();
void game2();
void gameMech();

//game 3
void goToGame3();
void game3();


// States
enum {START, INSTRUCT, MENU, MENU2, GAME, GAME2, GAME3, PAUSE, WIN, LOSE};
int state;
int lives;
int score;


OBJ_ATTR shadowOAM[128];

// Button Variables
unsigned short buttons;
unsigned short oldButtons;
//horz offset
int hhOff;
// Random Seed

// Text Buffer
char buffer[61];

SOUND soundA;
SOUND soundB;
const unsigned char* spaceSound;
int* spaceSoundLen;
int spaceSoundToPlay = 0;



int main() {

    initialize();
    setupSounds();
    setupInterrupts();
    playSoundA(bimmerr, BIMMERRLEN ,BIMMERRFREQ, 1);
    while(1) {

        // Update button variables
        oldButtons = buttons;
        buttons = BUTTONS;

        // State Machine
        switch(state) {

            case START:
                start();
                break;
            case INSTRUCT:
                instruct();
                break;
            case MENU:
                menu();
                break;
            case MENU2:
                menu2();
                break;
            case GAME:
                game();
                break;
            case GAME2:
                game2();
                break;
            case GAME3:
                game3();
                break;
            case PAUSE:
                pause();
                break;
            case WIN:
                win();
                break;
            case LOSE:
                lose();
                break;
        }
    } 
}

void initialize() {

    goToStart();
}

void goToStart() {
    waitForVBlank();

    REG_DISPCTL = MODE0 | BG0_ENABLE;
    loadPalette(startPal);

    REG_BG0CNT = BG_SIZE_LARGE | BG_CHARBLOCK(0) | BG_SCREENBLOCK(28);

    DMANow(3, startTiles, &CHARBLOCK[0], startTilesLen/2);
    DMANow(3, startMap, &SCREENBLOCK[28], startMapLen/2);


    REG_BG0HOFF = 0;
    REG_BG0VOFF = 0;


    state = START; 
}

void start() {

    waitForVBlank();

    if (BUTTON_PRESSED(BUTTON_START)) {
        playSoundA(abelly, ABELLYLEN ,ABELLYFREQ, 1);
        goToMenu();
        initStart();
        
    }else if(BUTTON_PRESSED(BUTTON_B)){
        goToInstruct();
    }
}
 
void goToInstruct(){
    waitForVBlank();

    REG_DISPCTL = MODE0 | BG0_ENABLE;
    loadPalette(instructionPal);

    REG_BG0CNT = BG_SIZE_SMALL | BG_CHARBLOCK(0) | BG_SCREENBLOCK(28);

    DMANow(3, instructionTiles, &CHARBLOCK[0], instructionTilesLen/2);
    DMANow(3, instructionMap, &SCREENBLOCK[28], instructionMapLen/2);


    REG_BG0HOFF = 0;
    REG_BG0VOFF = 0;


    state = INSTRUCT;
}

void instruct(){
    waitForVBlank();

    if (BUTTON_PRESSED(BUTTON_START)) {

        goToStart(); 
        initStart(); 
        
    }
}

void goToMenu(){
    loadPalette(bgPal);
    hOff = 0;

    DMANow(3, bgTiles, &CHARBLOCK[1], bgTilesLen/2);
    DMANow(3, bgMap, &SCREENBLOCK[24], bgMapLen/2);

    DMANow(3, bg2Tiles, &CHARBLOCK[0], bg2TilesLen/2);
    DMANow(3, bg2Map, &SCREENBLOCK[28], bg2MapLen/2);

    //loadPalette(bg2Pal); 

    DMANow(3, spritesheetTiles, &CHARBLOCK[4], spritesheetTilesLen/2);
    DMANow(3, spritesheetPal, SPRITEPALETTE, 256);
    hideSprites();
    DMANow(3, shadowOAM, OAM, 128*4);

    REG_DISPCTL = MODE0 | BG1_ENABLE |  SPRITE_ENABLE;

   // REG_BG0CNT = BG_SIZE_SMALL | BG_CHARBLOCK(0) | BG_SCREENBLOCK(28);
    REG_BG1CNT = BG_SIZE_SMALL | BG_CHARBLOCK(1) | BG_SCREENBLOCK(24);
 
    REG_BG0HOFF = hOff;
    REG_BG0VOFF = vOff;

    state = MENU;


}

void menu(){
    updateStart();
    waitForVBlank();
    drawStart();
    hOff = 0;
    if (BUTTON_PRESSED(BUTTON_START)) {
        if (option == 2){
        goToGame();
        initGame();
        }else if(BUTTON_PRESSED(BUTTON_B)){
            goToPause();
        }
        else if (option == 3){
            goToGame2();
            initGame2();
        }else if (option == 5){ 
            goToGame3();
            initGame3();
        }

    }
}

void goToMenu2(){
    loadPalette(bgPal);

    DMANow(3, bgTiles, &CHARBLOCK[1], bgTilesLen/2);
    DMANow(3, bgMap, &SCREENBLOCK[24], bgMapLen/2); 

    DMANow(3, bg2Tiles, &CHARBLOCK[0], bg2TilesLen/2);
    DMANow(3, bg2Map, &SCREENBLOCK[28], bg2MapLen/2);

    //loadPalette(bg2Pal);

    DMANow(3, spritesheetTiles, &CHARBLOCK[4], spritesheetTilesLen/2);
    DMANow(3, spritesheetPal, SPRITEPALETTE, 256);
    hideSprites();
    DMANow(3, shadowOAM, OAM, 128*4);

    REG_DISPCTL = MODE0 | BG0_ENABLE | BG1_ENABLE | SPRITE_ENABLE;

    REG_BG0CNT = BG_SIZE_LARGE | BG_CHARBLOCK(0) | BG_SCREENBLOCK(28);
    REG_BG1CNT = BG_SIZE_LARGE | BG_CHARBLOCK(1) | BG_SCREENBLOCK(24);
 
    REG_BG0HOFF = hOff;
    REG_BG0VOFF = vOff;
}

void menu2(){

}


void goToGame() {


    loadPalette(gamebgPal);

    DMANow(3, gamebgTiles, &CHARBLOCK[1], gamebgTilesLen/2);
    DMANow(3, gamebgMap, &SCREENBLOCK[28], gamebgMapLen/2);

    DMANow(3, gamebg2Tiles, &CHARBLOCK[0], gamebg2TilesLen/2); //box
    DMANow(3, gamebg2Map, &SCREENBLOCK[24], gamebg2MapLen/2);

    DMANow(3, gamebg3Tiles, &CHARBLOCK[2], gamebg3TilesLen/2); //city
    DMANow(3, gamebg3Map, &SCREENBLOCK[31], gamebg3MapLen/2);

    //loadPalette(bg2Pal);

    DMANow(3, spritesheetTiles, &CHARBLOCK[4], spritesheetTilesLen/2);
    DMANow(3, spritesheetPal, SPRITEPALETTE, 256);
    //hideSprites();
    DMANow(3, shadowOAM, OAM, 128*4);

    REG_DISPCTL = MODE0  | BG1_ENABLE  | BG0_ENABLE | BG2_ENABLE | SPRITE_ENABLE;

    REG_BG0CNT = BG_SIZE_SMALL | BG_CHARBLOCK(0) | BG_SCREENBLOCK(24); //box
    REG_BG1CNT = BG_SIZE_SMALL | BG_CHARBLOCK(1) | BG_SCREENBLOCK(28); //city 1

    REG_BG2CNT = BG_SIZE_SMALL | BG_CHARBLOCK(2) | BG_SCREENBLOCK(31); //city 2
    hOff = 0;

    //REG_BG0HOFF = hOff;
    //REG_BG0VOFF = vOff;
 
    // REG_DISPCTL = MODE0 | BG0_ENABLE | BG1_ENABLE;

    // // TODO 4.1 - edit display control register to enable bg 0
    // //REG_DISPCTL = BG1_ENABLE;

    // // TODO 2.2 - load tile palette
    // DMANow(3, &furtherTreesPal, PALETTE, 256);
    // //loadPalette(furtherTreesPal)
    // // TODO 2.3 - set up bg 1 control register
    // REG_BG1CNT = BG_SIZE_SMALL | BG_CHARBLOCK(0) | BG_SCREENBLOCK(31);
    // // TODO 2.4 - load furtherTrees tiles to charblock
    // DMANow(3, furtherTreesTiles, &CHARBLOCK[0], furtherTreesTilesLen/2);
    // // TODO 2.5 - load furtherTrees map to screenblock
    // DMANow(3, furtherTreesMap, &SCREENBLOCK[31], furtherTreesMapLen/2);

    // // TODO 4.2 - set up bg 0 control register
    // REG_BG0CNT = BG_SIZE_WIDE | BG_CHARBLOCK(1) | BG_SCREENBLOCK(29);
    // // TODO 4.3 - load trees tiles to charblock
    // DMANow(3, treesTiles, &CHARBLOCK[1], treesTilesLen/2);
    // // TODO 4.4 - load trees map to screenblock
    // DMANow(3, treesMap, &SCREENBLOCK[29], treesMapLen/2);
    
    // hhOff = 0;
    

    buttons = BUTTONS;
    state = GAME;
}

void game() {

    updateGame();
    
    
    

    drawGame();
    waitForVBlank();
    if(BUTTON_HELD(BUTTON_LEFT)) {
        hOff--;
    }
    if(BUTTON_HELD(BUTTON_RIGHT)) {
        hOff++;

    // State transitions
    if (BUTTON_PRESSED(BUTTON_B)){
        goToPause();
    }
    // else if (lives == 0){
        
    //     goToLose();
    //     lives = - 3;
    //     hOff = 0;
    // } 
    else if (score == 15) {
        goToWin();
    }
    }
    REG_BG2HOFF = hOff;
    REG_BG1HOFF = hOff/2;
}

void goToGame2(){
    //loadPalette(bg2Pal);

   // DMANow(3, acceptTiles, &CHARBLOCK[1], acceptTilesLen/2);
    //DMANow(3, acceptMap, &SCREENBLOCK[24], acceptMapLen/2);

    //DMANow(3, bg2Tiles, &CHARBLOCK[0], bg2TilesLen/2);
    //DMANow(3, bg2Map, &SCREENBLOCK[28], bg2MapLen/2);

    DMANow(3, gamebgTiles, &CHARBLOCK[1], gamebgTilesLen/2);
    DMANow(3, gamebgMap, &SCREENBLOCK[28], gamebgMapLen/2);

    DMANow(3, gamebg4Tiles, &CHARBLOCK[2], gamebg4TilesLen/2); //city
    DMANow(3, gamebg4Map, &SCREENBLOCK[31], gamebg4MapLen/2);

    //loadPalette(bg2Pal);

    DMANow(3, spriterTiles, &CHARBLOCK[4], spriterTilesLen/2);
    DMANow(3, spriterPal, SPRITEPALETTE, 256);
    hideSprites();
    DMANow(3, shadowOAM, OAM, 128*4);

    REG_DISPCTL = MODE0 | BG0_ENABLE | BG1_ENABLE | SPRITE_ENABLE;

    //REG_BG0CNT = BG_SIZE_LARGE | BG_CHARBLOCK(0) | BG_SCREENBLOCK(28);
    REG_BG0CNT = BG_SIZE_SMALL | BG_CHARBLOCK(1) | BG_SCREENBLOCK(28); //city 1

    REG_BG1CNT = BG_SIZE_SMALL | BG_CHARBLOCK(2) | BG_SCREENBLOCK(31);
    //REG_BG1CNT = BG_SIZE_LARGE | BG_CHARBLOCK(1) | BG_SCREENBLOCK(24);

    hOff = 0;

    state = GAME2;

}

void game2(){
    gameMech();
    if(BUTTON_PRESSED(BUTTON_B)){
        hOff = 0;
         goToPause();
    }
    if(BUTTON_HELD(BUTTON_LEFT)) {
        hOff--;
    }
    if(BUTTON_HELD(BUTTON_RIGHT)) {
        hOff++;
    }

    REG_BG2HOFF = hOff;
    REG_BG1HOFF = hOff/2;
}

void gameMech(){
    updateGame2();

    waitForVBlank();

    drawGame2();


    // State transitions
    
    
}

void goToGame3(){
    waitForVBlank();

    // Set up the house background
    DMANow(3, housePal, PALETTE, 256);
    DMANow(3, houseTiles, &CHARBLOCK[0], houseTilesLen/2);
    DMANow(3, houseMap, &SCREENBLOCK[31], houseMapLen/2);
    REG_BG0VOFF = vOff;
    REG_BG0HOFF = hOff;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_SIZE_SMALL;

    // Set up the sprites
    DMANow(3, spritesheetTiles, &CHARBLOCK[4], spritesheetTilesLen/2);
    DMANow(3, spritesheetPal, SPRITEPALETTE, spritesheetPalLen/2);
    hideSprites();
    DMANow(3, shadowOAM, OAM, 128*4);

    // Set up the display
    REG_DISPCTL = MODE0 | BG0_ENABLE | SPRITE_ENABLE;

    state = GAME3;
}

void game3(){
    updateGame3();
    drawGame3();
    if(BUTTON_PRESSED(BUTTON_B)){
        goToPause();
    }
}

 
void goToPause() {

    REG_DISPCTL = MODE0 | BG0_ENABLE;
    loadPalette(pausePal);

    REG_BG0CNT = BG_SIZE_LARGE | BG_CHARBLOCK(0) | BG_SCREENBLOCK(28);

    DMANow(3, pauseTiles, &CHARBLOCK[0], pauseTilesLen/2);
    DMANow(3, pauseMap, &SCREENBLOCK[28], pauseMapLen/2);

    state = PAUSE;
} 

void pause() { 

    // Lock the framerate to 60 fps
    waitForVBlank(); 

    // State transitions
    if (BUTTON_PRESSED(BUTTON_START))
        goToMenu();
    else if (BUTTON_PRESSED(BUTTON_B)){
        if(option == 3){
            goToGame2();
        }
        else if(option == 2){
            goToGame();
        }else if(option == 5){
            goToGame3();
        }
    }else if(BUTTON_PRESSED(BUTTON_A)){
        pauseSound();
        playSoundA(bimmerr, BIMMERRLEN ,BIMMERRFREQ, 1);
        goToStart();
    }
}

void goToWin() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;
    loadPalette(winPal);
    hOff = 0;
    REG_BG0CNT = BG_SIZE_SMALL | BG_CHARBLOCK(0) | BG_SCREENBLOCK(28);

    DMANow(3, winTiles, &CHARBLOCK[0], winTilesLen/2);
    DMANow(3, winMap, &SCREENBLOCK[28], winMapLen/2);
    state = WIN;
}

void win() {
    //hOff = 0;
    // Lock the framerate to 60 fps
    waitForVBlank();

    // State transitions
    if (BUTTON_PRESSED(BUTTON_START))
        goToMenu();
}

// Sets up the lose state
void goToLose() {
    REG_DISPCTL = MODE0 | BG0_ENABLE;
    loadPalette(losePal);

    REG_BG0CNT = BG_SIZE_SMALL | BG_CHARBLOCK(0) | BG_SCREENBLOCK(28);

    DMANow(3, loseTiles, &CHARBLOCK[0], loseTilesLen/2);
    DMANow(3, loseMap, &SCREENBLOCK[28], loseMapLen/2);
    state = LOSE;
}

// Runs every frame of the lose state
void lose() {

    // Lock the framerate to 60 fps
    waitForVBlank();

    // State transitions
    if (BUTTON_PRESSED(BUTTON_START))
        //hOff = 0;
        goToMenu();
        //hOff = 0;
}