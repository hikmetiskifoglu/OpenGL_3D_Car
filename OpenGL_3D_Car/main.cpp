#include <iostream>
#include <GL/glut.h>
#include <cmath>

#define M_PI           3.141592653589793238462643383279502884L

float pos_x = 0.0; //first location
float pos_y = 2.0;
float pos_z = 0.0;

float angle_car = 90.0;
float angle_camera_h = 270.0;
float angle_camera_v = 0;

float locate_x = 0.0; // moved location
float locate_z = 0.0;

float cam_distance = 20.0;

float window_width = 1280;
float window_height = 720;


void motion(int x, int y) {
	angle_camera_h += (window_width / 2 - (float)x) / 50.0;
	angle_camera_v -= (window_height / 2 - (float)y) / 50.0;
	if (angle_camera_v > 89)
	{
		angle_camera_v = 89;
	}
	if (angle_camera_v < 0)
	{
		angle_camera_v = 0;
	}
	glutWarpPointer(window_width / 2, window_height / 2);
	glutPostRedisplay();
}

float angle_to_radian(float angle)
{
	return angle * 2.0f * M_PI / 360;
}
void drawWheel(float pos_x, float pos_y, float pos_z, float radius, float depth)
{
	int numTriangles = 360;
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	// Set the center of the circle
	glVertex3f(pos_x, pos_y, pos_z + depth / 2);

	// Draw the triangles that make up the circle
	for (int i = 0; i <= numTriangles; i++) {
		double theta = i * 2.0f * M_PI / numTriangles;

		glVertex3f(pos_x + radius * cos(theta), pos_y + radius * sin(theta), pos_z + (depth / 2));
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	// Set the center of the circle
	glVertex3f(pos_x, pos_y, pos_z - depth / 2);

	// Draw the triangles that make up the circle
	for (int i = 0; i <= numTriangles; i++) {
		double theta = i * 2.0f * M_PI / numTriangles;

		glVertex3f(pos_x + radius * cos(theta), pos_y + radius * sin(theta), pos_z - depth / 2);
	}

	glEnd();
	glColor3f(38 / 255.0, 38 / 255.0, 38 / 255.0);
	glBegin(GL_TRIANGLE_STRIP);

	// Draw the triangles that make up the circle
	for (int i = 0; i <= numTriangles; i++) {
		double theta = i * 2.0f * M_PI / numTriangles;

		glVertex3f(pos_x + radius * cos(theta), pos_y + radius * sin(theta), pos_z - depth / 2);
		glVertex3f(pos_x + radius * cos(theta), pos_y + radius * sin(theta), pos_z + depth / 2);
	}
	glEnd();

}

void drawCar(float crowling_length, float baggage_length, float top_length, float body_length, float body_height, float window_height, float car_depth, float pos_x, float pos_y, float pos_z)
{
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(locate_x, 0.0, locate_z);
	glRotatef(angle_car - 90, 0.0f, 1.0f, 0.0f);

	glColor3f(174 / 255.0, 30 / 255.0, 22 / 255.0);
	glBegin(GL_QUADS);
	//right side
	glVertex3f(-body_length / 2 + pos_x, 0.0 + pos_y, car_depth / 2 + pos_z);
	glVertex3f(body_length / 2 + pos_x, 0.0 + pos_y, car_depth / 2 + pos_z);
	glColor3f(254 / 255.0, 67 / 255.0, 68 / 255.0);
	glVertex3f(body_length / 2 + pos_x, -body_height + pos_y, car_depth / 2 + pos_z);
	glVertex3f(-body_length / 2 + pos_x, -body_height + pos_y, car_depth / 2 + pos_z);

	//right top
	glColor3f(207 / 255.0, 207 / 255.0, 207 / 255.0);
	glVertex3f(-(body_length / 2 - baggage_length) + pos_x, 0.0 + pos_y, car_depth / 2 + pos_z);
	glVertex3f(body_length / 2 - crowling_length + pos_x, 0.0 + pos_y, car_depth / 2 + pos_z);
	glColor3f(115 / 255.0, 160 / 255.0, 160 / 255.0);
	glVertex3f(top_length / 2 + (((body_length / 2 - crowling_length) - (body_length / 2 - baggage_length))) / 2 + pos_x, window_height + pos_y, car_depth / 2 + pos_z);
	glVertex3f(-top_length / 2 + (((body_length / 2 - crowling_length) - (body_length / 2 - baggage_length))) / 2 + pos_x, window_height + pos_y, car_depth / 2 + pos_z);

	//front side far
	glColor3f(174 / 255.0, 30 / 255.0, 22 / 255.0);
	glVertex3f(body_length / 2 + pos_x, 0.0 + pos_y, car_depth / 2 + pos_z);
	glVertex3f(body_length / 2 + pos_x, 0.0 + pos_y, -car_depth / 2 + pos_z);
	glColor3f(254 / 255.0, 67 / 255.0, 68 / 255.0);
	glVertex3f(body_length / 2 + pos_x, -body_height + pos_y, -car_depth / 2 + pos_z);
	glVertex3f(body_length / 2 + pos_x, -body_height + pos_y, car_depth / 2 + pos_z);

	//front right headlight
	glColor3f(207 / 255.0, 207 / 255.0, 207 / 255.0);
	glVertex3f(body_length / 2 + pos_x + 0.01, -0.3 + pos_y, car_depth / 2 + pos_z);
	glVertex3f(body_length / 2 + pos_x + 0.01, -0.3 + pos_y, car_depth / 3.5 + pos_z);
	glColor3f(249 / 255.0, 240 / 255.0, 180 / 255.0);
	glVertex3f(body_length / 2 + pos_x + 0.01, -body_height / 2 + pos_y, car_depth / 3.5 + pos_z);
	glVertex3f(body_length / 2 + pos_x + 0.01, -body_height / 2 + pos_y, car_depth / 2 + pos_z);

	//front left headlight
	glColor3f(207 / 255.0, 207 / 255.0, 207 / 255.0);
	glVertex3f(body_length / 2 + pos_x + 0.01, -0.3 + pos_y, -car_depth / 2 + pos_z);
	glVertex3f(body_length / 2 + pos_x + 0.01, -0.3 + pos_y, -car_depth / 3.5 + pos_z);
	glColor3f(249 / 255.0, 240 / 255.0, 180 / 255.0);
	glVertex3f(body_length / 2 + pos_x + 0.01, -body_height / 2 + pos_y, -car_depth / 3.5 + pos_z);
	glVertex3f(body_length / 2 + pos_x + 0.01, -body_height / 2 + pos_y, -car_depth / 2 + pos_z);

	//front plate
	glColor3f(255 / 255.0, 255 / 255.0, 255 / 255.0);
	glVertex3f(body_length / 2 + pos_x + 0.01, -body_height / 2.5 + pos_y, -car_depth / 5 + pos_z);
	glVertex3f(body_length / 2 + pos_x + 0.01, -body_height / 2.5 + pos_y, car_depth / 5 + pos_z);
	glVertex3f(body_length / 2 + pos_x + 0.01, -body_height / 1.5 + pos_y, car_depth / 5 + pos_z);
	glVertex3f(body_length / 2 + pos_x + 0.01, -body_height / 1.5 + pos_y, -car_depth / 5 + pos_z);

	//front side cowling
	glColor3f(174 / 255.0, 30 / 255.0, 22 / 255.0);
	glVertex3f(body_length / 2 + pos_x, 0.0 + pos_y, car_depth / 2 + pos_z);
	glVertex3f(body_length / 2 + pos_x, 0.0 + pos_y, -car_depth / 2 + pos_z);
	glColor3f(254 / 255.0, 67 / 255.0, 68 / 255.0);
	glVertex3f(body_length / 2 - crowling_length + pos_x, 0.0 + pos_y, -car_depth / 2 + pos_z);
	glVertex3f(body_length / 2 - crowling_length + pos_x, 0.0 + pos_y, car_depth / 2 + pos_z);

	//front side window

	glColor3f(207 / 255.0, 207 / 255.0, 207 / 255.0);
	glVertex3f(body_length / 2 - crowling_length + pos_x, 0.0 + pos_y, -car_depth / 2 + pos_z);
	glVertex3f(body_length / 2 - crowling_length + pos_x, 0.0 + pos_y, car_depth / 2 + pos_z);
	glColor3f(115 / 255.0, 160 / 255.0, 160 / 255.0);
	glVertex3f(top_length / 2 + (((body_length / 2 - crowling_length) - (body_length / 2 - baggage_length))) / 2 + pos_x, window_height + pos_y, car_depth / 2 + pos_z);
	glVertex3f(top_length / 2 + (((body_length / 2 - crowling_length) - (body_length / 2 - baggage_length))) / 2 + pos_x, window_height + pos_y, -car_depth / 2 + pos_z);


	//top side 
	glColor3f(254 / 255.0, 67 / 255.0, 68 / 255.0);
	glVertex3f(top_length / 2 + (((body_length / 2 - crowling_length) - (body_length / 2 - baggage_length))) / 2 + pos_x, window_height + pos_y, car_depth / 2 + pos_z);
	glVertex3f(-top_length / 2 + (((body_length / 2 - crowling_length) - (body_length / 2 - baggage_length))) / 2 + pos_x, window_height + pos_y, car_depth / 2 + pos_z);
	glColor3f(174 / 255.0, 30 / 255.0, 22 / 255.0);
	glVertex3f(-top_length / 2 + (((body_length / 2 - crowling_length) - (body_length / 2 - baggage_length))) / 2 + pos_x, window_height + pos_y, -car_depth / 2 + pos_z);
	glVertex3f(top_length / 2 + (((body_length / 2 - crowling_length) - (body_length / 2 - baggage_length))) / 2 + pos_x, window_height + pos_y, -car_depth / 2 + pos_z);

	//back side window
	glColor3f(207 / 255.0, 207 / 255.0, 207 / 255.0);
	glVertex3f(-(body_length / 2 - baggage_length) + pos_x, 0.0 + pos_y, -car_depth / 2 + pos_z);
	glVertex3f(-(body_length / 2 - baggage_length) + pos_x, 0.0 + pos_y, car_depth / 2 + pos_z);
	glColor3f(115 / 255.0, 160 / 255.0, 160 / 255.0);
	glVertex3f(-top_length / 2 + (((body_length / 2 - crowling_length) - (body_length / 2 - baggage_length))) / 2 + pos_x, window_height + pos_y, car_depth / 2 + pos_z);
	glVertex3f(-top_length / 2 + (((body_length / 2 - crowling_length) - (body_length / 2 - baggage_length))) / 2 + pos_x, window_height + pos_y, -car_depth / 2 + pos_z);

	//back side baggage
	glColor3f(254 / 255.0, 67 / 255.0, 68 / 255.0);
	glVertex3f(-(body_length / 2 - baggage_length) + pos_x, 0.0 + pos_y, -car_depth / 2 + pos_z);
	glVertex3f(-(body_length / 2 - baggage_length) + pos_x, 0.0 + pos_y, car_depth / 2 + pos_z);
	glColor3f(174 / 255.0, 30 / 255.0, 22 / 255.0);
	glVertex3f(-body_length / 2 + pos_x, 0.0 + pos_y, car_depth / 2 + pos_z);
	glVertex3f(-body_length / 2 + pos_x, 0.0 + pos_y, -car_depth / 2 + pos_z);

	//back side tampon
	glColor3f(174 / 255.0, 30 / 255.0, 22 / 255.0);
	glVertex3f(-body_length / 2 + pos_x, 0.0 + pos_y, car_depth / 2 + pos_z);
	glVertex3f(-body_length / 2 + pos_x, 0.0 + pos_y, -car_depth / 2 + pos_z);
	glColor3f(254 / 255.0, 67 / 255.0, 68 / 255.0);
	glVertex3f(-body_length / 2 + pos_x, -body_height + pos_y, -car_depth / 2 + pos_z);
	glVertex3f(-body_length / 2 + pos_x, -body_height + pos_y, car_depth / 2 + pos_z);

	//right back headlight
	glColor3f(132 / 255.0, 16 / 255.0, 16 / 255.0);
	glVertex3f(-body_length / 2 + pos_x - 0.01, -0.3 + pos_y, car_depth / 2 + pos_z);
	glVertex3f(-body_length / 2 + pos_x - 0.01, -0.3 + pos_y, car_depth / 2.85 + pos_z);
	glColor3f(46 / 255.0, 7 / 255.0, 7 / 255.0);
	glVertex3f(-body_length / 2 + pos_x - 0.01, -body_height / 2 + pos_y, car_depth / 2.85 + pos_z);
	glVertex3f(-body_length / 2 + pos_x - 0.01, -body_height / 2 + pos_y, car_depth / 2 + pos_z);

	//left back headlight
	glColor3f(132 / 255.0, 16 / 255.0, 16 / 255.0);
	glVertex3f(-body_length / 2 + pos_x - 0.01, -0.3 + pos_y, -car_depth / 2 + pos_z);
	glVertex3f(-body_length / 2 + pos_x - 0.01, -0.3 + pos_y, -car_depth / 2.85 + pos_z);
	glColor3f(46 / 255.0, 7 / 255.0, 7 / 255.0);
	glVertex3f(-body_length / 2 + pos_x - 0.01, -body_height / 2 + pos_y, -car_depth / 2.85 + pos_z);
	glVertex3f(-body_length / 2 + pos_x - 0.01, -body_height / 2 + pos_y, -car_depth / 2 + pos_z);

	//back plate
	glColor3f(255 / 255.0, 255 / 255.0, 255 / 255.0);
	glVertex3f(-body_length / 2 + pos_x - 0.01, -body_height / 2.5 + pos_y, -car_depth / 5 + pos_z);
	glVertex3f(-body_length / 2 + pos_x - 0.01, -body_height / 2.5 + pos_y, car_depth / 5 + pos_z);
	glVertex3f(-body_length / 2 + pos_x - 0.01, -body_height / 1.5 + pos_y, car_depth / 5 + pos_z);
	glVertex3f(-body_length / 2 + pos_x - 0.01, -body_height / 1.5 + pos_y, -car_depth / 5 + pos_z);

	//left side
	glColor3f(174 / 255.0, 30 / 255.0, 22 / 255.0);
	glVertex3f(-body_length / 2 + pos_x, 0.0 + pos_y, -car_depth / 2 + pos_z);
	glVertex3f(body_length / 2 + pos_x, 0.0 + pos_y, -car_depth / 2 + pos_z);
	glColor3f(254 / 255.0, 67 / 255.0, 68 / 255.0);
	glVertex3f(body_length / 2 + pos_x, -body_height + pos_y, -car_depth / 2 + pos_z);
	glVertex3f(-body_length / 2 + pos_x, -body_height + pos_y, -car_depth / 2 + pos_z);

	//left top
	glColor3f(207 / 255.0, 207 / 255.0, 207 / 255.0);
	glVertex3f(-(body_length / 2 - baggage_length) + pos_x, 0.0 + pos_y, -car_depth / 2 + pos_z);
	glVertex3f(body_length / 2 - crowling_length + pos_x, 0.0 + pos_y, -car_depth / 2 + pos_z);
	glColor3f(115 / 255.0, 160 / 255.0, 160 / 255.0);
	glVertex3f(top_length / 2 + (((body_length / 2 - crowling_length) - (body_length / 2 - baggage_length))) / 2 + pos_x, window_height + pos_y, -car_depth / 2 + pos_z);
	glVertex3f(-top_length / 2 + (((body_length / 2 - crowling_length) - (body_length / 2 - baggage_length))) / 2 + pos_x, window_height + pos_y, -car_depth / 2 + pos_z);

	//bottom 
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(body_length / 2 + pos_x, -body_height + pos_y, -car_depth / 2 + pos_z);
	glVertex3f(-body_length / 2 + pos_x, -body_height + pos_y, -car_depth / 2 + pos_z);
	glVertex3f(-body_length / 2 + pos_x, -body_height + pos_y, car_depth / 2 + pos_z);
	glVertex3f(body_length / 2 + pos_x, -body_height + pos_y, car_depth / 2 + pos_z);

	glEnd();

	drawWheel(pos_x + body_length / 4, (pos_y - body_height), car_depth / 2, 0.5, 0.5);
	drawWheel(pos_x + -body_length / 4, (pos_y - body_height), car_depth / 2, 0.5, 0.5);
	drawWheel(pos_x + body_length / 4, (pos_y - body_height), -car_depth / 2, 0.5, 0.5);
	drawWheel(pos_x + -body_length / 4, (pos_y - body_height), -car_depth / 2, 0.5, 0.5);

	//right mirror
	glColor3f(0 / 255.0, 0 / 255.0, 0 / 255.0);
	glBegin(GL_TRIANGLE_FAN);

	glVertex3f(body_length / 2 - crowling_length - 1.0 + pos_x, 0.0 + pos_y, pos_z + car_depth / 2);

	for (int i = 0; i <= 90; i++) {
		glVertex3f(body_length / 2 - crowling_length - 1.0 + pos_x, pos_y + 0.35 * sin(angle_to_radian(i)), pos_z + (car_depth / 2) + 0.5 * cos(angle_to_radian(i)));
	}
	glEnd();

	//left mirror
	glColor3f(0 / 255.0, 0 / 255.0, 0 / 255.0);
	glBegin(GL_TRIANGLE_FAN);

	glVertex3f(body_length / 2 - crowling_length - 1.0 + pos_x, 0.0 + pos_y, pos_z - car_depth / 2);

	for (int i = 0; i <= 90; i++) {
		glVertex3f(body_length / 2 - crowling_length - 1.0 + pos_x, pos_y + 0.35 * sin(angle_to_radian(i)), pos_z - (car_depth / 2) - 0.5 * cos(angle_to_radian(i)));
	}
	glEnd();


	glPopMatrix();
	//glLoadIdentity();
}

void drawRoad(float length, float height, float pos_x, float pos_z, float angle)
{

	glPushMatrix();
	glTranslatef(pos_x, 0.0, pos_z);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);

	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_QUADS);
	glVertex3f(-height / 2, 0.0, -height / 2);
	glVertex3f(-height / 2, 0.0, height / 2);
	glVertex3f((height / 2 + length), 0.0, height / 2);
	glVertex3f((height / 2 + length), 0.0, -height / 2);

	glEnd();

	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_QUADS);

	for (float i = height / 2; i < length - height / 2; i += 4.5)
	{
		glVertex3f(i, 0.001, -0.5);
		glVertex3f(i, 0.001, 0.5);
		glVertex3f((i + 2.5), 0.001, 0.5);
		glVertex3f((i + 2.5), 0.001, -0.5);
	}
	glEnd();

	glColor3f(160 / 255.0, 160 / 255.0, 160 / 255.0);
	glBegin(GL_QUADS);
	glVertex3f(-height, -0.005, -height);
	glVertex3f(length + height, -0.005, -height);
	glVertex3f(length + height, -0.005, -height / 2);
	glVertex3f(-height, -0.005, -height / 2);


	glVertex3f(-height, -0.005, height);
	glVertex3f(length + height, -0.005, height);
	glVertex3f(length + height, -0.005, height / 2);
	glVertex3f(-height, -0.005, height / 2);

	//glVertex3f(height/2, 0.01, -height);
	//glVertex3f(length - height/2, 0.01, -height);
	//glVertex3f(length - height/2, 0.01, -height/2);
	//glVertex3f(height/2, 0.01, -height/2);


	//glVertex3f(height/2, 0.01, height);
	//glVertex3f(length - height/2, 0.01, height);
	//glVertex3f(length - height/2, 0.01, height/2);
	//glVertex3f(height/2, 0.01, height/2);
	glEnd();

	glPopMatrix();

}

