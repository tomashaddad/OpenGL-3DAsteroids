#include "Bullet.h"
#include "GlutHeaders.h"
#include "Assets/Asset.h"

#include <iostream>

Bullet::Bullet(Vector3D position, Vector3D velocity) :
	row(3),
	col(5),
	rate(1.0f / 24), // change image every 24 times per second
	current_timer(0),
	position(position),
	velocity(velocity),
	to_delete(false),
	texture(Asset::getTextureId(Entity::bullets)) { }

// init one UV 2D array for all bullets to use
void Bullet::initUVMap() {
	float step_size = 1.0f / 6;
	for (int r = 0; r < BULLET_VCOUNT; ++r) {
		for (int c = 0; c < BULLET_UCOUNT; ++c) {
			float u = (float)c * step_size;
			float v = 1 - (float)r * step_size; // store top to bottom
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

// the texture is drawn in backwards order because it looks like
// it rolls backwards if you draw it top left to bottom right
void Bullet::next_texture() {
	// if the window has reached the left side of the 2D array
	// reset its position to the right side
	// and move 2x2 window one up
	if (col == 0) {
		col = 5;
		--row;

		// if the window has reached the top of the 2D array
		// reset its position to the bottom side
		if (row == 0) {
			row = 3;
		}
	}
	// move 2x2 window one to the left
	--col;
	
	// draw on next loop
}

void Bullet::draw() const {
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glColor3f(1.0, 1.0, 1.0);

	glPushMatrix();
		glTranslatef(position.X, position.Y, position.Z);
		glMultMatrixf(Quaternion::toMatrix(Camera::getRotation()).data());
		glScalef(2, 2, 2);

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