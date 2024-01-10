#ifndef _chuankouping_h
#define _chuankouping_h
#include "stm32f10x.h"
void ckpqx(u8 id,u8 t,u8 s);
void ckpfasong(char x[]);
void ckpxianshis(char obj[],char shuju[]);
void ckpxianshid(char obj[],u32 shuju);
void ckpxianshids(char obj[],u32 shuju);
void ckpxianshifs(char obj[],double shuju);
void ckpjieshu(void);
#endif
