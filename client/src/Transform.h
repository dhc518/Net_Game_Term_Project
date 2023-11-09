#pragma once
#include "stdafx.h"

class Camera;

namespace xform {
	/* WorldTransform�� ��ȯ, ��� X */
	glm::mat4 GetWorld();

	/* Camera class���� View Tansform ����*/
	glm::mat4 GetView(const Camera* camera);
	/* Camera class���� Projection Tansform ����*/
	glm::mat4 GetProj(const Camera* camera);

	/* shader�� �ִ� name�� mat4(1.0f) ����*/
	GLvoid Disable(const Shader& shader, const GLchar* name);
}