#include <cassert>
#include <map>
#include "gl.h"
#include "glut.h"
#include <boost/assign.hpp>
#include "game.hpp"
#include "glut_core.hpp"
#include "keyboard_handler.hpp"
#include "keycodes.hpp"
#include "reshaper.hpp"

namespace ymse {

namespace {

// Bluarrrgh! Get rid of this global state!
game* global_g = 0;
reshaper* global_r = 0;
keyboard_handler* global_k = 0;

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


std::map<int, int> ascii_map = boost::assign::map_list_of<int, int>
	(' ', ymse::KEY_SPACE)
;

std::map<int, int> special_map = boost::assign::map_list_of<int, int>
	(GLUT_KEY_UP, ymse::KEY_UP)
	(GLUT_KEY_DOWN, ymse::KEY_DOWN)
	(GLUT_KEY_LEFT, ymse::KEY_LEFT)
	(GLUT_KEY_RIGHT, ymse::KEY_RIGHT)
;

void keyboard(const std::map<int, int>& m, int k, bool state) {
	if (!global_k) return;
	std::map<int, int>::const_iterator i = m.find(k);
	if (i == m.end()) return;
	global_k->key_event(i->second, state);
}

void keyboard_down(unsigned char key, int, int) {
	keyboard(ascii_map, key, true);
}

void keyboard_up(unsigned char key, int, int) {
	keyboard(ascii_map, key, false);
}

void keyboard_special_down(int key, int, int) {
	keyboard(special_map, key, true);
}

void keyboard_special_up(int key, int, int) {
	keyboard(special_map, key, false);
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

	glutDisplayFunc(&display);
	glutTimerFunc(100, &timercall, 0);
	glutReshapeFunc(&reshape);

	glutIgnoreKeyRepeat(true);
	glutKeyboardFunc(&keyboard_down);
	glutKeyboardUpFunc(&keyboard_up);
	glutSpecialFunc(&keyboard_special_down);
	glutSpecialUpFunc(&keyboard_special_up);
}

void glut_core::set_game_object(game* g) {
	global_g = g;
}

void glut_core::set_reshaper_object(reshaper* r) {
	global_r = r;
}

void glut_core::set_keyboard_handler(keyboard_handler* k) {
	global_k = k;
}

int glut_core::run() {
	glutMainLoop();

	return 0;
}

}

