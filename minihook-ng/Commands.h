#ifndef __COMMANDS_H__
#define __COMMANDS_H__

typedef void (*pfnCommand)(void);

void hpattack2(void);
void hpreload(void);

extern pfnCommand ppattack2;
extern pfnCommand ppreload;

#endif
