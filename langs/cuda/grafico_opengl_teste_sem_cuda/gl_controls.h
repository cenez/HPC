#ifndef GL_CONTROLS_BASE_H
#define GL_CONTROLS_BASE_H

#include "header_core.h"

void move_control(float angle, float movex, float movey, float cx, float cy, float cz) {
	glLoadIdentity();
	glTranslated(movex, movey, -40); // Setas: movex movey
	glRotated(angle, cx, cy, cz); // PG UP DOWN: angle
}
void redimensionar(const int W, const int H) {
	const float ASPECT = (float)W / (float)H; // proporcao p/ obj não desconfigurar
	const float ANGLE = 45.0;
	glViewport(0, 0, W, H);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(ANGLE, ASPECT, 0.1, 100.0); // Angulo, proporcao, zNear, zFar: Distancia em relacao ao observador
	glMatrixMode(GL_MODELVIEW);
}
void inicializar(const int W, const int H, const color BGRD) { // http://docs.gl/
	glClearColor(BGRD[0], BGRD[1], BGRD[2], 1.0); // define cor de fundo
	glLineWidth(1.5); // width das linhas
	glPointSize(3);
	redimensionar(W, H);
	glEnable(GL_DEPTH_TEST);
}

#endif
