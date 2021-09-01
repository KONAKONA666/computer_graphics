#pragma once

#include <cmath>
#include <vector>
#include <glm/glm.hpp>

class Torus {
private:
	int numVerticies;
	int numIndicies;

	int prec;
	float innerRadius;
	float outerRadius;

	std::vector<int> indicies;
	std::vector<glm::vec3> verticies;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> sTangents;
	std::vector<glm::vec3> tTangents;
	void init();
	float toRadians(float degrees);
public:
	Torus();
	Torus(float innerRadius, float outerRadius, int prec);

	int getNumVertices();
	int getNumIndices();
	std::vector<int> getIndices();
	std::vector<glm::vec3> getVertices();
	std::vector<glm::vec2> getTexCoords();
	std::vector<glm::vec3> getNormals();
	std::vector<glm::vec3> getStangents();
	std::vector<glm::vec3> getTtangents();
};