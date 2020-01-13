# 1 "lex.m"
struct _PRIVATE { struct _PRIVATE *isa; };
typedef struct _PRIVATE *id;
struct _SHARED {
  id isa;
  id clsSuper;
  char *clsName;
  char *clsTypes;
  short clsSizInstance;
  short clsSizDict;
  struct _SLT *clsDispTable;
  long clsStatus;
  struct modDescriptor *clsMod;
  unsigned clsVersion;
  id clsCats;
  id *clsGlbl;
};
extern id  (* _imp(id,char*))();
extern id  (* _impSuper(id,char*))();
extern struct modDescriptor  *_OBJCBIND_lex(void);
static char **selTransTbl;
struct _SLT {char *_cmd;id (*_imp)();};
struct modDescriptor {
  char *modName;
  char *modVersion;
  long modStatus;
  char *modMinSel;
  char *modMaxSel;
  id *modClsLst;
  short modSelRef;
  char **modSelTbl;
  struct methodDescriptor *modMapTbl;
};
extern struct modDescriptor lex_modDesc;

# 2 "lex.m"

# 1 "../../util/stdio.h"
#include <stdio.h>

# 1 "../../util/string.h"
#include <string.h>

# 1 "../../util/errno.h"
#include <errno.h>

# 1 "../../util/stdlib.h"
#include <stdlib.h>

# 50 "lex.yy.c"
typedef signed char flex_int8_t;
typedef short int flex_int16_t;
typedef int flex_int32_t;
typedef unsigned char flex_uint8_t;
typedef unsigned short int flex_uint16_t;
typedef unsigned int flex_uint32_t;
# 151 "lex.yy.c"
typedef struct yy_buffer_state*YY_BUFFER_STATE;


extern int yyleng;

extern FILE*yyin,*yyout;
# 187 "lex.yy.c"
typedef unsigned int yy_size_t;
# 192 "lex.yy.c"
struct yy_buffer_state
{
FILE*yy_input_file;

char*yy_ch_buf;
char*yy_buf_pos;
# 202 "lex.yy.c"
yy_size_t yy_buf_size;
# 207 "lex.yy.c"
int yy_n_chars;
# 213 "lex.yy.c"
int yy_is_our_buffer;
# 220 "lex.yy.c"
int yy_is_interactive;
# 226 "lex.yy.c"
int yy_at_bol;

int yy_bs_lineno;
int yy_bs_column;
# 234 "lex.yy.c"
int yy_fill_buffer;

int yy_buffer_status;
# 252 "lex.yy.c"
};
# 256 "lex.yy.c"
static size_t yy_buffer_stack_top=0;
static size_t yy_buffer_stack_max=0;
static YY_BUFFER_STATE*yy_buffer_stack=0;
# 276 "lex.yy.c"
static char yy_hold_char;
static int yy_n_chars;
int yyleng;


static char*yy_c_buf_p=(char*)0;
static int yy_init=0;
static int yy_start=0;
# 288 "lex.yy.c"
static int yy_did_buffer_switch_on_eof;

void yyrestart(FILE*input_file);
void yy_switch_to_buffer(YY_BUFFER_STATE new_buffer);
YY_BUFFER_STATE yy_create_buffer(FILE*file,int size);
void yy_delete_buffer(YY_BUFFER_STATE b);
void yy_flush_buffer(YY_BUFFER_STATE b);
void yypush_buffer_state(YY_BUFFER_STATE new_buffer);
void yypop_buffer_state(void);

static void yyensure_buffer_stack(void);
static void yy_load_buffer_state(void);
static void yy_init_buffer(YY_BUFFER_STATE b,FILE*file);
# 304 "lex.yy.c"
YY_BUFFER_STATE yy_scan_buffer(char*base,yy_size_t size);
YY_BUFFER_STATE yy_scan_string(const char*yy_str);
YY_BUFFER_STATE yy_scan_bytes(const char*bytes,int len);

void*yyalloc(yy_size_t);
void*yyrealloc(void*,yy_size_t);
void yyfree(void*);
# 338 "lex.yy.c"
typedef unsigned char YY_CHAR;

FILE*yyin=(FILE*)0,*yyout=(FILE*)0;

typedef int yy_state_type;

extern int yylineno;

int yylineno=1;

extern char*yytext;


static yy_state_type yy_get_previous_state(void);
static yy_state_type yy_try_NUL_trans(yy_state_type current_state);
static int yy_get_next_buffer(void);
static void yy_fatal_error(const char msg[]);
# 370 "lex.yy.c"
struct yy_trans_info
{
flex_int32_t yy_verify;
flex_int32_t yy_nxt;
};
static const flex_int16_t yy_accept[700]=
{0,
0,0,174,172,158,159,159,117,172,172,
170,123,134,172,111,112,121,124,152,125,
116,122,166,166,140,153,128,141,130,139,
172,113,114,135,170,170,170,170,170,170,
170,170,170,170,170,170,170,170,170,170,
170,154,136,155,118,158,159,133,0,161,
0,0,160,160,170,146,137,147,0,163,
0,144,119,142,120,143,115,0,169,171,
145,167,164,166,0,166,0,126,129,157,
132,131,127,0,0,0,0,0,0,149,

170,170,170,170,170,170,170,170,170,170,
170,170,170,170,170,170,170,170,170,170,
170,9,170,170,170,170,170,170,170,48,
19,170,170,170,170,170,170,170,170,170,
170,170,170,170,148,138,0,0,0,0,
0,0,156,0,169,171,167,0,167,164,
0,168,166,165,150,151,0,0,0,0,
0,0,0,0,170,170,170,170,170,170,
170,170,170,170,170,170,170,170,170,170,
170,170,170,170,170,170,170,170,170,170,

170,170,170,170,170,170,54,170,170,170,
170,170,170,170,170,170,170,170,79,170,
17,170,170,21,170,170,170,170,170,170,
170,170,170,170,170,170,170,170,170,170,
170,170,0,0,0,0,0,0,0,169,
169,0,167,0,167,167,164,168,166,165,
0,0,46,0,0,0,0,0,0,0,
170,170,170,170,170,170,170,170,170,170,
170,170,170,170,170,170,170,170,170,170,
170,170,170,170,170,170,170,170,170,170,

170,170,170,170,170,78,170,170,170,170,
1,35,170,4,6,170,170,170,170,11,
12,170,170,18,170,22,170,170,170,170,
170,170,170,170,170,170,170,170,170,33,
170,170,170,0,0,0,0,0,0,169,
0,167,167,167,164,168,165,42,0,0,
0,0,0,0,0,0,2,170,170,170,
170,170,170,170,170,66,170,170,170,170,
170,170,170,170,77,170,170,170,170,170,
170,170,170,170,170,170,170,170,170,170,

170,170,170,170,170,170,170,81,170,170,
3,38,170,170,170,170,16,170,170,170,
170,170,25,170,170,170,170,170,170,31,
170,170,170,34,0,0,167,168,165,0,
0,0,0,0,0,0,0,170,170,170,
170,170,104,170,170,0,170,0,170,170,
170,170,170,170,170,170,170,170,170,93,
170,170,170,170,170,80,170,170,170,170,
170,96,170,170,170,170,170,170,170,75,
170,170,170,170,170,10,15,53,82,170,

170,24,40,26,27,28,29,170,170,170,
170,47,0,0,0,0,50,0,0,170,
170,170,170,97,110,170,0,67,0,55,
170,88,76,60,170,170,170,170,103,170,
170,170,92,170,170,170,170,170,170,170,
170,170,170,170,170,170,170,170,68,83,
170,170,8,0,170,170,30,170,170,36,
0,0,52,0,0,0,109,5,170,108,
170,0,170,0,170,170,170,86,170,170,
170,70,170,100,170,170,170,170,170,170,

61,170,170,72,170,170,170,84,7,0,
23,39,32,41,0,0,0,49,43,170,
170,0,170,0,105,57,87,170,170,170,
98,170,170,170,0,170,170,94,95,170,
85,102,170,170,37,0,0,44,51,20,
170,0,170,89,170,90,69,170,170,0,
106,73,101,62,63,58,13,0,0,170,
0,0,170,0,170,99,91,170,170,170,
0,0,162,56,0,170,0,107,170,74,
64,59,14,0,65,71,0,45,0

};

static const flex_int32_t yy_ec[256]=
{0,
1,1,1,1,1,1,1,1,2,3,
1,1,4,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,
1,5,6,7,8,9,10,11,12,13,
14,15,16,17,18,19,20,21,22,23,
23,24,23,25,23,26,26,27,28,29,
30,31,32,33,34,35,36,34,37,38,
39,39,40,39,39,41,39,42,43,44,
39,39,45,46,47,39,39,48,39,39,
49,50,51,52,53,1,54,55,56,57,

58,59,60,61,62,39,63,64,65,66,
67,68,69,70,71,72,73,74,75,76,
77,78,79,80,81,82,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,

1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1
};

static const flex_int32_t yy_meta[83]=
{0,
1,2,3,3,2,1,4,1,5,1,
1,6,1,1,1,1,7,1,1,1,
8,8,8,8,8,9,1,1,1,1,
1,4,1,10,10,10,10,10,11,11,
11,11,11,11,11,11,11,12,1,4,
1,1,5,13,13,10,10,10,13,11,
11,11,11,11,11,12,11,11,11,12,
11,12,11,12,11,12,11,11,2,1,
1,1
};

