//  Module:             Gameplay Programming
//  Assignment1:        Ships and Shapes
//  Student Name:       Steven Koe
//  Student Number:     S10181536D

#ifndef _TEXTDX_H               // Prevent multiple definitions if this 
#define _TEXTDX_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <string>
#include "constants.h"
#include "graphics.h"

class Text
{
private:
	Graphics    *graphics;
	COLOR_ARGB  color;          // font color (a,r,g,b)
	LPD3DXFONT  dxFont;
	RECT        fontRect;       // text rectangle
	D3DXMATRIX  matrix;			// matrix to rotate the text
	float       angle;		// rotation angle of text in radians
	double		height;
	double		width;

public:
	Text();
	~Text();
	// Initialize font
	// Pre: *g points to Graphics object
	//      height = height in pixels
	//      bold = true/false
	//      italic = true/false
	//      &fontName = name of font to use
	virtual bool initialize(Graphics *g, int height, bool bold, bool italic, const std::string &fontName);

	// Print at x,y. Call between spriteBegin()/spriteEnd()
	// Return 0 on fail, height of text on success
	// Pre: &str contains text to display
	//      x, y = screen location
	virtual int print(const std::string &str, int x, int y);

	// Print inside rect using format. Call between spriteBegin()/spriteEnd()
	// Return 0 on fail, height of text on success
	// Pre: &str = text to display
	//      &rect = rectangular region
	//      format = format specifier
	virtual int print(const std::string &str, RECT &rect, UINT format);

	// Return rotation angle in degrees.
	virtual float getDegrees() { return angle * (180.0f / (float)PI); }


	// Return rotation angle in radians.
	virtual float getRadians() { return angle; }

	// Returns font color
	virtual COLOR_ARGB getFontColor() { return color; }

	// Set rotation angle in degrees.
	// 0 degrees is up. Angles progress clockwise.
	virtual void setDegrees(float deg) { angle = deg * ((float)PI / 180.0f); }

	// Set rotation angle in radians.
	// 0 radians is up. Angles progress clockwise.
	virtual void setRadians(float rad) { angle = rad; }

	// Set the font color. Use SETCOLOR_ARGB macro or colors from graphicsNS::
	virtual void setFontColor(COLOR_ARGB c) { color = c; }

	// Release resources
	virtual void onLostDevice();

	// Restore resources
	virtual void onResetDevice();

	// Get Height
	double getheight();

	// Get Length
	double getwidth();

};

#endif