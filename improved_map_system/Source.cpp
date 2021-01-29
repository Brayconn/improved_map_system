#include <windows.h>
#include <cstring>
#include <cstdio>
#include "Header.h"
extern "C"
{
#include "cave_story.h"
#include "mod_loader.h"
}

const int tileTypeEntries = 256;
//Map system tile for the corrseponding byte value
static int tileTypes[tileTypeEntries]
{
	0,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	1,3,3,2,1,3,3,3,3,3,3,3,3,3,3,3,
	2,1,1,2,2,1,1,2,3,3,3,3,3,3,3,3,
	1,3,3,2,3,3,3,3,3,3,3,3,3,3,3,3,
	2,1,1,2,2,1,1,2,3,3,3,3,3,3,3,3,
	1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
};

//Rects for all map system tiles
static RECT tileTypeRects[4] = 
{
{240, 24, 241, 25},
{241, 24, 242, 25},
{242, 24, 243, 25},
{243, 24, 244, 25}
};

//Draws one line of the minimap
void DrawMiniMapLine(int line, int scale)
{
	ModLoader_PrintDebug("Drawing map line %d:\n", line);
	for (int i = 0; i < CS_level_width; i++)
	{
		unsigned char tileType = GetTileType(i * scale, line * scale);
		ModLoader_PrintDebug("%d - %d\n", i, tileType);
		DrawSpriteOntoSurface(i, line, &tileTypeRects[tileTypes[tileType]], SURFACE_ID_MAP, SURFACE_ID_TEXT_BOX);
	}
	ModLoader_PrintDebug(", Complete!\n");
}

//Check whether ESC was hit/display the ESC menu
int WasESCHit()
{
	//ModLoader_PrintDebug("Checking to open esc menu\n");
	if (CS_input_bitfield_held & 0x8000)
	{
		int escStatus = Call_Escape(CS_hWnd);
		if (escStatus == 0 || escStatus == 2)
			return escStatus;
	}
	return 1;
}

//How many sqaures to draw before the full size one
int stepCount;
//DestX/DestY in pixels
int DrawBlackSquare(bool shown, int destX, int destY)
{
	ModLoader_PrintDebug("%sing map system background...\n", shown ? "Grow" : "Hid");
	for (int i = shown ? 0 : stepCount; shown ? i <= stepCount : i >= 0; shown ? i++ : i--) //TODO move these to settings file
	{
		GetKeys();
		int escStatus = WasESCHit();
		if (escStatus != 1)
			return escStatus;

		//Print screen (important for fading to work)
		CS_DrawSprite_NoTransparency(&CS_clip_rect_common, 0, 0, &CS_clip_rect_common, SURFACE_ID_SCREEN_GRAB);

		RECT DrawingArea;
		DrawingArea.left = (CS_clip_rect_common.right/2) - i * destX / (stepCount*2);
		DrawingArea.top = (CS_clip_rect_common.bottom/2) - i * destY / (stepCount * 2);
		DrawingArea.right = (CS_clip_rect_common.right / 2) + i * destX / (stepCount * 2);
		DrawingArea.bottom = (CS_clip_rect_common.bottom / 2) + i * destY / (stepCount * 2);
		ModLoader_PrintDebug("%d, %d, %d, %d\n", DrawingArea.left, DrawingArea.top, DrawingArea.right, DrawingArea.bottom);
		CS_DrawColourFill(&DrawingArea, 0);

		DisplayMapName(1);
		DrawFPS();

		if (!DrawWindow(CS_hWnd))
			return 0;
	}
	return 1;
}

