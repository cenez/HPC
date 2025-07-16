#ifndef DATA_BASE_H
#define DATA_BASE_H
#define MAX_DIAMETRO 10

float v0[3], v1[3], v2[3], v3[3], v4[3], v5[3], v6[3], v7[3], v8[3]; // Vertices
float v9[3], v10[3], v11[3], v12[3]; // Retangulo v9 + v10 v11 v12
float v13[3], v14[3], v15[3], v16[3]; // Losango

float set_vertices(float _diametro); // Prototipo

float diametro = set_vertices(MAX_DIAMETRO); // Um diametro maximo e default para o desenho

void setV(float *v, float x, float y, float z) { v[0] = x; v[1] = y; v[2] = z; }

float set_vertices(float _diametro) {
	float r = _diametro / 2.0;

	setV(v0, 0, r, 0);

	setV(v1, -r, r, r);
	setV(v2, -r, -r, r);
	setV(v3, r, -r, r);
	setV(v4, r, r, r);

	setV(v5, r, r, -r);
	setV(v6, r, -r, -r);
	setV(v7, -r, -r, -r);
	setV(v8, -r, r, -r);

	setV(v9, -r*2.2, r*1.3, 0.0); // ponto sup esq
	setV(v10, -r*2.2, -r * 1.3, 0.0); // ponto inf esq
	setV(v11, r*2.2, -r * 1.3, 0.0); // ponto inf dir
	setV(v12, r*2.2, r*1.3, 0.0); // ponto sup dir


	setV(v13, -r * 2, 0.0, 0.0); // ponto sup esq
	setV(v14, 0.0, -r * 1.2, 0.0); // ponto inf esq
	setV(v15, r * 2, 0.0, 0.0); // ponto inf dir
	setV(v16, 0.0, r*1.2, 0.0); // ponto sup dir

	return diametro = _diametro;
}

#endif
