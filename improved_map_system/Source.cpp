#include <windows.h>
#include "Header.h"
extern "C"
{
#include "cave_story.h"
#include "mod_loader.h"
}

//Map system tile for the corrseponding byte value
static int tileTypes[256] =
{
	0,
	1,
	1,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	1,
	3,
	3,
	2,
	1,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	2,
	1,
	1,
	2,
	2,
	1,
	1,
	2,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	1,
	3,
	3,
	2,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	2,
	1,
	1,
	2,
	2,
	1,
	1,
	2,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	1,
	1,
	1,
	1,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	1,
	1,
	1,
	1,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
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
		ModLoader_PrintDebug("\r%d", i);
		DrawSpriteOntoSurface(i, line, &tileTypeRects[tileTypes[GetTileType(i * scale, line * scale)]], SURFACE_ID_MAP, SURFACE_ID_TEXT_BOX);
	}
	ModLoader_PrintDebug(", Complete!\n");
}

/*
void DrawMiniMapLine(int line, int step)
{
	RECT rcLevel[4]; // [esp+28h] [ebp-50h]
	rcLevel[0].left = 240;
	rcLevel[0].top = 24;
	rcLevel[0].right = 241;
	rcLevel[0].bottom = 25;
	rcLevel[1].left = 241;
	rcLevel[1].top = 24;
	rcLevel[1].right = 242;
	rcLevel[1].bottom = 25;
	rcLevel[2].left = 242;
	rcLevel[2].top = 24;
	rcLevel[2].right = 243;
	rcLevel[2].bottom = 25;
	rcLevel[3].left = 243;
	rcLevel[3].top = 24;
	rcLevel[3].right = 244;
	rcLevel[3].bottom = 25;
	
	for (int x = 0; CS_level_width > x; ++x)
	{
		BYTE a =  (x, line);
		if (a)
		{
			if (a != 68
				&& a != 1
				&& a != 64
				&& a != -128
				&& a != -127
				&& a != -126
				&& a != -125
				&& a != 81
				&& a != 82
				&& a != 85
				&& a != 86
				&& a != 2
				&& a != 96
				&& a != 113
				&& a != 114
				&& a != 117
				&& a != 118
				&& a != -96
				&& a != -95
				&& a != -94
				&& a != -93)
			{
				if (a != 67
					&& a != 99
					&& a != 80
					&& a != 83
					&& a != 84
					&& a != 87
					&& a != 96
					&& a != 112
					&& a != 115
					&& a != 116
					&& a != 119)
				{
					DrawSpriteOntoSurface(x, line, &rcLevel[3], 9, 26);
				}
				else
				{
					DrawSpriteOntoSurface(x, line, &rcLevel[2], 9, 26);
				}
			}
			else
			{
				DrawSpriteOntoSurface(x, line, &rcLevel[1], 9, 26);
			}
		}
		else
		{
			DrawSpriteOntoSurface(x, line, rcLevel, 9, 26);
		}
	}
	return;
}
*/

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
	ModLoader_PrintDebug("%d,%d,%d,%d\n", Border.left, Border.top, Border.right, Border.bottom);


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

/*Old function by SIM
void createHook(DWORD *hookLocation, void *toHook)
{
	ModLoader_PrintDebug("Creating pointer to %x at %x...\n", toHook, hookLocation);

	void *jmp = (int*)0xE9;
	int relativeHook = (int)toHook - ((int)hookLocation + 5);

	WriteProcessMemory(GetCurrentProcess(), hookLocation, &jmp, 1, NULL);
	WriteProcessMemory(GetCurrentProcess(), (hookLocation + 1), &relativeHook, 4, NULL);
}
*/

extern "C" void InitMod()
{
	stepCount = ModLoader_GetSettingInt("stepCount", 8);
	
	borderSize = ModLoader_GetSettingInt("borderSize", 1);

	youAreHereBlinkDelay = ModLoader_GetSettingInt("youAreHereBlinkDelay", 8);
	youAreHereBlinkTime = ModLoader_GetSettingInt("youAreHereBlinkTime", 8);

	linesPerLoop = ModLoader_GetSettingInt("linesPerLoop", 2);

	ModLoader_WriteJump((DWORD*)0x004143C0, &DrawMiniMapLine);
	ModLoader_WriteJump((DWORD*)0x00414640, &DrawMiniMap);
}

