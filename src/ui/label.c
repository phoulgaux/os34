#include "../system.h"
#include "ui.h"

void UILabelDraw(UIWindow* win, u8int_t num) {
	UIPrint(win->left+win->comps[num].left, win->top+win->comps[num].top, win->comps[num].text, win->comps[num].width);
}

