
#include <Windows.h>

#include "src/window.h"
#include "src/types.h"
#include "src/loop.h"

#include "resource.h"

auto WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int show) -> i32 APIENTRY {
	auto window = CNFW::Window(L"CNFW Test", 256, 256, MAIN_ICON);

	auto loop = CNFW::Loop(60);

	loop.begin([&window]() { return window.getShouldClose(); }, [&window](auto timing) {
		static auto input = window.getInput();

		window.poll();

		if (input->getResized()) {
			glViewport(0, 0, input->getWidth(), input->getHeight());

			/* render scene */
			glClear(GL_COLOR_BUFFER_BIT);
			glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2i(0, 1);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2i(-1, -1);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex2i(1, -1);
			glEnd();
			glFlush();

			window.swap();
		}

		input->update();
	});

	window.close();

	return 0;
}
