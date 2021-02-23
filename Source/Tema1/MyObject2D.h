#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

constexpr auto PI = 3.141592653589793f;

namespace MyObject2D
{
	// Create each object used
	Mesh* CreateArrow(std::string name, float length, float height, float peak, glm::vec3 color) {
		glm::vec3 corner = glm::vec3(0, 0, 0);

		std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner, color),
			VertexFormat(corner +glm::vec3(0, -height / 2, 0), color),
			VertexFormat(corner + glm::vec3(length, -height / 2, 0), color),
			VertexFormat(corner + glm::vec3(length, -(peak - height) / 2 - height / 2, 0), color),
			VertexFormat(corner + glm::vec3(length + peak * sqrt(2), 0, 0), color),
			VertexFormat(corner + glm::vec3(length, height / 2 + (peak - height) / 2, 0), color),
			VertexFormat(corner + glm::vec3(length, height / 2, 0), color),
			VertexFormat(corner + glm::vec3(0, height / 2, 0), color),
		};

		std::vector<unsigned short> indices =
		{
			0, 1, 2,
			7, 0, 2,
			7, 2, 6,
			3, 4, 5
		};
		Mesh* arrow = new Mesh(name);
		arrow->InitFromData(vertices, indices);
		return arrow;
	}

	Mesh* CreateBow(std::string name, float radius, float scaleFactor, glm::vec3 color) {
		glm::vec3 corner = glm::vec3(0, 0, 0);
		std::vector<VertexFormat> vertices;
		unsigned short size = 0;
		for (float rad = - PI / 2; rad <= PI / 2; rad += PI / 128) {
			vertices.push_back(VertexFormat(corner + glm::vec3(cos(rad) * radius, sin(rad) * radius * scaleFactor, 0), color));
			size++;
		}

		std::vector<unsigned short> indices;
		for (unsigned short i = 0; i < size; i++) {
			indices.push_back(i);
		}
		Mesh* bow = new Mesh(name);
		bow->SetDrawMode(GL_LINE_LOOP);
		bow->InitFromData(vertices, indices);
		return bow;
	}

	Mesh* CreateShuriken(std::string name, float cathetus, glm::vec3 color) {
		glm::vec3 corner = glm::vec3(0, 0, 0);
		std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner + glm::vec3(-cathetus, -cathetus,  0), color),//0
			VertexFormat(corner + glm::vec3(-cathetus, 0,  0), color),
			VertexFormat(corner + glm::vec3(0, 0,  0), color),
			VertexFormat(corner + glm::vec3(0, -cathetus,  0), color),
			VertexFormat(corner + glm::vec3(cathetus, -cathetus,  0), color),
			VertexFormat(corner + glm::vec3(cathetus, 0,  0), color),
			VertexFormat(corner + glm::vec3(cathetus, cathetus,  0), color),
			VertexFormat(corner + glm::vec3(0, cathetus,  0), color),
			VertexFormat(corner + glm::vec3(-cathetus, cathetus,  0), color),//8
		};
		std::vector<unsigned short> indices =
		{
			1, 0, 2,
			2, 3, 4,
			2, 5, 6,
			2, 7, 8
		};
		Mesh* shuriken = new Mesh(name);
		shuriken->InitFromData(vertices, indices);
		return shuriken;
	}

	Mesh* CreateBaloon(std::string name, float radius, float scaleFactor, glm::vec3 color) {
		std::vector<VertexFormat> vertices;
		unsigned short size = 0;
		for (float rad = 0; rad <= 2 * PI; rad += PI / 32) {
			vertices.push_back(VertexFormat(glm::vec3(cos(rad) * radius, sin(rad) * radius * scaleFactor, 0), color));
			size++;
		}

		std::vector<unsigned short> indices;
		for (unsigned short i = 0; i < size; i++) {
			indices.push_back(i % size);
			indices.push_back((i + size / 2) % size);
			indices.push_back((i + size / 2 + 1) % size);
		}
		Mesh* baloon = new Mesh(name);
		baloon->InitFromData(vertices, indices);
		return baloon;
	}

	Mesh* CreateMargins(std::string name, float width, float xLim, float yLim, glm::vec3 color) {
		std::vector<VertexFormat> vertices =
		{
			VertexFormat(glm::vec3(0, 0, 0), color),
			VertexFormat(glm::vec3(width, 0, 0), color),
			VertexFormat(glm::vec3(0, yLim, 0), color),
			VertexFormat(glm::vec3(width, yLim, 0), color),
			VertexFormat(glm::vec3(width, width, 0), color),
			VertexFormat(glm::vec3(xLim - width, width, 0), color),//5
			VertexFormat(glm::vec3(xLim - width, 0, 0), color),//6
			VertexFormat(glm::vec3(xLim, 0, 0), color),//7
			VertexFormat(glm::vec3(xLim, yLim, 0), color),//8
			VertexFormat(glm::vec3(xLim - width, yLim - width, 0), color),//9
			VertexFormat(glm::vec3(xLim - width, yLim, 0), color),//10
			VertexFormat(glm::vec3(width, yLim - width, 0), color),//11
		};
		
		std::vector<unsigned short> indices =
		{
			0, 1, 2,
			2, 1, 3,
			1, 6, 4,
			4, 6, 5,
			6, 7, 10,
			10, 7, 8,
			11, 9, 3,
			3, 9, 10
		};
		
		Mesh* margins = new Mesh(name);
		margins->InitFromData(vertices, indices);
		return margins;
	}

	Mesh* CreatePowerBar(std::string name, float length, glm::vec3 color) {
		std::vector<VertexFormat> vertices =
		{
			VertexFormat(glm::vec3(0, 0, 0), color),
			VertexFormat(glm::vec3(length, 0, 0), color),
			VertexFormat(glm::vec3(length, length / 2, 0), color),
			VertexFormat(glm::vec3(0, length / 2, 0), color),
		};
		std::vector<unsigned short> indices =
		{
			0, 1, 3,
			3, 1, 2
		};
		Mesh* powerBar = new Mesh(name);
		powerBar->InitFromData(vertices, indices);
		return powerBar;
	}

	Mesh* CreateSharingan(std::string name, float radius) {
		std::vector<VertexFormat> vertices;
		std::vector<unsigned short> indices;
		unsigned short size = 0;
		glm::vec3 red = glm::vec3(1, 0, 0);
		glm::vec3 black = glm::vec3(0, 0, 0);
		for (float rad = 0; rad <= 2 * PI; rad += PI / 32) {
			vertices.push_back(VertexFormat(glm::vec3(cos(rad) * radius * 0.15f, sin(rad) * radius * 0.15f, 0), red));
			size++;
		}

		for (unsigned short i = 0; i < size; i++) {
			indices.push_back(i % size);
			indices.push_back((i + size / 2) % size);
			indices.push_back((i + size / 2 + 1) % size);
		}

		//0
		vertices.push_back(VertexFormat(glm::vec3(cos(PI / 4) * radius * 0.5f, sin(PI / 4) * radius * 0.5f, 0), black));
		//1
		vertices.push_back(VertexFormat(glm::vec3(cos(PI - PI / 4) * radius* 0.5f, sin(PI - PI / 4) * radius* 0.5f, 0), black));
		//2
		vertices.push_back(VertexFormat(glm::vec3(cos(PI + PI / 4) * radius* 0.5f, sin(PI + PI / 4) * radius* 0.5f, 0), black));
		//3
		vertices.push_back(VertexFormat(glm::vec3(cos(2 * PI - PI / 4) * radius* 0.5f, sin(2 * PI - PI / 4) * radius* 0.5f, 0), black));
		//4
		vertices.push_back(VertexFormat(glm::vec3(cos(PI / 4) * radius * 1.2f, sin(PI / 4) * radius * 0.5f, 0), black));
		//5
		vertices.push_back(VertexFormat(glm::vec3(cos(PI - PI / 4) * radius * 0.5f, sin(PI - PI / 4) * radius * 1.2f, 0), black));
		//6
		vertices.push_back(VertexFormat(glm::vec3(cos(PI + PI / 4) * radius * 1.2f, sin(PI + PI / 4) * radius * 0.5f, 0), black));
		//7
		vertices.push_back(VertexFormat(glm::vec3(cos(2 * PI - PI / 4) * radius * 0.5f, sin(2 * PI - PI / 4) * radius * 1.2f, 0), black));

		indices.push_back(size);
		indices.push_back(size+1);
		indices.push_back(size + 3);
		indices.push_back(size + 1);
		indices.push_back(size + 2);
		indices.push_back(size + 3);
		//1
		indices.push_back(size + 4);
		indices.push_back(size + 1);
		indices.push_back(size + 2);
		//2
		indices.push_back(size + 5);
		indices.push_back(size + 2);
		indices.push_back(size + 3);
		//3
		indices.push_back(size + 6);
		indices.push_back(size + 3);
		indices.push_back(size + 0);
		//4
		indices.push_back(size + 7);
		indices.push_back(size + 0);
		indices.push_back(size + 1);
		size += 8;
		int begin = size;
		for (float rad = 0; rad <= 2 * PI; rad += PI / 32) {
			vertices.push_back(VertexFormat(glm::vec3(cos(rad) * radius * 0.93f, sin(rad) * radius * 0.93f, 0), red));
			size++;
		}

		for (unsigned short i = begin; i < size; i++) {
			indices.push_back(i % (size - begin) + begin);
			indices.push_back((i + (size - begin) / 2) % (size - begin) + begin);
			indices.push_back((i + (size - begin) / 2 + 1) % (size - begin) + begin);
		}
		begin = size;
		for (float rad = 0; rad <= 2 * PI; rad += PI / 32) {
			vertices.push_back(VertexFormat(glm::vec3(cos(rad) * radius, sin(rad) * radius, 0), black));
			size++;
		}

		for (unsigned short i = begin; i < size; i++) {
			indices.push_back(i % (size - begin) + begin);
			indices.push_back((i + (size - begin) / 2) % (size - begin) + begin);
			indices.push_back((i + (size - begin) / 2 + 1) % (size - begin) + begin);
		}

		Mesh* sharingan = new Mesh(name);
		sharingan->InitFromData(vertices, indices);
		return sharingan;
	}

	Mesh *CreateBaloonLine(std::string name, float radius) {
		glm::vec3 color = glm::vec3(1, 1, 1);
		float d1 = radius / 5;
		std::vector<VertexFormat> vertices =
		{
			VertexFormat(glm::vec3(0, 0, 0), color),
			VertexFormat(glm::vec3(-d1, -d1, 0), color),
			VertexFormat(glm::vec3(d1, -2 * d1, 0), color),
			VertexFormat(glm::vec3(-d1, -4 * d1, 0), color),
			VertexFormat(glm::vec3(d1, -6 * d1, 0), color),
		};
		std::vector<unsigned short> indices =
		{
			0, 1, 2, 3, 4
		};
		Mesh* line = new Mesh(name);
		line->InitFromData(vertices, indices);
		line->SetDrawMode(GL_LINE_STRIP);
		return line;
	}
}

