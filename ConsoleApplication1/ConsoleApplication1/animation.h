#pragma once
#include "source.h"
#include "variables.h"

class Animation {
public:
	Image* images;
	int size;
	std::atomic_int current;

	Animation(const std::string& filename, const std::string& extension, size_t size);

	~Animation();
};