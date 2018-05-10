#include "texture.h"
#include <iostream>

Texture::Texture() {
	/*glGenTexture(1,&texture_id);
	glBindTexture(GL_TEXTURE_2D,texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);*/
}

Texture::~Texture() {
	glDeleteTextures(1, &texture_id);
}

bool Texture::load(const char* path) {
	SDL_Surface* res_texture = IMG_Load(path);
	if (res_texture == NULL) {
		std::cerr << "IMG_Load: " << SDL_GetError() << std::endl;
		return false;
	} else {
		glGenTextures(1,&texture_id);
		glBindTexture(GL_TEXTURE_2D,texture_id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, // target
			0,  // level, 0 = base, no minimap,
			GL_RGBA, // internalformat
			res_texture->w,  // width
			res_texture->h,  // height
			0,  // border, always 0 in OpenGL ES
			GL_RGBA,  // format
			GL_UNSIGNED_BYTE, // type
			res_texture->pixels);
		SDL_FreeSurface(res_texture);
		return true;
	}
}