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
		moveY(100),
		baseY(100),
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

void Character::handleInputMovement() {
	bool moveRight = isKeyPressed('d');
	bool moveLeft = isKeyPressed('a');

	if (moveLeft) {
		facingRight = false;
		moveX -= 5;
	}
	if (moveRight) {
		facingRight = true;
		moveX += 5;
	}
}


void Character::handleJump() {
	bool wPressed = isKeyPressed('w');

	if (wPressed && !jumpInProgress) {
		setState(JUMP);
		currentFrame = 0;
		jumpInProgress = true;
	}

	if (jumpInProgress) {
		int f = currentFrame;
		if (f == 0) moveY += 12;
		else if (f == 1) moveY += 8;
		else if (f == 2) moveY += 5;
		else if (f == 3) moveY -= 5;
		else if (f == 4) moveY -= 8;
		else if (f == 5) moveY -= 12;

		int maxJump = facingRight ? jumpCount_R : jumpCount_L;
		if (currentFrame >= maxJump - 1) {
			moveY = baseY;
			jumpInProgress = false;
		}
	}
}


void Character::handleAttack() {
	if (jumpInProgress && isKeyPressed('f')) {
		setState(ATTACK);
	}

	if (characterState == ATTACK) {
		int maxAtk = facingRight ? attackCount_R : attackCount_L;
		if (currentFrame >= maxAtk - 1) {
			if (isKeyPressed('f')) {
				currentFrame = 0;
			}
			else {
				setState(IDLE);
			}
		}
	}
	else if (isKeyPressed('f')) {
		setState(ATTACK);
	}
}

void Character::handleDefaultState() {
	if (!jumpInProgress && characterState != ATTACK) {
		if (isKeyPressed('a') || isKeyPressed('d')) {
			setState(WALK);
		}
		else {
			setState(IDLE);
		}

		// Ground check
		if (moveY < baseY) {
			moveY = baseY;
		}
	}
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

void draw() {
	int* spriteArray = nullptr;
	int count = 0;

	switch (characterState) {
	case IDLE:
		if (facingRight) {
			spriteArray = idleSprites_R;
			count = idleCount_R;
		}
		else {
			spriteArray = idleSprites_L;
			count = idleCount_L;
		} break;
	case WALK:
		if (facingRight) {
			spriteArray = walkSprites_R;
			count = walkCount_R;
		}
		else {
			spriteArray = walkSprites_L;
			count = walkCount_L;
		} break;

	case JUMP:
		if (facingRight) {
			spriteArray = jumpSprites_R;
			count = jumpCount_R;
		}
		else {
			spriteArray = jumpSprites_L;
			count = jumpCount_L;
		} break;

	case ATTACK:
		if (facingRight) {
			spriteArray = attackSprites_R;
			count = attackCount_R;
		}
		else {
			spriteArray = attackSprites_L;
			count = attackCount_L;
		} break;

	case SKILL:
		if (facingRight) {
			spriteArray = skillSprites_R;
			count = skillCount_R;
		}
		else {
			spriteArray = skillSprites_L;
			count = skillCount_L;
		} break;

	case ULTIMATE:
		if (facingRight) {
			spriteArray = ultimateSprites_R;
			count = ultimateCount_R;
		}
		else {
			spriteArray = ultimateSprites_L;
			count = ultimateCount_L;
		} break;

	case DEAD:
		if (facingRight) {
			spriteArray = deadSprites_R;
			count = deadCount_R;
		}
		else {
			spriteArray = deadSprites_L;
			count = deadCount_L;
		} break;
	}

	if (spriteArray && spriteArray[currentFrame] >= 0) {
		iShowImage(moveX, moveY, 100, 140, spriteArray[currentFrame]);
	}
	else {
		printf("Invalid image at frame %d\n", currentFrame);
	}
}

*/








