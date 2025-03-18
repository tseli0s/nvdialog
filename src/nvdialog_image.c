#include <nvdialog_image.h>
#include <stdint.h>
#include <stb_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "nvdialog_assert.h"

#define STB_IMAGE_IMPLEMENTATION

struct _NvdImage {
    const uint8_t *data;
    size_t len;
};

/* 
 * FIXME: This assumes that the laoded data is always RGBA (Only checks for the channels).
 * Since I haven't found a way to find how to determine the format of the image I just assume
 * it's always RGBA, but this will mess up many images.
 */
const uint8_t *nvd_image_from_filename(const char *filename, size_t *len) {
    NVD_ASSERT_FATAL(filename != NULL);
    FILE *f = fopen(filename, "rb");
    NVD_RETURN_IF_NULL(f);
    int w, h, channels;
	const uint8_t *data = stbi_load_from_file(f, &w, &h, &channels, 0);
    NVD_ASSERT_FATAL(data != NULL);
    NVD_ASSERT(channels == 4); // We need 4 channels per pixel (RGBA).

    *len = (w * h * channels);

    fclose(f);
    return data;
}

NvdImage *nvd_create_image(const uint8_t *data, size_t len) {
    NvdImage *image = calloc(1, sizeof(struct _NvdImage));
    NVD_ASSERT_FATAL(image != NULL);
    NVD_ASSERT_FATAL(data  != NULL);

    image->data = data;
    image->len  = len;

    return image;
}

void nvd_destroy_image(NvdImage *image) {
    if (image != NULL) {
        stbi_image_free((void*) image->data);
        free(image);
    }
}