static const flex_int16_t yy_base[718]=
{0,
0,0,1252,1253,81,1253,1248,1220,77,84,
0,1219,74,78,1253,1253,1218,73,1253,75,
73,71,110,168,1253,1253,78,82,80,1253,
82,1253,1253,1217,207,29,46,63,56,79,
92,1179,103,1178,1190,1185,103,1165,1175,1173,
59,1253,91,1253,1253,117,1253,1253,111,1253,
177,122,1253,1236,0,1253,1253,1253,126,1253,
189,1253,1253,1253,1253,1253,1253,1219,197,0,
1253,258,198,0,282,229,0,1207,1253,1253,
1253,1253,1206,1177,1168,76,93,1175,1174,1253,

81,1164,1165,1161,1174,119,285,1170,1172,1159,
1166,1169,1150,1156,1148,1152,1160,1146,1162,1149,
1155,1140,1141,1138,1138,1139,1141,1137,1134,0,
0,108,1139,1133,110,1136,89,125,1140,1133,
126,142,1139,1137,1253,1253,304,265,0,349,
312,0,1253,360,190,0,368,392,360,381,
342,412,382,400,1253,1253,1139,128,1129,1124,
141,1140,1125,1129,1125,1129,1125,1135,1116,1131,
1126,1114,1137,145,1129,191,1124,1105,173,1107,
1113,1111,1119,1106,1117,386,1097,1107,1105,1115,

1112,1099,1104,1113,1095,1108,0,1097,1099,1108,
1103,1090,158,1105,1103,1099,1091,1097,0,1100,
0,1086,1090,0,1091,1094,1087,1076,1074,1076,
1079,1086,1071,1069,1069,1082,1072,1076,1080,1082,
1081,1070,444,488,527,458,575,614,463,477,
496,550,529,506,582,583,581,615,1253,614,
1062,1065,1253,1067,1072,1055,1056,1063,1053,1067,
1060,1059,1054,1061,1056,1056,1096,1045,1074,1050,
1042,1042,1054,1045,1046,1053,196,221,1038,1047,
172,231,1052,1051,1033,1029,249,1042,1044,1029,

1031,1027,1033,1035,1039,0,1032,1023,1036,1035,
0,0,1027,0,0,1017,1026,1014,1022,0,
0,1015,1012,0,1017,0,1028,1010,1010,1009,
1006,1019,1009,1013,1018,1017,1015,1005,1010,0,
997,998,1009,217,0,667,282,0,706,1253,
593,674,621,1253,1253,622,672,1253,1009,1007,
994,1009,1004,999,998,1003,0,986,993,994,
993,996,1028,994,1015,316,980,991,992,976,
973,981,977,985,1020,969,968,981,976,252,
980,976,965,974,961,974,254,972,964,973,

972,969,964,971,970,959,956,0,967,966,
0,0,953,954,959,950,0,957,950,941,
950,945,0,953,950,952,935,945,947,0,
938,941,949,0,338,300,1253,1253,1253,943,
935,940,926,941,940,925,922,931,934,925,
924,932,0,923,941,398,933,904,922,926,
918,909,909,908,908,911,951,919,904,0,
907,948,901,913,916,0,903,897,896,907,
910,0,905,908,907,870,855,842,841,0,
814,807,806,796,796,0,862,0,0,808,

807,0,0,0,0,0,0,803,799,792,
779,1253,792,782,773,758,1253,771,760,759,
745,766,756,0,0,777,0,0,734,1253,
748,781,0,740,700,691,686,686,0,702,
701,696,0,683,681,687,696,687,690,681,
681,682,673,671,675,654,656,664,0,0,
652,656,0,704,640,637,0,651,649,0,
640,638,1253,626,612,612,0,0,607,0,
633,402,602,653,613,601,606,0,596,593,
578,590,554,0,559,589,539,534,520,533,

537,525,516,0,521,514,505,0,0,533,
0,0,0,0,487,500,500,1253,1253,479,
512,437,468,525,1253,0,0,479,466,457,
0,467,451,451,502,435,435,0,0,452,
0,0,447,439,0,380,442,1253,1253,0,
439,455,433,448,390,0,0,371,371,416,
1253,368,0,0,367,359,1253,395,330,326,
457,447,324,361,295,0,0,285,278,277,
307,239,0,473,488,204,219,1253,154,0,
0,0,1253,106,0,0,71,1253,1253,765,

778,787,800,810,820,833,839,845,851,863,
876,882,895,908,921,934,947
};

static const flex_int16_t yy_def[718]=
{0,
699,1,699,699,699,699,699,699,700,701,
702,699,699,703,699,699,699,699,699,699,
699,699,699,699,699,699,699,699,699,699,
699,699,699,699,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,
702,699,699,699,699,699,699,699,700,699,
704,701,699,699,702,699,699,699,703,699,
705,699,699,699,699,699,699,699,699,706,
699,699,23,24,699,699,707,699,699,699,
699,699,699,699,699,699,699,699,699,699,

702,702,702,702,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,
702,702,702,702,699,699,700,700,708,703,
703,709,699,699,699,706,699,699,699,699,
699,699,699,707,699,699,699,699,699,699,
699,699,699,699,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,

702,702,702,702,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,
702,702,700,700,244,703,703,247,699,699,
699,699,699,699,699,699,699,699,699,699,
699,699,699,699,699,699,699,699,699,699,
702,702,702,702,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,

702,702,702,702,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,
702,702,702,700,245,245,703,248,248,699,
699,699,699,699,699,699,699,699,699,699,
699,699,699,699,699,699,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,

702,702,702,702,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,
702,702,702,702,700,703,699,699,699,699,
699,699,699,699,699,699,699,702,702,702,
702,702,702,702,702,710,702,711,702,702,
702,702,702,702,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,

702,702,702,702,702,702,702,702,702,702,
702,699,699,699,699,699,699,699,699,702,
702,702,702,702,702,702,712,702,711,699,
702,702,702,702,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,
702,702,702,699,702,702,702,702,702,702,
699,699,699,699,699,699,702,702,702,702,
702,712,702,713,702,702,702,702,702,702,
702,702,702,702,702,702,702,702,702,702,

702,702,702,702,702,702,702,702,702,699,
702,702,702,702,699,699,699,699,699,702,
702,714,702,713,699,702,702,702,702,702,
702,702,702,702,715,702,702,702,702,702,
702,702,702,702,702,699,699,699,699,702,
702,714,702,702,702,702,702,702,702,715,
699,702,702,702,702,702,699,699,699,702,
699,716,702,717,702,702,702,702,702,702,
699,699,702,716,716,702,717,699,702,702,
702,702,699,699,702,702,699,699,0,699,

699,699,699,699,699,699,699,699,699,699,
699,699,699,699,699,699,699
};

static const flex_int16_t yy_nxt[1336]=
{0,
4,5,6,7,5,8,9,10,11,12,
13,14,15,16,17,18,19,20,21,22,
23,24,24,24,24,24,25,26,27,28,
29,30,31,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,32,4,
33,34,35,36,37,38,39,40,41,42,
11,43,11,44,11,11,11,45,11,46,
47,48,49,50,51,11,11,11,52,53,
54,55,56,60,67,56,63,64,73,70,
80,78,75,79,79,79,79,79,79,114,

81,115,74,68,76,77,88,89,90,92,
93,91,116,121,143,117,118,60,56,144,
145,56,122,119,63,64,61,71,82,120,
83,83,83,83,83,84,698,70,94,95,
169,170,123,96,124,126,85,175,231,97,
86,98,99,176,125,127,86,87,128,130,
61,131,171,136,137,172,232,85,132,227,
146,223,697,86,138,71,181,139,233,224,
228,229,86,262,263,87,82,237,84,84,
84,84,84,84,234,182,238,147,148,148,

148,148,266,239,85,240,696,267,86,150,
151,151,151,151,86,280,281,79,79,79,
79,79,79,60,149,85,288,251,316,317,
251,86,688,154,155,389,152,155,160,289,
86,101,102,390,160,699,103,283,251,104,
105,106,149,251,154,155,695,284,285,107,
155,160,108,383,152,109,61,384,110,163,
160,60,111,699,112,163,472,113,157,157,
157,157,157,157,391,243,243,243,243,243,
385,386,163,70,158,159,392,161,159,161,

694,163,162,162,162,162,162,162,397,473,
60,70,398,693,61,158,159,456,480,481,
456,159,183,70,243,243,243,243,243,692,
691,71,246,246,246,246,246,690,184,185,
186,187,188,189,60,190,191,689,192,71,
193,244,194,61,195,196,197,198,199,200,
70,71,162,162,162,162,162,162,457,246,
246,246,246,246,688,249,686,249,683,244,
250,250,250,250,250,250,667,61,157,157,
157,157,157,157,458,668,247,256,71,456,

256,682,456,622,252,253,622,254,253,254,
681,680,255,255,255,255,255,255,256,679,
678,257,259,256,247,252,253,257,259,661,
677,253,162,162,162,162,162,162,622,296,
260,622,676,297,257,259,260,298,685,258,
60,685,258,257,259,675,671,299,671,671,
674,671,300,260,344,344,344,344,344,70,
258,672,260,672,699,258,458,699,347,347,
347,347,347,250,250,250,250,250,250,685,
673,670,685,61,60,669,666,250,250,250,

250,250,250,665,664,663,662,71,345,345,
345,345,345,345,155,661,659,155,658,657,
656,345,345,345,345,345,255,255,255,255,
255,255,655,350,654,155,350,61,625,653,
155,345,345,345,345,345,345,346,346,346,
346,346,346,651,350,650,649,648,647,350,
346,346,346,346,346,351,353,351,646,353,
352,352,352,352,352,352,645,644,643,642,
346,346,346,346,346,346,70,353,641,640,
639,638,353,637,636,348,348,348,348,348,

348,635,255,255,255,255,255,255,348,348,
348,348,348,352,352,352,352,352,352,159,
354,355,159,354,71,634,633,355,348,348,
348,348,348,348,349,349,349,349,349,349,
159,354,632,631,355,159,354,349,349,349,
349,349,356,355,357,356,630,629,437,438,
357,437,438,628,627,626,625,349,349,349,
349,349,349,356,623,621,620,357,356,437,
438,619,618,617,437,438,357,435,435,435,
435,435,435,616,352,352,352,352,352,352,

435,435,435,435,435,615,614,613,612,611,
610,253,439,609,253,608,607,606,439,605,
435,435,435,435,435,435,436,436,436,436,
436,436,253,604,603,439,602,253,601,436,
436,436,436,436,439,600,599,598,597,596,
595,594,593,592,591,590,589,588,587,436,
436,436,436,436,436,59,59,586,59,59,
59,59,59,59,59,59,59,59,62,62,
62,62,62,62,62,62,62,62,62,62,
62,65,585,584,65,65,65,65,65,65,

69,69,583,69,69,69,69,69,69,69,
69,69,69,59,530,59,581,59,580,579,
578,59,59,69,577,69,576,69,575,574,
573,69,69,156,156,572,156,156,156,156,
156,156,156,156,156,156,164,164,164,571,
570,164,245,245,245,569,568,245,248,248,
248,567,566,248,527,565,564,563,562,561,
560,559,527,527,527,527,529,529,529,529,
529,529,529,529,529,529,529,529,529,582,
582,582,582,582,582,624,624,624,624,624,

624,624,624,624,624,624,624,624,652,652,
558,652,652,557,556,652,652,652,652,652,
652,660,660,660,660,660,660,660,660,660,
660,660,660,660,684,684,555,684,684,684,
684,684,684,684,684,684,684,687,687,687,
687,687,687,687,687,687,687,687,687,687,
554,553,552,551,550,549,548,547,546,545,
544,543,542,541,540,539,538,537,536,535,
534,533,532,531,530,528,526,525,524,523,
522,521,520,519,518,517,516,515,514,513,

512,511,510,509,508,507,506,505,504,503,
502,501,500,499,498,497,496,495,494,493,
492,491,490,489,488,487,486,485,484,483,
482,479,478,477,476,475,474,471,470,469,
468,467,466,465,464,463,462,461,460,459,
455,454,453,452,451,450,449,448,447,446,
445,444,443,442,441,440,434,433,432,431,
430,429,428,427,426,425,424,423,422,421,
420,419,418,417,416,415,414,413,412,411,
410,409,408,407,406,405,404,403,402,401,

400,399,396,395,394,393,388,387,382,381,
380,379,378,377,376,375,374,373,372,371,
370,369,368,367,366,365,364,363,362,361,
360,359,358,343,342,341,340,339,338,337,
336,335,334,333,332,331,330,329,328,327,
326,325,324,323,322,321,320,319,318,315,
314,313,312,311,310,309,308,307,306,305,
304,303,302,301,295,294,293,292,291,290,
287,286,282,279,278,277,276,275,274,273,
272,271,270,269,268,265,264,261,242,241,

236,235,230,226,225,222,221,220,219,218,
217,216,215,214,213,212,211,210,209,208,
207,206,205,204,203,202,201,180,179,178,
177,174,173,168,167,166,165,153,63,142,
141,140,135,134,133,129,100,72,66,58,
57,699,3,699,699,699,699,699,699,699,
699,699,699,699,699,699,699,699,699,699,
699,699,699,699,699,699,699,699,699,699,
699,699,699,699,699,699,699,699,699,699,
699,699,699,699,699,699,699,699,699,699,

699,699,699,699,699,699,699,699,699,699,
699,699,699,699,699,699,699,699,699,699,
699,699,699,699,699,699,699,699,699,699,
699,699,699,699,699
};