//draw apartment
void drawApartment(float window_count, float floor, float pos_x, float pos_z, float angle)
{

	float width;
	if (window_count < 1)
	{
		width = 6.0;
	}
	else
	{
		width = 2 + window_count * 4;
	}

	float height = 6 + floor * 4;
	glPushMatrix();
	glColor3f(155 / 255.0, 118 / 255.0, 83 / 255.0);
	glTranslatef(pos_x, 0.0, pos_z);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glBegin(GL_QUADS);

	//apartment base
	glColor3f(155 / 255.0, 118 / 255.0, 83 / 255.0);
	glVertex3f(width / 2, 0.0, width / 2);
	glVertex3f(width / 2, 0.0, -width / 2);
	glColor3f(255 / 255.0, 173 / 255.0, 87 / 255.0);
	glVertex3f(-width / 2, 0.0, -width / 2);
	glVertex3f(-width / 2, 0.0, width / 2);

	//apartment top
	glColor3f(155 / 255.0, 118 / 255.0, 83 / 255.0);
	glVertex3f(width / 2, height, width / 2);
	glVertex3f(width / 2, height, -width / 2);
	glColor3f(255 / 255.0, 173 / 255.0, 87 / 255.0);
	glVertex3f(-width / 2, height, -width / 2);
	glVertex3f(-width / 2, height, width / 2);

	//Left Wall
	glColor3f(255 / 255.0, 173 / 255.0, 87 / 255.0);
	glVertex3f(width / 2, height, width / 2);
	glVertex3f(width / 2, height, -width / 2);
	glColor3f(155 / 255.0, 118 / 255.0, 83 / 255.0);
	glVertex3f(width / 2, 0.0, -width / 2);
	glVertex3f(width / 2, 0.0, width / 2);

	//Right Wall
	glColor3f(255 / 255.0, 173 / 255.0, 87 / 255.0);
	glVertex3f(-width / 2, height, width / 2);
	glVertex3f(-width / 2, height, -width / 2);
	glColor3f(155 / 255.0, 118 / 255.0, 83 / 255.0);
	glVertex3f(-width / 2, 0.0, -width / 2);
	glVertex3f(-width / 2, 0.0, width / 2);

	//Back Wall
	glColor3f(155 / 255.0, 118 / 255.0, 83 / 255.0);
	glVertex3f(width / 2, 0.0, -width / 2);
	glVertex3f(-width / 2, 0.0, -width / 2);
	glColor3f(255 / 255.0, 173 / 255.0, 87 / 255.0);
	glVertex3f(-width / 2, height, -width / 2);
	glVertex3f(width / 2, height, -width / 2);

	//Front Wall
	glColor3f(155 / 255.0, 118 / 255.0, 83 / 255.0);
	glVertex3f(-width / 2, 0.0, width / 2);
	glVertex3f(width / 2, 0.0, width / 2);
	glColor3f(255 / 255.0, 173 / 255.0, 87 / 255.0);
	glVertex3f(width / 2, height, width / 2);
	glVertex3f(-width / 2, height, width / 2);

	//Door
	glColor3f(39 / 255.0, 11 / 255.0, 6 / 255.0);
	glVertex3f(-1.5, 0.0, width / 2 + 0.01);
	glVertex3f(1.5, 0.0, width / 2 + 0.01);
	glVertex3f(1.5, 4.0, width / 2 + 0.01);
	glVertex3f(-1.5, 4.0, width / 2 + 0.01);

	glEnd();
	glPopMatrix();

	for (float k = 0; k < 360; k += 90)
	{
		glPushMatrix();
		glTranslatef(pos_x, 0.0, pos_z);
		glRotatef(k, 0.0, 1.0, 0.0);
		//Window
		glColor3f(16 / 255.0, 12 / 255.0, 8 / 255.0);
		glBegin(GL_QUADS);
		for (float i = -width / 2 + 2; i < width / 2 - 2; i += 4)
		{
			for (float j = 6; j <= height - 2; j += 4)
			{
				glVertex3f(i, j, width / 2 + 0.01);
				glVertex3f(i + 2, j, width / 2 + 0.01);
				glVertex3f(i + 2, j + 2, width / 2 + 0.01);
				glVertex3f(i, j + 2, width / 2 + 0.01);
			}
		}
		glEnd();
		glPopMatrix();
	}
}

