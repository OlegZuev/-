#include "pch.h"
#include <cstdlib>
#include "png.h"

png_byte color_type;
png_byte bit_depth;

unsigned char* readPngFile(char* filename, int& height, int& width) {
	FILE* infile;
	fopen_s(&infile, filename, "rb");

	if (infile == nullptr) {
		fprintf(stderr, "Can't open %s\n", filename);
		return nullptr;
	}

	unsigned char header[7];
	fread(header, 1, 7, infile);
	const bool isPng = !png_sig_cmp(header, 0, 7);
	
	if (!isPng) {
		fprintf(stderr, "Non png format\n");
		return nullptr;
	}

	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (!png) {
		fprintf(stderr, "Can't create png_structp\n");
		return nullptr;
	}

	png_infop info = png_create_info_struct(png);
	if (!info) {
		png_destroy_read_struct(&png, (png_infopp)nullptr, (png_infopp)nullptr);
		fprintf(stderr, "Can't create png_infop\n");
		return nullptr;
	}
	
	if (setjmp(png_jmpbuf(png))) {
		png_destroy_read_struct(&png, &info,
								(png_infopp)nullptr);
		fprintf(stderr, "Critical bug occured\n");
		fclose(infile);
		return nullptr;
	}

	png_init_io(png, infile);

	png_set_sig_bytes(png, 7);

	png_read_info(png, info);

	width = png_get_image_width(png, info);
	height = png_get_image_height(png, info);
	color_type = png_get_color_type(png, info);
	bit_depth = png_get_bit_depth(png, info);

	// Read any color_type into 8bit depth, RGBA format.
	// See http://www.libpng.org/pub/png/libpng-manual.txt

	if (bit_depth == 16)
		png_set_strip_16(png);

	if (color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png);

	// PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		png_set_expand_gray_1_2_4_to_8(png);

	if (png_get_valid(png, info, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png);

	// These color_type don't have an alpha channel then fill it with 0xff.
	if (color_type == PNG_COLOR_TYPE_RGB ||
		color_type == PNG_COLOR_TYPE_GRAY ||
		color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

	if (color_type == PNG_COLOR_TYPE_GRAY ||
		color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png);

	// RGB -> BGR
	if (color_type & PNG_COLOR_MASK_COLOR)
		png_set_bgr(png);

	png_read_update_info(png, info);

	int a = png_get_channels(png, info);
	unsigned char* buffer = new unsigned char[width * 4];
	unsigned char* output = new unsigned char[width * height * 4];
	for (int y = 0; y < height; y++) {
		png_read_row(png, buffer, nullptr);
	
		size_t position = y * width * 4;
		for (int i = 0; i < width * 4; ++i) {
			output[position + i] = buffer[i];
		}
	}

	fclose(infile);

	png_destroy_read_struct(&png, &info, nullptr);
	return output;
}