static const flex_int16_t yy_chk[1336]=
{0,
1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,
1,1,5,9,13,5,10,10,18,14,
22,21,20,21,21,21,21,21,21,36,

22,36,18,13,20,20,27,27,28,29,
29,28,37,39,51,37,38,59,56,51,
53,56,39,38,62,62,9,14,23,38,
23,23,23,23,23,23,697,69,31,31,
96,96,40,31,40,41,23,101,137,31,
23,31,31,101,40,41,23,23,41,43,
59,43,97,47,47,97,137,23,43,135,
53,132,694,23,47,69,106,47,138,132,
135,135,23,168,168,23,24,141,24,24,
24,24,24,24,138,106,141,61,61,61,

61,61,171,142,24,142,689,171,24,71,
71,71,71,71,24,184,184,79,79,79,
79,79,79,344,61,24,189,155,213,213,
155,24,687,79,79,291,71,79,83,189,
24,35,35,291,83,83,35,186,155,35,
35,35,61,155,79,79,686,186,186,35,
79,83,35,287,71,35,344,287,35,86,
83,148,35,83,35,86,390,35,82,82,
82,82,82,82,292,148,148,148,148,148,
288,288,86,347,82,82,292,85,82,85,

682,86,85,85,85,85,85,85,297,390,
147,436,297,681,148,82,82,376,397,397,
376,82,107,151,147,147,147,147,147,680,
679,347,151,151,151,151,151,678,107,107,
107,107,107,107,435,107,107,675,107,436,
107,147,107,147,107,107,107,107,107,107,
150,151,161,161,161,161,161,161,376,150,
150,150,150,150,674,154,673,154,670,147,
154,154,154,154,154,154,646,435,157,157,
157,157,157,157,376,646,150,159,150,456,

159,669,456,582,157,157,582,158,157,158,
668,666,158,158,158,158,158,158,159,665,
662,160,163,159,150,157,157,160,163,660,
659,157,162,162,162,162,162,162,622,196,
164,622,658,196,160,163,164,196,672,162,
243,672,162,160,163,655,652,196,671,652,
654,671,196,164,243,243,243,243,243,246,
162,652,164,671,684,162,456,684,246,246,
246,246,246,249,249,249,249,249,249,685,
653,651,685,243,244,647,644,250,250,250,

250,250,250,643,640,637,636,246,244,244,
244,244,244,244,250,635,634,250,633,632,
630,244,244,244,244,244,254,254,254,254,
254,254,629,251,628,250,251,244,624,623,
250,244,244,244,244,244,244,245,245,245,
245,245,245,621,251,620,617,616,615,251,
245,245,245,245,245,252,253,252,610,253,
252,252,252,252,252,252,607,606,605,603,
245,245,245,245,245,245,247,253,602,601,
600,599,253,598,597,247,247,247,247,247,

247,596,255,255,255,255,255,255,247,247,
247,247,247,351,351,351,351,351,351,255,
256,257,255,256,247,595,593,257,247,247,
247,247,247,247,248,248,248,248,248,248,
255,256,592,591,257,255,256,248,248,248,
248,248,258,257,260,258,590,589,353,356,
260,353,356,587,586,585,584,248,248,248,
248,248,248,258,583,581,579,260,258,353,
356,576,575,574,353,356,260,346,346,346,
346,346,346,572,352,352,352,352,352,352,

346,346,346,346,346,571,569,568,566,565,
564,352,357,562,352,561,558,557,357,556,
346,346,346,346,346,346,349,349,349,349,
349,349,352,555,554,357,553,352,552,349,
349,349,349,349,357,551,550,549,548,547,
546,545,544,542,541,540,538,537,536,349,
349,349,349,349,349,700,700,535,700,700,
700,700,700,700,700,700,700,700,701,701,
701,701,701,701,701,701,701,701,701,701,
701,702,534,532,702,702,702,702,702,702,

703,703,531,703,703,703,703,703,703,703,
703,703,703,704,529,704,526,704,523,522,
521,704,704,705,520,705,519,705,518,516,
515,705,705,706,706,514,706,706,706,706,
706,706,706,706,706,706,707,707,707,513,
511,707,708,708,708,510,509,708,709,709,
709,508,501,709,710,500,497,495,494,493,
492,491,710,710,710,710,711,711,711,711,
711,711,711,711,711,711,711,711,711,712,
712,712,712,712,712,713,713,713,713,713,

713,713,713,713,713,713,713,713,714,714,
489,714,714,488,487,714,714,714,714,714,
714,715,715,715,715,715,715,715,715,715,
715,715,715,715,716,716,486,716,716,716,
716,716,716,716,716,716,716,717,717,717,
717,717,717,717,717,717,717,717,717,717,
485,484,483,481,480,479,478,477,475,474,
473,472,471,469,468,467,466,465,464,463,
462,461,460,459,458,457,455,454,452,451,
450,449,448,447,446,445,444,443,442,441,

440,433,432,431,429,428,427,426,425,424,
422,421,420,419,418,416,415,414,413,410,
409,407,406,405,404,403,402,401,400,399,
398,396,395,394,393,392,391,389,388,387,
386,385,384,383,382,381,380,379,378,377,
375,374,373,372,371,370,369,368,366,365,
364,363,362,361,360,359,343,342,341,339,
338,337,336,335,334,333,332,331,330,329,
328,327,325,323,322,319,318,317,316,313,
310,309,308,307,305,304,303,302,301,300,

299,298,296,295,294,293,290,289,286,285,
284,283,282,281,280,279,278,277,276,275,
274,273,272,271,270,269,268,267,266,265,
264,262,261,242,241,240,239,238,237,236,
235,234,233,232,231,230,229,228,227,226,
225,223,222,220,218,217,216,215,214,212,
211,210,209,208,206,205,204,203,202,201,
200,199,198,197,195,194,193,192,191,190,
188,187,185,183,182,181,180,179,178,177,
176,175,174,173,172,170,169,167,144,143,

140,139,136,134,133,129,128,127,126,125,
124,123,122,121,120,119,118,117,116,115,
114,113,112,111,110,109,108,105,104,103,
102,99,98,95,94,93,88,78,64,50,
49,48,46,45,44,42,34,17,12,8,
7,3,699,699,699,699,699,699,699,699,
699,699,699,699,699,699,699,699,699,699,
699,699,699,699,699,699,699,699,699,699,
699,699,699,699,699,699,699,699,699,699,
699,699,699,699,699,699,699,699,699,699,

699,699,699,699,699,699,699,699,699,699,
699,699,699,699,699,699,699,699,699,699,
699,699,699,699,699,699,699,699,699,699,
699,699,699,699,699
};

static yy_state_type yy_last_accepting_state;
static char*yy_last_accepting_cpos;

extern int yy_flex_debug;
int yy_flex_debug=0;
# 982 "lex.yy.c"
char*yytext;
# 1 "../../util/stdarg.h"
#include <stdarg.h>

# 1 "../../util/assert.h"
#include <assert.h>

# 1 "../../util/stdio.h"
#include <stdio.h>

# 1 "../../util/stdio.h"
#include <stdio.h>

# 1 "../../util/stddef.h"
#include <stddef.h>

