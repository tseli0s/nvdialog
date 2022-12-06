#ifndef __nvdialog_cocoa_h__
#define __nvdialog_cocoa_h__

#include "nvdialog.h"

/* Shows a dialog box using Cocoa */
NvdDialogBox *nvd_dialog_box_cocoa(const char *title, const char *message, NvdDialogType type);

/* Open file dialog using Cocoa */
NvdFileDialog *nvd_open_file_dialog_cocoa(const char *title, const char *file_extensions);

/* Open file dialog using Cocoa */
NvdFileDialog *nvd_save_file_dialog_cocoa(const char *title, const char *default_filename);

/* Creates a dialog box with the usual yes, no and cancel buttons. */
NvdQuestionBox *nvd_question_cocoa(const char       *title,
								   const char       *question,
								   NvdQuestionButton buttons);

void nvd_show_dialog_box_cocoa(NvdDialogBox *dialog);
void nvd_get_file_location_cocoa(NvdFileDialog *dlg, const char **out);
NvdReply nvd_get_reply_cocoa(NvdQuestionBox *box);

#endif //__nvdialog_adw_h__
