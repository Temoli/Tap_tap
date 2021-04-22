#include <SPI.h>
#include <Gamebuino.h>
Gamebuino gb;

const int LEFT = 1;
const int RIGHT = 2;
const int NO_DIR = 0;
const int NUM_BRICKS = 5;

int arrow = NO_DIR;
int score = 0;
int bricks[NUM_BRICKS];
int highscore = 0;

void setup(){
	gb.begin();
	gb.titleScreen(F("Tap Tap"));

	for (int i = 0; i < NUM_BRICKS; i++){
		bricks[i] = random(LEFT, RIGHT +1);
	}
}

void loop(){
	while(gb.update()){ //returns true every 50ms
		//PLAYER INPUT
		if(gb.buttons.released(BTN_LEFT)){
			arrow = LEFT;
		} else if (gb.buttons.released(BTN_RIGHT)){
			arrow = RIGHT;
		} else arrow = NO_DIR;

		//LOGIC
		if (score > 0){
			score -= 1;
		}

		if (arrow != NO_DIR){
			if (arrow == bricks[0]){
				score += 5;

				for (int i = 0; i < NUM_BRICKS - 1; i++)
					bricks[i] = bricks[i + 1];
				bricks[3] = random(LEFT, RIGHT + 1);
			} else{
				score -= 1;
			}
		}

		if (score > highscore) highscore = score;

		//DRAWIGN
		gb.display.clear();

		for (int i = 0, y = 0; i < NUM_BRICKS; i++, y += 10){ //y - corection in y axis; from bottom to top
			if (bricks[i] == LEFT){
				i == 0 ? gb.display.drawRect(20, 40 - y, 20, 10) : gb.display.fillRect(20, 40 - y, 20, 10);
			} else{
				i == 0 ? gb.display.drawRect(40, 40 - y, 20, 10) : gb.display.fillRect(40, 40 - y, 20, 10);
			}
		}

		gb.display.print(score);
		gb.display.cursorX = LCDWIDTH-11;
		gb.display.print(highscore);
		gb.display.fillRect(0, LCDHEIGHT - (score / 5), 4, (score / 5));
		gb.display.drawFastHLine(0, LCDHEIGHT - (highscore / 5), 6);
	}
}