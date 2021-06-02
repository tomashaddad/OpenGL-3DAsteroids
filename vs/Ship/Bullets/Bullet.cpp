#include "Bullet.h"
#include "GlutHeaders.h"
#include "Assets/Asset.h"

#include <iostream>

Bullet::Bullet(Vector3D position, Vector3D velocity) :
	row(3),
	col(5),
	rate(1.0f / 24),
	current_timer(0),
	position(position),
	velocity(velocity),
	to_delete(false),
	texture(Asset::getTextureId(Entity::bullets)) { }

void Bullet::initUVMap() {
	float step_size = 1.0f / 6;
	for (int r = 0; r < BULLET_VCOUNT; ++r) {
		for (int c = 0; c < BULLET_UCOUNT; ++c) {
			float u = (float)c * step_size;
			float v = 1 - (float)r * step_size;
			uvs[r][c] = std::make_pair(u, v);
		}
	}
}

void Bullet::update(float dt) {
	position += velocity * BULLET_SPEED * dt;
	current_timer += dt;

	if (current_timer > rate) {
		current_timer = 0;
		next_texture();
	}
}

void Bullet::next_texture() {
	// if the window is at the end of the array
	// reset col, go to next row
	if (col == 0) {
		col = 5;
		--row;

		// if we have reached the last row of the array
		if (row == 0) {
			row = 3;
		}
	}
	// move 2x2 window one to the right
	--col;
}

void Bullet::draw() const {
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glColor3f(1.0, 1.0, 1.0);

	glPushMatrix();
		glTranslatef(position.X, position.Y, position.Z);
		glMultMatrixf(Quaternion::toMatrix(Camera::getRotation()).data());
		glScalef(5, 5, 5);

		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
			glTexCoord2f(uvs[row + 1][col].first, uvs[row + 1][col].second); glVertex3f(-0.5, -0.5, 0.0);
			glTexCoord2f(uvs[row + 1][col + 1].first, uvs[row + 1][col + 1].second); glVertex3f(0.5, -0.5, 0.0);
			glTexCoord2f(uvs[row][col + 1].first, uvs[row][col + 1].second); glVertex3f(0.5, 0.5, 0.0);
			glTexCoord2f(uvs[row][col].first, uvs[row][col].second); glVertex3f(-0.5, 0.5, 0.0);
		glEnd();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

}

const Vector3D& Bullet::getPosition() const {
	return position;
}

void Bullet::markForDeletion() {
	to_delete = true;
}
bool Bullet::markedForDeletion() {
	return to_delete;
}