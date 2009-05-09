#include <cassert>
#include <GL/gl.h>
//#include <GL/glext.h>
//#include <GL/glu.h>
#include <GL/glut.h>
#include "game.hpp"
#include "glut_core.hpp"
#include "reshaper.hpp"

namespace ymse {

namespace {

// Bluarrrgh! Get rid of this global state!
game* global_g = 0;
reshaper* global_r = 0;

void display() {
	assert(global_g);
	global_g->render();
	glutSwapBuffers();
}

void timercall(int) {
	assert(global_g);
	global_g->tick();
	glutPostRedisplay();
	glutTimerFunc(10, &timercall, 0);
}

void reshape(int width, int height) {
	assert(global_r);
	global_r->reshape(width, height);
	glutPostRedisplay();
}

}

glut_core::glut_core() {
}

glut_core::~glut_core() {
}

void glut_core::init(int argc, const char *argv[]) {
	glutInit(&argc, (char**)argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA);

	glutInitWindowSize(640, 480);
	glutCreateWindow("Lul");

//	initGL();

	glutDisplayFunc(&display);
	glutTimerFunc(100, &timercall, 0);
	glutReshapeFunc(&reshape);

/*	
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
//	glutIdleFunc(idle);
	glutTimerFunc(SLEEP_TICKS, timercall, 0);
//	glutMouseFunc(buttons);
	glutPassiveMotionFunc(mouse);
	glutMouseFunc(click);
*/
}

void glut_core::set_game_object(game* g) {
	global_g = g;
}

void glut_core::set_reshaper_object(reshaper* r) {
	global_r = r;
}

int glut_core::run() {
	glutMainLoop();

	return 0;
}

}

