/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2025 the NvDialog contributors
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

#include "nvdialog_cocoa.h"
#include <stdlib.h>

NvdInputBox *nvd_input_box_cocoa(const char *title, const char *message) {
    NvdInputBox *box = malloc(sizeof(NvdInputBox));
    NVD_RETURN_IF_NULL(box);

    box->title = nvd_string_new(title);
    box->content = message ? nvd_string_new(message) : NULL;
    box->user_input = NULL;

    NSAlert *alert = [[NSAlert alloc] init];
    alert.messageText = @(title);
    alert.informativeText = @(message ? message : "");
    alert.alertStyle = NSAlertStyleInformational;

    NSTextField *inputField = [[NSTextField alloc] initWithFrame:NSMakeRect(0,0,200,24)];
    [inputField setStringValue:@""];
    [alert setAccessoryView:inputField];

    [alert addButtonWithTitle:@"OK"];
    [alert addButtonWithTitle:@"Cancel"];

    box->window_handle = alert;
    box->title   = nvd_string_new(title);

    return box;
}


void nvd_show_input_box_cocoa(NvdInputBox *box) {
    NSAlert *alert = box->window_handle;
    NSModalResponse resp = [alert runModal];

    if (resp == NSAlertFirstButtonReturn) {
        NSTextField *field = (NSTextField *)[alert accessoryView];
        box->user_input = nvd_string_new([[field stringValue] UTF8String]);
    }
    else box->user_input = NULL;

    [alert orderOut:nil];
}

NvdDynamicString *nvd_input_box_get_string_cocoa(NvdInputBox *box) {
    return box->user_input;
}