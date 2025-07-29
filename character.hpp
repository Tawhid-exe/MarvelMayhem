#include "iGraphics.h"
#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include <cstdlib> // For rand()
#include <ctime>   // For srand()
#include <iostream>
#include <string>

using namespace std;

const int MAX_FRAMES = 30;

enum AnimationState {
	IDLE,
	MOVE,
	MOVE_B,
	JUMP,
	ATTACK,
	SKILL,
	ULTIMATE,
	DEAD
};

struct Character{
	std::string name;
	AnimationState characterState;
	double hp;
	bool alive;
	int moveX;
	int moveY;

	// Animation data
	int idleSprites[MAX_FRAMES];
	int moveSprites[MAX_FRAMES];
	int moveBackSprites[MAX_FRAMES];
	int jumpSprites[MAX_FRAMES];
	int attackSprites[MAX_FRAMES];
	int skillSprites[MAX_FRAMES];
	int ultimateSprites[MAX_FRAMES];
	int deadSprites[MAX_FRAMES];

	// Frame counts
	int idleCount, moveCount, moveBackCount, jumpCount;
	int attackCount, skillCount, ultimateCount, deadCount;

	// Current animation frame
	int currentFrame;

	//direction of facing
	bool facingRight;
	
	Character()
		: name("Captain America"),
		characterState(IDLE),
		hp(1000),
		alive(true),
		moveX(100),
		moveY(100),
		idleCount(0), moveCount(0), moveBackCount(0), jumpCount(0),
		attackCount(0), skillCount(0), ultimateCount(0), deadCount(0),
		currentFrame(0),
		facingRight(true)
	{}

	// Updates the current frame 
	// & initiazile maxFrame for each AnimationState
	void update() {
		int maxFrame = 1;
		switch (characterState) {
		case IDLE:     maxFrame = idleCount; break;
		case MOVE:     maxFrame = moveCount; break;
		case MOVE_B:   maxFrame = moveBackCount; break;
		case JUMP:     maxFrame = jumpCount; break;
		case ATTACK:   maxFrame = attackCount; break;
		case SKILL:    maxFrame = skillCount; break;
		case ULTIMATE: maxFrame = ultimateCount; break;
		case DEAD:     maxFrame = deadCount; break;
		}
		// if current frame exeeds maxFrame then it resets back to 0
		// prevent divide-by-zero
		if (maxFrame > 0) currentFrame = (currentFrame + 1) % maxFrame;
		else currentFrame = 0;
	}

	// a pointer is declared and initialized with zero 
	// this pointer points to each array address in case of each AnimationState
	void draw() {
		int* spriteArray = nullptr;
		int count = 0;

		switch (characterState) {
		case IDLE:      spriteArray = idleSprites;      count = idleCount; break;
		case MOVE:      spriteArray = moveSprites;      count = moveCount; break;
		case MOVE_B:    spriteArray = moveBackSprites;  count = moveBackCount; break;
		case JUMP:      spriteArray = jumpSprites;      count = jumpCount; break;
		case ATTACK:    spriteArray = attackSprites;    count = attackCount; break;
		case SKILL:     spriteArray = skillSprites;     count = skillCount; break;
		case ULTIMATE:  spriteArray = ultimateSprites;  count = ultimateCount; break;
		case DEAD:      spriteArray = deadSprites;      count = deadCount; break;
		}

		// if the pointer is not null and count has frames Show the images
		if (spriteArray && count > 0) {
			iShowImage(moveX, moveY, 100, 140, spriteArray[currentFrame]);
		}
	}

	void setState(AnimationState newState) {
		if (characterState != newState) {
			characterState = newState;
			currentFrame = 0;
		}
	}

};


// this fuction loads sprites in sequence from a folder
// *arr points to int array that hold ID of loaded sprites  
// count is passed by ref for the func to change the original value
// *folder is a pointer to string that hold path of my sprites folder
// *prefix is pointer to string that hold common name of all the sprites in a folder
//										[walk001.p, walk002.p, ..... etc]
void loadSprites(int *arr, int &count, const char *folder, const char *prefix, int frameCount){
	char path[200];  // holds the file path of each image
	count = frameCount;  // sets the count to number frames we are going to load for an animation state
	for (int i = 0; i < frameCount; i++) {
		// Build "folder/prefix1.png", "folder/prefix2.png", …
		sprintf_s(path, sizeof(path), "%s/%s%d.png", folder, prefix, i + 1);

		// Load once and check for failure
		int imageID = iLoadImage(path);
		if (imageID < 0) {
			printf("Failed to load sprite: %s\n", path);
		}
		arr[i] = imageID;
	}
}

void loadCaptainAmerica(Character &ca) {
	loadSprites(ca.idleSprites, ca.idleCount, "SPRITE/CaptainAmerica", "idle", 1);
	loadSprites(ca.moveSprites, ca.moveCount, "SPRITE/CaptainAmerica/walking_transparent_png", "walk", 12);
	loadSprites(ca.moveBackSprites, ca.moveBackCount, "SPRITE/CaptainAmerica/walking_transparent_png", "walk", 12); // reuse same walk for back
}


#endif






// --------------- might use later -------------------------
/*
void loadCaptainAmerica(Character& ca) {
ca.name = "Captain America";

loadAnimation(ca.idleSprites, ca.idleCount, "Characters/CaptainAmerica/Idle/ca_idle_", 1);
loadAnimation(ca.moveSprites, ca.moveCount, "Characters/CaptainAmerica/Walk/ca_walk_", 12);
loadAnimation(ca.moveBackSprites, ca.moveBackCount, "Characters/CaptainAmerica/WalkBack/ca_back_", 12); // optional
loadAnimation(ca.jumpSprites, ca.jumpCount, "Characters/CaptainAmerica/Jump/ca_jump_", 8);
loadAnimation(ca.attackSprites, ca.attackCount, "Characters/CaptainAmerica/Attack/ca_atk_", 10);
loadAnimation(ca.skillSprites, ca.skillCount, "Characters/CaptainAmerica/Skill/ca_skill_", 15);
loadAnimation(ca.ultimateSprites, ca.ultimateCount, "Characters/CaptainAmerica/Ultimate/ca_ult_", 20);
loadAnimation(ca.deadSprites, ca.deadCount, "Characters/CaptainAmerica/Dead/ca_dead_", 10);
}
*/








