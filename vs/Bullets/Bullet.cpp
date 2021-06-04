#include "Bullet.h"
#include "GlutHeaders.h"
#include "Assets/Asset.h"

#include "World/Camera.h"
#include "Math/Quaternion.h"

Bullet::Bullet(Vector3D position, Vector3D velocity)
	: animation(AnimationDrawer(BULLET_GRID_SIZE, BULLET_TEX_ROWS, BULLET_TEX_COLS, BULLET_FRAMERATE, true))
	, position(position)
	, velocity(velocity)
	, to_delete(false) { }

void Bullet::update(float dt) {
	position += velocity * dt;
	animation.update(dt);
}

void Bullet::draw() const {
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
		glTranslatef(position.X, position.Y, position.Z);
		glMultMatrixf(Quaternion::toMatrix(Camera::getRotation()).data());
		glScalef(BULLET_SIZE, BULLET_SIZE, BULLET_SIZE);

		glBindTexture(GL_TEXTURE_2D, Asset::getTextureId(Entity::bullets));
		animation.draw();
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