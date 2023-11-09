#pragma once
#include "stdafx.h"

namespace shd {
	/* ��ϵ� ��� Shader ���� */
	GLvoid Init();

	GLint GetShaderProgram(const Shader& shader);
	GLvoid Use(const Shader& shader);

	/* shader�� �ִ� name�� mat4 ���� */
	GLvoid SetShader(const Shader& shader, const GLchar* name, const glm::mat4& transform);
	/* shader�� �ִ� name�� vec3 ���� */
	GLvoid SetShader(const Shader& shader, const GLchar* name, const glm::vec3& value);
	/* shader�� �ִ� name�� GLfloat ���� */
	GLvoid SetShader(const Shader& shader, const GLchar* name, const GLfloat& value);
}