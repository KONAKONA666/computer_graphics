#include <cmath>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Torus.h"


using namespace std;

#define PI 3.14159265359f

Torus::Torus(): prec(48), innerRadius(0.5f), outerRadius(0.2f) {
	init();
}

Torus::Torus(float innerRadius, float outerRadius, int prec) : prec(prec), innerRadius(innerRadius), outerRadius(outerRadius) {
	init();
}

float Torus::toRadians(float degrees) { return (degrees * 2.0f * PI) / 360.0f;}

void Torus::init() {

	numVerticies = (prec + 1) * (prec + 1);
	numIndicies = 6 * (prec) * (prec);
	verticies = vector<glm::vec3>(numVerticies, glm::vec3());
	texCoords = vector<glm::vec2>(numVerticies, glm::vec2());
	normals = vector<glm::vec3>(numVerticies, glm::vec3());
	sTangents = vector<glm::vec3>(numVerticies, glm::vec3());
	tTangents = vector<glm::vec3>(numVerticies, glm::vec3());

	indicies = vector<int>(numIndicies, 0);

	for (int i = 0; i <= prec; i++) {
		float phi = toRadians(360.0f*i/prec);
		
		glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), phi, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::vec3 initPos(rMat*glm::vec4(0.0f, outerRadius, 0.0f, 1.0f));
		verticies[i] = initPos + glm::vec3(innerRadius, 0.0f, 0.0f);
		texCoords[i] = glm::vec2(0.0f, (float)i / float(prec));

		rMat = glm::rotate(glm::mat4(1.0f), phi + PI / 2.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		tTangents[i] = glm::vec3(rMat * glm::vec4(0.0f, -1.0f, 0.0f, 1.0f));
		sTangents[i] = glm::vec3(0.0f, 0.0f, -1.0f);
		normals[i] = glm::cross(sTangents[i], tTangents[i]);
	}

	for (int i = 1; i <= prec; i++) {
		for (int j = 0; j <= prec; j++) {
			float phi = toRadians(360.0f * (float)i/ prec);
			glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), phi, glm::vec3(0.0f, 1.0f, 0.0f));

			verticies[i * (prec + 1) + j] = glm::vec3(rMat*glm::vec4(verticies[j], 1.0f));
			texCoords[i * (prec + 1) + j] = glm::vec2((float)i*2.0f/prec, texCoords[j].t);

			rMat = glm::rotate(glm::mat4(1.0f), phi, glm::vec3(0.0f, 1.0f, 0.0f));
			sTangents[i * (prec + 1) + j] = glm::vec3(rMat * glm::vec4(sTangents[j], 1.0f));
			tTangents[i * (prec + 1) + j] = glm::vec3(rMat * glm::vec4(tTangents[j], 1.0f));

			normals[i * (prec + 1) + j] = glm::vec3(rMat * glm::vec4(normals[j], 1.0f));

		}
	}

	cout << "VERTICIES DONE" << endl;

	for (int i = 0; i < prec; i++) {
		for (int j = 0; j < prec; j++) {
			indicies[((i * prec + j) * 2) * 3 + 0] = i * (prec + 1) + j;
			indicies[((i * prec + j) * 2) * 3 + 1] = (i+1) * (prec+1) + j;
			indicies[((i * prec + j) * 2) * 3 + 2] = i * (prec + 1) + j+1;
			indicies[((i * prec + j) * 2+1) * 3 + 0] = i * (prec + 1) + j+1;
			indicies[((i * prec + j) * 2+1) * 3 + 1] = (i+1) * (prec + 1) + j;
			indicies[((i * prec + j) * 2+1) * 3 + 2] = (i+1) * (prec + 1) + j+1;
		}
	}

	cout << "INDICIES DONE" << endl;
}

int Torus::getNumVertices() { return numVerticies; }
int Torus::getNumIndices() { return numIndicies; }
std::vector<int> Torus::getIndices() { return indicies; }
std::vector<glm::vec3> Torus::getVertices() { return verticies; }
std::vector<glm::vec2> Torus::getTexCoords() { return texCoords; }
std::vector<glm::vec3> Torus::getNormals() { return normals; }
std::vector<glm::vec3> Torus::getStangents() { return sTangents; }
std::vector<glm::vec3> Torus::getTtangents() { return tTangents; }
