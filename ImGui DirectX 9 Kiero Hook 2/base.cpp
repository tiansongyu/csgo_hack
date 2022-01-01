#include "base.h"


int AC::Base::WindowWidth = 0;
int AC::Base::WindowHeigth = 0;
Matrixf* AC::Base::MatrixAddress = nullptr;

bool WorldToScreen(vec pos3D, vec* pos2D)
{
	float mX = (float)AC::Base::WindowWidth / 2.0f;
	float mY = (float)AC::Base::WindowHeigth / 2.0f;
	float x = AC::Base::MatrixAddress->transformx(pos3D);
	float y = AC::Base::MatrixAddress->transformy(pos3D);
	float z = AC::Base::MatrixAddress->transformz(pos3D);
	float w = AC::Base::MatrixAddress->transformw(pos3D);

	if (w < 0.01f)
		return false;
	pos2D->x = mX + (mX * x / w) + x / w;
	pos2D->y = mY - (mY * y / w) + y / w;
	pos2D->z = 0;
	return true;

}