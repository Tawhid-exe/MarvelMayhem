//#include "iGraphics.h"
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
	WALK,
	JUMP,
	ATTACK,
	SKILL,
	ULTIMATE,
	DEAD
};

struct Character{
	
	AnimationState characterState;
	string name;
	double hp;
	bool alive;
	int moveX;
	int moveY;
	int baseY; // fixed ground Y


	// Animation data(hold Image ID) 
	int idleSprites_R[MAX_FRAMES], idleSprites_L[MAX_FRAMES];
	int walkSprites_R[MAX_FRAMES], walkSprites_L[MAX_FRAMES];
	int jumpSprites_R[MAX_FRAMES], jumpSprites_L[MAX_FRAMES];
	int attackSprites_R[MAX_FRAMES], attackSprites_L[MAX_FRAMES];
	int skillSprites_R[MAX_FRAMES], skillSprites_L[MAX_FRAMES];
	int ultimateSprites_R[MAX_FRAMES], ultimateSprites_L[MAX_FRAMES];
	int deadSprites_R[MAX_FRAMES], deadSprites_L[MAX_FRAMES];              

	// Frame counts
	int idleCount_R, idleCount_L;
	int walkCount_R, walkCount_L;
	int attackCount_R, attackCount_L;
	int skillCount_R, skillCount_L;
	int ultimateCount_R, ultimateCount_L;
	int deadCount_R, deadCount_L;
	int jumpCount_R, jumpCount_L;

	// Current animation frame
	int currentFrame;

	//direction of facing
	bool facingRight;
	
	// Constructor
	Character()
		: name("Captain America"),
		characterState(IDLE),
		hp(1000),
		alive(true),
		moveX(100),
		moveY(113),
		baseY(113),
		facingRight(true),
		currentFrame(0),
		idleCount_R(0), idleCount_L(0),
		walkCount_R(0), walkCount_L(0),
		jumpCount_R(0), jumpCount_L(0),
		attackCount_R(0), attackCount_L(0),
		skillCount_R(0), skillCount_L(0),
		ultimateCount_R(0), ultimateCount_L(0),
		deadCount_R(0), deadCount_L(0)
	{}  // initializer list has been used so the body stays empty

	//initiazile maxFrame for each AnimationState update frames
	void update() {
		int maxFrame = 1;
		switch (characterState) {
		case IDLE:     maxFrame = facingRight ? idleCount_R : idleCount_L; break;
		case WALK:     maxFrame = facingRight ? walkCount_R : walkCount_L; break;
		case JUMP:     maxFrame = facingRight ? jumpCount_R : jumpCount_L; break;
		case ATTACK:   maxFrame = facingRight ? attackCount_R : attackCount_L; break;
		case SKILL:    maxFrame = facingRight ? skillCount_R : skillCount_L; break;
		case ULTIMATE: maxFrame = facingRight ? ultimateCount_R : ultimateCount_L; break;
		case DEAD:     maxFrame = facingRight ? deadCount_R : deadCount_L; break;
		}
		// Updates the current frame
		if (maxFrame > 0) currentFrame = (currentFrame + 1) % maxFrame;
		else currentFrame = 0;
	}


	// a pointer is declared and initialized as a null pointer 
	// this pointer points to each array address in case of each AnimationState
	void draw() {
		int* spriteArray = nullptr;
		int count = 0;

		switch (characterState) {
		case IDLE:
			spriteArray = facingRight ? idleSprites_R : idleSprites_L;
			count = facingRight ? idleCount_R : idleCount_L;
			break;
		case WALK:
			spriteArray = facingRight ? walkSprites_R : walkSprites_L;
			count = facingRight ? walkCount_R : walkCount_L;
			break;
		case JUMP:
			spriteArray = facingRight ? jumpSprites_R : jumpSprites_L;
			count = facingRight ? jumpCount_R : jumpCount_L;
			break;
		case ATTACK:
			spriteArray = facingRight ? attackSprites_R : attackSprites_L;
			count = facingRight ? attackCount_R : attackCount_L;
			break;
		case SKILL:
			spriteArray = facingRight ? skillSprites_R : skillSprites_L;
			count = facingRight ? skillCount_R : skillCount_L;
			break;
		case ULTIMATE:
			spriteArray = facingRight ? ultimateSprites_R : ultimateSprites_L;
			count = facingRight ? ultimateCount_R : ultimateCount_L;
			break;
		case DEAD:
			spriteArray = facingRight ? deadSprites_R : deadSprites_L;
			count = facingRight ? deadCount_R : deadCount_L;
			break;
		}

		if (spriteArray && spriteArray[currentFrame] >= 0) {
			iShowImage(moveX, moveY, 100, 140, spriteArray[currentFrame]);
		}
		else {
			printf("Invalid image at frame %d\n", currentFrame);
		}
	}


	// Changes the character's animation state and resets the frame to zero to start animation of the state from beggining again
	void setState(AnimationState newState) {
		if (characterState != newState) {
			characterState = newState;
			currentFrame = 0;
		}
	}

	bool jumpInProgress = false;
	void handleInputMovement();
	void handleJump();
	void handleAttack();
	void handleDefaultState();
};

//Character c1, c2;

