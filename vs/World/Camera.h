#ifndef I3D_CAMERA_H
#define I3D_CAMERA_H

class Camera {
public:
	Camera(float theta, float phi, float r);
	void changeZoomBy(float zoom);
	void changePhiBy(float angle);
	void changeThetaBy(float angle);

	float X;
	float Y;
	float Z;

private:
	void computeCoordinates();
	float phi; // angle in z
	float theta; // angle in xy
	float radius;
};

#endif // I3D_CAMERA_H