#include "ui.h"

UIWindow* wins[MAXWINS];
UIWindow workspace;
char ui_style_double[6]	=	{0xC9, 0xBB, 0xC8, 0xBC, 0xBA, 0xCD};
char ui_style_single[6]	=	{0xDA, 0xBF, 0xC0, 0xD9, 0xB3, 0xC4};
char ui_style_bold[6]		=	{0xDC, 0xDC, 0xDF, 0xDF, 0xDB, 0xDB};
char ui_style_bold2[6]	=	{0xDB, 0xDB, 0xDB, 0xDB, 0xDB, 0xDB};
char ui_style_icon[4]		= {'!', 'X', '?', 0xFE};

void UIPutCh(u8int_t x, u8int_t y, char ch) {
	u8int_t* buf = (u8int_t *)VGA_ADDR;
	buf[2*(x+y*SCR_WIDTH)]=ch;
}

void UIPutChAtt(u8int_t x, u8int_t y, char ch, u8int_t att) {
	u8int_t* buf = (u8int_t *)VGA_ADDR;
	buf[2*(x+y*SCR_WIDTH)]=ch;
	buf[2*(x+y*SCR_WIDTH)+1]=att;
}

void UIKey(char key) {
	switch (key) {
		case 0x1B	: newline(); break;
		case 'l'	: UIMsg(1,"Wcisnieto"); getch(); break;
	}
}

void UIDrawWindow(UIWindow* win) {
	int c, i, j, tlen;
	char* ui_style;
	if(win->left+win->width>=SCR_WIDTH) win->width=SCR_WIDTH-win->left;
	if(win->top+win->height>=SCR_HEIGHT) win->height=SCR_HEIGHT-win->top;
	for(i=(win->top);i<(win->height);i++)
		for(j=(win->left);j<(win->width);j++)
			UIPutCh(j,i,0);
	switch ((win->style)&3) {
		case UI_STYLE_SINGLE: ui_style=ui_style_single; break;
		case UI_STYLE_BOLD: ui_style=ui_style_bold; break;
		case UI_STYLE_BOLD2: ui_style=ui_style_bold2; break;
		default: ui_style=ui_style_double; break;
	}
	UIPutCh(win->left, win->top, ui_style[0]);
	UIPutCh((win->left+win->width-1), win->top, ui_style[1]);
	UIPutCh(win->left, (win->top+win->height-1), ui_style[2]);
	UIPutCh((win->left+win->width-1), (win->top+win->height-1), ui_style[3]);
	for(i=0;i<(win->width-2);i++)
		UIPutCh((win->left+i+1), win->top, ui_style[5]);
	for(i=0;i<(win->height-2);i++)
		UIPutCh(win->left, (win->top+i+1), ui_style[4]);
	for(i=0;i<(win->height-2);i++)
		UIPutCh((win->left+win->width-1), (win->top+i+1), ui_style[4]);
	for(i=0;i<(win->width-2);i++)
		UIPutCh((win->left+i+1), (win->top+win->height-1), ui_style[5]);
	tlen=win->width-4;
	if(tlen<=0) tlen=0;
	if(win->title) {
		UIPrint((win->left+2),win->top,win->title,tlen);
	}
	switch(win->style&28) {
		case UI_STYLE_INFO: UIPutCh(win->left,win->top,ui_style_icon[0]); break;
		case UI_STYLE_ERROR: UIPutCh(win->left,win->top,ui_style_icon[1]); break;
		case UI_STYLE_QUEST: UIPutCh(win->left,win->top,ui_style_icon[2]); break;
		case UI_STYLE_SQUARE: UIPutCh(win->left,win->top,ui_style_icon[3]); break;
		default: break;
	}
	
	c=0;
	while(c<MCPW) {
		UIDrawComp(win, c);
		c++;
	}
}

void UIRefresh() {
	int i;
	char key;
ui_ref:
	for(i=0;wins[i];i++)
		UIDrawWindow(wins[i]);
	while(getch()!=0x1B);
	send_serial_str("Odswiezanie UI");
	key=getch();
	UIKey(key);
goto ui_ref;
}

void UIPrint(u8int_t x, u8int_t y, char* str, char maxlen) {
	int i;
	for(i=0; (str[i] && i<maxlen); i++)
		UIPutCh(x+i,y,str[i]);
}

void UIAddWindow(UIWindow* win) {
	int i=0;
	while((wins[i])||(i<MAXWINS))
		i++;
	if(i>=MAXWINS) return;
	wins[i]=win;
}

void UIInit(u8int_t scrw, u8int_t scrh) {
	send_serial_str("Inicializacja UI");
	int i;
	init_video();
	mov_csr(0,scrh-1);
	for(i=0;i<MAXWINS;i++)
		wins[i]=NULL;
	send_serial_str("Ustawianie okna nadrzednego");
	wins[0]=&workspace;
	wins[0]->left		= 0;
	wins[0]->top		= 0;
	wins[0]->height	= scrh;
	wins[0]->width	= scrw;
	wins[0]->title	= "os34 Experimental Block UI";
	wins[0]->style	= UI_STYLE_SQUARE;
	wins[0]->compnum	= 1;
	wins[0]->comps[0].left=2;
	wins[0]->comps[0].top=3;
	wins[0]->comps[0].text="Tekst";
	wins[0]->comps[0].width=10;
	wins[0]->comps[0].type='l';
	UIRefresh();
}

void UIMsg(u8int_t type, char* msg) {
	send_serial_str(msg);
	switch (type) {
		case 1: UIPrint(wins[0]->left, wins[0]->height-1, "W: ", 3); break;
		case 2: UIPrint(wins[0]->left, wins[0]->height-1, "E: ", 3); break;
	}
	if(!type) UIPrint(wins[0]->left, wins[0]->height-1, msg, wins[0]->width-3);
	else UIPrint(wins[0]->left+2, wins[0]->height-1, msg, wins[0]->width-3);
}

void UIAddComp(UIWindow* win, UIComponent comp) {
	win->comps[win->compnum]=comp;
	win->compnum++;
}

void UIDrawComp(UIWindow* win, u8int_t num) {
	switch(win->comps[num].type) {
		case 'l': UILabelDraw(win, num); break;
		default: UIPutCh(win->comps[num].left, win->comps[num].top, '?');
	}
}

void okienka() {
	UIWindow win1, win2;
	win1.left=5;
	win1.top=4;
	win1.height=20;
	win1.width=50;
	win1.style=(UI_STYLE_BOLD2|UI_STYLE_SQUARE);
	win1.compnum=0;
	win1.title="Okienko 1";
	
	win2.left=10;
	win2.top=7;
	win2.height=5;
	win2.width=70;
	win2.style=(UI_STYLE_SINGLE|UI_STYLE_QUEST);
	win2.compnum=0;
	win2.title="Okienko 2";
	
	wins[1]=&win1;
	wins[2]=&win2;
	UIRefresh();
}

