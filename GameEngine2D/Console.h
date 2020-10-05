#pragma once
#include "Rectangle.h"
#include "InputBar.h"
#include "TextArea.h"

namespace ge {
#define CONSOLE_LOG(X) ge::Console::getInstance()->log(X)
#define CONSOLE_LOG_ERROR(X) ge::Console::getInstance()->log(X, ge::Color{255, 100, 100})

	class Console
	{
	private:
		//Static attribute that make the console a singleton
		static Console* instance;

		//The size of the console
		Rectangle coordinate;
		std::unique_ptr<TextInput> textInput;
		Color backgroundColor;
		Color borderColor;
		int borderSize;
		int textHeight;
		int margin;

		bool opened{ false };

		//The input bar at the bottom of the console
		InputBar inputBar;
		//The text area in the console
		TextArea textArea;

		//Used when the user press enter
		void pushText();

		//Constructor
		Console(Rectangle coordinate, Color backgroundColor, Color borderColor, int borderSize, int textHeight, int margin);
	public:
		static void init(Rectangle coordinate, Color backgroundColor = Color{ 100, 100, 100 }, Color borderColor = Color{ 200, 200, 200 },
			int borderSize = 3, int textHeight = 15, int margin = 5);

		static Console* getInstance() { return instance; }

		static void quit();

		//Refresh the console
		void update(SDL_Renderer* renderer);

		//Render the console on the screen
		void render(SDL_Renderer* renderer) const;

		//Get the command that the user typed in the console
		//TextToCommand getCommand() const { return TextToCommand{ getInputText() }; }

		//Log a text in the console
		void log(const std::string& text, const Color& color = Color{ 255, 255, 255 }) { textArea.addText(text, color); }

		//Write a text in the input bar
		void write(const std::string& text) { inputBar.write(text); }

		//Delete the last character of the input bar
		void popText() { inputBar.popText(); }

		//Used to treat the input text as a command
		void pushCommand();

		//Open or close the console
		void toggle();

		//Close the console
		void close();

		//Open the console
		void open();

		//Is the console open
		bool isOpened() const { return opened; }

		//Vertical scroll in the console
		void verticalScroll(int amount) { textArea.verticalScroll(amount); }
	};

}
