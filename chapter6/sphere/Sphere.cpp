#include <cmath>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>

#include "Sphere.h"

#define PI 3.14159265359f

using namespace std;

Sphere::Sphere() {
	init(48);
}

Sphere::Sphere(int prec) {
	init(prec);
}

float Sphere::toRadians(float degrees) {
	return (degrees * 2.0f * PI) / 360.0f;
}

void Sphere::init(int prec) {

	numVerticies = (prec + 1) * (prec + 1);
	numIndicies = prec * prec * 6;

	for (int i = 0; i < numVerticies; i++) verticies.push_back(glm::vec3());
	for (int i = 0; i < numVerticies; i++) normals.push_back(glm::vec3());
	for (int i = 0; i < numVerticies; i++) texCoords.push_back(glm::vec2());
	for (int i = 0; i < numIndicies; i++) indices.push_back(0);

	for (int i = 0; i <= prec; i++) {
		for (int j = 0; j <= prec; j++) {
			float y = (float)cos(toRadians(180.0f - i*180.0f/prec));
			float x = -(float)cos(toRadians(360.0f * j / prec)) * (float)abs(cos(asin(y)));
			float z = (float)sin(toRadians(360.0f * j / prec)) * (float)abs(cos(asin(y)));

			verticies[(prec + 1) * i + j] = glm::vec3(x, y, z);
			texCoords[(prec + 1) * i + j] = glm::vec2((float)j/prec, (float)i/prec);
			normals[(prec + 1) * i + j] = glm::vec3(x, y, z);
		}
	}

	for (int i = 0; i < prec; i++) {
		for (int j = 0; j < prec; j++) {
			indices[6 * (i * prec + j) + 0] = i * (prec + 1) + j;
			indices[6 * (i * prec + j) + 1] = i * (prec + 1) + j + 1;
			indices[6 * (i * prec + j) + 2] = (i+1) * (prec + 1) + j;
			indices[6 * (i * prec + j) + 3] = i * (prec + 1) + j + 1;
			indices[6 * (i * prec + j) + 4] = (i+1) * (prec + 1) + j + 1;
			indices[6 * (i * prec + j) + 5] = (i+1) * (prec + 1) + j;
		}
	}
}

int Sphere::getNumVerticies() { return numVerticies; }
int Sphere::getNumIndicies() { return numIndicies; }
std::vector<int> Sphere::getIndicies() { return indices; }
std::vector<glm::vec3> Sphere::getVerticies() { return verticies; }
std::vector<glm::vec2> Sphere::getTexCoords() { return texCoords; }
std::vector<glm::vec3> Sphere::getNormals() { return normals; }

