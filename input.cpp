
#include "input.h"

namespace CNGE {
	Input::Input() : mouseX(),
		mouseY(), scroll(),
		buttons(), keys(),
		width(), height(), resized() {}

	auto Input::update() -> void {
		resized = false;

		for (auto& key : keys)
			if (key == BUTTON_INITIAL || key == BUTTON_PRESSED)
				++key;

		for (auto& button : buttons)
			if (button == BUTTON_INITIAL || button == BUTTON_PRESSED)
				++button;
	}
	
	auto Input::getButtonPressed(const i32 button) const -> bool {
		return buttons[button] == BUTTON_PRESSED;
	}
	
	auto Input::getButtonDown(const i32 button) const -> bool {
		return buttons[button] == BUTTON_HELD || buttons[button] == BUTTON_PRESSED;
	}
	
	auto Input::getKeyPressed(const i32 keyCode) const -> bool {
		return keys[keyCode] == BUTTON_PRESSED;
	}
	
	auto Input::getKeyDown(const i32 keyCode) const -> bool {
		return keys[keyCode] == BUTTON_HELD || keys[keyCode] == BUTTON_PRESSED;
	}
	
	auto Input::getMouseX() const -> i32 {
		return mouseX;
	}
	
	auto Input::getMouseY() const -> i32 {
		return mouseY;
	}
	
	auto Input::getScroll() const -> i32 {
		return scroll;
	}
	
	auto Input::getWidth() const -> i32 {
		return width;
	}
	
	auto Input::getHeight() const -> i32 {
		return height;
	}
	
	auto Input::getResized() const -> bool {
		return resized;
	}

}
