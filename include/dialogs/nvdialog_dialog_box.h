/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2024 Aggelos Tselios
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

#include "../nvdialog_platform.h"
#include "../nvdialog_types.h"

/**
 * @brief A type to identify a single dialog box.
 * @note You can only use a dialog box once. Reusing it is undefined behavior.
 * <b>Example:</b>
 * @code
 * #include <nvdialog/nvdialog.h>
 * int main(int argc, char** argv) {
 *      nvd_init(argv[0]);
 *      NvdDialogBox *dialog = nvd_dialog_box_new("Hello World!",
 *                                                "A simple dialog box.",
 *                                                NVD_DIALOG_SIMPLE);
 *      if (!dialog) return -1;
 *
 *      nvd_show_dialog(dialog);
 *      nvd_free_object(dialog);
 *
 *      return 0;
 * }
 * @endcode
 * @since v0.1.0
 */
typedef struct _NvdDialogBox NvdDialogBox;

/**
 * @brief A similar struct to @ref NvdDialogBox, but
 * instead used for question dialogs.
 * @since v0.1.0
 * @ingroup QuestionDialog
 */
typedef struct _NvdQuestionBox NvdQuestionBox;

/**
 * @brief Creates a new dialog object and returns it.
 *
 * This function creates a simple dialog with the specified arguments,
 * and returns an opaque handle to it for use with @ref nvd_show_dialog.
 *
 * @ingroup QuestionDialog
 * @return The dialog handle on success, else NULL.
 */
NVD_API NvdDialogBox *nvd_dialog_box_new(const char *title, const char *message,
                                         NvdDialogType type);

/**
 * @brief Shows a dialog to the system shell.
 * @details The dialog given is rendered to the screen when this function is called.
 * This function is not yet useful since some API changes may be required to work.
 * @param dialog The dialog to show.
 * @ingroup QuestionDialog
 * @note Obsolete function, currently unnecessary.
 */
NVD_API void nvd_show_dialog(NvdDialogBox *dialog);

/**
 * @brief Creates a question dialog box with the given parameters.
 * This function creates a dialog box containing a question with a few
 * buttons such as:
 * - Yes / No
 * - Yes / No / Cancel
 * - Yes / Cancel
 * @ingroup QuestionDialog
 * @return The NvdReply on success, else -1 -- Check @ref nvd_get_error for
 * more.
 * @since  v0.1.1
 */
NVD_API NvdQuestionBox* nvd_dialog_question_new(const char *title, const char *question,
                                        NvdQuestionButton button);

/**
 * @brief Shows the dialog box given to the system and returns the choice given
 * @param box The box to use to show the reply.
 * @ingroup QuestionDialog
 * @return The reply from the dialog box.
 */
NVD_API NvdReply nvd_get_reply(NvdQuestionBox *box);

/**
 * @brief Returns the raw object behind the dialog.
 * @param dialog The dialog to retrieve the object from.
 * @ingroup QuestionDialog
 * @return void* The raw toolkit-created object.
 */ 
NVD_API void *nvd_dialog_question_get_raw(NvdQuestionBox *dialog);

/**
 * @brief Returns the raw object behind the dialog.
 * @param dialog The dialog to retrieve the object from.
 * @ingroup QuestionDialog
 * @return void* The raw toolkit-created object.
 */
NVD_API void *nvd_dialog_box_get_raw(NvdDialogBox *dialog);

/**
 * @brief Sets the accept text for the dialog (The "Ok" button label).
 * @param dialog The dialog to change the button label.
 * @ingroup QuestionDialog
 * @param accept_text The new label of the dialog button. May not be NULL.
 * @since v0.8.0
 */
NVD_API void nvd_dialog_box_set_accept_text(NvdDialogBox* dialog, const char* accept_text);