void drawEnvironment()
{
	//Soil
	glColor3f(24 / 255.0, 145 / 255.0, 43 / 255.0);
	glBegin(GL_QUADS);
	glVertex3f(-500.0, -0.01, -500.0);
	glVertex3f(500.0, -0.01, -500.0);
	glVertex3f(500.0, -0.01, 500.0);
	glVertex3f(-500.0, -0.01, 500.0);
	glEnd();
}

void drawTrafficLight(float pos_x, float pos_z, float angle)
{
	float length = 6.0;
	float head_height = 1.0;
	float head_length = head_height * 2;
	float column_radius = 0.4;
	float light_radius = head_height / 4;

	glPushMatrix();
	glTranslatef(pos_x, 0.0, pos_z);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);

	// Set the center of the circle
	glVertex3f(0.0, 0.0, 0.0);

	// Draw the triangles that make up the circle
	for (int i = 0; i <= 360; i++) {
		glVertex3f(column_radius * sin(angle_to_radian(i)), 0.0, column_radius * cos(angle_to_radian(i)));
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	// Set the center of the circle
	glVertex3f(0.0, length, 0.0);

	// Draw the triangles that make up the circle
	for (int i = 0; i <= 360; i++) {
		glVertex3f(column_radius * sin(angle_to_radian(i)), length, column_radius * cos(angle_to_radian(i)));
	}
	glEnd();

	glColor3f(38 / 255.0, 38 / 255.0, 38 / 255.0);
	glBegin(GL_TRIANGLE_STRIP);

	// Draw the triangles that make up the circle
	for (int i = 0; i <= 360; i++) {
		glVertex3f(column_radius * sin(angle_to_radian(i)), 0.0, column_radius * cos(angle_to_radian(i)));
		glVertex3f(column_radius * sin(angle_to_radian(i)), length, column_radius * cos(angle_to_radian(i)));
	}
	glEnd();

	glBegin(GL_QUADS);

	//bottom
	glVertex3f(-head_height / 2, length, -head_height / 2);
	glVertex3f(-head_height / 2, length, head_height / 2);
	glVertex3f(head_height / 2, length, head_height / 2);
	glVertex3f(head_height / 2, length, -head_height / 2);

	//top
	glVertex3f(-head_height / 2, length + head_length, -head_height / 2);
	glVertex3f(-head_height / 2, length + head_length, head_height / 2);
	glVertex3f(head_height / 2, length + head_length, head_height / 2);
	glVertex3f(head_height / 2, length + head_length, -head_height / 2);

	//left
	glVertex3f(-head_height / 2, length, -head_height / 2);
	glVertex3f(-head_height / 2, length, head_height / 2);
	glVertex3f(-head_height / 2, length + head_length, head_height / 2);
	glVertex3f(-head_height / 2, length + head_length, -head_height / 2);

	//right
	glVertex3f(head_height / 2, length, -head_height / 2);
	glVertex3f(head_height / 2, length, head_height / 2);
	glVertex3f(head_height / 2, length + head_length, head_height / 2);
	glVertex3f(head_height / 2, length + head_length, -head_height / 2);

	//back
	glVertex3f(head_height / 2, length, head_height / 2);
	glVertex3f(-head_height / 2, length, head_height / 2);
	glVertex3f(-head_height / 2, length + head_length, head_height / 2);
	glVertex3f(head_height / 2, length + head_length, head_height / 2);

	//front
	glVertex3f(head_height / 2, length, -head_height / 2);
	glVertex3f(-head_height / 2, length, -head_height / 2);
	glVertex3f(-head_height / 2, length + head_length, -head_height / 2);
	glVertex3f(head_height / 2, length + head_length, -head_height / 2);

	glEnd();
	for (int i = 1; i <= 3; ++i)
	{
		float r, g, b;
		glBegin(GL_TRIANGLE_FAN);
		if (i == 1)
		{
			r = 0.0;
			g = 1.0;
			b = 0.0;
		}
		else if (i == 2)
		{
			r = 1.0;
			g = 1.0;
			b = 0.0;
		}
		else {
			r = 1.0;
			g = 0.0;
			b = 0.0;
		}
		glColor3f(1, 1, 1);
		// Set the center of the circle
		glVertex3f(0.0, length + i * head_height / 2, head_height / 2 + 0.001);
		glColor3f(r, g, b);
		// Draw the triangles that make up the circle
		for (int j = 0; j <= 360; j++) {
			glVertex3f(light_radius * sin(angle_to_radian(j)), length + i * head_height / 2 + light_radius * cos(angle_to_radian(j)), head_height / 2 + 0.001);
		}
		glEnd();
	}
	glPopMatrix();

}

