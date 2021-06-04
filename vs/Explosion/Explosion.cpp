#include "Explosion.h"
#include "GlutHeaders.h"
#include "Assets/Asset.h"

#include "World/Camera.h"
#include "Math/Quaternion.h"

Explosion::Explosion(Vector3D position, Vector3D velocity)
	: animation(AnimationDrawer(EXPLOSION_GRID_SIZE, EXPLOSION_TEX_ROWS, EXPLOSION_TEX_COLS, EXPLOSION_FRAMERATE, false))
	, position(position)
	, velocity(velocity)
	, to_delete(false) { }

void Explosion::update(float dt) {
	position += velocity * dt;
	animation.update(dt);
	if (animation.hasCycled()) {
		markForDeletion();
	}
}

void Explosion::draw() const {
	if (markedForDeletion()) {
		return;
	}

	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
		glTranslatef(position.X, position.Y, position.Z);
		glMultMatrixf(Quaternion::toMatrix(Camera::getRotation()).data());
		glScalef(EXPLOSION_SIZE, EXPLOSION_SIZE, EXPLOSION_SIZE);

		glBindTexture(GL_TEXTURE_2D, Asset::getTextureId(Entity::explosion));
		animation.draw();
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

bool Explosion::markedForDeletion() const {
	return to_delete;
}