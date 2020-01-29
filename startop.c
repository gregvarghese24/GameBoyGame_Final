#include <stdlib.h>
#include "myLib.h"
#include "game.h"
#include "bg.h"
#include "bg2.h"
#include "spritesheet.h"
#include "startop.h"
#include "gamebg.h"
#include "gamebg2.h" 


// Variables
SELECTOR selector;
int option;
int hOff;
int win;
int vOff;
  


void initStart() {
 	option = 0;
 	win = 1;
    initSelector(); 
    // initBullets();
    // initEnemyBullets();
    // initGreenAliens();
    // initBlueAliens();
    // initRedAliens();
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
void updateStart() {
    updateSelector();
    // for (int i = 0; i < BULLETCOUNT; i++) {
    //     updateBullets(&bullets[i]);
    // }
    // for (int i = 0; i < BULLETCOUNT; i++) {
    //     updateEBullets(&ebullets[i]);
    // }
    // for (int i = 0; i < GALIENCOUNT; i++) {
    //     updateGreenAliens(&greenAliens[i]);
    // }
    // for (int i = 0; i < BALIENCOUNT; i++) {
    //     updateBlueAliens(&blueAliens[i]);
    // }
    // for (int i = 0; i < RALIENCOUNT; i++) {
    //     updateRedAliens(&redAliens[i]);
    // }
    // if (seed % 30 == 0) {
    //     enemyFireBullets();
    //     srand(seed);
    // } else {
    //     srand(seed);
    // }
}
void drawStart() {
    drawSelector();
    // shadowOAM[100].attr0 = 2 | ATTR0_4BPP | ATTR0_WIDE;
    // shadowOAM[100].attr1 = 5 | ATTR1_MEDIUM;
    // shadowOAM[100].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(0,14);
    // if (lives == 3) {
    //     loadPalette(bg2Pal);
    //     shadowOAM[101].attr0 = 2 | ATTR0_4BPP | ATTR0_SQUARE;
    //     shadowOAM[101].attr1 = 35 | ATTR1_TINY;
    //     shadowOAM[101].attr2 = ATTR2_PALROW(2) | ATTR2_TILEID(2,18);
    // } else if (lives == 2) {
    //     loadPalette(bg2Pal);
    //     shadowOAM[101].attr0 = 2 | ATTR0_4BPP | ATTR0_SQUARE;
    //     shadowOAM[101].attr1 = 35 | ATTR1_TINY;
    //     shadowOAM[101].attr2 = ATTR2_PALROW(1) | ATTR2_TILEID(1,18);

    // } else if (lives == 1) {
    //     loadPalette(bg2Pal);
    //     shadowOAM[101].attr0 = 2 | ATTR0_4BPP | ATTR0_SQUARE;
    //     shadowOAM[101].attr1 = 35 | ATTR1_TINY;
    //     shadowOAM[101].attr2 = ATTR2_PALROW(1) | ATTR2_TILEID(1,18);

    // }
    // for (int i = 0; i < BULLETCOUNT; i++) {
    //     drawBullet(&bullets[i]);
    // }
    // for (int i = 0; i < BULLETCOUNT; i++) {
    //     drawEBullet(&ebullets[i]);
    // }
    // for (int i = 0; i < GALIENCOUNT; i++) {
    //     drawGreenAliens(&greenAliens[i]);
    // }
    // for (int i = 0; i < BALIENCOUNT; i++) {
    //     drawBlueAliens(&blueAliens[i]);
    // }
    // for (int i = 0; i < RALIENCOUNT; i++) {
    //     drawRedAliens(&redAliens[i]);
    // }
     DMANow(3, shadowOAM, OAM, 128*4);
}

void initSelector() {

    selector.width = 16;
    selector.height = 16;
    selector.rdel = 1;
    selector.cdel = 1;
    selector.row = 90;
    selector.col = 5;


}
void updateSelector() {
if (BUTTON_PRESSED(BUTTON_LEFT)
        && selector.col >= selector.cdel) {

			if(option > 0){
			selector.col -= 40; 
			option--;
		}
		
    } else if (BUTTON_PRESSED(BUTTON_RIGHT)
        && selector.col + selector.width - 1 < SCREENWIDTH - selector.cdel) {

        	if(option < 5 ){
        	selector.col += 40;
        	option++;
        }

    } 

    // Fire bullets

}

void drawSelector() {
    if (BUTTON_HELD(BUTTON_LEFT)) {

        shadowOAM[0].attr0 = selector.row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[0].attr1 = selector.col | ATTR1_SMALL;
        shadowOAM[0].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(2,0);

    } else if (BUTTON_HELD(BUTTON_RIGHT)) {
        shadowOAM[0].attr0 = selector.row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[0].attr1 = selector.col | ATTR1_SMALL;
        shadowOAM[0].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(2,0);

    } else {
        shadowOAM[0].attr0 = selector.row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[0].attr1 = selector.col | ATTR1_SMALL;
        shadowOAM[0].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(0,0);

    }
}
