#pragma once
#include <memory>

#include "TextInRect.h"
#include "Command.h"

namespace ge {
	class Button
	{
	private:
		TextInRect textInRect;
		Color offSetOnHovering;
		bool isHovering{ false };
		std::unique_ptr<Command> commandToExecute;
	public:
		//Constructor
		Button(TextInRect textInRect, std::unique_ptr<Command> commandToExecute, Color offSetOnHovering = Color{ 10, 10, 10 });

		void changeCommand(std::unique_ptr<Command> newCommandToExecute) { commandToExecute = std::move(newCommandToExecute); }

		//Take the mouse position and check and apply effect and return true if the mouse is hovering
		bool checkIfHovering(const Vector2<>& mousePosition);

		//Apply effect of the mouse overing
		void onHovering();

		//Cancel the hovering effect
		void unHovering();

		//On click, execute the stocked command
		void onClick() { commandToExecute->execute(std::vector<float>{}); }

		//Get the button position
		const Vector2<>& getPosition() const { return textInRect.getPosition(); }

		//Is a point in the button
		bool pointIsIn(const Vector2<>& point) const;
	};
}

