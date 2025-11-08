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

#include "nvdialog.h"
#include "nvdialog_cocoa.h"

#include <AppKit/AppKit.h>
#include <stdbool.h>

#include "../../nvdialog_assert.h"

NvdQuestionBox *nvd_question_cocoa(const char *title, const char *question, NvdQuestionButton buttons)
{
	NvdQuestionBox *box = nvd_malloc(sizeof(struct _NvdQuestionBox));
	box->title = title;
	box->contents = question;
	box->buttons = buttons;
	box->reply = 0;

	NSAlert *dlg = box->window_handle = [[NSAlert alloc] init];
	dlg.messageText = [NSString stringWithUTF8String:title];
	dlg.informativeText = [NSString stringWithUTF8String:question];


	//added buttons are in reverse
	switch (buttons) {
        	case NVD_YES_NO_CANCEL:
			[dlg addButtonWithTitle: [NSString stringWithUTF8String:"Cancel"]];
        	case NVD_YES_NO:
			[dlg addButtonWithTitle: [NSString stringWithUTF8String:"No"]];
			[dlg addButtonWithTitle: [NSString stringWithUTF8String:"Yes"]];
			break;
		
        	case NVD_YES_CANCEL:
			[dlg addButtonWithTitle: [NSString stringWithUTF8String:"Cancel"]];
			[dlg addButtonWithTitle: [NSString stringWithUTF8String:"Yes"]];
          		break;
        }

	return box;
}

NvdReply nvd_get_reply_cocoa(NvdQuestionBox *box)
{
	NSAlert *dlg = box->window_handle;
	long resp = [dlg runModal];

	NvdReply repl = 0;
	switch (resp) {
		//yes
		case NSAlertFirstButtonReturn:
			repl = NVD_REPLY_OK;
			break;

		case NSAlertSecondButtonReturn:
			if (box->buttons == NVD_YES_CANCEL)
				repl = NVD_REPLY_CANCEL;
			else
			 	repl = NVD_REPLY_NO;
			break;

		default:
		case NSAlertThirdButtonReturn:
			repl = NVD_REPLY_CANCEL;
			break;
	}
	
	[dlg release];
	return repl;
}

void *nvd_dialog_question_get_raw_cocoa(NvdQuestionBox *dlg)
{
	return dlg->window_handle;
}
