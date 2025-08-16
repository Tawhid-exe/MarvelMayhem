#ifndef MENU_HPP
#define MENU_HPP

#include <stdlib.h>
#include <stdio.h>
//#include "character.hpp"

#define BUTTON_COUNT 4
#define CHARACTER_COUNT 6
#define ARENA_COUNT 1
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// Main Menu Screen Value = -1
// Sub Menu Screen Value = 0
// Settings Screen = 1
// About Screen = 2
// 1v1 Character Selection Screen value = 10
// Arcade Mode Character Selection Screen value = 11
// 1v1 Arena Screen value = 20
// Arcade Arena Screen value = 30

int selectedCharacterIndexP1 = 2; //default // index for spawning character in areana
int selectedCharacterIndexP2 = 2; //default
// 1 for ironman
// 2 for cap
// 3 for thor
// 4 for thanos
// 5 for logan
// 6 for hulk

int currentScreen = -1;

// Main menu variables
int mainMenuScreen = -1;
int buttonImages[BUTTON_COUNT];
const char* buttonNames[BUTTON_COUNT] = { "Play", "Settings", "About", "Exit" };
int hoveredButtonIndex = -1;

//  Variables for the two options after clicking "Play"

int optionButtonImages[2];
int hoveredOptionButtonIndex = -1;
int subMenuBackground;

// Variables for Character Selection
int characterImages[CHARACTER_COUNT];
int characterSelectionBackground;
int selectedCharacterP1 = -1;
int selectedCharacterP2 = -1;
int selectionImages[2];

// Variables for Arena
int arenaImages[ARENA_COUNT];

// Back button variables
int backButtonImage;
bool backButtonHover = false;

struct Button {
	int x;
	int y;
	int width;
	int height;
};

Button buttons[BUTTON_COUNT];
Button backButton;
Button optionButtons[2];
Button characterButtonsP1[CHARACTER_COUNT]; // Player 1 buttons
Button characterButtonsP2[CHARACTER_COUNT]; // Player 2 buttons