# 53 "../../include/objcrt/objcrt.h"
typedef char*SEL;
typedef char*STR;
typedef char BOOL;
typedef FILE*IOD;
typedef id SHR;
# 62 "../../include/objcrt/objcrt.h"
typedef id(*IMP)();


typedef void(*ARGIMP)(id,SEL,void*);
# 85 "../../include/objcrt/objcrt.h"
extern BOOL msgFlag;
extern FILE*msgIOD;
extern FILE*dbgIOD;
extern BOOL allocFlag;
extern BOOL dbgFlag;
extern BOOL noCacheFlag;
extern BOOL noNilRcvr;
# 98 "../../include/objcrt/objcrt.h"
SEL selUid(STR);
STR selName(SEL);
void dbg(char*fmt,...);
void prnstack(FILE*file);
void loadobjc(void*modPtr);
void unloadobjc(void*modPtr);
# 107 "../../include/objcrt/objcrt.h"
IMP fwdimp(id,SEL,IMP);
IMP fwdimpSuper(id,SEL,IMP);
void fwdmsg(id,SEL,void*,ARGIMP);
id selptrfwd(id,SEL,id,id,id,id);


id idincref(id obj);
id idassign(id*lhs,id rhs);
id iddecref(id obj);

extern id(*_fileIn)(FILE*);
extern BOOL(*_fileOut)(FILE*,id);
extern BOOL(*_storeOn)(STR,id);
extern id(*_readFrom)(STR);
void setfilein(id(*f)(FILE*));
void setfileout(BOOL(*f)(FILE*,id));

extern id(*_showOn)(id,unsigned);

void*OC_Malloc(size_t);
void*OC_MallocAtomic(size_t);
void*OC_Calloc(size_t);
void*OC_Realloc(void*,size_t);
void*OC_Free(void*data);
# 1 "../../util/string.h"
#include <string.h>

# 32 "../../include/objpak/ocstring.h"
typedef struct objstr
{
int count;
int capacity;
char*ptr;
}*
objstr_t;
# 22 "../oclib/symbol.h"
extern id s_void;
extern id s_char;
extern id s_bool;
extern id s_int;
extern id s_uns;
extern id s_long;
extern id s_double;
extern id s_str;
extern id s_sel;
extern id s_newblock;
extern id s_main;
extern id s_objcmain;
extern id s_id;
extern id s_nil;
extern id s_self;
extern id s_cmd;
extern id s_super;
extern id s_type;
extern id s_aFiler;
extern id s_fileIn;
extern id s_fileOut;
extern id s_fileInIdsFrom;
extern id s_fileOutIdsFor;
extern id s_returnval;
extern id s_returnflag;
extern id s_increfs;
extern id s_decrefs;
extern id s_idincref;
extern id s_iddecref;

BOOL istypeword(id sym);
BOOL isbuiltinfun(id sym);
int pragmatoggle(char*s);
void definebuiltintype(char*s);
void definebuiltinfun(char*s);
void definebuiltinvar(char*s);
# 22 "../oclib/node.h"
extern FILE*gfile;
extern int inlineno;
extern id infilename;
extern int outlineno;
extern char*outfilename;
extern int exitstatus;
extern id loadedmodules;

void gc(char c);
void gextc(void);
void gcom(char*cm);
void gvarlist(id c,char*sp,char*iz);
void gcommalist(id c);
void gs(char*str);
void gf(char*fmt,...);
void gl(int no,char*fn);
void g_otbvars(void);
void gstderr(void);
void gnormal(void);
char*browsepath(char*filename);

void warn(char*fmt,...);
void warnat(id sym,char*fmt,...);
void fatal(char*fmt,...);
void fatalat(id sym,char*fmt,...);
# 23 "../oclib/util.h"
extern FILE*yyin;
extern int yyparse();

FILE*openfile(STR name,STR modfs);
FILE*reopenfile(STR name,STR modfs,FILE*of);

extern int okblock;

id mkcppdirect(char*s);
id mkexprstmt(id expr);
id mklabeledstmt(id label,id stmt);
id mkcasestmt(id keyw,id expr,id stmt);
id mkdefaultstmt(id keyw,id stmt);
id mkifstmt(id keyw,id expr,id stmt);
id mkifelsestmt(id keyw,id expr,id stmt,id ekeyw,id estmt);
id mkswitchstmt(id keyw,id expr,id stmt);
id mkwhilestmt(id keyw,id expr,id stmt);
id mkdostmt(id keyw,id stmt,id wkeyw,id expr);
id mkforstmt(id keyw,id a,id b,id c,id stmt);
id mkgotostmt(id keyw,id label);
id mkcontinuestmt(id keyw);
id mkbreakstmt(id keyw);
id mkreturnstmt(id keyw,id expr);
id mkcastexpr(id a,id b);
id mkcondexpr(id a,id b,id c);
id mkunaryexpr(STR op,id a);
id mksizeof(id a);
id mktypeof(id kw,id a);
id mkaddressof(id a);
id mkdereference(id a);
id mkbinexpr(id a,STR op,id b);
id mkcommaexpr(id a,id b);
id mkrelexpr(id a,STR op,id b);
id mkassignexpr(id a,STR op,id b);
id mkfuncall(id funname,id args);
id mkbuiltincall(id funname,id args);
id mkfunbody(id datadefs,id compound);
void declarefun(id specs,id decl);
void declaremeth(BOOL factory,id decl);
id mkfundef(id specs,id decl,id body);
id mkmethdef(BOOL factory,id decl,id body);
id mkmesgexpr(id receiver,id args);
id mkdecl(id ident);
id mkprecdecl(id tquals,id decl);
id mkarraydecl(id lhs,id ix);
id mkfundecl(id lhs,id args);
id mkprefixdecl(id lhs,id rhs);
id mkpostfixdecl(id lhs,id rhs);
id mkpointer(id specs,id pointer);
id mkbitfielddecl(id decl,id expr);
id mkstardecl(id pointer,id decl);
id mkasmop(id string,id expr);
id mkasmstmt(id keyw,id tqual,id expr,id asmop1,id asmop2,id clobbers);
id mkcompstmt(id lb,id datadefs,id stmtlist,id subblock,id rb);
id mklist(id c,id s);
id mklist2(id c,id s,id t);
id atdefsaddall(id c,id n);
id mkblockexpr(id lb,id parms,id datadefs,id stmts,id expr,id rb);
id mkclassdef(id keyw,id name,id sname,id ivars,id cvars);
id mkdatadef(id datadef,id specs,id decl,id initializer);
id mkencodeexpr(id name);
id mkenumspec(id keyw,id name,id lb,id list,id rb);
id mkenumerator(id name,id value);
id mkgnuattrib(id anyword,id exprlist);
id mkgnuattribdecl(id keyw,id list);
id mklistexpr(id lb,id x,id rb);
id mktypename(id specs,id decl);
id mkcomponentdef(id cdef,id specs,id decl);
id mkstructspec(id keyw,id name,id lb,id defs,id rb);
id mkkeywarg(id sel,id arg);
id mkkeywdecl(id sel,id cast,id arg);
id mkmethproto(id cast,id usel,id ksel,BOOL varargs);
id mkidentexpr(id name);
id mkconstexpr(id name,id schain);
id mkprecexpr(id expr);
id mkbracedgroup(id expr);
id mkarrowexpr(id array,id ix);
id mkdotexpr(id array,id ix);
id mkindexexpr(id array,id ix);
id mkpostfixexpr(id expr,id pf);
id mkparmdef(id parmdef,id specs,id decl);
id mkparmdeflist(id idents,id parmdefs,BOOL varargs);
id mkselarg(id selarg,id usel,int ncols);
id mkselectorexpr(id expr);

void procextdef(id def);
void finclassdef(void);
void datadefokblock(id datadef,id specs,id decl);

id mkfileinmeth(id classdef,id ivarnames,id ivartypes);
id mkfileoutmeth(id classdef,id ivarnames,id ivartypes);

id mkincrefsmeth(id classdef,id ivarnames,id ivartypes);
id mkdecrefsmeth(id classdef,id ivarnames,id ivartypes);
# 22 "../oclib/type.h"
extern id t_unknown;
extern id t_void;
extern id t_char;
extern id t_bool;
extern id t_int;
extern id t_long;
extern id t_uns;
extern id t_double;
extern id t_str;
extern id t_sel;
extern id t_id;
# 22 "../oclib/options.h"
void defoptions(void);

extern int o_warnings;
extern int o_gnu;
extern int o_hpux;
extern int o_vms;
extern int o_refcnt;
extern int o_ppi;
extern int o_watcom;
extern int o_ibmvac;
extern int o_msdos;
extern int o_enableasm;
extern int o_nolinetags;
extern int o_buffered;
extern int o_quiet;
extern int o_outputcode;
extern int o_version;
extern int o_otb;
extern int o_llkeyw;
extern int o_comments;
extern int o_duptypedefs;
extern int o_seltranslation;
extern int o_categories;
extern int o_blocks;
extern int o_fwd;
extern int o_selptr;
extern int o_cache;
extern int o_filer;
extern int o_selfassign;
extern char*o_bind;
extern char*o_browsedir;
extern int o_refbind;
extern int o_inlinecache;
extern int o_cplus;
extern int o_gencode;
extern int o_st80;
extern int o_selfassign;
extern int o_nilrcvr;
extern int o_shareddata;
extern int o_oneperfile;
extern int o_cvars;
extern int o_warnlex;
extern int o_warnfwd;
extern int o_warnsuggest;
extern int o_warnintvar;
extern int o_warnclasstype;
extern int o_warntypeconflict;
extern int o_warnundefined;
extern int o_warnlocalnst;
extern int o_warnnotfound;
extern int o_warnmissingmethods;
extern int o_postlink;
extern char*o_infile;
extern char*o_outfile;
extern char*o_srcfilename;
extern char*o_initcall;
extern char*o_tagformat;
extern char*o_mainfun;
extern char*o_pathsep;
extern int o_debuginfo;
extern int o_checkbind;
extern int o_linemax;
extern int o_structassign;
extern id o_stepbreak;
extern int o_stepnext;
# 45 "lex.lm"
extern id yylval;

