#include "nvdialog.h"
#include "nvdialog_cocoa.h"

#include <AppKit/AppKit.h>
#include <stdbool.h>

#include "../../nvdialog_assert.h"

NvdQuestionBox *nvd_question_cocoa(const char *title, const char *question, NvdQuestionButton buttons)
{
	NvdQuestionBox *box = malloc(sizeof(struct _NvdQuestionBox));
	box->title = title;
	box->contents = question;
	box->buttons = buttons;
	box->reply = 0;

	NSAlert *dlg = box->window_handle = [[NSAlert alloc] init];
	dlg.messageText = @(title);
	dlg.informativeText = @(question);


	//added buttons are in reverse
	switch (buttons) {
        	case NVD_YES_NO_CANCEL:
			[dlg addButtonWithTitle: @"Cancel"];
        	case NVD_YES_NO:
			[dlg addButtonWithTitle: @"No"];
			[dlg addButtonWithTitle: @"Yes"];
			break;
		
        	case NVD_YES_CANCEL:
			[dlg addButtonWithTitle: @"Cancel"];
			[dlg addButtonWithTitle: @"Yes"];
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