void display()
{
	float crowling_length = 2.0; //kaput geniþliði
	float baggage_length = 1.5; //bagaj geniþliði
	float top_length = 4.0; //tavan geniþliði
	float body_length = 10.0; //gövde geniþliði
	float body_height = 1.5; //gövde uzunluðu
	float window_height = 1.0; //cam uzunluðu
	float car_depth = 4.0; //araba derinliði

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawEnvironment();
	drawCar(crowling_length, baggage_length, top_length, body_length, body_height, window_height, car_depth, pos_x, pos_y, pos_z);

	//cross
	drawRoad(100.0, 10.0, 0.0, 0.0, 0.0);
	drawRoad(100.0, 10.0, 0.0, 0.0, 90.0);
	drawRoad(100.0, 10.0, 0.0, 0.0, 180.0);
	drawRoad(100.0, 10.0, 0.0, 0.0, 270.0);

	//circle
	drawRoad(200.0, 10.0, 100.0, -100.0, 270.0);
	drawRoad(200.0, 10.0, 100.0, -100.0, 180.0);
	drawRoad(200.0, 10.0, -100.0, 100.0, 90.0);
	drawRoad(200.0, 10.0, -100.0, 100.0, 0.0);

	//front side
	drawRoad(100.0, 10.0, 50.0, 0.0, 270.0);

	//front left
	drawRoad(50.0, 10.0, 50.0, 0.0, 90);
	drawRoad(100.0, 10.0, 0.0, -50.0, 0.0);

	//back right
	drawRoad(100.0, 10.0, -50.0, 0.0, 270.0);
	drawRoad(100.0, 10.0, 0.0, 50.0, 180.0);

	//back left
	drawRoad(50.0, 10.0, -50.0, 0.0, 90);
	drawRoad(50.0, 10.0, 0.0, -50.0, 180.0);

	//cross
	drawTrafficLight(5, 5, 0.0);
	drawTrafficLight(5, -5, 90.0);
	drawTrafficLight(-5, -5, 180.0);
	drawTrafficLight(-5, 5, 270.0);

	//cross Front
	drawTrafficLight(55, 5, 0.0);
	drawTrafficLight(55, -5, 90.0);
	drawTrafficLight(45, -5, 180.0);
	drawTrafficLight(45, 5, 270.0);

	drawTrafficLight(105, 5, 0.0);
	drawTrafficLight(95, -5, 180.0);
	drawTrafficLight(95, 5, 270.0);

	//cross back
	drawTrafficLight(-45, 5, 0.0);
	drawTrafficLight(-45, -5, 90.0);
	drawTrafficLight(-55, -5, 180.0);
	drawTrafficLight(-55, 5, 270.0);

	drawTrafficLight(-95, 5, 0.0);
	drawTrafficLight(-95, -5, 90.0);
	drawTrafficLight(-105, -5, 180.0);

	//cross left
	drawTrafficLight(5, -45, 0.0);
	drawTrafficLight(5, -55, 90.0);
	drawTrafficLight(-5, -55, 180.0);
	drawTrafficLight(-5, -45, 270.0);

	drawTrafficLight(5, -95, 0.0);
	drawTrafficLight(5, -105, 90.0);
	drawTrafficLight(-5, -95, 270.0);

	//cross right
	drawTrafficLight(5, 55, 0.0);
	drawTrafficLight(-5, 45, 180.0);
	drawTrafficLight(-5, 55, 270.0);

	drawTrafficLight(5, 95, 90.0);
	drawTrafficLight(-5, 95, 180.0);
	drawTrafficLight(-5, 105, 270.0);

	//front right
	drawTrafficLight(55, 95, 90.0);
	drawTrafficLight(45, 95, 180.0);
	drawTrafficLight(45, 105, 270.0);

	//front left
	drawTrafficLight(55, -45, 0.0);
	drawTrafficLight(55, -55, 90.0);
	drawTrafficLight(45, -45, 270.0);

	drawTrafficLight(105, -45, 0.0);
	drawTrafficLight(95, -55, 180.0);
	drawTrafficLight(95, -45, 270.0);

	//back right
	drawTrafficLight(-45, 55, 0.0);
	drawTrafficLight(-45, 45, 90.0);
	drawTrafficLight(-55, 45, 180.0);
	drawTrafficLight(-55, 55, 270.0);

	drawTrafficLight(-45, 95, 90.0);
	drawTrafficLight(-55, 95, 180.0);
	drawTrafficLight(-55, 105, 270.0);

	drawTrafficLight(-95, 55, 0.0);
	drawTrafficLight(-95, 45, 90.0);
	drawTrafficLight(-105, 45, 180.0);

	//front right apartmans
	drawApartment(3, 3, 67, 83, 270);
	drawApartment(4, 4, 69, 49, 270);
	drawApartment(3, 3, 67, 17, 270);

	drawApartment(3, 3, 83, 83, 90);
	drawApartment(2, 2, 85, 64, 90);
	drawApartment(2, 2, 85, 41, 90);
	drawApartment(3, 3, 83, 17, 90);

	drawApartment(2, 2, 35, 85, 90);
	drawApartment(1, 1, 37, 72, 90);
	drawApartment(3, 3, 33, 58, 90);
	drawApartment(4, 4, 31, 38, 90);
	drawApartment(2, 2, 35, 15, 180);

	drawApartment(3, 3, 17, 83, 270);
	drawApartment(2, 2, 15, 65, 270);

	//back right apartmans
	drawApartment(2, 2, -15, 65, 90);
	drawApartment(4, 4, -19, 81, 90);
	drawApartment(2, 2, -35, 65, 270);


	//back left
	drawApartment(5, 5, -75, 73, 180);
	drawApartment(5, 5, -75, 27, 0);
	drawApartment(3, 3, -75, -17, 0);
	drawApartment(2, 2, -85, -35, 270);
	drawApartment(2, 2, -85, -55, 270);
	drawApartment(2, 2, -85, -85, 270);
	drawApartment(2, 2, -65, -85, 180);
	drawApartment(2, 2, -45, -85, 180);
	drawApartment(4, 4, -20, -80, 90);
	drawApartment(2, 2, -45, -65, 0);
	drawApartment(2, 2, -65, -55, 90);
	drawApartment(2, 2, -65, -35, 90);

	//front left
	drawApartment(3, 3, 67, -17, 270);
	drawApartment(3, 3, 83, -17, 0);
	drawApartment(2, 2, 85, -35, 90);
	drawApartment(2, 2, 85, -65, 90);
	drawApartment(2, 2, 85, -85, 90);
	drawApartment(2, 2, 65, -85, 180);
	drawApartment(2, 2, 35, -85, 180);
	drawApartment(2, 2, 15, -85, 180);
	drawApartment(2, 2, 65, -65, 0);

	drawApartment(2, 2, 35, -65, 0);
	drawApartment(2, 2, 15, -65, 0);
	drawApartment(5, 5, 25, -21, 90);
	drawApartment(3, 3, 17, 17, 180);
	drawApartment(3, 3, -17, -17, 0);
	drawApartment(5, 5, -21, 21, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		locate_x + cam_distance * sin(angle_to_radian(angle_camera_h)) * cos(angle_to_radian(angle_camera_v)),
		pos_y + cam_distance * sin(angle_to_radian(angle_camera_v)),
		locate_z + cam_distance * cos(angle_to_radian(angle_camera_h)) * cos(angle_to_radian(angle_camera_v)),  // Eye position

		//locate_x + locate_cam_x * sin(angle_to_radian(angle_car)) + locate_cam_z * sin(angle_to_radian(angle_car + angle_camera)), 
		//pos_y + 5.0,
		//locate_z + locate_cam_x * cos(angle_to_radian(angle_car)) + locate_cam_z * cos(angle_to_radian(angle_car + angle_camera)),  // Eye position

		locate_x, 0.0, locate_z,  // Look-at point
		0.0, 1.0, 0.0); // Up vector
	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}


