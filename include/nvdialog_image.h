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

#pragma once

#ifdef __nvdialog_image_h__
#error[ NVDIALOG ] Header file included twice, only #include <nvdialog/nvdialog.h>
#endif /* __nvdialog_image_h__ */
 
#ifndef __nvdialog_image_h__
#define __nvdialog_image_h__ 1

#include "nvdialog_types.h"
#include "nvdialog.h"
#include <stdint.h>
#include <stddef.h>

#ifndef __nvdialog_h__
#error[ NVDIALOG ] Please only include <nvdialog.h> and no other headers.
#endif /* __nvdialog_h__ */
 

/**
 * @brief Data that can be interpeted as an image.
 *
 * The data format is RGBA for library-wide compatibility
 * across various operating systems. Other formats are supported
 * and automatically converted.
 *
 * @ingroup Image
 * @since v0.9.0
*/
typedef struct _NvdImage NvdImage;
 
/**
 * @brief 
 * 
 * @param filename The path to the file to be loaded. For best compatibility, provide a full path
 * or use @ref NvdFileDialog
 * @param len A pointer to a variable to hold the length of the data in bytes. (Can be NULL although not recommended)
 * @param width A pointer to a variable to hold the width of the image
 * @param height A pointer to a variable to hold the height of the image
 * @ingroup Image
 * @since v0.9.0
 * @return A pointer to dynamically allocated image data. The returned pointer must not be freed manually; Instead use @ref nvd_destroy_image.
 */
NVD_API const uint8_t *nvd_image_from_filename(const char *filename, int *width, int *height);

/**
 * @brief Creates an `NvdImage` from the given buffer (data). 
 * Although recommended, it is not necessary to use @ref nvd_image_from_filename since other libraries can also
 * provide RGBA data.
 * @param data The data to use as the image
 * @param width The width of the image
 * @param height The height of the image
 * @ingroup Image
 * @return NvdImage* A pointer to an `NvdImage` object.
 */
NVD_API NvdImage* nvd_create_image(const uint8_t *data, int width, int height);

/**
 * @brief Destroys an @ref NvdImage.
 * @param image The image to destroy
 * @ingroup Image
 * @since v0.9.0
 */
NVD_API void nvd_destroy_image(NvdImage *image);

#endif /* __nvdialog_image_h__ */