int identif(void);
int keyw(int x);
int tkeyw(int x,id t);
int gnukeyw(int x);
int msdoskeyw(int x);
int watcomkeyw(int x);
int ibmvackeyw(int x);


int okblock;
# 1 "../../util/unistd.h"
#include <unistd.h>

# 1062 "lex.yy.c"
static int yy_init_globals(void);
# 1072 "lex.yy.c"
extern int yywrap(void);
# 1076 "lex.yy.c"
static void yyunput(int c,char*buf_ptr);
# 1091 "lex.yy.c"
static int input(void);

# 22 "../oclib/dasmstmt.h"
extern id  DosAsmStmt;

# 1193 "lex.yy.c"
int yylex_raw()
{
register yy_state_type yy_current_state;
register char*yy_cp,*yy_bp;
register int yy_act;
# 1204 "lex.yy.c"
if( !(yy_init))
{
(yy_init)=1;
# 1212 "lex.yy.c"
if( !(yy_start))
(yy_start)=1;

if( !yyin)
yyin=stdin;

if( !yyout)
yyout=stdout;

if( !((yy_buffer_stack)?(yy_buffer_stack)[(yy_buffer_stack_top)]:NULL)){
yyensure_buffer_stack();
(yy_buffer_stack)[(yy_buffer_stack_top)]=
yy_create_buffer(yyin,16384);
}

yy_load_buffer_state();
}

while(1)
{
yy_cp=(yy_c_buf_p); *


yy_cp=(yy_hold_char);
# 1240 "lex.yy.c"
yy_bp=yy_cp;

yy_current_state=(yy_start);
yy_match:
do
{
register YY_CHAR yy_c=yy_ec[((unsigned int)(unsigned char) *yy_cp)];
if(yy_accept[yy_current_state])
{
(yy_last_accepting_state)=yy_current_state;
(yy_last_accepting_cpos)=yy_cp;
}
while(yy_chk[yy_base[yy_current_state]+yy_c]!=yy_current_state)
{
yy_current_state=(int)yy_def[yy_current_state];
if(yy_current_state>=700)
yy_c=yy_meta[(unsigned int)yy_c];
}
yy_current_state=yy_nxt[yy_base[yy_current_state]+(unsigned int)yy_c]; ++
yy_cp;
}
while(yy_base[yy_current_state]!=1253);

yy_find_action:
yy_act=yy_accept[yy_current_state];
if(yy_act==0)
{
yy_cp=(yy_last_accepting_cpos);
yy_current_state=(yy_last_accepting_state);
yy_act=yy_accept[yy_current_state];
}

(yytext)=yy_bp;yyleng=(size_t)(yy_cp-yy_bp);(yy_hold_char)= *yy_cp; *yy_cp='\0';(yy_c_buf_p)=yy_cp;;

do_action:

switch(yy_act)
{
case 0: *

yy_cp=(yy_hold_char);
yy_cp=(yy_last_accepting_cpos);
yy_current_state=(yy_last_accepting_state);
goto yy_find_action;

case 1:
# 93 "lex.lm"
{return keyw(262);}
break;
case 2:
# 94 "lex.lm"
{return keyw(261);}
break;
case 3:
# 95 "lex.lm"
{return keyw(277);}
break;
case 4:
# 96 "lex.lm"
{return keyw(275);}
break;
case 5:
# 97 "lex.lm"
{return keyw(261);}
break;
case 6:
# 98 "lex.lm"
{return keyw(261);}
break;
case 7:
# 99 "lex.lm"
{return keyw(278);}
break;
case 8:
# 100 "lex.lm"
{return keyw(276);}
break;
case 9:
# 101 "lex.lm"
{return keyw(272);}
break;
case 10:
# 102 "lex.lm"
{return keyw(261);}
break;
case 11:
# 103 "lex.lm"
{return keyw(270);}
break;
case 12:
# 104 "lex.lm"
{return keyw(267);}
break;
case 13:
# 105 "lex.lm"
{if(o_cplus)return keyw(265);}
break;
case 14:
# 106 "lex.lm"
{if(o_cplus)return keyw(265);}
break;
case 15:
# 107 "lex.lm"
{return keyw(262);}
break;
case 16:
# 108 "lex.lm"
{return keyw(261);}
break;
case 17:
# 109 "lex.lm"
{return keyw(273);}
break;
case 18:
# 110 "lex.lm"
{return keyw(280);}
break;
case 19:
# 111 "lex.lm"
{return keyw(269);}
break;
case 20:
# 112 "lex.lm"
{return keyw(261);}
break;
case 21:
# 113 "lex.lm"
{return keyw(261);}
break;
case 22:
# 114 "lex.lm"
{return keyw(261);}
break;
case 23:
# 115 "lex.lm"
{return keyw(262);}
break;
case 24:
# 116 "lex.lm"
{return keyw(279);}
break;
case 25:
# 117 "lex.lm"
{return keyw(261);}
break;
case 26:
# 118 "lex.lm"
{return keyw(282);}
break;
case 27:
# 119 "lex.lm"
{return keyw(262);}
break;
case 28:
# 120 "lex.lm"
{return keyw(268);}
break;
case 29:
# 121 "lex.lm"
{return keyw(274);}
break;
case 30:
# 122 "lex.lm"
{return keyw((o_duptypedefs)?263:262);}
break;
case 31:
# 123 "lex.lm"
{return keyw(268);}
break;
case 32:
# 124 "lex.lm"
{return keyw(261);}
break;
case 33:
# 125 "lex.lm"
{return keyw(261);}
break;
case 34:
# 126 "lex.lm"
{return keyw(271);}
break;
case 35:
# 128 "lex.lm"
{return(o_cplus)?keyw(261):identif();}
break;
case 36:
# 129 "lex.lm"
{return(o_cplus)?keyw(261):identif();}
break;
case 37:
# 130 "lex.lm"
{return(o_cplus)?keyw(261):identif();}
break;
case 38:
# 132 "lex.lm"
{return keyw(264);}
break;
case 39:
# 133 "lex.lm"
{return keyw(264);}
break;
case 40:
# 134 "lex.lm"
{return keyw(261);}
break;
case 41:
# 135 "lex.lm"
{return keyw(264);}
break;
case 42:
# 137 "lex.lm"
{return keyw(294);}
break;
case 43:
# 138 "lex.lm"
{return keyw(295);}
break;
case 44:
# 139 "lex.lm"
{return keyw(296);}
break;
case 45:
# 140 "lex.lm"
{return keyw(296);}
break;
case 46:
# 141 "lex.lm"
{return keyw(297);}
break;
case 47:
# 142 "lex.lm"
{return keyw(298);}
break;
case 48:
# 143 "lex.lm"
{return keyw(261);}
break;
case 49:
# 144 "lex.lm"
{return keyw(299);}
break;
case 50:
# 145 "lex.lm"
{warn("ignoring @public.");}
break;
case 51:
# 146 "lex.lm"
{warn("ignoring @protected.");}
break;
case 52:
# 147 "lex.lm"
{warn("ignoring @private.");}
break;
case 53:
# 149 "lex.lm"
{return keyw(262);}
break;
case 54:
# 151 "lex.lm"
{return(o_enableasm)?keyw(281):identif();}
break;
case 55:
# 152 "lex.lm"
{
id objcT0;

# 152 "lex.lm"
yylval=(objcT0=DosAsmStmt,(*(id(*)(id,SEL,STR))_imp(objcT0,selTransTbl[0]))(objcT0,selTransTbl[0],yytext));return 285;}
break;
case 56:
# 154 "lex.lm"
{
id objcT1;

# 154 "lex.lm"
yylval=(objcT1=DosAsmStmt,(*(id(*)(id,SEL,STR))_imp(objcT1,selTransTbl[0]))(objcT1,selTransTbl[0],yytext));return 285;}
break;
case 57:
# 157 "lex.lm"
{return gnukeyw(264);}
break;
case 58:
# 158 "lex.lm"
{return gnukeyw(264);}
break;
case 59:
# 159 "lex.lm"
{return gnukeyw(264);}
break;
case 60:
# 160 "lex.lm"
{return gnukeyw(264);}
break;
case 61:
# 161 "lex.lm"
{return gnukeyw(261);}
break;
case 62:
# 162 "lex.lm"
{return gnukeyw(261);}
break;
case 63:
# 163 "lex.lm"
{return gnukeyw(261);}
break;
case 64:
# 164 "lex.lm"
{return gnukeyw(261);}
break;
case 65:
# 165 "lex.lm"
{return gnukeyw(302);}
break;
case 66:
# 166 "lex.lm"
{return keyw(281);}
break;
case 67:
# 167 "lex.lm"
{return keyw(281);}
break;
case 68:
# 168 "lex.lm"
{return keyw(262);}
break;
case 69:
# 169 "lex.lm"
{return keyw(262);}
break;
case 70:
# 170 "lex.lm"
{return keyw(262);}
break;
case 71:
# 171 "lex.lm"
{return gnukeyw(301);}
break;
case 72:
# 172 "lex.lm"
{return gnukeyw(283);}
break;
case 73:
# 173 "lex.lm"
{return gnukeyw(264);}
break;
case 74:
# 174 "lex.lm"
{return gnukeyw(264);}
break;
case 75:
# 176 "lex.lm"
{return msdoskeyw(264);}
break;
case 76:
# 177 "lex.lm"
{return msdoskeyw(264);}
break;
case 77:
# 178 "lex.lm"
{return msdoskeyw(264);}
break;
case 78:
# 179 "lex.lm"
{return msdoskeyw(264);}
break;
case 79:
# 180 "lex.lm"
{return msdoskeyw(264);}
break;
case 80:
# 181 "lex.lm"
{return msdoskeyw(264);}
break;
case 81:
# 182 "lex.lm"
{return msdoskeyw(264);}
break;
case 82:
# 183 "lex.lm"
{return msdoskeyw(264);}
break;
case 83:
# 184 "lex.lm"
{return msdoskeyw(264);}
break;
case 84:
# 185 "lex.lm"
{return msdoskeyw(264);}
break;
case 85:
# 186 "lex.lm"
{return msdoskeyw(264);}
break;
case 86:
# 187 "lex.lm"
{return msdoskeyw(264);}
break;
case 87:
# 188 "lex.lm"
{return msdoskeyw(264);}
break;
case 88:
# 189 "lex.lm"
{return msdoskeyw(264);}
break;
case 89:
# 190 "lex.lm"
{return msdoskeyw(264);}
break;
case 90:
# 191 "lex.lm"
{return msdoskeyw(264);}
break;
case 91:
# 193 "lex.lm"
{

return(o_llkeyw)?keyw(261):identif();
}
break;
case 92:
# 198 "lex.lm"
{

return watcomkeyw(261);
}
break;
case 93:
# 202 "lex.lm"
{return watcomkeyw(264);}
break;
case 94:
# 203 "lex.lm"
{return watcomkeyw(264);}
break;
case 95:
# 204 "lex.lm"
{return watcomkeyw(264);}
break;
case 96:
# 205 "lex.lm"
{return watcomkeyw(264);}
break;
case 97:
# 206 "lex.lm"
{return watcomkeyw(264);}
break;
case 98:
# 207 "lex.lm"
{return watcomkeyw(264);}
break;
case 99:
# 208 "lex.lm"
{return watcomkeyw(264);}
break;
case 100:
# 209 "lex.lm"
{return watcomkeyw(264);}
break;
case 101:
# 210 "lex.lm"
{return watcomkeyw(264);}
break;
case 102:
# 211 "lex.lm"
{return watcomkeyw(264);}
break;
case 103:
# 212 "lex.lm"
{return watcomkeyw(264);}
break;
case 104:
# 213 "lex.lm"
{return watcomkeyw(264);}
break;
case 105:
# 214 "lex.lm"
{return watcomkeyw(264);}
break;
case 106:
# 215 "lex.lm"
{return watcomkeyw(264);}
break;
case 107:
# 216 "lex.lm"
{return watcomkeyw(264);}
break;
case 108:
# 218 "lex.lm"
{return ibmvackeyw(264);}
break;
case 109:
# 219 "lex.lm"
{return ibmvackeyw(264);}
break;
case 110:
# 220 "lex.lm"
{return ibmvackeyw(264);}
break;
case 111:
# 222 "lex.lm"
{
okblock=0;
return'(';
}
break;
case 112:
# 226 "lex.lm"
{return')';}
break;
case 113:
# 227 "lex.lm"
{return'[';}
break;
case 114:
# 228 "lex.lm"
{return']';}
break;
case 115:
# 229 "lex.lm"
{return keyw(293);}
break;
case 116:
# 230 "lex.lm"
{return'.';}
break;
case 117:
# 231 "lex.lm"
{return'!';}
break;
case 118:
# 232 "lex.lm"
{return'~';}
break;
case 119:
# 233 "lex.lm"
{return keyw(290);}
break;
case 120:
# 234 "lex.lm"
{return keyw(290);}
break;
case 121:
# 235 "lex.lm"
{return'*';}
break;
case 122:
# 236 "lex.lm"
{return'/';}
break;
case 123:
# 237 "lex.lm"
{return'%';}
break;
case 124:
# 238 "lex.lm"
{return'+';}
break;
case 125:
# 239 "lex.lm"
{return'-';}
break;
case 126:
# 240 "lex.lm"
{return keyw(289);}
break;
case 127:
# 241 "lex.lm"
{return keyw(289);}
break;
case 128:
# 242 "lex.lm"
{return keyw(288);}
break;
case 129:
# 243 "lex.lm"
{return keyw(288);}
break;
case 130:
# 244 "lex.lm"
{return keyw(288);}
break;
case 131:
# 245 "lex.lm"
{return keyw(288);}
break;
case 132:
# 246 "lex.lm"
{return keyw(287);}
break;
case 133:
# 247 "lex.lm"
{return keyw(288);}
break;
case 134:
# 248 "lex.lm"
{return'&';}
break;
case 135:
# 249 "lex.lm"
{return'^';}
break;
case 136:
# 250 "lex.lm"
{return'|';}
break;
case 137:
# 251 "lex.lm"
{return 291;}
break;
case 138:
# 252 "lex.lm"
{return 292;}
break;
case 139:
# 253 "lex.lm"
{return'?';}
break;
case 140:
# 254 "lex.lm"
{return':';}
break;
case 141:
# 255 "lex.lm"
{return'=';}
break;
case 142:
# 256 "lex.lm"
{return keyw(286);}
break;
case 143:
# 257 "lex.lm"
{return keyw(286);}
break;
case 144:
# 258 "lex.lm"
{return keyw(286);}
break;
case 145:
# 259 "lex.lm"
{return keyw(286);}
break;
case 146:
# 260 "lex.lm"
{return keyw(286);}
break;
case 147:
# 261 "lex.lm"
{return keyw(286);}
break;
case 148:
# 262 "lex.lm"
{return keyw(286);}
break;
case 149:
# 263 "lex.lm"
{return keyw(286);}
break;
case 150:
# 264 "lex.lm"
{return keyw(286);}
break;
case 151:
# 265 "lex.lm"
{return keyw(286);}
break;
case 152:
# 266 "lex.lm"
{return',';}
break;
case 153:
# 267 "lex.lm"
{return';';}
break;
case 154:
# 268 "lex.lm"
{return keyw((okblock)?(okblock=0,300):('{'));}
break;
case 155:
# 269 "lex.lm"
{return keyw('}');}
break;
case 156:
# 271 "lex.lm"
{return keyw(284);}
break;
case 157:
# 273 "lex.lm"
{return keyw(297);}
break;
case 158:
# 275 "lex.lm"
{;}
break;
case 159:
# 277 "lex.lm"
{inlineno++;}
break;
case 160:
# 279 "lex.lm"
{

yylval=mkcppdirect(yytext);
if(yylval){inlineno++;return 266;}
}
break;
case 161:
# 285 "lex.lm"
{
return tkeyw(259,t_str);
}
break;
case 162:
# 289 "lex.lm"
{
return(o_gnu)?tkeyw(259,t_str):identif();
}
break;
case 163:
# 293 "lex.lm"
{


return tkeyw(258,t_char);
}
break;
case 164:
# 299 "lex.lm"
{
return tkeyw(258,t_int);
}
break;
case 165:
# 303 "lex.lm"
{
return tkeyw(258,t_int);
}
break;
case 166:
# 307 "lex.lm"
{
return tkeyw(258,t_int);
}
break;
case 167:
# 311 "lex.lm"
{
return tkeyw(258,t_double);
}
break;
case 168:
# 315 "lex.lm"
{
return tkeyw(258,t_double);
}
break;
case 169:
# 319 "lex.lm"
{
return tkeyw(258,t_double);
}
break;
case 170:
# 323 "lex.lm"
{
return identif();
}
break;
case 171:
# 327 "lex.lm"
{;

}
break;
case 172:
# 331 "lex.lm"
{
if(o_warnlex){
char c=(yytext)[0];
warn("lex ignoring '0x%x' (%c)",(int)c,c);
}
}
break;
case 173:
# 338 "lex.lm"
(void)fwrite(yytext,yyleng,1,yyout);
break;
# 2199 "lex.yy.c"
case(174+0+1):
return 0;

case 174:
{

int yy_amount_of_matched_text=(int)(yy_cp-(yytext))-1; *


yy_cp=(yy_hold_char);


if((yy_buffer_stack)[(yy_buffer_stack_top)]->yy_buffer_status==0)
{
# 2222 "lex.yy.c"
(yy_n_chars)=(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_n_chars;
(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_input_file=yyin;
(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_buffer_status=1;
}
# 2234 "lex.yy.c"
if((yy_c_buf_p)<= &(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_ch_buf[(yy_n_chars)])
{
yy_state_type yy_next_state;

(yy_c_buf_p)=(yytext)+yy_amount_of_matched_text;

yy_current_state=yy_get_previous_state();
# 2251 "lex.yy.c"
yy_next_state=yy_try_NUL_trans(yy_current_state);

yy_bp=(yytext)+0;

if(yy_next_state)
{

yy_cp= ++(yy_c_buf_p);
yy_current_state=yy_next_state;
goto yy_match;
}

else
{
yy_cp=(yy_c_buf_p);
goto yy_find_action;
}
}

else switch(yy_get_next_buffer())
{
case 1:
{
(yy_did_buffer_switch_on_eof)=0;

if(yywrap())
{
# 2287 "lex.yy.c"
(yy_c_buf_p)=(yytext)+0;

yy_act=(174+(((yy_start)-1)/2)+1);
goto do_action;
}

else
{
if( !(yy_did_buffer_switch_on_eof))
yyrestart(yyin);
}
break;
}

case 0:
(yy_c_buf_p)=
(yytext)+yy_amount_of_matched_text;

yy_current_state=yy_get_previous_state();

yy_cp=(yy_c_buf_p);
yy_bp=(yytext)+0;
goto yy_match;

case 2:
(yy_c_buf_p)= &
(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_ch_buf[(yy_n_chars)];

yy_current_state=yy_get_previous_state();

yy_cp=(yy_c_buf_p);
yy_bp=(yytext)+0;
goto yy_find_action;
}
break;
}

default:
yy_fatal_error("fatal flex scanner internal error--no action found");

}
}
}

# 2338 "lex.yy.c"
static int yy_get_next_buffer(void)
{
register char*dest=(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_ch_buf;
register char*source=(yytext);
register int number_to_move,i;
int ret_val;

if((yy_c_buf_p)> &(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_ch_buf[(yy_n_chars)+1])
yy_fatal_error("fatal flex scanner internal error--end of buffer missed");


if((yy_buffer_stack)[(yy_buffer_stack_top)]->yy_fill_buffer==0)
{
if((yy_c_buf_p)-(yytext)-0==1)
{
# 2356 "lex.yy.c"
return 1;
}

else
{
# 2364 "lex.yy.c"
return 2;
}
}
# 2371 "lex.yy.c"
number_to_move=(int)((yy_c_buf_p)-(yytext))-1;

for(i=0;i<number_to_move; ++i) *
(dest++)= *(source++);

if((yy_buffer_stack)[(yy_buffer_stack_top)]->yy_buffer_status==2)
# 2380 "lex.yy.c"
(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_n_chars=(yy_n_chars)=0;

else
{
int num_to_read=
(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_buf_size-number_to_move-1;

while(num_to_read<=0)
{


YY_BUFFER_STATE b=((yy_buffer_stack)?(yy_buffer_stack)[(yy_buffer_stack_top)]:NULL);

int yy_c_buf_p_offset=
(int)((yy_c_buf_p)-b->yy_ch_buf);

if(b->yy_is_our_buffer)
{
int new_size=b->yy_buf_size*2;

if(new_size<=0)
b->yy_buf_size+=b->yy_buf_size/8;
else
b->yy_buf_size*=2;

b->yy_ch_buf=(char*)

yyrealloc((void*)b->yy_ch_buf,b->yy_buf_size+2);
}
else

b->yy_ch_buf=0;

if( !b->yy_ch_buf)
yy_fatal_error("fatal error - scanner input buffer overflow");


(yy_c_buf_p)= &b->yy_ch_buf[yy_c_buf_p_offset];

num_to_read=(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_buf_size-
number_to_move-1;

}

if(num_to_read>8192)
num_to_read=8192;


if((yy_buffer_stack)[(yy_buffer_stack_top)]->yy_is_interactive){int c='*';size_t n;for(n=0;n<num_to_read&&(c=getc(yyin))!=EOF&&c!='\n'; ++n)( &(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_ch_buf[number_to_move])[n]=(char)c;if(c=='\n')( &(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_ch_buf[number_to_move])[n++]=(char)c;if(c==EOF&&ferror(yyin))yy_fatal_error("input in flex scanner failed");(yy_n_chars)=n;}else{errno=0;while(((yy_n_chars)=fread(( &(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_ch_buf[number_to_move]),1,num_to_read,yyin))==0&&ferror(yyin)){if(errno!=EINTR){yy_fatal_error("input in flex scanner failed");break;}errno=0;clearerr(yyin);}};


(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_n_chars=(yy_n_chars);
}

if((yy_n_chars)==0)
{
if(number_to_move==0)
{
ret_val=1;
yyrestart(yyin);
}

else
{
ret_val=2;
(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_buffer_status=
2;
}
}

else
ret_val=0;

(yy_n_chars)+=number_to_move;
(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_ch_buf[(yy_n_chars)]=0;
(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_ch_buf[(yy_n_chars)+1]=0;

(yytext)= &(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_ch_buf[0];

return ret_val;
}



static yy_state_type yy_get_previous_state(void)
{
register yy_state_type yy_current_state;
register char*yy_cp;

yy_current_state=(yy_start);

for(yy_cp=(yytext)+0;yy_cp<(yy_c_buf_p); ++yy_cp)
{
register YY_CHAR yy_c=( *yy_cp?yy_ec[((unsigned int)(unsigned char) *yy_cp)]:1);
if(yy_accept[yy_current_state])
{
(yy_last_accepting_state)=yy_current_state;
(yy_last_accepting_cpos)=yy_cp;
}
while(yy_chk[yy_base[yy_current_state]+yy_c]!=yy_current_state)
{
yy_current_state=(int)yy_def[yy_current_state];
if(yy_current_state>=700)
yy_c=yy_meta[(unsigned int)yy_c];
}
yy_current_state=yy_nxt[yy_base[yy_current_state]+(unsigned int)yy_c];
}

return yy_current_state;
}

# 2496 "lex.yy.c"
static yy_state_type yy_try_NUL_trans(yy_state_type yy_current_state)
{
register int yy_is_jam;
register char*yy_cp=(yy_c_buf_p);

register YY_CHAR yy_c=1;
if(yy_accept[yy_current_state])
{
(yy_last_accepting_state)=yy_current_state;
(yy_last_accepting_cpos)=yy_cp;
}
while(yy_chk[yy_base[yy_current_state]+yy_c]!=yy_current_state)
{
yy_current_state=(int)yy_def[yy_current_state];
if(yy_current_state>=700)
yy_c=yy_meta[(unsigned int)yy_c];
}
yy_current_state=yy_nxt[yy_base[yy_current_state]+(unsigned int)yy_c];
yy_is_jam=(yy_current_state==699);

return yy_is_jam?0:yy_current_state;
}

static void yyunput(int c,char*yy_bp)
{
register char*yy_cp;

yy_cp=(yy_c_buf_p); *


yy_cp=(yy_hold_char);

if(yy_cp<(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_ch_buf+2)
{

register int number_to_move=(yy_n_chars)+2;
register char*dest= &(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_ch_buf[
(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_buf_size+2];
register char*source= &
(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_ch_buf[number_to_move];

while(source>(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_ch_buf) * --
dest= * --source;

yy_cp+=(int)(dest-source);
yy_bp+=(int)(dest-source);
(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_n_chars=
(yy_n_chars)=(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_buf_size;

if(yy_cp<(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_ch_buf+2)
yy_fatal_error("flex scanner push-back overflow");
} * --

yy_cp=(char)c;

(yytext)=yy_bp;
(yy_hold_char)= *yy_cp;
(yy_c_buf_p)=yy_cp;
}

# 2560 "lex.yy.c"
static int input(void)


{
int c; *

(yy_c_buf_p)=(yy_hold_char);

if( *(yy_c_buf_p)==0)
{
# 2574 "lex.yy.c"
if((yy_c_buf_p)< &(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_ch_buf[(yy_n_chars)]) *

(yy_c_buf_p)='\0';

else
{
int offset=(yy_c_buf_p)-(yytext); ++
(yy_c_buf_p);

switch(yy_get_next_buffer())
{
case 2:
# 2597 "lex.yy.c"
yyrestart(yyin);
# 2601 "lex.yy.c"
case 1:
{
if(yywrap())
return EOF;

if( !(yy_did_buffer_switch_on_eof))
yyrestart(yyin);
# 2611 "lex.yy.c"
return input();

}

case 0:
(yy_c_buf_p)=(yytext)+offset;
break;
}
}
}

c= *(unsigned char*)(yy_c_buf_p); *
(yy_c_buf_p)='\0';
(yy_hold_char)= * ++(yy_c_buf_p);

return c;
}

# 2635 "lex.yy.c"
void yyrestart(FILE*input_file)
{

if( !((yy_buffer_stack)?(yy_buffer_stack)[(yy_buffer_stack_top)]:NULL)){
yyensure_buffer_stack();
(yy_buffer_stack)[(yy_buffer_stack_top)]=
yy_create_buffer(yyin,16384);
}

yy_init_buffer(((yy_buffer_stack)?(yy_buffer_stack)[(yy_buffer_stack_top)]:NULL),input_file);
yy_load_buffer_state();
}

# 2652 "lex.yy.c"
void yy_switch_to_buffer(YY_BUFFER_STATE new_buffer)
{
# 2660 "lex.yy.c"
yyensure_buffer_stack();
if(((yy_buffer_stack)?(yy_buffer_stack)[(yy_buffer_stack_top)]:NULL)==new_buffer)
return;

if(((yy_buffer_stack)?(yy_buffer_stack)[(yy_buffer_stack_top)]:NULL))
{ *

(yy_c_buf_p)=(yy_hold_char);
(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_buf_pos=(yy_c_buf_p);
(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_n_chars=(yy_n_chars);
}

(yy_buffer_stack)[(yy_buffer_stack_top)]=new_buffer;
yy_load_buffer_state();
# 2680 "lex.yy.c"
(yy_did_buffer_switch_on_eof)=1;
}

static void yy_load_buffer_state(void)
{
(yy_n_chars)=(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_n_chars;
(yytext)=(yy_c_buf_p)=(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_buf_pos;
yyin=(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_input_file;
(yy_hold_char)= *(yy_c_buf_p);
}

# 2697 "lex.yy.c"
YY_BUFFER_STATE yy_create_buffer(FILE*file,int size)
{
YY_BUFFER_STATE b;

b=(YY_BUFFER_STATE)yyalloc(sizeof(struct yy_buffer_state));
if( !b)
yy_fatal_error("out of dynamic memory in yy_create_buffer()");

b->yy_buf_size=size;
# 2710 "lex.yy.c"
b->yy_ch_buf=(char*)yyalloc(b->yy_buf_size+2);
if( !b->yy_ch_buf)
yy_fatal_error("out of dynamic memory in yy_create_buffer()");

b->yy_is_our_buffer=1;

yy_init_buffer(b,file);

return b;
}

# 2725 "lex.yy.c"
void yy_delete_buffer(YY_BUFFER_STATE b)
{

if( !b)
return;

if(b==((yy_buffer_stack)?(yy_buffer_stack)[(yy_buffer_stack_top)]:NULL))
(yy_buffer_stack)[(yy_buffer_stack_top)]=(YY_BUFFER_STATE)0;

if(b->yy_is_our_buffer)
yyfree((void*)b->yy_ch_buf);

yyfree((void*)b);
}


extern int isatty(int);

# 2748 "lex.yy.c"
static void yy_init_buffer(YY_BUFFER_STATE b,FILE*file)

{
int oerrno=errno;

yy_flush_buffer(b);

b->yy_input_file=file;
b->yy_fill_buffer=1;
# 2762 "lex.yy.c"
if(b!=((yy_buffer_stack)?(yy_buffer_stack)[(yy_buffer_stack_top)]:NULL)){
b->yy_bs_lineno=1;
b->yy_bs_column=0;
}

b->yy_is_interactive=file?(isatty(fileno(file))>0):0;

errno=oerrno;
}

# 2776 "lex.yy.c"
void yy_flush_buffer(YY_BUFFER_STATE b)
{
if( !b)
return;

b->yy_n_chars=0;
# 2787 "lex.yy.c"
b->yy_ch_buf[0]=0;
b->yy_ch_buf[1]=0;

b->yy_buf_pos= &b->yy_ch_buf[0];

b->yy_at_bol=1;
b->yy_buffer_status=0;

if(b==((yy_buffer_stack)?(yy_buffer_stack)[(yy_buffer_stack_top)]:NULL))
yy_load_buffer_state();
}

# 2805 "lex.yy.c"
void yypush_buffer_state(YY_BUFFER_STATE new_buffer)
{
if(new_buffer==NULL)
return;

yyensure_buffer_stack();


if(((yy_buffer_stack)?(yy_buffer_stack)[(yy_buffer_stack_top)]:NULL))
{ *

(yy_c_buf_p)=(yy_hold_char);
(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_buf_pos=(yy_c_buf_p);
(yy_buffer_stack)[(yy_buffer_stack_top)]->yy_n_chars=(yy_n_chars);
}


if(((yy_buffer_stack)?(yy_buffer_stack)[(yy_buffer_stack_top)]:NULL))
(yy_buffer_stack_top)++;
(yy_buffer_stack)[(yy_buffer_stack_top)]=new_buffer;


yy_load_buffer_state();
(yy_did_buffer_switch_on_eof)=1;
}

# 2835 "lex.yy.c"
void yypop_buffer_state(void)
{
if( !((yy_buffer_stack)?(yy_buffer_stack)[(yy_buffer_stack_top)]:NULL))
return;

yy_delete_buffer(((yy_buffer_stack)?(yy_buffer_stack)[(yy_buffer_stack_top)]:NULL));
(yy_buffer_stack)[(yy_buffer_stack_top)]=NULL;
if((yy_buffer_stack_top)>0) --
(yy_buffer_stack_top);

if(((yy_buffer_stack)?(yy_buffer_stack)[(yy_buffer_stack_top)]:NULL)){
yy_load_buffer_state();
(yy_did_buffer_switch_on_eof)=1;
}
}

# 2854 "lex.yy.c"
static void yyensure_buffer_stack(void)
{
int num_to_alloc;

if( !(yy_buffer_stack)){
# 2864 "lex.yy.c"
num_to_alloc=1;
(yy_buffer_stack)=(struct yy_buffer_state**)yyalloc(
num_to_alloc*sizeof(struct yy_buffer_state*));


memset((yy_buffer_stack),0,num_to_alloc*sizeof(struct yy_buffer_state*));

(yy_buffer_stack_max)=num_to_alloc;
(yy_buffer_stack_top)=0;
return;
}

if((yy_buffer_stack_top)>=((yy_buffer_stack_max))-1){


int grow_size=8;

num_to_alloc=(yy_buffer_stack_max)+grow_size;
(yy_buffer_stack)=(struct yy_buffer_state**)yyrealloc(
(yy_buffer_stack),
num_to_alloc*sizeof(struct yy_buffer_state*));
# 2888 "lex.yy.c"
memset((yy_buffer_stack)+(yy_buffer_stack_max),0,grow_size*sizeof(struct yy_buffer_state*));
(yy_buffer_stack_max)=num_to_alloc;
}
}

# 2899 "lex.yy.c"
YY_BUFFER_STATE yy_scan_buffer(char*base,yy_size_t size)
{
YY_BUFFER_STATE b;

if(size<2||
base[size-2]!=0||
base[size-1]!=0)

return 0;

b=(YY_BUFFER_STATE)yyalloc(sizeof(struct yy_buffer_state));
if( !b)
yy_fatal_error("out of dynamic memory in yy_scan_buffer()");

b->yy_buf_size=size-2;
b->yy_buf_pos=b->yy_ch_buf=base;
b->yy_is_our_buffer=0;
b->yy_input_file=0;
b->yy_n_chars=b->yy_buf_size;
b->yy_is_interactive=0;
b->yy_at_bol=1;
b->yy_fill_buffer=0;
b->yy_buffer_status=0;

yy_switch_to_buffer(b);

return b;
}

# 2936 "lex.yy.c"
YY_BUFFER_STATE yy_scan_string(const char*yystr)
{

return yy_scan_bytes(yystr,strlen(yystr));
}

# 2949 "lex.yy.c"
YY_BUFFER_STATE yy_scan_bytes(const char*yybytes,int _yybytes_len)
{
YY_BUFFER_STATE b;
char*buf;
yy_size_t n;
int i;


n=_yybytes_len+2;
buf=(char*)yyalloc(n);
if( !buf)
yy_fatal_error("out of dynamic memory in yy_scan_bytes()");

for(i=0;i<_yybytes_len; ++i)
buf[i]=yybytes[i];

buf[_yybytes_len]=buf[_yybytes_len+1]=0;

b=yy_scan_buffer(buf,n);
if( !b)
yy_fatal_error("bad buffer in yy_scan_bytes()");
# 2974 "lex.yy.c"
b->yy_is_our_buffer=1;

return b;
}

# 2983 "lex.yy.c"
static void yy_fatal_error(const char*msg)
{
(void)fprintf(stderr,"%s\n",msg);
exit(2);
}

# 3011 "lex.yy.c"
int yyget_lineno(void)
{

return yylineno;
}

# 3020 "lex.yy.c"
FILE*yyget_in(void)
{
return yyin;
}

# 3028 "lex.yy.c"
FILE*yyget_out(void)
{
return yyout;
}

# 3036 "lex.yy.c"
int yyget_leng(void)
{
return yyleng;
}

# 3045 "lex.yy.c"
char*yyget_text(void)
{
return yytext;
}

# 3054 "lex.yy.c"
void yyset_lineno(int line_number)
{

yylineno=line_number;
}

# 3066 "lex.yy.c"
void yyset_in(FILE*in_str)
{
yyin=in_str;
}

void yyset_out(FILE*out_str)
{
yyout=out_str;
}

int yyget_debug(void)
{
return yy_flex_debug;
}

void yyset_debug(int bdebug)
{
yy_flex_debug=bdebug;
}

static int yy_init_globals(void)
{
# 3092 "lex.yy.c"
(yy_buffer_stack)=0;
(yy_buffer_stack_top)=0;
(yy_buffer_stack_max)=0;
(yy_c_buf_p)=(char*)0;
(yy_init)=0;
(yy_start)=0;
# 3104 "lex.yy.c"
yyin=(FILE*)0;
yyout=(FILE*)0;
# 3111 "lex.yy.c"
return 0;
}


int yylex_destroy(void)
{


while(((yy_buffer_stack)?(yy_buffer_stack)[(yy_buffer_stack_top)]:NULL)){
yy_delete_buffer(((yy_buffer_stack)?(yy_buffer_stack)[(yy_buffer_stack_top)]:NULL));
(yy_buffer_stack)[(yy_buffer_stack_top)]=NULL;
yypop_buffer_state();
}


yyfree((yy_buffer_stack));
(yy_buffer_stack)=NULL;
# 3131 "lex.yy.c"
yy_init_globals();

return 0;
}

# 3160 "lex.yy.c"
void*yyalloc(yy_size_t size)
{
return(void*)malloc(size);
}

void*yyrealloc(void*ptr,yy_size_t size)
{
# 3174 "lex.yy.c"
return(void*)realloc((char*)ptr,size);
}

void yyfree(void*ptr)
{
free((char*)ptr);
}

# 346 "lex.lm"
void yyerror(char*str)
{
fatal("%s \"%s\"",str,yytext);
}

# 354 "lex.lm"
int yywrap(){return 1;}

# 59 "../oclib/symbol.h"
extern id  Symbol;

# 357 "lex.lm"
int identif(void)
{
id objcT2;

# 359 "lex.lm"
yylval=(objcT2=Symbol,(*(id(*)(id,SEL,char*,int,id))_imp(objcT2,selTransTbl[1]))(objcT2,selTransTbl[1],yytext,inlineno,infilename));
if( !o_duptypedefs){
if(isbuiltinfun(yylval))return 260;
if(istypeword(yylval))return 261;
}
return 257;
}

# 22 "../oclib/stclass.h"
extern id  Storageclass;

# 367 "lex.lm"
int keyw(int x)
{
if(x==262||x==263||x==265||x==301){
id objcT3;

# 370 "lex.lm"
yylval=(objcT3=Storageclass,(*(id(*)(id,SEL,char*,int,id))_imp(objcT3,selTransTbl[1]))(objcT3,selTransTbl[1],yytext,inlineno,infilename));
}else{
id objcT4;

# 372 "lex.lm"
yylval=(objcT4=Symbol,(*(id(*)(id,SEL,char*,int,id))_imp(objcT4,selTransTbl[1]))(objcT4,selTransTbl[1],yytext,inlineno,infilename));
}
return x;
}

int tkeyw(int x,id t)
{
id objcT5,objcT6;

# 379 "lex.lm"
yylval=(objcT5=Symbol,(*(id(*)(id,SEL,char*,int,id))_imp(objcT5,selTransTbl[1]))(objcT5,selTransTbl[1],yytext,inlineno,infilename));
(objcT6=yylval,(*_imp(objcT6,selTransTbl[2]))(objcT6,selTransTbl[2],t));
return x;
}

int gnukeyw(int x)
{
return(o_gnu)?keyw(x):identif();
}

int msdoskeyw(int x)
{
return(o_msdos)?keyw(x):identif();
}

int watcomkeyw(int x)
{
return(o_watcom)?keyw(x):identif();
}

int ibmvackeyw(int x)
{
return(o_ibmvac)?keyw(x):identif();
}


#ident "acomp: Sun C 5.10 SunOS_i386 2009/06/03"

static char *_selTransTbl[] ={
"str:",
"str:lineno:filename:",
"type:",
0
};
struct modDescriptor lex_modDesc = {
  "lex",
  "objc3.2.11",
  0L,
  0,
  0,
  0,
  3,
  _selTransTbl,
  0
};
struct modDescriptor *_OBJCBIND_lex(void)
{
  selTransTbl = _selTransTbl;
  return &lex_modDesc;
}
int _OBJCPOSTLINK_lex = 1;


