#include "iGraphics.h"
#include "menu.hpp"
#include "character.hpp"

Character captainAmericaP1;
Character captainAmericaP2;
int loadingScreen;

// Loading screen variables
int loadingBarWidth = 0;
bool loadingDone = false;
bool goToMainMenu = false;
bool blinkTextWhite = true;
static bool assetsLoaded = false;

// had to declare the function definition here otherwise it was not working 
void loadingScreenText();


void iDraw()
{
	iClear();

	if (!goToMainMenu)
	{
		// Show loading screen
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, loadingScreen);

		// Loading bar frame and fill
		iSetColor(255, 255, 255);
		iRectangle(390, 100, 500, 30);
		iFilledRectangle(390, 100, loadingBarWidth, 30);
		loadingScreenText();
	}
	else
	{
		// Show the actual menu screen after loading
		showMenu();
		
		// On the gameplay screen, render Captain
		if (currentScreen == 20){
			showArenaImages();
			if(selectedCharacterIndexP1 == 2) captainAmericaP1.draw();
			if(selectedCharacterIndexP2 == 2){
				//captainAmericaP2.moveX = 820;
				captainAmericaP2.draw();
			}

		}

	}
}

void iMouseMove(int mx, int my)
{

}

void iPassiveMouseMove(int mx, int my)
{
	if (goToMainMenu) {
		// Handle hover Animation
		handleHoverAnimation(mx, my);
	}
}

void iMouse(int button, int state, int mx, int my)
{
	if (goToMainMenu) {
		// Handle menu clicks only after the loading screen
		handleMenuClick(button, state, mx, my);
	}
}

// This function runs at a fixed interval
// Special Keys:
// GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
// GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT

void fixedUpdate() {
	if (!goToMainMenu || currentScreen != 20) return;

	// Player 1 controls (WASD + FEQ)
	handleInputMovementP1(captainAmericaP1);
	handleJumpP1(captainAmericaP1);
	handleAttackP1(captainAmericaP1);
	handleDefaultStateP1(captainAmericaP1);

	// Player 2 controls (Arrow keys + )
	handleInputMovementP2(captainAmericaP2);
	handleJumpP2(captainAmericaP2);
	handleAttackP2(captainAmericaP2);
	handleDefaultStateP2(captainAmericaP2);
}

// Handles the loading bar animation on loading screen
void loadingBar(){
	if (!loadingDone){
		loadingBarWidth += 5;
		if (loadingBarWidth >= 500){
			loadingBarWidth = 500;
			loadingDone = true;
		}
	}

	else{
		if (isKeyPressed(' ')){
			goToMainMenu = true;
			// Load menu 
			if (mainMenuScreen == -1){
				loadMenuAssets();
				loadCharacterSelectionAssets();
				loadArenaAssets();
			}
		}
	}
}

void loadingScreenText(){
	// If loading done, show text prompt
	if (loadingDone){
		if (blinkTextWhite) {
			iSetColor(255, 255, 255); // white
		}
		else {
			iSetColor(0, 0, 0); // black
		}
		iText(530, 150, "Press SPACE to continue", GLUT_BITMAP_HELVETICA_18);
	}
	else{
		iSetColor(255, 255, 255);
		iText(390, 140, "Loading...", GLUT_BITMAP_HELVETICA_18);
	}
}

void toggleBlinkColor() {
	blinkTextWhite = !blinkTextWhite;
}

void updateCharacters() {
	// Only advance frames if we’re on the gameplay screen
	if (currentScreen == 20){
		if(selectedCharacterIndexP1 == 2) captainAmericaP1.update();
		if(selectedCharacterIndexP2 == 2) captainAmericaP2.update();
		// ironMan.update();
	}
}

int main()
{
	// Initialize graphics window
	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Marvel Mayhem");

	//loading screen background image
	loadingScreen = iLoadImage("BG/loading.png");

	loadCaptainAmerica(captainAmericaP1);
	loadCaptainAmerica(captainAmericaP2);

	captainAmericaP1.moveX = 100;        // Player 1 starts on the left
	captainAmericaP1.facingRight = true; // Player 1 faces right

	captainAmericaP2.moveX = 800;         // Player 2 starts on the right  
	captainAmericaP2.facingRight = false; // Player 2 faces left

	iSetTimer(350, toggleBlinkColor); // 350 ms = 0.35 sec toggle

	iSetTimer(10, loadingBar);

	iSetTimer(25, fixedUpdate);

	iSetTimer(100, updateCharacters);

	iSetTimer(100, loadArenaAssets);
	
	iStart(); // Start the graphics engine

	return 0;
}







/*
void fixedUpdate() {

if (!goToMainMenu || currentScreen != 10) return;

static bool jumpInProgress = false;

bool wPressed = isKeyPressed('w');
bool moveRight = isKeyPressed('d');
bool moveLeft = isKeyPressed('a');

// ? Move left
if (moveLeft) {
captainAmerica.facingRight = false;
captainAmerica.moveX -= 5;
}

// ? Move right
if (moveRight) {
captainAmerica.facingRight = true;
captainAmerica.moveX += 5;
}

// Start jump if W is pressed and not already jumping
if (wPressed && !jumpInProgress) {
captainAmerica.setState(JUMP);
captainAmerica.currentFrame = 0;
jumpInProgress = true;
}

// Handle jump animation movement
if (jumpInProgress){
int f = captainAmerica.currentFrame;

// Y axis arc movement (fake)
if (f == 0) captainAmerica.moveY += 12;
else if (f == 1) captainAmerica.moveY += 8;
else if (f == 2) captainAmerica.moveY += 5;
else if (f == 3) captainAmerica.moveY -= 5;
else if (f == 4) captainAmerica.moveY -= 8;
else if (f == 5) captainAmerica.moveY -= 12;

// When jump ends
int maxJump = captainAmerica.facingRight ? captainAmerica.jumpCount_R : captainAmerica.jumpCount_L;
if (captainAmerica.currentFrame >= maxJump - 1) {
captainAmerica.moveY = captainAmerica.baseY; // go back to ground
jumpInProgress = false;
}
}
// If not jumping, pick proper state
if (!jumpInProgress && captainAmerica.characterState != ATTACK) {
if (moveRight || moveLeft) captainAmerica.setState(WALK);
else captainAmerica.setState(IDLE);
// Safety check — never below ground
if (captainAmerica.moveY < captainAmerica.baseY) {
captainAmerica.moveY = captainAmerica.baseY;
}
}

if (captainAmerica.characterState == ATTACK) {
int maxAtk = captainAmerica.facingRight ? captainAmerica.attackCount_R : captainAmerica.attackCount_L;

if (captainAmerica.currentFrame >= maxAtk - 1) {
if (isKeyPressed('f')) {
captainAmerica.currentFrame = 0; // loop attack
}
else {
captainAmerica.setState(IDLE); // go back to idle
}
}
}
else if (isKeyPressed('f')) {
captainAmerica.setState(ATTACK);
}
if (jumpInProgress && isKeyPressed('f')) {
captainAmerica.setState(ATTACK); // mid-air attack
}


}
*/
