#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <nvdialog.h>
#include <nvdialog_image.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "nvdialog_assert.h"
#include "impl/nvdialog_typeimpl.h"

/* 
 * FIXME: This assumes that the laoded data is always RGBA (Only checks for the channels).
 * Since I haven't found a way to find how to determine the format of the image I just assume
 * it's always RGBA, but this will mess up many images.
 */
const uint8_t *nvd_image_from_filename(const char *filename, int *width, int *height) {
    NVD_ASSERT(filename != NULL);
    FILE *f = fopen(filename, "rb");
    NVD_RETURN_IF_NULL(f);
    int w, h, channels;
	const uint8_t *data = stbi_load_from_file(f, &w, &h, &channels, 0);
    NVD_ASSERT(data != NULL);
    NVD_ASSERT(channels == 4); // We need 4 channels per pixel (RGBA).

    *width = w;
    *height = h;

    fclose(f);
    return data;
}

NvdImage *nvd_create_image(const uint8_t *data, int width, int height) {
    NvdImage *image = calloc(1, sizeof(struct _NvdImage));
    NVD_ASSERT(image != NULL);
    NVD_ASSERT(data  != NULL);

    image->data   = data;
    image->len    = 4 * (width * height);
    image->width  = width;
    image->height = height;

    return image;
}

void nvd_destroy_image(NvdImage *image) {
    if (image != NULL) {
        free((void*) image->data);
        free(image);
    }
}
