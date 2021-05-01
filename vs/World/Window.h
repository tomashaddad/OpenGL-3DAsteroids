#ifndef I3D_WINDOW_H
#define I3D_WINDOW_H

class Window {
public:
	Window();

	double width, height;
	double arena_width, arena_height;
	double plane_lim;
	double xmin, ymin, xmax, ymax;
};


#endif // I3D_WINDOW_H