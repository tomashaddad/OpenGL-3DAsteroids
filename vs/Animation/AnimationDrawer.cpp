#include "AnimationDrawer.h"
#include "GlutHeaders.h"

#include <iostream>

AnimationDrawer::AnimationDrawer(int grid_size, int rows, int cols, float rate, bool loop)
	: current_row(0)
	, current_col(0)
	, rows(rows)
	, cols(cols)
	, loop(loop)
	, cycled(false)
	, grid_size(grid_size)
	, current_timer(0)
	, rate(rate)
{
	initUVMap();
}

// NOTE: THIS ASSUMES TEXTURE MAP IS SQUARE WITH TEXTURES CONTAINED WITHIN SUBSQUARES
// The only downside to this approach is that the UV map is created for every entity!
void AnimationDrawer::initUVMap() {
	float step_size = 1.0f / (grid_size - 1);
	for (int r = 0; r < grid_size; ++r) {
		std::vector<std::pair<float, float>> row;
		for (int c = 0; c < grid_size; ++c) {
			float u = (float)c * step_size;
			float v = 1 - (float)r * step_size; // store top to bottom
			row.push_back(std::make_pair(u, v));
		}
		uvs.push_back(row);
	}
}

void AnimationDrawer::update(float dt) {
	current_timer += dt;
	if (current_timer > rate) {
		current_timer = 0;
		next_texture();
	}
}

void AnimationDrawer::next_texture() {
	++current_col;
	if (current_col > cols) {
		current_col = 0;
		++current_row;
		if (current_row > rows) {
			current_row = 0;
			if (!loop) {
				cycled = true;
			}
		}
	}
}

void AnimationDrawer::draw() const {
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(uvs[current_row + 1][current_col].first, uvs[current_row + 1][current_col].second); glVertex3f(-0.5, -0.5, 0.0);
			glTexCoord2f(uvs[current_row + 1][current_col + 1].first, uvs[current_row + 1][current_col + 1].second); glVertex3f(0.5, -0.5, 0.0);
			glTexCoord2f(uvs[current_row][current_col + 1].first, uvs[current_row][current_col + 1].second); glVertex3f(0.5, 0.5, 0.0);
			glTexCoord2f(uvs[current_row][current_col].first, uvs[current_row][current_col].second); glVertex3f(-0.5, 0.5, 0.0);
		glEnd();
	glPopMatrix();
}

bool AnimationDrawer::hasCycled() const {
	return cycled;
}