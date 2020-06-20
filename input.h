
#ifndef CNGE_INPUT
#define CNGE_INPUT

#include "types.h"

namespace CNGE {
	class Input {
	private:
		static constexpr i32 NUM_BUTTONS = 3;
		static constexpr i32 NUM_KEYS = 0xff;
		
		static constexpr i32 BUTTON_RELEASED = 0;
		static constexpr i32 BUTTON_INITIAL = 1;
		static constexpr i32 BUTTON_PRESSED = 2;
		static constexpr i32 BUTTON_HELD = 3;

		static constexpr i32 BUTTON_LEFT = 0;
		static constexpr i32 BUTTON_MIDDLE = 1;
		static constexpr i32 BUTTON_RIGHT = 2;
		
		i32 mouseX, mouseY;
		i32 scroll;

		i32 buttons[NUM_BUTTONS];
		i32 keys[NUM_KEYS];

		i32 width, height;
		bool resized;
		
		auto update() -> void;
		
		friend class Window;

	public:
		Input();

		[[nodiscard]] auto getButtonPressed(i32) const -> bool;
		[[nodiscard]] auto getButtonDown(i32) const -> bool;

		[[nodiscard]] auto getKeyPressed(i32) const -> bool;
		[[nodiscard]] auto getKeyDown(i32) const -> bool;

		[[nodiscard]] auto getMouseX() const -> i32;
		[[nodiscard]] auto getMouseY() const -> i32;
		
		[[nodiscard]] auto getScroll() const -> i32;

		[[nodiscard]] auto getWidth() const -> i32;
		[[nodiscard]] auto getHeight() const -> i32;

		[[nodiscard]] auto getResized() const -> bool;
	};
}

#endif
