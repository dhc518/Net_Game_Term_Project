#pragma once
#include "stdafx.h"

enum class Timer : GLint {
	LightRotation_Y,
};

namespace timer {
	/* ��ϵ� ��� Timer �ʱ�ȭ */
	GLvoid Init();

	/* �ش� Timer �ʱ�ȭ */
	GLvoid InitTimer(const Timer& timer);
	GLvoid InitTimer(GLboolean(*timerFunc)(GLint));

	/* �ش� Timer�� ���� �غ� ���·� ���� */
	GLvoid ReadyTimer(const Timer& timer);

	/* ��ϵ� ��� Timer Update */
	GLvoid Update();
	/* Enable Timer Update */
	GLvoid StartUpdate();
	/* Disable Timer Update */
	GLvoid StopUpdate();

	/* Timer Enable/Disable */
	GLvoid ToggleTimer(const Timer& timer);
	GLvoid ToggleTimer(GLboolean(*timerFunc)(GLint));
	/* Timer Enable */
	GLvoid EnableTimer(const Timer& timer);
	GLvoid EnableTimer(GLboolean(*timerFunc)(GLint));
	/* Timer Disable */
	GLvoid DisableTimer(const Timer& timer);
	GLvoid DisableTimer(GLboolean(*timerFunc)(GLint));
	
	/* FPS�� ����Ͽ� DeltaTime�� ��� */
	GLvoid CalculateFPS();
	/* ����� �ð�(DeltaTime) ��ȯ */
	GLfloat DeltaTime();

	GLvoid StartRecord();
	GLvoid PrintDuration();
}

