#include "sf_frotz.h"
#include <string.h>

static byte Zfont3[] = {
/* 32*/	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 33*/	0x00,0x00,0x20,0x60,0xfe,0x60,0x20,0x00,
/* 34*/	0x00,0x00,0x08,0x0c,0xfe,0x0c,0x08,0x00,
/* 35*/	0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,
/* 36*/	0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,
/* 37*/	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 38*/	0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
/* 39*/	0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
/* 40*/	0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
/* 41*/	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
/* 42*/	0x08,0x08,0x08,0xff,0x00,0x00,0x00,0x00,
/* 43*/	0x00,0x00,0x00,0x00,0xff,0x08,0x08,0x08,
/* 44*/	0x08,0x08,0x08,0x08,0x0f,0x08,0x08,0x08,
/* 45*/	0x10,0x10,0x10,0x10,0xf0,0x10,0x10,0x10,
/* 46*/	0x10,0x10,0x10,0x10,0x1f,0x00,0x00,0x00,
/* 47*/	0x00,0x00,0x00,0x1f,0x10,0x10,0x10,0x10,
/* 48*/	0x00,0x00,0x00,0xf8,0x08,0x08,0x08,0x08,
/* 49*/	0x08,0x08,0x08,0x08,0xf8,0x00,0x00,0x00,
/* 50*/	0x10,0x10,0x10,0x10,0x1f,0x20,0x40,0x80,
/* 51*/	0x80,0x40,0x20,0x1f,0x10,0x10,0x10,0x10,
/* 52*/	0x01,0x02,0x04,0xf8,0x08,0x08,0x08,0x08,
/* 53*/	0x08,0x08,0x08,0x08,0xf8,0x04,0x02,0x01,
/* 54*/	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
/* 55*/	0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,
/* 56*/	0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,
/* 57*/	0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,
/* 58*/	0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,
/* 59*/	0x08,0x08,0x08,0xff,0xff,0xff,0xff,0xff,
/* 60*/	0xff,0xff,0xff,0xff,0xff,0x08,0x08,0x08,
/* 61*/	0xf8,0xf8,0xf8,0xf8,0xff,0xf8,0xf8,0xf8,
/* 62*/	0x1f,0x1f,0x1f,0x1f,0xff,0x1f,0x1f,0x1f,
/* 63*/	0x1f,0x1f,0x1f,0x1f,0x1f,0x00,0x00,0x00,
/* 64*/	0x00,0x00,0x00,0x1f,0x1f,0x1f,0x1f,0x1f,
/* 65*/	0x00,0x00,0x00,0xf8,0xf8,0xf8,0xf8,0xf8,
/* 66*/	0xf8,0xf8,0xf8,0xf8,0xf8,0x00,0x00,0x00,
/* 67*/	0x1f,0x1f,0x1f,0x1f,0x1f,0x20,0x40,0x80,
/* 68*/	0x80,0x40,0x20,0x1f,0x1f,0x1f,0x1f,0x1f,
/* 69*/	0x01,0x02,0x04,0xf8,0xf8,0xf8,0xf8,0xf8,
/* 70*/	0xf8,0xf8,0xf8,0xf8,0xf8,0x04,0x02,0x01,
/* 71*/	0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 72*/	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
/* 73*/	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,
/* 74*/	0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 75*/	0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 76*/	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
/* 77*/	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
/* 78*/	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
/* 79*/	0x00,0xff,0x00,0x00,0x00,0x00,0xff,0x00,
/* 80*/	0x00,0xff,0x80,0x80,0x80,0x80,0xff,0x00,
/* 81*/	0x00,0xff,0xc0,0xc0,0xc0,0xc0,0xff,0x00,
/* 82*/	0x00,0xff,0xe0,0xe0,0xe0,0xe0,0xff,0x00,
/* 83*/	0x00,0xff,0xf0,0xf0,0xf0,0xf0,0xff,0x00,
/* 84*/	0x00,0xff,0xf8,0xf8,0xf8,0xf8,0xff,0x00,
/* 85*/	0x00,0xff,0xfc,0xfc,0xfc,0xfc,0xff,0x00,
/* 86*/	0x00,0xff,0xfe,0xfe,0xfe,0xfe,0xff,0x00,
/* 87*/	0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,
/* 88*/	0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x00,
/* 89*/	0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,
/* 90*/	0x81,0x42,0x24,0x18,0x18,0x24,0x42,0x81,
/* 91*/	0x08,0x08,0x08,0x08,0xff,0x08,0x08,0x08,
/* 92*/	0x18,0x3c,0xdb,0x18,0x18,0x18,0x18,0x00,
/* 93*/	0x18,0x18,0x18,0x18,0xdb,0x3c,0x18,0x00,
/* 94*/	0x18,0x3c,0xdb,0x18,0xdb,0x3c,0x18,0x00,
/* 95*/	0xff,0x81,0x81,0x81,0x81,0x81,0x81,0xff,
/* 96*/	0x3c,0x66,0x06,0x0c,0x18,0x00,0x18,0x00,
/* 97*/	0xc4,0xa8,0x90,0xc0,0xa0,0x90,0x80,0x00,
/* 98*/	0x60,0x50,0x48,0x70,0x48,0x50,0x60,0x00,
/* 99*/	0x10,0x18,0x14,0x92,0x50,0x30,0x10,0x00,
/*100*/	0x82,0xc6,0xaa,0x92,0xaa,0xc6,0x82,0x00,
/*101*/	0x82,0xc6,0xaa,0x92,0x82,0x82,0x82,0x00,
/*102*/	0x94,0xa8,0xd0,0xa0,0xc0,0x80,0x80,0x00,
/*103*/	0x82,0x44,0x28,0x10,0x28,0x44,0x82,0x00,
/*104*/	0xc2,0xa2,0xd2,0xaa,0x96,0x8a,0x86,0x00,
/*105*/	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,
/*106*/	0x10,0x38,0x54,0x92,0x54,0x38,0x10,0x00,
/*107*/	0x10,0x10,0x10,0x38,0x54,0x92,0x92,0x00,
/*108*/	0x10,0x18,0x14,0x12,0x10,0x10,0x10,0x00,
/*109*/	0xc6,0xaa,0x92,0xaa,0xc6,0x82,0x82,0x00,
/*110*/	0x90,0x50,0x38,0x14,0x12,0x10,0x10,0x00,
/*111*/	0xc4,0xac,0xd4,0xa8,0x90,0x80,0x80,0x00,
/*112*/	0x80,0x80,0x80,0x90,0xa8,0xc4,0x82,0x00,
/*113*/	0x40,0x40,0x40,0x78,0x44,0x44,0x44,0x00,
/*114*/	0x60,0x50,0x48,0x50,0x60,0x50,0x48,0x00,
/*115*/	0x40,0x44,0x4c,0x54,0x64,0x44,0x04,0x00,
/*116*/	0x10,0x38,0x54,0x92,0x10,0x10,0x10,0x00,
/*117*/	0x60,0x50,0x48,0x44,0x44,0x44,0x44,0x00,
/*118*/	0x10,0xba,0x54,0x10,0x10,0x10,0x10,0x00,
/*119*/	0x60,0x50,0x48,0x50,0x60,0x40,0x40,0x00,
/*120*/	0x92,0x54,0x38,0x10,0x10,0x10,0x10,0x00,
/*121*/	0xe0,0xd0,0xa8,0x94,0x9a,0x96,0x92,0x00,
/*122*/	0x10,0x28,0x44,0x28,0x10,0x28,0x44,0x00,
/*123*/	0xe7,0xc3,0x24,0xe7,0xe7,0xe7,0xe7,0xff,
/*124*/	0xe7,0xe7,0xe7,0xe7,0x24,0xc3,0xe7,0xff,
/*125*/	0xe7,0xc3,0x24,0xe7,0x24,0xc3,0xe7,0xff,
/*126*/	0xc3,0x99,0xf9,0xf3,0xe7,0xff,0xe7,0xff};

