#include <windows.h>
#pragma once

#pragma region Functions

//Draws the window
typedef int __cdecl dw(HWND hWnd);
dw* DrawWindow = (dw*)(0x0040B340);

//Draws a sprite onto a surface
typedef int __cdecl dsos(int x, int y, RECT* rect, int to, int from);
dsos* DrawSpriteOntoSurface = (dsos*)(0x0040C7A0);

//Draws a solid rectangle of a given color
typedef int __cdecl dfros(RECT*, int, int);
dfros* DrawFilledRectangleOntoSurface = (dfros*)(0x0040CA80);

//Escapes
typedef int __cdecl ce(HWND);
ce* Call_Escape = (ce*)(0x0040DD70);

//Gets keyboard input
typedef void __cdecl gk();
gk* GetKeys = (gk*)(0x004122E0);

//Draws the FPS counter
typedef void __cdecl dfps();
dfps* DrawFPS = (dfps*)(0x00412370);

//Gets the type of the given tile
typedef CHAR __cdecl gtt(int x,	int y);
gtt* GetTileType = (gtt*)(0x004139A0);

//Displays the map name, <MNA calls it
typedef void __cdecl dmn(int);
dmn* DisplayMapName = (dmn*)(0x00414250);

#pragma endregion

#pragma region Variables

//REPLACED BY CS_clip_rect_common
//RECT* FullscreenRect = (RECT*)(0x0048F91C);

int* OkKey = (int*)(0x00493628);
int* CancelKey = (int*)(0x0049362C);

int* LastPressedKey = (int*)(0x0049E218);

int* QuoteX = (int*)(0x0049E654);
int* QuoteY = (int*)(0x0049E658);

#pragma endregion