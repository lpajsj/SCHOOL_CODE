#ifndef _ds1302_h_
#define _ds1302_h_
sbit ce_ds1302=P1^3;sbit scl_ds1302=P1^7;sbit io_ds1302=P2^3;
void write_ds13(uchar x);
uchar read_ds13();
uchar read_ds1302(uchar a);
void write_ds1302(uchar a,uchar x);
void read_dstime();
void write_dstime();
#endif