//Size of the border around the map system
int borderSize;
//How many frames to wait before displaying quote's position
int youAreHereBlinkDelay;
//How many frames to display quote's position
int youAreHereBlinkTime;
//What pixel to use for quote's position
RECT youAreHerePixelRect = { 0, 57, 1, 58 };
//Amount of lines to draw per check for ESC
int linesPerLoop;
//Main Minimap draw function
int DrawMiniMap()
{
	ModLoader_PrintDebug("About to draw entire map...\n");
	
	//Shrinking the map scale
	int scale = 1;
	int scaledx = CS_level_width;
	int scaledy = CS_level_height;
	while (scaledx / scale > CS_clip_rect_common.right || scaledy / scale > CS_clip_rect_common.bottom)
		scale++;
	scaledx /= scale;
	scaledy /= scale;
	ModLoader_PrintDebug("Map being displayed at 1/%d scale. %dx%d -> %dx%d\n",
		scale, CS_level_width, CS_level_height, scaledx, scaledy);

	//Grow/Draw the background
	int blackSquareDraw = DrawBlackSquare(true, scaledx, scaledy);
	if (blackSquareDraw != 1)
		return blackSquareDraw;
	
	//Clears the map system display from the previous time
	RECT rcMiniMap = { 0, 0, scaledx, scaledy };
	DrawFilledRectangleOntoSurface(&rcMiniMap, 0, SURFACE_ID_MAP);
	
	//Black border around map system
	RECT Border = {
		(CS_clip_rect_common.right / 2) - (scaledx / 2) - borderSize,
		(CS_clip_rect_common.bottom / 2) - (scaledy / 2) - borderSize, 
		(CS_clip_rect_common.right / 2) + (scaledx / 2) + borderSize,
		(CS_clip_rect_common.bottom / 2) + (scaledy / 2) + borderSize
	};
	//ModLoader_PrintDebug("%d,%d,%d,%d\n", Border.left, Border.top, Border.right, Border.bottom);


	int youAreHereX = ((*QuoteX / 512 + 8) / 16) / scale;
	int youAreHereY = ((*QuoteY / 512 + 8) / 16) / scale;	
	int youAreHereBlinkTimer = 0;
	int lineNumber = 0;
	while (1)
	{
		GetKeys();
		//This is the part that lets you exit the map system
		if (CS_input_bitfield_newly_pressed & (*CancelKey | *OkKey))
			break;

		int escStatus = WasESCHit();
		if (escStatus != 1)
			return escStatus;

		//Draw the background (important for fading out)
		CS_DrawSprite_NoTransparency(&CS_clip_rect_common, 0, 0, &CS_clip_rect_common, SURFACE_ID_SCREEN_GRAB);

		CS_DrawColourFill(&Border, 0);

		for(int i = 0; lineNumber < scaledy && i < linesPerLoop; i++)
			DrawMiniMapLine(lineNumber++, scale);

		CS_DrawSprite_WithTransparency(&CS_clip_rect_common,
			Border.left + borderSize,
			Border.top + borderSize,
			&rcMiniMap, SURFACE_ID_MAP);

		if (youAreHereBlinkTimer > youAreHereBlinkDelay)
		{
			CS_DrawSprite_WithTransparency(&CS_clip_rect_common,
				youAreHereX + Border.left + borderSize,
				youAreHereY + Border.top + borderSize,
				&youAreHerePixelRect, SURFACE_ID_TEXT_BOX);
		}
		youAreHereBlinkTimer = (youAreHereBlinkTimer + 1 > youAreHereBlinkDelay + youAreHereBlinkTime) ? 1 : youAreHereBlinkTimer + 1;

		DisplayMapName(1);
		DrawFPS();

		if (!DrawWindow(CS_hWnd))
			return 0;
	}

	//Shrink/remove the background
	int blackSquareUnDraw = DrawBlackSquare(false, scaledx, scaledy);
	if (blackSquareUnDraw != 1)
		return blackSquareUnDraw;

	return 1;
}

const char* IndexMap = "IndexMap.bin";

#pragma warning( disable: 4996) //_CRT_SECURE_NO_WARNINGS
extern "C" void InitMod()
{
	stepCount = ModLoader_GetSettingInt("stepCount", 8);
	
	borderSize = ModLoader_GetSettingInt("borderSize", 1);

	youAreHereBlinkDelay = ModLoader_GetSettingInt("youAreHereBlinkDelay", 8);
	youAreHereBlinkTime = ModLoader_GetSettingInt("youAreHereBlinkTime", 8);

	linesPerLoop = ModLoader_GetSettingInt("linesPerLoop", 2);

	//Prepare path to the file
	char* strbuff = new char[strlen(ModLoader_path_to_dll) + strlen(IndexMap)]();
	strcpy(strbuff, ModLoader_path_to_dll);
	strcat(strbuff, IndexMap);
	ModLoader_PrintDebug("%s\n", strbuff);

	FILE* file = fopen(strbuff, "rb");
	if (file)
	{
		//load if exists
		ModLoader_PrintDebug("tileTypes length should == %d", tileTypeEntries * sizeof(int));
		fread(tileTypes, sizeof(int), tileTypeEntries, file);
		fclose(file);
		ModLoader_PrintDebug("tileTypes[1] = %d\n", tileTypes[1]);
	}
	else
	{
		//otherwise create with defaults
		ModLoader_PrintDebug("Error opening \"%s\"!\nGenerating file instead...", strbuff);
		file = fopen(strbuff, "wb");
		fwrite(tileTypes, sizeof(int), tileTypeEntries, file);
		fclose(file);
		ModLoader_PrintDebug("File created succesfully!");
	}

	ModLoader_WriteJump((DWORD*)0x004143C0, &DrawMiniMapLine);
	ModLoader_WriteJump((DWORD*)0x00414640, &DrawMiniMap);
}
#pragma warning( default: 4996)