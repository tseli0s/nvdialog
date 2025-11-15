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

#include "nvdialog_assert.h"
#include "nvdialog_util.h"

#ifdef _NVD_SUPPORT_IMAGES
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(x) NVD_ASSERT_FATAL(x)
#include <stb_image.h>
#endif /* _NVD_SUPPORT_IMAGES */

#include <nvdialog.h>
#include <nvdialog_image.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "impl/nvdialog_typeimpl.h"

const uint8_t *nvd_image_from_filename(const char *filename, int *width,
                                       int *height) {
#ifdef _NVD_SUPPORT_IMAGES
        NVD_ASSERT(filename != NULL);
        FILE *f = fopen(filename, "rb");
        NVD_RETURN_IF_NULL(f);
        int w, h, channels;
        const uint8_t *data =
                stbi_load_from_file(f, &w, &h, &channels, STBI_rgb_alpha);
        NVD_ASSERT(data != NULL);
        NVD_ASSERT(channels == 4);  // We need 4 channels per pixel (RGBA).

        *width = w;
        *height = h;

        fclose(f);
        return data;
#else
        nvd_set_error(NVD_UNSUPPORTED_ACTION);
        return NULL;
#endif
}

NvdImage *nvd_create_image(const uint8_t *data, int width, int height) {
#ifdef _NVD_SUPPORT_IMAGES
        NvdImage *image = nvd_calloc(1, sizeof(struct _NvdImage));
        NVD_ASSERT(image != NULL);
        NVD_ASSERT(data != NULL);

        image->data = data;
        image->len = 4 * (unsigned int) (width * height);
        image->width = width;
        image->height = height;

        return image;
#else
        nvd_set_error(NVD_UNSUPPORTED_ACTION);
        return NULL;
#endif
}

void nvd_destroy_image(NvdImage *image) {
#ifdef _NVD_SUPPORT_IMAGES
        if (image != NULL) {
                free((void *)image->data);
                free(image);
        }
#else
        nvd_set_error(NVD_UNSUPPORTED_ACTION);
        return;
#endif
}

uint8_t *nvd_image_to_bytes(NvdImage *image) {
#ifdef _NVD_SUPPORT_IMAGES
        NVD_ASSERT(image != NULL);
        return image->data;
#else
        nvd_set_error(NVD_UNSUPPORTED_ACTION);
        return NULL;
#endif
}