// menu 
void showMenu() {
	if (currentScreen == -1) { // On the Main Menu
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, mainMenuScreen);

		// main menu buttons 
		for (int i = 0; i < BUTTON_COUNT; i++) {
			iShowImage(buttons[i].x, buttons[i].y, buttons[i].width, buttons[i].height, buttonImages[i]);
		}
		if (hoveredButtonIndex != -1) {
			int i = hoveredButtonIndex;
			double zoomFactor = 1.1;
			int newWidth = buttons[i].width * zoomFactor;
			int newHeight = buttons[i].height * zoomFactor;
			int newX = buttons[i].x - (newWidth - buttons[i].width) / 2;
			int newY = buttons[i].y - (newHeight - buttons[i].height) / 2;
			iShowImage(newX, newY, newWidth, newHeight, buttonImages[i]);
		}
	}
	else if (currentScreen == 0) { // Play Sub-Menu
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, subMenuBackground);
		iSetColor(253, 240, 213);
		iText(590, 680, "Select Mode", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(300, 580, "1 V 1", GLUT_BITMAP_HELVETICA_18);
		iText(920, 580, "Arcade", GLUT_BITMAP_HELVETICA_18);

		//two option buttons
		for (int i = 0; i < 2; i++) {
			iShowImage(optionButtons[i].x, optionButtons[i].y, optionButtons[i].width, optionButtons[i].height, optionButtonImages[i]);
		}

		//  hover effect for option buttons
		if (hoveredOptionButtonIndex != -1) {
			int i = hoveredOptionButtonIndex;
			double zoomFactor = 1.06;
			int newWidth = optionButtons[i].width * zoomFactor;
			int newHeight = optionButtons[i].height * zoomFactor;
			int newX = optionButtons[i].x - (newWidth - optionButtons[i].width) / 2;
			int newY = optionButtons[i].y - (newHeight - optionButtons[i].height) / 2;
			iShowImage(newX, newY, newWidth, newHeight, optionButtonImages[i]);
		}

		//  Back Button on this screen
		if (backButtonHover) {
			double zoomFactor = 1.1;
			int newWidth = backButton.width * zoomFactor;
			int newHeight = backButton.height * zoomFactor;
			int newX = backButton.x - (newWidth - backButton.width) / 2;
			int newY = backButton.y - (newHeight - backButton.height) / 2;
			iShowImage(newX, newY, newWidth, newHeight, backButtonImage);
		}
		else {
			iShowImage(backButton.x, backButton.y, backButton.width, backButton.height, backButtonImage);
		}
	}
	else if (currentScreen == 1 || currentScreen == 2) { 
		iSetColor(255, 255, 255);
		iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		iSetColor(0, 0, 0);
		//iText(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, buttonNames[currentScreen], GLUT_BITMAP_TIMES_ROMAN_24);

		// Back Button
		if (backButtonHover) {
			double zoomFactor = 1.1;
			int newWidth = backButton.width * zoomFactor;
			int newHeight = backButton.height * zoomFactor;
			int newX = backButton.x - (newWidth - backButton.width) / 2;
			int newY = backButton.y - (newHeight - backButton.height) / 2;
			iShowImage(newX, newY, newWidth, newHeight, backButtonImage);
		}
		else {
			iShowImage(backButton.x, backButton.y, backButton.width, backButton.height, backButtonImage);
		}
	}
	else if (currentScreen == 10 || currentScreen == 11) { // play options selection
		// Display which option was chosen
		if (currentScreen == 10) {
			iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, characterSelectionBackground);

			// Titles
			iSetColor(253, 240, 213);
			iText(155, SCREEN_HEIGHT - 70, "Player 1: Choose Your Character", GLUT_BITMAP_HELVETICA_18);
			iText(SCREEN_WIDTH - 395, SCREEN_HEIGHT - 70, "Player 2: Choose Your Character", GLUT_BITMAP_HELVETICA_18);

			// Player 1 Side (Left)
			for (int i = 0; i < CHARACTER_COUNT; i++) {
				iShowImage(characterButtonsP1[i].x, characterButtonsP1[i].y, characterButtonsP1[i].width, characterButtonsP1[i].height, characterImages[i]);
			}

			// Player 2 Side (Right)
			for (int i = 0; i < CHARACTER_COUNT; i++) {
				iShowImage(characterButtonsP2[i].x, characterButtonsP2[i].y, characterButtonsP2[i].width, characterButtonsP2[i].height, characterImages[i]);
			}

			// Show border around selected characters
			if (selectedCharacterP1 != -1) {
				iShowImage(characterButtonsP1[selectedCharacterP1].x - 30, characterButtonsP1[selectedCharacterP1].y - 30, 160, 160, selectionImages[0]);
			}
			if (selectedCharacterP2 != -1) {
				iShowImage(characterButtonsP2[selectedCharacterP2].x - 20, characterButtonsP2[selectedCharacterP2].y - 20, 140, 140, selectionImages[1]);
			}
			// Start Button on Character Selection
			if (selectedCharacterP1 != -1 && selectedCharacterP2 != -1) {
				iShowImage(520, 50, 250, 100, buttonImages[0]);
			}

			if (hoveredButtonIndex != -1) {
				int i = hoveredButtonIndex;
				double zoomFactor = 1.1;
				int newWidth = 250 * zoomFactor;
				int newHeight = 100 * zoomFactor;
				int newX = 520 - (newWidth - 250) / 2;
				int newY = 50 - (newHeight - 100) / 2;
				iShowImage(newX, newY, newWidth, newHeight, buttonImages[0]);
			}
		}
		else iText(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, "Option 2 Screen", GLUT_BITMAP_TIMES_ROMAN_24);
		

		// Back Button
		if (backButtonHover) {
			double zoomFactor = 1.1;
			int newWidth = backButton.width * zoomFactor;
			int newHeight = backButton.height * zoomFactor;
			int newX = backButton.x - (newWidth - backButton.width) / 2;
			int newY = backButton.y - (newHeight - backButton.height) / 2;
			iShowImage(newX, newY, newWidth, newHeight, backButtonImage);
		}
		else {
			iShowImage(backButton.x, backButton.y, backButton.width, backButton.height, backButtonImage);
		}
	}
	else if (currentScreen == 30) {
		//iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, arenaImages[0]);
	}
}

