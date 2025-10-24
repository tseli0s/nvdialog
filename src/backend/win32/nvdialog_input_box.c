/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2025 Aggelos Tselios
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <stdlib.h>
#include <windows.h>

#include "nvdialog_core.h"
#include "nvdialog_string.h"
#include "nvdialog_win32.h"

#define IDC_EDIT 101
#define IDC_OK 102
#define IDC_CANCEL 103

/*
 * It'd be really nice if Windows just had something like Gtk where I can add
 * children to my UI instead of creating a bunch of widgets. Or at least a
 * proper input dialog right into WinAPI.

 * Also yes, this WILL look horribly outdated in modern Windows. Again, not my fault guys,
 * I'm doing my best.
 */
static LRESULT CALLBACK nvd_input_proc(HWND hwnd, UINT msg, WPARAM wParam,
				       LPARAM lParam) {
	NvdInputBox *box = (NvdInputBox *)GetWindowLongPtr(hwnd, GWLP_USERDATA);

	switch (msg) {
		case WM_CREATE: {
			CREATESTRUCT *cs = (CREATESTRUCT *)lParam;
			box = (NvdInputBox *)cs->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)box);

			CreateWindow("STATIC", NVD_CSTR(box->content),
				     WS_CHILD | WS_VISIBLE, 10, 10, 260, 75,
				     hwnd, NULL, NULL, NULL);

			CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",
				       WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
				       10, 40, 260, 20, hwnd, (HMENU)IDC_EDIT,
				       NULL, NULL);

			CreateWindow("BUTTON", "OK",
				     WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     80, 80, 70, 25, hwnd, (HMENU)IDC_OK, NULL,
				     NULL);

			CreateWindow("BUTTON", "Cancel", WS_CHILD | WS_VISIBLE,
				     160, 80, 70, 25, hwnd, (HMENU)IDC_CANCEL,
				     NULL, NULL);
		} break;

		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case IDC_OK: {
					char buf[256];
					GetDlgItemText(hwnd, IDC_EDIT, buf,
						       sizeof(buf));
					box->user_input = nvd_string_new(buf);
					DestroyWindow(hwnd);
				} break;
				case IDC_CANCEL:
					DestroyWindow(hwnd);
					break;
			}
			break;

		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

NvdInputBox *nvd_input_box_win32(const char *title, const char *message) {
	NvdInputBox *obj = malloc(sizeof(NvdInputBox));
	const char *default_msg = "Enter your text below...";
	obj->title = nvd_string_new(title);
	if (!message)
		obj->content = nvd_string_new(default_msg);
	else
		obj->content = nvd_string_new(message);

	obj->window_handle = NULL;
	obj->user_input = NULL;

	return obj;
}

void nvd_show_input_box_win32(NvdInputBox *box) {
	WNDCLASS wc = {0};
	/* Also, to continue with my rant, the naming could've been a little
	 * better. Like, spare my poor eyes a little... */
	wc.lpfnWndProc = nvd_input_proc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = "NvdInputBoxClass";
	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(0, "NvdInputBoxClass", NVD_CSTR(box->title),
				   WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
				   CW_USEDEFAULT, CW_USEDEFAULT, 300, 150, nvd_get_parent(),
				   NULL, wc.hInstance, box);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	MSG msg;
	while (IsWindow(hwnd) && GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	/* Delete the title string after showing the input box.
	 * We already call reusing the same dialog twice undefined behaviour, so we are technically
	 * within our limits to do so. Without this, nvd_free_object() actually creates a memory leak.
	 */
	nvd_delete_string(box->title);
}

NvdDynamicString *nvd_input_box_get_string_win32(NvdInputBox *box) {
	return box->user_input;
}
