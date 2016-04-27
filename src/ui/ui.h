#ifndef UI_H
#define UI_H

#include "../system.h"

// maksymalna liczba komponentów na okno
#define MCPW 5
// maksymalna liczba okien
#define MAXWINS 1
// bity stylu
#define UI_STYLE_SINGLE	1
#define UI_STYLE_BOLD		2
#define UI_STYLE_BOLD2	3

#define UI_STYLE_INFO		4
#define UI_STYLE_ERROR	8
#define UI_STYLE_QUEST	12
#define UI_STYLE_SQUARE	16

#define UICOMP_MAXSTRLEN 15
#define UICOMP_NONE		0
#define UICOMP_LABEL	1
#define UICOMP_BUTTON	2
#define UICOMP_EDIT		3
#define UICOMP_TEXT		4

typedef struct {
	u8int_t left, top, height, width, style, type;
	u8int_t parent;
	char* text;
	
} UIComponent;

typedef struct {
		u8int_t left, top, height, width, style, compnum;
		UIComponent comps[MCPW];
		char* title;
} UIWindow;

void UIInit(u8int_t, u8int_t);
void UISetHW(UIWindow*, u8int_t, u8int_t);
void UISetPos(UIWindow*, u8int_t, u8int_t);
void UIPutCh(u8int_t, u8int_t, char);
void UIPutChAtt(u8int_t, u8int_t, char, u8int_t);
void UIDrawWindow(UIWindow*);
void UIRefresh();
void UIPrint(u8int_t, u8int_t, char*, char);
void UIAddWindow(UIWindow*);
void UIMsg(u8int_t, char*);
void UIDrawComp(UIWindow*, u8int_t);
void UIAddComp(UIWindow*, UIComponent);
void UIKey(char);

#endif

