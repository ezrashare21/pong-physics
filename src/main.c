// pong with physics 1.0

#include "raylib.h"

int center_text(char *text, int fontsize) {
	return MeasureText(text,fontsize)/2;
}

int main(void) {
	// initalize raylib
	InitWindow(800, 500, "Pong With Physics - 1.0");
	InitAudioDevice();

	int target_y_en = 0;
	float en_y = 0;
	float py = 0;
	float ballx = (GetScreenWidth() / 2);
	float bally = 40;
	float ballsy = 0;
	float ballsx = -5;
	float ballspeed_x = 0.1;
	bool collision = false;
	bool en_collision = false;
	char* score = "0";
	int middle_screen = (GetScreenWidth()/2);

	int p_score = 0;
	int en_score = 0;

	Rectangle BallBox = {ballx, bally, 20, 20};
	Rectangle playerBox = {20, py, 10, 100};
	Rectangle enemyBox = {GetScreenWidth()-60, en_y, 10, 100};

	int won = 0;

	Sound bounce = LoadSound("data/bounce.wav");
	Sound enemy = LoadSound("data/enemy.wav");
	Sound score_sound = LoadSound("data/score.wav");
	Sound bounce_wall = LoadSound("data/bouncewall.wav");
	Sound newgame = LoadSound("data/newgame.wav");

	SetTargetFPS(60);

	target_y_en = GetScreenHeight()/2;

    while (!WindowShouldClose()) {
        BeginDrawing();
        	ClearBackground(RAYWHITE);
        	if (won == 0) {
	        	if (ballx > middle_screen) {
	        		target_y_en = bally + 20;
	        	}

	        	BallBox.x = ballx;
	        	BallBox.y = bally;
	        	playerBox.y = py;
	        	enemyBox.y = en_y;

	        	collision = CheckCollisionRecs(BallBox, playerBox);
	        	en_collision = CheckCollisionRecs(BallBox,enemyBox);

	        	if (collision || en_collision) {
	        		ballsy = -7;
	        		ballsx *= -1;
	        		ballsx *= 1.05;
	        		PlaySound(bounce);
	        	} else if (bally < 0 || (bally+20) > GetScreenHeight()) {
	        		ballsy *= -1.1;
	        		PlaySound(bounce_wall);
	        	} else if (ballx < 0) { // enemy score
	        		ballx = (GetScreenWidth() / 2);
	        		bally = 40;
	        		ballsy = 0;
					ballsx = -5;
					en_score+=1;
					PlaySound(enemy);
	        	} else if (ballx > GetScreenWidth()) { // player score
	        		ballx = (GetScreenWidth() / 2);
	        		bally = 40;
	        		ballsy = 0;
					ballsx = -5;
					p_score+=1;
					PlaySound(score_sound);
	        	}

	        	if (p_score > 4) {
	        		won = 1;
	        	} else if (en_score > 4) {
	        		won = 2;
	        	}

	        	int speed = 3;
				ballsy += ballspeed_x;

				py += ((GetMousePosition().y - 40) - py) / speed;
				en_y += ((target_y_en - 40) - en_y) / (speed + 4);
				ballx += ballsx;
				bally += ballsy;
	            DrawRectangle(20, py, 10, 100, BLACK); // player paddle
	            DrawRectangle(ballx,bally,20,20,BLACK); // ball
	            DrawRectangle(GetScreenWidth()-60,en_y,10,100,BLACK); // enemy paddle
	            for (int a = 0; a < GetScreenHeight(); a += 30) {
	            	DrawRectangle(middle_screen-2,a,4,20,BLACK);
	            }
	            score = p_score+'0';
	            DrawText(&score,middle_screen-50,10,60,BLACK);
	            score = en_score+'0';
	            DrawText(&score,middle_screen+20,10,60,BLACK);
	        } else {
	        	int size = 60;
	        	if (won == 1) {
	        		DrawText("You Win!", middle_screen - center_text("You Win!",size), (GetScreenHeight()/2)-size, size, LIGHTGRAY);
	        	} else {
	        		DrawText("You Lose...", middle_screen - center_text("You Lose...",size), (GetScreenHeight()/2)-size, size, LIGHTGRAY);
	        	}
	        	if (IsMouseButtonPressed(3)) {
	        		PlaySound(newgame);
	        		target_y_en = 0;
					en_y = 0;
					py = 0;
					ballx = (GetScreenWidth() / 2);
					bally = 40;
					ballsy = 0;
					ballsx = -5;
					ballspeed_x = 0.1;
					collision = false;
					en_collision = false;
					score = "0";
					middle_screen = (GetScreenWidth()/2);
					p_score = 0;
					en_score = 0;
					won = 0;
					SetTargetFPS(60);
					target_y_en = GetScreenHeight()/2;
	        	}
	        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
