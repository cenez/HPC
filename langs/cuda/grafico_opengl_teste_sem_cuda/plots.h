#ifndef DRAWS_BASE_H
#define DRAWS_BASE_H

#include "header_core.h"

void triangulo(float a[3], float b[3], float c[3], const color COR) {
	glColor3fv(COR);
	glBegin(GL_TRIANGLES);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glEnd();
}
void rect(float a[3], float b[3], float c[3], float d[3], const color COR) {
	glColor3fv(COR);
	glBegin(GL_QUADS);
	  glVertex3fv(a);
	  glVertex3fv(b);
	  glVertex3fv(c);
	  glVertex3fv(d);
	glEnd();
}
void cubo() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	rect(v1, v2, v3, v4, RED); // frente
	rect(v4, v3, v6, v5, BLUE);     // direita
	rect(v5, v8, v7, v6, YELLOW);  // back
	rect(v1, v8, v7, v2, GREEN);    // esquerda
	rect(v1, v4, v5, v8, ORANGE);  // topo
	rect(v2, v7, v6, v3, VIOLET);  // bottom
}
void tetraedro() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	triangulo(v2, v3, v0, WHITE);
	triangulo(v2, v7, v0, BLUE);
	triangulo(v7, v6, v0, GRAY);
	triangulo(v6, v3, v0, GREEN);
}
void about() {
	std::cout << "Empresa: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Modelo: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
}
void circulo(float z) {
	double raio = diametro / 2.0;
	glColor3fv(BLUE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLE_STRIP);// LINE_STRIP);
	for (int i = 0; raio > 0.0001; i++) {
		for (double angle = 0.0f; angle < 360; angle = angle + 2) {
			double rad = 2 * angle / 10;
			double x = raio * sin(rad);
			double y = raio * cos(rad);
			glVertex3f(x, y, z);
		}
		raio -= 0.01;
	}
	glEnd();
	glFlush();
}
void faixa(float z) {
	glColor3fv(WHITE);
	int i;
	float a = 2, b = 5, c = 2, d = 10, dd = 2; const int MAX = 200;
	float m = 1.5;
	float pa = 0.9, pb = 0.9, pc = 0.9, pd = 0.9;
	float bi = pa + 0.08, bj = pb + 0.08;
	GLfloat x1[4], x2[4], y1[4], y2[4];
	GLdouble BX1[MAX], BX2[MAX], BY1[MAX], BY2[MAX], t;
	//x1[0] = -pa*diametro/a; x1[1] = -pb*diametro/b; x1[2] = pc*diametro/b; x1[3] = pd*diametro/c;
	//y1[0] = diametro/b; y1[1] = m*diametro/b; y1[2] = m*diametro/b; y1[3] = diametro/b;
	//x2[0] = -bi*diametro / a; x2[1] = -pb*diametro/b; x2[2] = pc*diametro/b; x2[3] = bj*diametro/c;
	//y2[0] = diametro / d; y2[1] = m*diametro / d; y2[2] = m*diametro / d; y2[3] = diametro / d;

	float px0 = pa * diametro / a, px1 = 1.02 * px0, px2 = 1.04 * px0, px3 = 1.06 * px0;
	float py0 = diametro / b, py1 = 1.2 * py0, py2 = 1.2 * py0, py3 = py0 / 2;

	x1[0] = -px0; x1[1] = -px1; x1[2] = px2; x1[3] = px3;
	y1[0] = py0; y1[1] = py1; y1[2] = py2; y1[3] = py3;
	x2[0] = -px0 * 1.05; x2[1] = -px1; x2[2] = px2; x2[3] = px3 * 1.02;
	y2[0] = py0 / dd; y2[1] = py1 / dd; y2[2] = py2 / dd; y2[3] = py3 / (dd * 5);

	for (i = 0, t = 0; t <= 1; i++, t = t + 0.01) {
		BX1[i] = pow(1 - t, 3)*x1[0] + 3 * t*pow(1 - t, 2)*x1[1] + 3 * pow(t, 2)*(1 - t)*x1[2] + pow(t, 3)*x1[3];
		BY1[i] = pow(1 - t, 3)*y1[0] + 3 * t*pow(1 - t, 2)*y1[1] + 3 * pow(t, 2)*(1 - t)*y1[2] + pow(t, 3)*y1[3];
		BX2[i] = pow(1 - t, 3)*x2[0] + 3 * t*pow(1 - t, 2)*x2[1] + 3 * pow(t, 2)*(1 - t)*x2[2] + pow(t, 3)*x2[3];
		BY2[i] = pow(1 - t, 3)*y2[0] + 3 * t*pow(1 - t, 2)*y2[1] + 3 * pow(t, 2)*(1 - t)*y2[2] + pow(t, 3)*y2[3];
	}
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLE_STRIP);// GL_POINTS);
	for (i = 0; i < MAX-100; i++) {
		glVertex3d(BX1[i], BY1[i], z);
		glVertex3d(BX2[i], BY2[i], z);
	}
	glEnd(); glFlush();
}
void retangulo() {
	glColor3fv(GREEN);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glVertex3fv(v9);
	glVertex3fv(v10);
	glColor3fv(GREEN3);
	glVertex3fv(v11);
	glVertex3fv(v12);
	glEnd();
}
void losango() {
	glColor3fv(YELLOW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glVertex3fv(v13);
	glVertex3fv(v14);
	glVertex3fv(v15);
	glVertex3fv(v16);
	glEnd();
}
void estrela(float x1, float y1, float z, float len, const color COR) {
	float aj = 0.7;
	float sx = diametro / (90/len);
	float sy = diametro / (90/len);
	const float a1[] = {sx*(-2*aj   + x1), sy*(-3*aj + y1), z};  //inferior esq
	const float a2[] = {sx*( 2*aj   + x1), sy*(-3*aj + y1), z }; //inferior dir
	const float a3[] = {sx*( 0   + x1), sy*( 3 + y1), z }; //superior centro
	const float a4[] = {sx*(-2   + x1), sy*( 1 + y1), z }; //meio esq
	const float a5[] = {sx*( 2   + x1), sy*( 1 + y1), z }; //meio dir
	const float a6[] = {sx*( 2/3 + x1), sy*( 1 + y1), z }; //a4 a6 a5
	const float a7[] = {sx*( 1   + x1), sy*( 0 + y1), z }; //a1 a7 a5
	glColor3fv(COR);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLE_STRIP);

	glVertex3fv(a1);
	glVertex3fv(a3);
	glVertex3fv(a7);

	glVertex3fv(a7);
	glVertex3fv(a2);
	glVertex3fv(a4);

	glVertex3fv(a4);
	glVertex3fv(a5);
	glVertex3fv(a7);
	glEnd();
}
void estrelas(float z) {
	estrela(-8, 28, z, 0.8, WHITE);//1
	estrela(0, 0, z, 0.5, WHITE);//2
	estrela(4, 10, z, 0.3, WHITE);//3
	estrela(-60, -10, z, 0.4, WHITE);//4
	estrela(-90, -15, z, 0.3, WHITE);//5
	estrela(0, -80, z, 0.3, WHITE);//6
	estrela(-18, -40, z, 0.3, WHITE);//7
	estrela(-23, -23, z, 0.3, WHITE);//8
	estrela(-35, -60, z, 0.3, WHITE);//9
	estrela(-45, -70, z, 0.3, WHITE);//10
	estrela(-90, -100, z, 0.3, WHITE);//11
	estrela(90, -70, z, 0.3, WHITE);//12
	estrela(-30, -130, z, 0.3, WHITE);//13
	estrela(20, -105, z, 0.3, WHITE);//14
	estrela(-110, -68, z, 0.3, WHITE);//15
	estrela(-125, 2, z, 0.3, WHITE);//16
	estrela(70, -110, z, 0.3, WHITE);//17
	estrela(30, -43, z, 0.3, WHITE);//18
	estrela(128, -43, z, 0.3, WHITE);//19
	estrela(65, -13, z, 0.3, WHITE);//20
	estrela(-30, 8, z, 0.5, WHITE);//21
	estrela(-39, -33, z, 0.3, WHITE);//22
	estrela(-48, -37, z, 0.3, WHITE);//23
	estrela(-53, -43, z, 0.3, WHITE);//24
	estrela(-77, -57, z, 0.3, WHITE);//25
}

#endif