// this fuction loads sprites in sequence from a folder
// *arr points to int array that hold ID of loaded sprites  
// count is passed by ref for the func to change the original value
// *folder is a pointer to string that hold path of my sprites folder
// *prefix is pointer to string that hold common name of all the sprites in a folder
//										[walk001.p, walk002.p, ..... etc]
void loadSprites(int *arr, int &count, const char *folder, const char *prefix, int frameCount){
	char path[200];  // holds the file path of each image
	count = 0;  
	for (int i = 0; i < frameCount; i++) {
		// Build "folder/prefix1.png", "folder/prefix2.png", …
		sprintf_s(path, sizeof(path), "%s/%s%d.png", folder, prefix, i + 1);

		// Load once and check for failure
		int imageID = iLoadImage(path);
		if (imageID < 0) {
			printf("Failed to load sprite: %s\n", path);
			continue; // skip invalid image
		}
		arr[count++] = imageID;
	}
}

void loadCaptainAmerica(Character &ca) {
	loadSprites(ca.idleSprites_R, ca.idleCount_R, "SPRITE/CaptainAmerica/IDLE_R", "idle", 1);
	loadSprites(ca.idleSprites_L, ca.idleCount_L, "SPRITE/CaptainAmerica/IDLE_L", "idle", 1);

	loadSprites(ca.walkSprites_R, ca.walkCount_R, "SPRITE/CaptainAmerica/WALK_R", "walk", 12);
	loadSprites(ca.walkSprites_L, ca.walkCount_L, "SPRITE/CaptainAmerica/WALK_L", "walk", 12);

	loadSprites(ca.jumpSprites_R, ca.jumpCount_R, "SPRITE/CaptainAmerica/JUMP_R", "jump", 6);
	loadSprites(ca.jumpSprites_L, ca.jumpCount_L, "SPRITE/CaptainAmerica/JUMP_L", "jump", 6);

	loadSprites(ca.attackSprites_R, ca.attackCount_R, "SPRITE/CaptainAmerica/ATTACK_R", "attack", 8);
	loadSprites(ca.attackSprites_L, ca.attackCount_L, "SPRITE/CaptainAmerica/ATTACK_L", "attack", 8);

	//loadSprites(ca.skillSprites_R, ca.skillCount_R, "SPRITE/CaptainAmerica/SKILL_R", "skill", 15);
	//loadSprites(ca.skillSprites_L, ca.skillCount_L, "SPRITE/CaptainAmerica/SKILL_L", "skill", 15);

	//loadSprites(ca.ultimateSprites_R, ca.ultimateCount_R, "SPRITE/CaptainAmerica/ULTIMATE_R", "ultimate", 20);
	//loadSprites(ca.ultimateSprites_L, ca.ultimateCount_L, "SPRITE/CaptainAmerica/ULTIMATE_L", "ultimate", 20);

	//loadSprites(ca.deadSprites_R, ca.deadCount_R, "SPRITE/CaptainAmerica/DEAD_R", "dead", 10);
	//loadSprites(ca.deadSprites_L, ca.deadCount_L, "SPRITE/CaptainAmerica/DEAD_L", "dead", 10);
}

void handleInputMovement(Character &c1, bool moveRight, bool moveLeft) {
	if (moveLeft) {
		c1.facingRight = false;
		c1.moveX -= 5;
	}
	if (moveRight) {
		c1.facingRight = true;
		c1.moveX += 5;
	}
}

void handleJump(Character &c1, bool wPressed) {
	if (wPressed && !c1.jumpInProgress) {
		c1.setState(JUMP);
		c1.currentFrame = 0;
		c1.jumpInProgress = true;
	}

	if (c1.jumpInProgress) {
		int f = c1.currentFrame;
		if (f == 0) c1.moveY += 12;
		else if (f == 1) c1.moveY += 8;
		else if (f == 2) c1.moveY += 5;
		else if (f == 3) c1.moveY -= 5;
		else if (f == 4) c1.moveY -= 8;
		else if (f == 5) c1.moveY -= 12;

		int maxJump = c1.facingRight ? c1.jumpCount_R : c1.jumpCount_L;
		if (c1.currentFrame >= maxJump - 1) {
			c1.moveY = c1.baseY;
			c1.jumpInProgress = false;
			c1.setState(IDLE);
		}
	}
}

void handleAttack(Character &c1, bool fPressed) {
	if (c1.jumpInProgress && fPressed) {
		c1.setState(ATTACK);
	}
	if (c1.characterState == ATTACK) {
		int maxAtk = c1.facingRight ? c1.attackCount_R : c1.attackCount_L;
		if (c1.currentFrame >= maxAtk - 1) {
			if (fPressed) {
				c1.currentFrame = 0;
			}
			else {
				c1.setState(IDLE);
			}
		}
	}
	else if (fPressed) {
		c1.setState(ATTACK);
	}
}

void handleDefaultState(Character &c1, bool moveRight, bool moveLeft) {
	if (!c1.jumpInProgress && c1.characterState != ATTACK) {
		if (moveRight || moveLeft) {
			c1.setState(WALK);
		}
		else {
			c1.setState(IDLE);
		}

		// Ground check
		if (c1.moveY < c1.baseY) {
			c1.moveY = c1.baseY;
		}
	}
}

#endif




