#include "spaceWar.h"
#include "ship.h"
#include "constants.h"


bool TextDX::initialize(Graphics *g, int height, bool bold, bool italic,
	const std::string &fontName)
{
	graphics = g;                   // the graphics system

	UINT weight = FW_NORMAL;
	if (bold)
		weight = FW_BOLD;

	// create DirectX font
	if (FAILED(D3DXCreateFont(graphics->get3Ddevice(), height, 0, weight, 1, italic,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, fontName.c_str(),
		&dxFont))) return false;
	// Create the tranformation matrix
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, NULL, NULL, 0.0f, NULL);

	return true;
}