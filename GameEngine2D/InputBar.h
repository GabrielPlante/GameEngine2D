#pragma once
#include <memory>

#include "TextInRect.h"
#include "TextInput.h"
class InputBar
{
private:
	//If true, the inputBar will render the content of inputText in graphicText during the rendering of the frame
	bool needRendering = false;

	//The input text as a string
	std::string inputText;

	Font font;

	//The actual texture rendered
	std::unique_ptr<Text> graphicText;

	//Those are needed to recreate the texture each time a character is typed
	RenderableRectangle graphicRect;

	Position<> position;

	Color textColor;

	std::string fontFileName;

	bool opened = false;

	//To tackle the "open letter input" issue
	bool openingFrame = false;

	//Used to start and stop the SDL input
	std::unique_ptr<TextInput> textInput;

	//Render the text introduced that frame
	void renderPendingText(SDL_Renderer* renderer);

public:
	//Constructor
	InputBar(RenderableRectangle graphicRect, Position<> position, Color textColor = Color{ 0, 0, 0 }, const std::string& fontFileName = "mainFont.ttf");

	//Add text at the end of the input bar
	void write(const std::string& text);

	//Delete the content of the inputBar and replace it
	void setText(const std::string& text);

	//Pop one character of the inputBar, if there is one
	void popText();

	//Open the inputBar and start the SDL text input
	void open();

	//Close the inputBar and stop the SDL text input
	void close();

	//Render the inputBar, process the new input text if needed
	void render(SDL_Renderer* renderer);

	//Is the input bar opened
	bool isOpened() const { return opened; }

	//Does the input bar need rendering to render new letter in it
	bool doesNeedRendering() const { return needRendering; }

	//Get the text in the input bar
	const std::string& getInputText() const { return inputText; }

	//Clear the text and return what was in the inputBar
	std::unique_ptr<Text> clear();
};

