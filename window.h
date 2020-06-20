
#ifndef CNGE_WINDOW
#define CNGE_WINDOW

#include <windows.h>
#include <GL/gl.h>

#include "input.h"
#include "types.h"

namespace CNGE {
	class Window {
	private:
		static HWND window;
		static HINSTANCE instance;
		static HDC deviceContext;
		static HGLRC glContext;
		static HPALETTE palette;

		static Input input;
		static bool shouldClose;
		
		static auto windowProc(HWND, UINT, WPARAM, LPARAM) -> LONG WINAPI;

		static auto createOpenGLWindow(const wchar_t*, i32, i32, i32, i32, i32, BYTE, DWORD) -> void;
		
	public:
		Window(const wchar_t*, i32, i32, i32);

		/* no copying the window */
		auto operator=(const Window&) -> void = delete;
		Window(const Window&) = delete;

		static auto setIcon(i32) -> void;

		[[nodiscard]] static auto getShouldClose() -> bool;
		[[nodiscard]] static auto getInput() -> Input const *;

		static auto close() -> void;
	};
}

#endif