#pragma region OLD CODE
/*
//----- (0809209E) --------------------------------------------------------
signed int MiniMapLoop()
{
	signed int v0; // eax
	signed int v2; // eax
	signed int v3; // eax
	RECT my_rect; // [esp+2Ch] [ebp-4Ch]
	RECT rcMiniMap; // [esp+3Ch] [ebp-3Ch]
	RECT rcView; // [esp+4Ch] [ebp-2Ch]
	int f; // [esp+5Ch] [ebp-1Ch]
	int line; // [esp+60h] [ebp-18h]
	int my_x; // [esp+64h] [ebp-14h]
	int my_y; // [esp+68h] [ebp-10h]
	unsigned __int8 my_wait; // [esp+6Fh] [ebp-9h]

	my_rect.left = 0;
	my_rect.top = 57;
	my_rect.right = 1;
	my_rect.bottom = 58;
	my_x = (x / 512 + 8) / 16;
	my_y = (y / 512 + 8) / 16;
	for (f = 0; f <= 8; ++f)
	{
		GetTrg();
		if (gKey & 0x8000)
		{
			v0 = Call_Escape(gscreen);
			if (!v0)
				return 0;
			if (v0 == 2)
				return 2;
		}
		PutBitmap4(&grcGame, 0, 0, &grcGame, 10);
		rcView.left = 160 - f * gMap.width / 16;
		rcView.right = f * gMap.width / 16 + 160;
		rcView.top = 120 - f * gMap.length / 16;
		rcView.bottom = f * gMap.length / 16 + 120;
		PutMapName(1);
		CortBox(&rcView, 0);
		PutFramePerSecound();
		if (!Flip_SystemTask(gscreen))
			return 0;
	}
	rcMiniMap.left = 0;
	rcMiniMap.right = gMap.width;
	rcMiniMap.top = 0;
	rcMiniMap.bottom = gMap.length;
	rcView.right = --rcView.left + gMap.width + 2;
	rcView.bottom = --rcView.top + gMap.length + 2;
	CortBox2(&rcMiniMap, 0, 9);
	line = 0;
	my_wait = 0;
	while (1)
	{
		GetTrg();
		if ((gKeyCancel | gKeyOk) & gKeyTrg)
			break;
		if (gKey & 0x8000)
		{
			v2 = Call_Escape(gscreen);
			if (!v2)
				return 0;
			if (v2 == 2)
				return 2;
		}
		PutBitmap4(&grcGame, 0, 0, &grcGame, 10);
		CortBox(&rcView, 0);
		if (gMap.length > line)
			WriteMiniMapLine(line++);
		if (gMap.length > line)
			WriteMiniMapLine(line++);
		PutBitmap3(&grcGame, rcView.left + 1, rcView.top + 1, &rcMiniMap, 9);
		PutMapName(1);
		if ((++my_wait >> 3) & 1)
			PutBitmap3(&grcGame, my_x + rcView.left + 1, my_y + rcView.top + 1, &my_rect, 26);
		PutFramePerSecound();
		if (!Flip_SystemTask(gscreen))
			return 0;
	}
	for (f = 8; f >= -1; --f)
	{
		GetTrg();
		if (gKey & 0x8000)
		{
			v3 = Call_Escape(gscreen);
			if (!v3)
				return 0;
			if (v3 == 2)
				return 2;
		}
		PutBitmap4(&grcGame, 0, 0, &grcGame, 10);
		rcView.left = 160 - f * gMap.width / 16;
		rcView.right = f * gMap.width / 16 + 160;
		rcView.top = 120 - f * gMap.length / 16;
		rcView.bottom = f * gMap.length / 16 + 120;
		PutMapName(1);
		CortBox(&rcView, 0);
		PutFramePerSecound();
		if (!Flip_SystemTask(gscreen))
			return 0;
	}
	return 1;
}
//*/
/*----- (00414640) --------------------------------------------------------
int Game_Loop_Map()
{
	int v1; // [sp+0h] [bp-50h]@32
	int v2; // [sp+4h] [bp-4Ch]@15
	int v3; // [sp+8h] [bp-48h]@4
	RECT Ptr_Img_Rects; // [sp+Ch] [bp-44h]@9
	int v5; // [sp+1Ch] [bp-34h]@1
	int Src_Rects; // [sp+20h] [bp-30h]@12
	int v7; // [sp+24h] [bp-2Ch]@12
	int v8; // [sp+28h] [bp-28h]@12
	int v9; // [sp+2Ch] [bp-24h]@12
	int v10; // [sp+30h] [bp-20h]@1
	char v11; // [sp+37h] [bp-19h]@12
	int i; // [sp+38h] [bp-18h]@1
	LONG v13; // [sp+3Ch] [bp-14h]@12
	int v14; // [sp+40h] [bp-10h]@1
	int v15; // [sp+44h] [bp-Ch]@1
	int v16; // [sp+48h] [bp-8h]@1
	int v17; // [sp+4Ch] [bp-4h]@1

	v14 = 0;
	v15 = 57;
	v16 = 1;
	v17 = 58;
	v10 = (Quote_X_Pos / 512 + 8) / 16;
	v5 = (Quote_Y_Pos / 512 + 8) / 16;
	for (i = 0; i <= 8; ++i)
	{
		Get_Keys();
		if (Key_Held & 0x8000)
		{
			v3 = Call_Escape(AppWinHandle);
			if (!v3)
				return 0;
			if (v3 == 2)
				return 2;
		}
		DrawSpriteNoTransparency((int)&FullscreenRect, 0, 0, (int)&FullscreenRect, 10);
		Ptr_Img_Rects.left = 160 - i * *(signed __int16 *)&MapWidth / 8 / 2;
		Ptr_Img_Rects.right = i * *(signed __int16 *)&MapWidth / 8 / 2 + 160;
		Ptr_Img_Rects.top = 120 - i * *(signed __int16 *)&MapHeight / 8 / 2;
		Ptr_Img_Rects.bottom = i * *(signed __int16 *)&MapHeight / 8 / 2 + 120;
		TSC_MNA(1);
		Draw_Color_Fill(&Ptr_Img_Rects, 0);
		Display_FPS_Counter();
		if (!Draw_Window(AppWinHandle))
			return 0;
	}
	Src_Rects = 0;
	v8 = *(signed __int16 *)&MapWidth;
	v7 = 0;
	v9 = *(signed __int16 *)&MapHeight;
	Ptr_Img_Rects.right = --Ptr_Img_Rects.left + *(signed __int16 *)&MapWidth + 2;
	Ptr_Img_Rects.bottom = --Ptr_Img_Rects.top + *(signed __int16 *)&MapHeight + 2;
	Draw_Color_Fill_Onto_Surface((int)&Src_Rects, 0, 9);
	v13 = 0;
	v11 = 0;
	while (1)
	{
		Get_Keys();
		if (Key_Pressed & (Key_Cancel | Key_Ok))
			break;
		if (Key_Held & 0x8000)
		{
			v2 = Call_Escape(AppWinHandle);
			if (!v2)
				return 0;
			if (v2 == 2)
				return 2;
		}
		DrawSpriteNoTransparency((int)&FullscreenRect, 0, 0, (int)&FullscreenRect, 10);
		Draw_Color_Fill(&Ptr_Img_Rects, 0);
		if (v13 < *(signed __int16 *)&MapHeight)
			Render_Map_System_Green_Stuff(v13++);
		if (v13 < *(signed __int16 *)&MapHeight)
			Render_Map_System_Green_Stuff(v13++);
		Draw_Bitmap_With_Transparency(&FullscreenRect, Ptr_Img_Rects.left + 1, Ptr_Img_Rects.top + 1, (RECT *)&Src_Rects, 9);
		TSC_MNA(1);
		if (((signed int)(unsigned __int8)++v11 >> 3) % 2)
			Draw_Bitmap_With_Transparency(
				&FullscreenRect,
				v10 + Ptr_Img_Rects.left + 1,
				v5 + Ptr_Img_Rects.top + 1,
				(RECT *)&v14,
				26);
		Display_FPS_Counter();
		if (!Draw_Window(AppWinHandle))
			return 0;
	}
	for (i = 8; i >= -1; --i)
	{
		Get_Keys();
		if (Key_Held & 0x8000)
		{
			v1 = Call_Escape(AppWinHandle);
			if (!v1)
				return 0;
			if (v1 == 2)
				return 2;
		}
		DrawSpriteNoTransparency((int)&FullscreenRect, 0, 0, (int)&FullscreenRect, 10);
		Ptr_Img_Rects.left = 160 - i * *(signed __int16 *)&MapWidth / 8 / 2;
		Ptr_Img_Rects.right = i * *(signed __int16 *)&MapWidth / 8 / 2 + 160;
		Ptr_Img_Rects.top = 120 - i * *(signed __int16 *)&MapHeight / 8 / 2;
		Ptr_Img_Rects.bottom = i * *(signed __int16 *)&MapHeight / 8 / 2 + 120;
		TSC_MNA(1);
		Draw_Color_Fill(&Ptr_Img_Rects, 0);
		Display_FPS_Counter();
		if (!Draw_Window(AppWinHandle))
			return 0;
	}
	return 1;
}
*/
#pragma endregion