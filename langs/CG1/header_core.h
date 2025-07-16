#ifndef CORE_BASE_H
#define CORE_BASE_H

#include <iostream>
#include <thread>
#include <math.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include "colors.h"
#include "gl_controls.h"
#include "data.h"
#include "plots.h"

float compara_float(const float A, const float B, float erro = 0.005f) { return (fabs(A - B) < erro) ? 1 : 0; }

void eventos(
	GLFWwindow* window,
	float* angle,
	float* movex,
	float* movey,
	float* cx,
	float* cy,
	float* cz,
	int xlen,
	int ylen,
	float *Z) {
	const int DELAY = 10;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	else if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS) { // Seta PG UP
		*angle = (*angle == 1) ? 360 : *angle - 1;
		std::cout << "Angulo Rotate: " << (*angle) << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY)); //Windows: Sleep(DELAY); LINUX: usleep(DELAY);
	}
	else if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS) { // Seta PG Down
		*angle = (*angle == 360) ? 1 : *angle + 1;
		std::cout << "Angulo Rotate: " << (*angle) << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY)); //Windows: Sleep(DELAY); LINUX: usleep(DELAY);
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) { // Seta esquerda
		*movex = (*movex == -xlen) ? -xlen : *movex - 1;
		std::cout << "Movex " << (*movex) << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY)); //Windows: Sleep(DELAY); LINUX: usleep(DELAY);
	}
	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) { // Seta direita
		*movex = (*movex == xlen) ? xlen : *movex + 1;
		std::cout << "Movex " << (*movex) << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY)); //Windows: Sleep(DELAY); LINUX: usleep(DELAY);
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) { // Seta Down
		*movey = (*movey == -ylen) ? -ylen : *movey - 1;
		std::cout << "Movey " << (*movey) << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY)); //Windows: Sleep(DELAY); LINUX: usleep(DELAY);
	}
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) { // Seta UP
		*movey = (*movey == ylen) ? ylen : *movey + 1;
		std::cout << "Movey " << (*movey) << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY)); //Windows: Sleep(DELAY); LINUX: usleep(DELAY);
	}
	else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		*cx = compara_float(*cx, 0);
		std::cout << "cx: " << *cx << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(200)); //Windows: Sleep(200); LINUX: usleep(200);
	}
	else if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
		*cy = compara_float(*cy, 0);
		std::cout << "cy: " << *cy << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(200)); //Windows: Sleep(200); LINUX: usleep(200);
	}
	else if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		*cz = compara_float(*cz, 0);
		std::cout << "cz: " << *cz << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(200)); //Windows: Sleep(200); LINUX: usleep(200);
	}
	else if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS) {
		set_vertices(diametro+2);
		std::cout << "+: " << *cz << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(200)); //Windows: Sleep(200); LINUX: usleep(200);
	}
	else if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
		set_vertices(diametro - 2);
		std::cout << "-: " << *cz << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(200)); //Windows: Sleep(200); LINUX: usleep(200);
	}
	else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		*Z = *Z + 0.1;
		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
	}
	else if (glfwGetKey(window, GLFW_KEY_DELETE) == GLFW_PRESS) {
		*Z = *Z - 0.1;
		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
	}
}

#endif