// glyph buffer
static struct {
  byte dx;
  byte w, h;
  char xof, yof;
  byte bitmap[16];
  } myglyph = {8,8,8,0,0};

static void nodestroy(SFONT *s){}
static int myheight(SFONT *s){ return 8;}
static int myascent(SFONT *s){ return 6;}
static int mydescent(SFONT *s){ return 2;}
static int myminchar(SFONT *s){ return 32;}
static int mymaxchar(SFONT *s){ return 126;}
static int myhasglyph(SFONT *s, word c, int allowdef)
  { if (c >= 32 && c <= 126) return 1; if (allowdef) return 1;}
static SF_glyph * mygetglyph(SFONT *s, word c, int allowdef)
  {
  byte *src;
  if (c < 32 || c > 126)
    {
    if (!allowdef) return NULL;
    c = 32;
    }
  src = Zfont3+8*(c-32);
  memcpy(&(myglyph.bitmap[0]),src,8);
  myglyph.h = 8;
  return (SF_glyph *)&myglyph;
  }

static SFONT myfont3 = {
  0,
  nodestroy,
  myheight,
  myascent,
  mydescent,
  myminchar,
  mymaxchar,
  myhasglyph,
  mygetglyph,
  0,
  NULL};

SFONT * SF_font3 = &myfont3;

static int myheight2(SFONT *s){ return 16;}
static int myascent2(SFONT *s){ return 12;}
static int mydescent2(SFONT *s){ return 4;}
static SF_glyph * mygetglyph2(SFONT *s, word c, int allowdef)
  {
  byte *src, *dst; int i;
  if (c < 32 || c > 126)
    {
    if (!allowdef) return NULL;
    c = 32;
    }
  src = Zfont3+8*(c-32);
  dst = &(myglyph.bitmap[0]);
  for (i=0;i<8;i++)
	{ dst[0] = dst[1] = src[i]; dst += 2;}
  myglyph.h = 16;
  return (SF_glyph *)&myglyph;
  }

static SFONT myfont3dbl = {
  0,
  nodestroy,
  myheight2,
  myascent2,
  mydescent2,
  myminchar,
  mymaxchar,
  myhasglyph,
  mygetglyph2,
  0,
  NULL};

SFONT * SF_font3double = &myfont3dbl;
