// Selector Struct
typedef struct {
    int row;
    int col;
    int rdel; 
    int cdel;
    int width;
    int height;
    int aniCounter;
    int aniState;
    int prevAniState;
    int curFrame;
    int numFrames;
    int bulletTimer;
    int cDirection;
} SELECTOR;
  
//variables
extern SELECTOR selector;
extern int option;
extern int hOff;
extern int vOff;


//proto
void initStart();
void updateStart();
//void drawStart();
void initSelector();
void updateSelector();
void drawSelector();