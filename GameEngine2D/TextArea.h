#pragma once
#include <vector>
#include <queue>
#include <memory>

#include "Text.h"
#include "Camera.h"

class TextArea
{
private:
	//Where the text is stocked
	std::vector<std::unique_ptr<Text>> textList;
	Rectangle position;
	std::queue<std::string> textToRender;
	std::queue<Color> textColor;
	Font font;
	int scrollMultiplier;

	//The camera is used to define what text will be seen in the text area
	Camera camera;

	//Add all the text stocked this frame to the text area
	void addPendingText(SDL_Renderer* renderer);

public:
	//Constructor
	TextArea(const Rectangle& position, int textHeight, const std::string& fontFileName = "mainFont.ttf", const int scrollMultiplier = 25);

	//Add text in form of the Text object
	void addText(std::unique_ptr<Text> text) { textList.push_back(std::move(text)); }

	//Add text with an std::string
	void addText(const std::string& text, const Color& color = Color{ 0, 0, 0 }) { textToRender.push(text); textColor.push(color); }

	//Refresh the textArea, process the newly added text if needed
	void update(SDL_Renderer* renderer);

	//Render the textArea
	void render(SDL_Renderer* renderer) const;

	//Scroll in the text area
	void verticalScroll(int amount);
};

