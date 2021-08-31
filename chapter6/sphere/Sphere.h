#pragma once
#include <cmath>
#include <vector>
#include <glm/glm.hpp>

class Sphere
{
private:
	int numVerticies;
	int numIndicies;

	std::vector<int> indices;

	std::vector<glm::vec3> verticies;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;

	void init(int);
	float toRadians(float degrees);

public:

	Sphere(int prec);
	Sphere();

	int getNumVerticies();
	int getNumIndicies();

	std::vector<int> getIndicies();

	std::vector<glm::vec3> getVerticies();
	std::vector<glm::vec3> getNormals();
	std::vector<glm::vec2> getTexCoords();

	

};