//for the car movement
void specialkey(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		for (int i = 0; i < 5; i++) {
			//std::cout << pos_x << std::endl;
			locate_x += 0.1 * sin(angle_to_radian(angle_car));
			locate_z += 0.1 * cos(angle_to_radian(angle_car));
			glutPostRedisplay();
		}
		break;
	case GLUT_KEY_DOWN:
		for (int i = 0; i < 5; i++) {
			//std::cout << pos_x << std::endl;
			locate_x -= 0.1 * sin(angle_to_radian(angle_car));
			locate_z -= 0.1 * cos(angle_to_radian(angle_car));
			glutPostRedisplay();
		}
		break;
	case GLUT_KEY_LEFT:
		for (int i = 0; i < 10; i++) {
			angle_car += 0.5;
			angle_camera_h += 0.5;
			//std::cout << angle_car << std::endl;
			glutPostRedisplay();
		}
		break;
	case GLUT_KEY_RIGHT:
		for (int i = 0; i < 10; i++) {
			angle_car -= 0.5;
			angle_camera_h -= 0.5;
			//std::cout << angle_car << std::endl;
			glutPostRedisplay();
		}
		break;
	case GLUT_KEY_PAGE_UP:
		if(cam_distance > 5)
		{
			for (int i = 0; i < 10; i++) {
				cam_distance -= 0.02; 
				glutPostRedisplay();
			}
		}
		break;
	case GLUT_KEY_PAGE_DOWN:
		if(cam_distance < 30)
		{
			for (int i = 0; i < 10; i++) {
				cam_distance += 0.02; 
				glutPostRedisplay();
			}
		}
		break;
	}
}

void init()
{
	glClearColor(0.75, 0.918, 0.9608, 1);
	glClearDepth(1.0f);                   
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("Kachoooooooooww");
	glutDisplayFunc(display);
	init();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, window_width / window_height, 0.1, 1000.0);
	glutPassiveMotionFunc(motion);
	glutSpecialFunc(specialkey);
	glutMainLoop();
}