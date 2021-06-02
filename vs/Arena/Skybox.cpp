#include "Skybox.h"

#include "Assets/Asset.h"
#include "GlutHeaders.h"

#include <iostream>

Skybox::Skybox() {
	top = Asset::getTextureId(Entity::skybox_top);
	bottom = Asset::getTextureId(Entity::skybox_bottom);
	left = Asset::getTextureId(Entity::skybox_left);
	right = Asset::getTextureId(Entity::skybox_right);
	front = Asset::getTextureId(Entity::skybox_front);
	back = Asset::getTextureId(Entity::skybox_back);
}

void Skybox::draw() const {
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, top);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f(-0.5f, 0.5f, -0.5f);
			glTexCoord2f(1, 0); glVertex3f(0.5f, 0.5f, -0.5f);
			glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, 0.5f);
			glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, 0.5f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, bottom);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, 0.5f);
			glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, 0.5f);
			glTexCoord2f(1, 1); glVertex3f(0.5f, -0.5f, -0.5f);
			glTexCoord2f(0, 1); glVertex3f(-0.5f, -0.5f, -0.5f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, left);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, 0.5f);
			glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
			glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
			glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, 0.5f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, right);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f(0.5f, -0.5f, -0.5f);
			glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, 0.5f);
			glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, 0.5f);
			glTexCoord2f(0, 1); glVertex3f(0.5f, 0.5f, -0.5f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, front);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
			glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, -0.5f);
			glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, -0.5f);
			glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, back);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f(0.5f, -0.5f, 0.5f);
			glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.5f, 0.5f);
			glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.5f, 0.5f);
			glTexCoord2f(0, 1); glVertex3f(0.5f, 0.5f, 0.5f);
		glEnd();
	glPopMatrix();

	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glPopAttrib();
}