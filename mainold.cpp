/* An example of the minimal Win32 & OpenGL program.  It only works in
   16 bit color modes or higher (since it doesn't create a
   palette). */

#include <cstdio>

#include <windows.h>			/* must include this before GL/gl.h */
		
#include <GL/glew.h> /* OpenGL header file */
#include <GL/gl.h>
#include <gl/wglext.h>

void display()
{
    /* rotate a triangle around */
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
}


LONG WINAPI WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static PAINTSTRUCT ps;

    switch (uMsg) {
    case WM_PAINT:
        display();
        BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        return 0;

    case WM_SIZE:
        glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
        PostMessage(hWnd, WM_PAINT, 0, 0);
        return 0;

    case WM_CHAR:
        switch (wParam) {
        case 27:			/* ESC key */
            PostQuitMessage(0);
            break;
        }
        return 0;

    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

HWND CreateOpenGLWindow(const wchar_t* title, int x, int y, int width, int height, BYTE type, DWORD flags) {
    int         pf;
    HDC         hDC;
    HWND        hWnd;
    WNDCLASS    wc;
    PIXELFORMATDESCRIPTOR pfd;
    static HINSTANCE hInstance = 0;

    /* only register the window class once - use hInstance as a flag. */
    if (!hInstance) {
        hInstance = GetModuleHandle(nullptr);
        wc.style = CS_OWNDC;
        wc.lpfnWndProc = (WNDPROC)WindowProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = hInstance;
        wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hbrBackground = nullptr;
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = L"OpenGL";
    	
        if (!RegisterClass(&wc)) {
            MessageBox(nullptr, L"RegisterClass() failed:  "
                "Cannot register window class.", L"Error", MB_OK);
            return nullptr;
        }
    }

    hWnd = CreateWindow(L"OpenGL", title, WS_OVERLAPPEDWINDOW |
        WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
        x, y, width, height, nullptr, nullptr, hInstance, nullptr);

    if (hWnd == nullptr) {
        MessageBox(nullptr, L"CreateWindow() failed:  Cannot create a window.",
            L"Error", MB_OK);
        return nullptr;
    }

    hDC = GetDC(hWnd);

    /* there is no guarantee that the contents of the stack that become
       the pfd are zeroed, therefore _make sure_ to clear these bits. */
    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | flags;
    pfd.iPixelType = type;
    pfd.cColorBits = 32;

    pf = ChoosePixelFormat(hDC, &pfd);
    if (pf == 0) {
        MessageBox(nullptr, L"ChoosePixelFormat() failed:  "
            "Cannot find a suitable pixel format.", L"Error", MB_OK);
        return nullptr;
    }

    if (SetPixelFormat(hDC, pf, &pfd) == FALSE) {
        MessageBox(nullptr, L"SetPixelFormat() failed:  "
            "Cannot set format specified.", L"Error", MB_OK);
        return 0;
    }

    DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

    ReleaseDC(hWnd, hDC);

    return hWnd;
}

int APIENTRY WinMain(HINSTANCE hCurrentInst, HINSTANCE hPreviousInst, LPSTR lpszCmdLine, int nCmdShow) {
    HDC hDC;				/* device context */
    HGLRC hRC;				/* opengl context */
    HWND  hWnd;				/* window */
    MSG   msg;				/* message */

    hWnd = CreateOpenGLWindow(L"minimal", 0, 0, 256, 256, PFD_TYPE_RGBA, 0);
    if (hWnd == nullptr)
        exit(1);

    hDC = GetDC(hWnd);
    hRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hRC);
    //wglSwapIntervalEXT(1);
    ShowWindow(hWnd, nCmdShow);

    while (GetMessage(&msg, hWnd, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    wglMakeCurrent(nullptr, nullptr);
    ReleaseDC(hWnd, hDC);
    wglDeleteContext(hRC);
    DestroyWindow(hWnd);

    return msg.wParam;
}
