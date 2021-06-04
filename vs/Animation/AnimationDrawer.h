#ifndef I3D_ANIMATIONDRAWER_H
#define I3D_ANIMATIONDRAWER_H

#include <vector>
#include <utility>

// Composition over inheritance!
// Converts an n by n grid from a square texture animation map into UV coordinates and renders accordingly 

class AnimationDrawer {
public:
	AnimationDrawer(int grid_size, int rows, int cols, float rate, bool loop);
	void initUVMap();
	void update(float dt);
	void draw() const;
	void next_texture();

	bool hasCycled() const;

private:
	// Can't use 2D std::array since we don't know size at compile time
	std::vector<std::vector<std::pair<float, float>>> uvs;
	int grid_size;
	bool loop;
	bool cycled;

	int current_row; // the current row of the top left corner of the 2x2 window
	int current_col; // the current col of the top left corner of the 2x2 window
	int rows; // the maximuim allowed row index allowed for the top left corner of the 2x2 window 
	int cols; // the maximuim allowed col index allowed for the top left corner of the 2x2 window 

	float current_timer;
	float rate;
};

#endif // I3D_ANIMATIONDRAWER_H