void handleMenuClick(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (currentScreen == -1) { // On the main menu
			for (int i = 0; i < BUTTON_COUNT; i++) {
				if (mx >= buttons[i].x && mx <= buttons[i].x + buttons[i].width &&
					my >= buttons[i].y && my <= buttons[i].y + buttons[i].height) {
					if (i == 3) { exit(0); } // Exit button
					currentScreen = i; // Sets screen to 0 (Play), 1 (Settings), or 2 (About)
					break;
				}
			}
		}
		else if (currentScreen == 0) { // On the Play Sub-Menu
			// Check for clicks on the two option buttons
			for (int i = 0; i < 2; i++) {
				if (mx >= optionButtons[i].x && mx <= optionButtons[i].x + optionButtons[i].width &&
					my >= optionButtons[i].y && my <= optionButtons[i].y + optionButtons[i].height) {
					currentScreen = 10 + i; // Set screen to 10 or 11
					return; // Exit function after handling click
				}
			}
			// Check for click on the back button
			if (mx >= backButton.x && mx <= backButton.x + backButton.width &&
				my >= backButton.y && my <= backButton.y + backButton.height) {
				currentScreen = -1; // Go back to the main menu
			}
		}
		else if (currentScreen == 1 || currentScreen == 2) { // On Settings or About

			// Check for back button click
			if (mx >= backButton.x && mx <= backButton.x + backButton.width &&
				my >= backButton.y && my <= backButton.y + backButton.height) {
				currentScreen = -1; // Go back to the main menu
			}
		}
		else if (currentScreen == 10 || currentScreen == 11) { // On final placeholder screens
			// Check for back button click
			if (mx >= backButton.x && mx <= backButton.x + backButton.width &&
				my >= backButton.y && my <= backButton.y + backButton.height) {
				currentScreen = 0; // Go back to the Play Sub-Menu
			}
			// 1v1 character selection
			if (currentScreen == 10) {
				for (int i = 0; i < CHARACTER_COUNT; i++) {
					// Player 1 selection
					if (mx >= characterButtonsP1[i].x && mx <= characterButtonsP1[i].x + characterButtonsP1[i].width &&
						my >= characterButtonsP1[i].y && my <= characterButtonsP1[i].y + characterButtonsP1[i].height) {
						selectedCharacterP1 = i;
						selectedCharacterIndexP1 = i+1;
						//printf(" %d", selectedCharacterIndexP1);
					}
					// Player 2 selection
					if (mx >= characterButtonsP2[i].x && mx <= characterButtonsP2[i].x + characterButtonsP2[i].width &&
						my >= characterButtonsP2[i].y && my <= characterButtonsP2[i].y + characterButtonsP2[i].height) {
						selectedCharacterP2 = i;
						selectedCharacterIndexP2 = i + 1;
						//printf(" %d", selectedCharacterIndexP2);
					}
					// Entering Arena Screen
					if (selectedCharacterP1 != -1 && selectedCharacterP2 != -1) {
						if (mx >= 520 && mx <= 520 + 250 && my >= 50 && my <= 50 + 100) {
							currentScreen = 20;
						}
					}
				}
			}
		}
	}
}

void handleHoverAnimation(int mx, int my){
	// By default, assume nothing is hovered
	hoveredButtonIndex = -1;
	hoveredOptionButtonIndex = -1;
	backButtonHover = false;

	if (currentScreen == -1) { // On the main menu
		for (int i = 0; i < BUTTON_COUNT; i++) {
			if (mx >= buttons[i].x && mx <= buttons[i].x + buttons[i].width &&
				my >= buttons[i].y && my <= buttons[i].y + buttons[i].height) {
				hoveredButtonIndex = i;
				break;
			}
		}
	}
	else if (currentScreen == 0) { // On the Play Sub-Menu
		// hover for the two option buttons
		for (int i = 0; i < 2; i++) {
			if (mx >= optionButtons[i].x && mx <= optionButtons[i].x + optionButtons[i].width &&
				my >= optionButtons[i].y && my <= optionButtons[i].y + optionButtons[i].height) {
				hoveredOptionButtonIndex = i;
				return; // Exit after finding a hover
			}
		}
		//hover for the back button
		if (mx >= backButton.x && mx <= backButton.x + backButton.width &&
			my >= backButton.y && my <= backButton.y + backButton.height) {
			backButtonHover = true;
		}
	}
	else if (currentScreen == 10) { // On Character Selection
		// Back button hover
		if (mx >= backButton.x && mx <= backButton.x + backButton.width &&
			my >= backButton.y && my <= backButton.y + backButton.height) {
			backButtonHover = true;
		}

		// Start button hover 
		if (selectedCharacterP1 != -1 && selectedCharacterP2 != -1) {
			if (mx >= 520 && mx <= 520 + 250 && my >= 50 && my <= 50 + 100) {
				hoveredButtonIndex = 0;
			}
		}
	}
	else { // On any other sub-screen (Settings, About, Option 1, Option 2)
		// back button hover
		if (mx >= backButton.x && mx <= backButton.x + backButton.width &&
			my >= backButton.y && my <= backButton.y + backButton.height) {
			backButtonHover = true;
		}
	}
}

