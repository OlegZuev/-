#include "animation.h"
#include "utilities.h"

Animation::Animation(const std::string& filename, const std::string& extension, size_t size) {
	std::vector<std::string> filenames;
	this->size = size;
	current = 0;
	filenames.reserve(size);
	for (size_t i = 0; i < size; ++i) {
		filenames.push_back((filename + " (" + std::to_string(i + 1) + ").").append(extension));
	}
	if (extension == "png") {
		images = readPngImages(&filenames[0], size);
	} else if (extension == "jpg" || extension == "jpeg") {
		images = readJpegImages(&filenames[0], size);
	} else {
		throw std::exception("Don't know the picture's extension.");
	}
}

Animation::~Animation() {
	for (int i = 0; i < size; ++i) {
		delete images[i].hBuffer;
	}
	delete images;
}
