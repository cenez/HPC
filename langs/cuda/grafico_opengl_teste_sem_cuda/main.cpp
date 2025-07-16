#include "header_core.h"

const int W = 800, H = 600;

int main(void) {
	if (!glfwInit()) return -1; // Inicializar a biblioteca

	GLFWwindow* window = glfwCreateWindow(W, H, "Janela OpenGL", NULL, NULL); //Cria o modo janela e seu contexto OpenGL

	if (!window) { glfwTerminate(); return -1; }

	glfwMakeContextCurrent(window);	// Define o atual contexto com a janela window

	inicializar(W, H, BACKGROUND);

	set_vertices(10); // o padrao em data.h eh 10 jah

	float angle = 20.0f, movex = 0.0, movey = 0.0, cx = 0.0f, cy = 0.0f, cz = 0.0f;
	float Z = 5;
	while (!glfwWindowShouldClose(window)) { //Loop at� que o usuario feche a janela

		glfwPollEvents();		/* Poll para processar eventos: usam-se eventos, como uma tecla apertada, para tomada de decisao */
		eventos(window, &angle, &movex, &movey, &cx, &cy, &cz, W, H, &Z);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		/* apaga cor e informacao de profundidade, Render here */

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		redimensionar(width, height);
		move_control(angle, movex, movey, cx, cy, cz);
		/*
		cubo();
		*/
		//tetraedro();
		estrelas(Z);
		faixa(Z);
		circulo(Z);
		losango();
		retangulo();
		glfwSwapBuffers(window);		/* Troca front/back buffers */
		std::cout << "Z=" << Z << std::endl;
	}
	glfwTerminate();
	return 0;
}
