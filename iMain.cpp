#include "iGraphics.h"
#include "menu.hpp"
#include "character.hpp"
#include "pause.hpp"

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
		iShowImage(0, 10, SCREEN_WIDTH, SCREEN_HEIGHT, loadingScreen);

		// Loading bar frame and fill
		iSetColor(255, 60, 60);
		iRectangle(390, 35, 500, 25);
		iFilledRectangle(390, 35, loadingBarWidth, 25);
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

				captainAmericaP2.draw();
			}

			// paused button
			iShowImage(pauseButton.x, pauseButton.y, pauseButton.width, pauseButton.height, pauseButtonImage);

			// If the game is paused, show the pause menu
			if (currentGameState == PAUSED) {
				showPauseMenu();
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
		// If in game and paused, handle pause menu hover
		if (currentScreen == 20 && currentGameState == PAUSED) {
			handlePauseHoverAnimation(mx, my);
		}
		else {
			// Handle main menu hover Animation
			handleHoverAnimation(mx, my);
		}
	}
}

void iMouse(int button, int state, int mx, int my)
{
	if (goToMainMenu) {
		if (currentScreen == 20) { // Clicks inside the arena screen
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				if (currentGameState == PAUSED) {
					// If paused, check for clicks on the pause menu
					int clickedButtonIndex = handlePauseMenuClick(mx, my);
					if (clickedButtonIndex == 0) { // Resume
						currentGameState = PLAYING;
					}
					else if (clickedButtonIndex == 1) { // Restart
						resetCharacters(captainAmericaP1, captainAmericaP2);
						currentGameState = PLAYING;
					}
					else if (clickedButtonIndex == 2) { // Character Selection
						resetCharacters(captainAmericaP1, captainAmericaP2);
						currentScreen = 10; // Go back to character selection
						currentGameState = PLAYING; // Reset state for next time
					}
				}
				else {
					// If playing, check for clicks on the main pause button
					if (mx >= pauseButton.x && mx <= pauseButton.x + pauseButton.width &&
						my >= pauseButton.y && my <= pauseButton.y + pauseButton.height) {
						currentGameState = PAUSED;
					}
				}
			}
		}
		else {
			// Handle menu clicks only after the loading screen
			handleMenuClick(button, state, mx, my);
		}
	}
}

// This function runs at a fixed interval
// Special Keys:
// GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
// GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT

void fixedUpdate() {
	if (!goToMainMenu || currentScreen != 20 || currentGameState == PAUSED) return;

	// Player 1 controls (WASD + FEQ)
	handleInputMovement(captainAmericaP1, isKeyPressed('d'), isKeyPressed('a'));
	handleDefaultState(captainAmericaP1, isKeyPressed('d'), isKeyPressed('a'));
	handleJump(captainAmericaP1, isKeyPressed('w'));
	handleAttack(captainAmericaP1, isKeyPressed('f'));
	

	// Player 2 controls (Arrow keys + )
	handleInputMovement(captainAmericaP2, isSpecialKeyPressed(GLUT_KEY_RIGHT), isSpecialKeyPressed(GLUT_KEY_LEFT));
	handleDefaultState(captainAmericaP2, isSpecialKeyPressed(GLUT_KEY_RIGHT), isSpecialKeyPressed(GLUT_KEY_LEFT));
	handleJump(captainAmericaP2, isSpecialKeyPressed(GLUT_KEY_UP));
	handleAttack(captainAmericaP2, isSpecialKeyPressed(GLUT_KEY_DOWN));
	
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
				loadCharacterSelectionAssetsForArcade();
				loadArenaAssets();
				loadPauseAssets();
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
		iText(530, 80, "Press SPACE to continue", GLUT_BITMAP_HELVETICA_18);
	}
	else{
		iSetColor(255, 255, 255);
		iText(390, 70, "Loading...", GLUT_BITMAP_HELVETICA_18);
	}
}

void toggleBlinkColor() {
	blinkTextWhite = !blinkTextWhite;
}

void updateCharacters() {
	// Only update character animations if the game is playing
	if (currentScreen == 20 && currentGameState == PLAYING){
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
	loadingScreen = iLoadImage("BG/loading3.png");

	loadCaptainAmerica(captainAmericaP1);
	loadCaptainAmerica(captainAmericaP2);

	captainAmericaP1.moveX = 200;        // Player 1 starts on the left
	captainAmericaP1.facingRight = true; // Player 1 faces right

	captainAmericaP2.moveX = 980;         // Player 2 starts on the right  
	captainAmericaP2.facingRight = false; // Player 2 faces left

	iSetTimer(350, toggleBlinkColor); // 350 ms = 0.35 sec toggle

	iSetTimer(10, loadingBar);

	iSetTimer(25, fixedUpdate);

	iSetTimer(100, updateCharacters);

	iSetTimer(100, loadArenaAssets);
	
	iStart(); // Start the graphics engine

	return 0;
}