// Load all images and set button positions
void loadMenuAssets() {
	mainMenuScreen = iLoadImage("BG/main.png");
	subMenuBackground = iLoadImage("BG/subMenu.jpg");
	characterSelectionBackground = iLoadImage("BG/playerSelectionBg.png");

	// Load Back button image and define its properties
	backButtonImage = iLoadImage("UiElements/backButton.png");
	backButton.x = 50;
	backButton.y = 50;
	backButton.width = 195;
	backButton.height = 75;

	optionButtonImages[0] = iLoadImage("BG/modeSelection1.png");
	optionButtonImages[1] = iLoadImage("BG/modeSelection2.jpg");

	// two option buttons
	int optWidth = 600;
	int optHeight = 400;
	int spacing = 100;
	int totalWidth = (optWidth * 2) + spacing;
	int startX = (SCREEN_WIDTH - totalWidth) / 2;

	optionButtons[0].x = startX;
	optionButtons[0].y = (SCREEN_HEIGHT - optHeight) / 2;
	optionButtons[0].width = optWidth;
	optionButtons[0].height = optHeight;

	optionButtons[1].x = startX + optWidth + spacing;
	optionButtons[1].y = (SCREEN_HEIGHT - optHeight) / 2;
	optionButtons[1].width = optWidth;
	optionButtons[1].height = optHeight;

	// main menu buttons
	char imagePath[100];
	int startY = 525;
	for (int i = 0; i < BUTTON_COUNT; i++) {
		sprintf_s(imagePath, sizeof(imagePath), "UiElements/button%d.png", i + 1);
		buttonImages[i] = iLoadImage(imagePath);

		buttons[i].x = 100;
		buttons[i].y = startY - i * 140;
		buttons[i].width = 300;
		buttons[i].height = 117;
	}

}
void loadCharacterSelectionAssets() {
	// Load character images
	for (int i = 0; i < CHARACTER_COUNT; i++) {
		char imagePath[100];
		sprintf_s(imagePath, sizeof(imagePath), "UiElements/Characters/char%d.jpg", i + 1);
		characterImages[i] = iLoadImage(imagePath);
	}
	// Load selection images
	for (int i = 0; i < 2; i++) {
		char imagePath[100];
		sprintf_s(imagePath, sizeof(imagePath), "UiElements/characterSelection%d.png", i + 1);
		selectionImages[i] = iLoadImage(imagePath);
	}

	// Position settings of characters
	int charWidth = 100, charHeight = 100;
	int spacingX = 80, spacingY = 50;
	int cols = 2, rows = 3;

	// total width and height of the grid
	int totalWidth = 250;
	int totalHeight = 400;

	// Starting positions to center the grid vertically
	int startY = (SCREEN_HEIGHT - totalHeight) / 2;
	int startX_P1 = 150; // Player 1's grid starts 150px from the left
	int startX_P2 = SCREEN_WIDTH - 150 - totalWidth; // Player 2's grid starts 150px from right

	for (int i = 0; i < CHARACTER_COUNT; i++) {
		int row = i / cols;
		int col = i % cols;

		// Player 1 (Left Side)
		characterButtonsP1[i].x = startX_P1 + col * (charWidth + spacingX);
		characterButtonsP1[i].y = startY + (rows - 1 - row) * (charHeight + spacingY);
		characterButtonsP1[i].width = charWidth;
		characterButtonsP1[i].height = charHeight;

		// Player 2 (Right Side)
		characterButtonsP2[i].x = startX_P2 + col * (charWidth + spacingX);
		characterButtonsP2[i].y = characterButtonsP1[i].y; // Align with P1
		characterButtonsP2[i].width = charWidth;
		characterButtonsP2[i].height = charHeight;
	}

}

void showArenaImages(){
	iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, arenaImages[0]);
}


void loadArenaAssets(){
	// Load Arena Images
	if (currentScreen == 20){
		arenaImages[0] = iLoadImage("BG/arena1.jpg");
	}
}

#endif 
