#include "Button.h"

namespace ge {

	Button::Button(TextInRect textInRect, std::unique_ptr<Command> commandToExecute, Color offSetOnHovering)
		:textInRect{ std::move(textInRect) }, commandToExecute{ std::move(commandToExecute) }, offSetOnHovering{ offSetOnHovering }
	{}


	bool Button::checkIfHovering(const Position<>& mousePosition) {
		if (!isHovering && pointIsIn(mousePosition)) {
			onHovering();
			isHovering = true;
			return true;
		}
		else if (isHovering && !pointIsIn(mousePosition)) {
			unHovering();
			isHovering = false;
		}
		return false;
	}

	bool Button::pointIsIn(const Position<>& point) const {
		return point.x > getPosition().x && point.x < getPosition().x + textInRect.getW() && point.y > getPosition().y && point.y < getPosition().y + textInRect.getH();
	}

	void Button::onHovering() {
		textInRect.changeColor(Color{ textInRect.getColor().red + offSetOnHovering.red, textInRect.getColor().green + offSetOnHovering.green,
			textInRect.getColor().blue + offSetOnHovering.blue, textInRect.getColor().alpha + offSetOnHovering.alpha });
	}

	void Button::unHovering() {
		textInRect.changeColor(Color{ textInRect.getColor().red - offSetOnHovering.red, textInRect.getColor().green - offSetOnHovering.green,
			textInRect.getColor().blue - offSetOnHovering.blue, textInRect.getColor().alpha - offSetOnHovering.alpha });
	}
}
