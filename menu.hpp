#ifndef MENU_HPP
#define MENU_HPP

#include <stdlib.h>
#include <stdio.h>
//#include "character.hpp"

#define BUTTON_COUNT 4
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

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

		//two option buttons
		for (int i = 0; i < 2; i++) {
			iShowImage(optionButtons[i].x, optionButtons[i].y, optionButtons[i].width, optionButtons[i].height, optionButtonImages[i]);
		}

		//  hover effect for option buttons
		if (hoveredOptionButtonIndex != -1) {
			int i = hoveredOptionButtonIndex;
			double zoomFactor = 1.1;
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
		iSetColor(255, 255, 255);
		iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		iSetColor(0, 0, 0);

		// Display which option was chosen
		if (currentScreen == 10) iText(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, "Option 1 Screen", GLUT_BITMAP_TIMES_ROMAN_24);
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
	subMenuBackground = iLoadImage("BG/mian.png");

	// Load Back button image and define its properties
	backButtonImage = iLoadImage("UiElements/backButton.png");
	backButton.x = 50;
	backButton.y = 50;
	backButton.width = 195;
	backButton.height = 75;

	optionButtonImages[0] = iLoadImage("UiElements/buttons.png");
	optionButtonImages[1] = iLoadImage("UiElements/buttons.png");

	// two option buttons
	int optWidth = 250;
	int optHeight = 250;
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

#endif 
