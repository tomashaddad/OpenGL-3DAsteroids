#include "Explosion.h"
#include "GlutHeaders.h"
#include "Assets/Asset.h"

Explosion::Explosion(Vector3D position, Vector3D velocity) :
	row(0),
	col(0),
	rate(1.0f / 60), // change image every 24 times per second
	current_timer(0),
	position(position),
	velocity(velocity),
	texture(Asset::getTextureId(Entity::explosion)),
	to_delete(false) { }

// init one UV 2D array for all bullets to use
void Explosion::initUVMap() {
	float step_size = 1.0f / (EXPLOSION_GRID_SIZE - 1);
	for (int r = 0; r < EXPLOSION_GRID_SIZE; ++r) {
		for (int c = 0; c < EXPLOSION_GRID_SIZE; ++c) {
			float u = (float)c * step_size;
			float v = 1 - (float)r * step_size; // store top to bottom
			uvs[r][c] = std::make_pair(u, v);
		}
	}
}

void Explosion::update(float dt) {
	position += velocity * dt;
	current_timer += dt;

	if (current_timer > rate) {
		current_timer = 0;
		next_texture();
	}
}

void Explosion::next_texture() {
	++col;
	if (col > 7) {
		col = 0;
		++row;
		if (row > 5) {
			row = 0;
			markForDeletion();
		}
	}
}

void Explosion::draw() const {
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glColor3f(1.0, 1.0, 1.0);

	glPushMatrix();
	glTranslatef(position.X, position.Y, position.Z);
	glMultMatrixf(Quaternion::toMatrix(Camera::getRotation()).data());
	glScalef(EXPLOSION_SIZE, EXPLOSION_SIZE, EXPLOSION_SIZE);

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

const Vector3D& Explosion::getPosition() const {
	return position;
}

void Explosion::markForDeletion() {
	to_delete = true;
}
bool Explosion::markedForDeletion() {
	return to_delete;
}