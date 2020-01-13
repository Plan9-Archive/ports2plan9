# 1 "type.m"
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
extern struct modDescriptor  *_OBJCBIND_type(void);
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
extern struct modDescriptor type_modDesc;

# 1 "../../util/stdarg.h"
#include <stdarg.h>

# 1 "../../util/stdlib.h"
#include <stdlib.h>

# 1 "../../util/assert.h"
#include <assert.h>

# 1 "../../util/string.h"
#include <string.h>

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
# 31 "../../include/objpak/ordcltn.h"
typedef struct objcol
{
int count;
int capacity;
id*ptr;
}*
objcol_t;
# 22 "node.h"
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
# 22 "type.h"
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
# 22 "symbol.h"
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
# 22 "options.h"
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
# 22 "structsp.h"
extern id curstruct;
# 46 "type.m"
id t_unknown;
id t_void;
id t_char;
id t_bool;
id t_int;
id t_uns;
id t_long;
id t_double;
id t_str;
id t_sel;
id t_id;
# 34 "type.h"
struct Type_PRIVATE {

# 42 "../../include/objcrt/Object.h"
id isa;
# 46 "../../include/objcrt/Object.h"
unsigned short attr;
unsigned short objID;
# 36 "type.h"
id specs,decl;
BOOL isstatic;
BOOL isextern;
BOOL haslistinit;};

# 34 "type.h"
extern id  Type;

# 34 "type.h"
extern struct _SHARED _Type;
extern struct _SHARED __Type;


# 60 "type.m"
static id c_Type_commontypes(struct Type_PRIVATE *self,SEL _cmd)
{
if( !t_unknown){
id objcT0,objcT1,objcT2,objcT3,objcT4;
id objcT5,objcT6,objcT7,objcT8,objcT9;
id objcT10,objcT11,objcT12,objcT13,objcT14;
id objcT15,objcT16,objcT17,objcT18,objcT19;
id objcT20;

# 63 "type.m"
t_unknown=(objcT0=Type,(*_imp(objcT0,selTransTbl[0]))(objcT0,selTransTbl[0]));
t_void=(objcT1=(objcT2=Type,(*_imp(objcT2,selTransTbl[0]))(objcT2,selTransTbl[0])),(*_imp(objcT1,selTransTbl[1]))(objcT1,selTransTbl[1],s_void));
t_char=(objcT3=(objcT4=Type,(*_imp(objcT4,selTransTbl[0]))(objcT4,selTransTbl[0])),(*_imp(objcT3,selTransTbl[1]))(objcT3,selTransTbl[1],s_char));
t_bool=(objcT5=(objcT6=Type,(*_imp(objcT6,selTransTbl[0]))(objcT6,selTransTbl[0])),(*_imp(objcT5,selTransTbl[1]))(objcT5,selTransTbl[1],s_bool));
t_int=(objcT7=(objcT8=Type,(*_imp(objcT8,selTransTbl[0]))(objcT8,selTransTbl[0])),(*_imp(objcT7,selTransTbl[1]))(objcT7,selTransTbl[1],s_int));
t_uns=(objcT9=(objcT10=Type,(*_imp(objcT10,selTransTbl[0]))(objcT10,selTransTbl[0])),(*_imp(objcT9,selTransTbl[1]))(objcT9,selTransTbl[1],s_uns));
t_long=(objcT11=(objcT12=Type,(*_imp(objcT12,selTransTbl[0]))(objcT12,selTransTbl[0])),(*_imp(objcT11,selTransTbl[1]))(objcT11,selTransTbl[1],s_long));
t_double=(objcT13=(objcT14=Type,(*_imp(objcT14,selTransTbl[0]))(objcT14,selTransTbl[0])),(*_imp(objcT13,selTransTbl[1]))(objcT13,selTransTbl[1],s_double));
t_str=(objcT15=(objcT16=Type,(*_imp(objcT16,selTransTbl[0]))(objcT16,selTransTbl[0])),(*_imp(objcT15,selTransTbl[1]))(objcT15,selTransTbl[1],s_str));
t_sel=(objcT17=(objcT18=Type,(*_imp(objcT18,selTransTbl[0]))(objcT18,selTransTbl[0])),(*_imp(objcT17,selTransTbl[1]))(objcT17,selTransTbl[1],s_sel));
t_id=(objcT19=(objcT20=Type,(*_imp(objcT20,selTransTbl[0]))(objcT20,selTransTbl[0])),(*_imp(objcT19,selTransTbl[1]))(objcT19,selTransTbl[1],s_id));
}
return(id)self;
}

static id i_Type_specs(struct Type_PRIVATE *self,SEL _cmd)
{
return self->specs;
}

static id i_Type_decl(struct Type_PRIVATE *self,SEL _cmd)
{
return self->decl;
}

# 39 "../../include/objpak/ordcltn.h"
extern id  OrdCltn;

# 88 "type.m"
static id i_Type_abstrspecs_(struct Type_PRIVATE *self,SEL _cmd,id aList)
{
if(aList){self->
specs=aList;
}else{
id objcT21,objcT22;
self->
# 93 "type.m"
specs=(objcT21=OrdCltn,(*_imp(objcT21,selTransTbl[0]))(objcT21,selTransTbl[0]));
(objcT22=self->specs,(*_imp(objcT22,selTransTbl[2]))(objcT22,selTransTbl[2],s_int));
}
return(id)self;
}

# 59 "symbol.h"
extern id  Symbol;

# 24 "structsp.h"
extern id  StructSpec;

# 22 "enumsp.h"
extern id  EnumSpec;

# 99 "type.m"
static id i_Type_checkspec_(struct Type_PRIVATE *self,SEL _cmd,id s)
{
id objcT23,objcT24,objcT25,objcT26,objcT27;
id objcT28,objcT29;

# 101 "type.m"
if((objcT23=s,(*(BOOL(*)(id,SEL,id))_imp(objcT23,selTransTbl[3]))(objcT23,selTransTbl[3],(id)(objcT24=Symbol,(*_imp(objcT24,selTransTbl[4]))(objcT24,selTransTbl[4])))))
return(id)self;
if((objcT25=s,(*(BOOL(*)(id,SEL,id))_imp(objcT25,selTransTbl[3]))(objcT25,selTransTbl[3],(id)(objcT26=StructSpec,(*_imp(objcT26,selTransTbl[4]))(objcT26,selTransTbl[4])))))
return(id)self;
if((objcT27=s,(*(BOOL(*)(id,SEL,id))_imp(objcT27,selTransTbl[3]))(objcT27,selTransTbl[3],(id)(objcT28=EnumSpec,(*_imp(objcT28,selTransTbl[4]))(objcT28,selTransTbl[4])))))
return(id)self;
fprintf(stderr,"%s\n",(objcT29=s,(*(STR(*)(id,SEL))_imp(objcT29,selTransTbl[5]))(objcT29,selTransTbl[5])));
return(id)0;
}

static int i_Type_lineno(struct Type_PRIVATE *self,SEL _cmd)
{
if(self->specs){
id objcT30;

# 114 "type.m"
int i,n=(objcT30=self->specs,(*(unsigned(*)(id,SEL))_imp(objcT30,selTransTbl[6]))(objcT30,selTransTbl[6]));
for(i=0;i<n;i++){
id objcT31,objcT32;

# 116 "type.m"
int no=(objcT31=(objcT32=self->specs,(*(id(*)(id,SEL,unsigned))_imp(objcT32,selTransTbl[7]))(objcT32,selTransTbl[7],i)),(*(int(*)(id,SEL))_imp(objcT31,selTransTbl[8]))(objcT31,selTransTbl[8]));if(no)return no;
}
}
return 0;
}

static id i_Type_filename(struct Type_PRIVATE *self,SEL _cmd)
{
if(self->specs){
id objcT33;

# 125 "type.m"
int i,n=(objcT33=self->specs,(*(unsigned(*)(id,SEL))_imp(objcT33,selTransTbl[6]))(objcT33,selTransTbl[6]));
for(i=0;i<n;i++){
id objcT34,objcT35;

# 127 "type.m"
id no=(objcT34=(objcT35=self->specs,(*(id(*)(id,SEL,unsigned))_imp(objcT35,selTransTbl[7]))(objcT35,selTransTbl[7],i)),(*_imp(objcT34,selTransTbl[9]))(objcT34,selTransTbl[9]));if(no)return no;
}
}
return(id)0;
}

static id i_Type_specs_(struct Type_PRIVATE *self,SEL _cmd,id aList)
{
if(aList){
id objcT36,objcT37,objcT41;

# 136 "type.m"
int i,n;
id typespecs=(objcT36=OrdCltn,(*_imp(objcT36,selTransTbl[0]))(objcT36,selTransTbl[0]));

for(i=0,n=(objcT37=aList,(*(unsigned(*)(id,SEL))_imp(objcT37,selTransTbl[6]))(objcT37,selTransTbl[6]));i<n;i++){
id objcT38,objcT39,objcT40;

# 140 "type.m"
id s=(objcT38=aList,(*(id(*)(id,SEL,unsigned))_imp(objcT38,selTransTbl[7]))(objcT38,selTransTbl[7],i));

(void)0;

if( !(objcT39=s,(*(BOOL(*)(id,SEL))_imp(objcT39,selTransTbl[10]))(objcT39,selTransTbl[10])))
(objcT40=typespecs,(*_imp(objcT40,selTransTbl[2]))(objcT40,selTransTbl[2],s));
}
return(objcT41=(id)self,(*_imp(objcT41,selTransTbl[11]))(objcT41,selTransTbl[11],typespecs));
}else{
id objcT42;

# 149 "type.m"
return(objcT42=(id)self,(*_imp(objcT42,selTransTbl[1]))(objcT42,selTransTbl[1],s_int));
}
}

static id i_Type_addspec_(struct Type_PRIVATE *self,SEL _cmd,id aSpec)
{
id objcT43;

# 155 "type.m"
if( !self->specs)self->
specs=(objcT43=OrdCltn,(*_imp(objcT43,selTransTbl[0]))(objcT43,selTransTbl[0]));
if(aSpec){
id objcT44;

# 158 "type.m"
(void)0;
(void)0;
(objcT44=self->specs,(*_imp(objcT44,selTransTbl[2]))(objcT44,selTransTbl[2],aSpec));
}
return(id)self;
}

static id i_Type_abstrdecl_(struct Type_PRIVATE *self,SEL _cmd,id aDecl)
{self->
decl=aDecl;
return(id)self;
}

static id i_Type_decl_(struct Type_PRIVATE *self,SEL _cmd,id aDecl)
{
id objcT45,objcT46;

# 173 "type.m"
return(objcT45=(id)self,(*_imp(objcT45,selTransTbl[12]))(objcT45,selTransTbl[12],(aDecl)?(objcT46=aDecl,(*_imp(objcT46,selTransTbl[13]))(objcT46,selTransTbl[13])):(id)0));
}

static BOOL i_Type_haslistinit(struct Type_PRIVATE *self,SEL _cmd)
{
return self->haslistinit;
}

static BOOL i_Type_isstatic(struct Type_PRIVATE *self,SEL _cmd)
{
return self->isstatic;
}

static BOOL i_Type_isextern(struct Type_PRIVATE *self,SEL _cmd)
{
return self->isextern;
}

static BOOL i_Type_definesocu(struct Type_PRIVATE *self,SEL _cmd)
{
return !self->isstatic;
}

static id i_Type_isstatic_(struct Type_PRIVATE *self,SEL _cmd,BOOL flag)
{self->
isstatic=flag;
return(id)self;
}

static id i_Type_isextern_(struct Type_PRIVATE *self,SEL _cmd,BOOL flag)
{self->
isextern=flag;
return(id)self;
}

static id i_Type_haslistinit_(struct Type_PRIVATE *self,SEL _cmd,BOOL flag)
{self->
haslistinit=flag;
return(id)self;
}

static id i_Type_max_(struct Type_PRIVATE *self,SEL _cmd,id aType)
{
if((id)self==t_unknown||aType==t_unknown)
return t_unknown;
return(id)self;
}

static unsigned i_Type_hash(struct Type_PRIVATE *self,SEL _cmd)
{
id objcT50;

# 223 "type.m"
unsigned h=0;

if(self->specs){
id objcT47,objcT48,objcT49;

# 226 "type.m"
int i,n;

h=(n=(objcT47=self->specs,(*(unsigned(*)(id,SEL))_imp(objcT47,selTransTbl[6]))(objcT47,selTransTbl[6])));
for(i=0;i<n;i++)
h=(h<<1)^((objcT48=(objcT49=self->specs,(*(id(*)(id,SEL,unsigned))_imp(objcT49,selTransTbl[7]))(objcT49,selTransTbl[7],i)),(*(unsigned(*)(id,SEL))_imp(objcT48,selTransTbl[14]))(objcT48,selTransTbl[14])));
}
if(self->decl)
h^=(objcT50=self->decl,(*(unsigned(*)(id,SEL))_imp(objcT50,selTransTbl[14]))(objcT50,selTransTbl[14]));
return h;
}

static BOOL i_Type_isEqual_(struct Type_PRIVATE *self,SEL _cmd,id x)
{
if((id)self==x){
return(BOOL)1;
}else{
id objcT51,objcT52,objcT53,objcT54;

# 242 "type.m"
id y,z;

y=(objcT51=x,(*_imp(objcT51,selTransTbl[15]))(objcT51,selTransTbl[15]));
if(self->specs&&y&& !(objcT52=self->specs,(*(BOOL(*)(id,SEL,id))_imp(objcT52,selTransTbl[16]))(objcT52,selTransTbl[16],y)))
return(BOOL)0;
if(( !self->specs|| !y)&&self->specs!=y)
return(BOOL)0;
z=(objcT53=x,(*_imp(objcT53,selTransTbl[17]))(objcT53,selTransTbl[17]));
if(self->decl&&z&& !(objcT54=self->decl,(*(BOOL(*)(id,SEL,id))_imp(objcT54,selTransTbl[16]))(objcT54,selTransTbl[16],z)))
return(BOOL)0;
if(( !self->decl|| !z)&&self->decl!=z)
return(BOOL)0;
return(BOOL)1;
}
}

static BOOL i_Type_isvoid(struct Type_PRIVATE *self,SEL _cmd)
{
id objcT55,objcT56,objcT57;

# 260 "type.m"
if((id)self==t_void)
return(BOOL)1;
return self->decl==(id)0&&(objcT55=self->specs,(*(unsigned(*)(id,SEL))_imp(objcT55,selTransTbl[6]))(objcT55,selTransTbl[6]))==1&&(objcT56=(objcT57=self->specs,(*(id(*)(id,SEL,unsigned))_imp(objcT57,selTransTbl[7]))(objcT57,selTransTbl[7],0)),(*(BOOL(*)(id,SEL))_imp(objcT56,selTransTbl[18]))(objcT56,selTransTbl[18]));
}

static BOOL i_Type_isid(struct Type_PRIVATE *self,SEL _cmd)
{
id objcT58,objcT59,objcT60;

# 267 "type.m"
if((id)self==t_id)
return(BOOL)1;
return self->decl==(id)0&&(objcT58=self->specs,(*(unsigned(*)(id,SEL))_imp(objcT58,selTransTbl[6]))(objcT58,selTransTbl[6]))==1&&(objcT59=(objcT60=self->specs,(*(id(*)(id,SEL,unsigned))_imp(objcT60,selTransTbl[7]))(objcT60,selTransTbl[7],0)),(*(BOOL(*)(id,SEL))_imp(objcT59,selTransTbl[19]))(objcT59,selTransTbl[19]));
}

static BOOL i_Type_isrefcounted(struct Type_PRIVATE *self,SEL _cmd)
{
id objcT61;

# 274 "type.m"
int n;
if((id)self==t_id){
return(BOOL)1;
}
if(self->decl==(id)0&&(n=(objcT61=self->specs,(*(unsigned(*)(id,SEL))_imp(objcT61,selTransTbl[6]))(objcT61,selTransTbl[6])))>0){
id objcT64,objcT65;

# 279 "type.m"
int i;
for(i=0;i<n;i++){
id objcT62,objcT63;

# 281 "type.m"
if((objcT62=(objcT63=self->specs,(*(id(*)(id,SEL,unsigned))_imp(objcT63,selTransTbl[7]))(objcT63,selTransTbl[7],i)),(*(BOOL(*)(id,SEL))_imp(objcT62,selTransTbl[20]))(objcT62,selTransTbl[20])))return(BOOL)0;
}
return(objcT64=(objcT65=self->specs,(*(id(*)(id,SEL,unsigned))_imp(objcT65,selTransTbl[7]))(objcT65,selTransTbl[7],n-1)),(*(BOOL(*)(id,SEL))_imp(objcT64,selTransTbl[21]))(objcT64,selTransTbl[21]));
}
return(BOOL)0;
}

static BOOL i_Type_isscalartype(struct Type_PRIVATE *self,SEL _cmd)
{
id objcT66;
if((objcT66=self->decl,(*(BOOL(*)(id,SEL))_imp(objcT66,selTransTbl[22]))(objcT66,selTransTbl[22]))){
return(BOOL)1;
}else{
id objcT67;

# 294 "type.m"
if(self->decl==(id)0||(objcT67=self->decl,(*(BOOL(*)(id,SEL))_imp(objcT67,selTransTbl[23]))(objcT67,selTransTbl[23]))){
id objcT68;

# 295 "type.m"
int i,n;


for(i=0,n=(objcT68=self->specs,(*(unsigned(*)(id,SEL))_imp(objcT68,selTransTbl[6]))(objcT68,selTransTbl[6]));i<n;i++){
id objcT69,objcT70,objcT71;

# 299 "type.m"
id sp=(objcT69=self->specs,(*(id(*)(id,SEL,unsigned))_imp(objcT69,selTransTbl[7]))(objcT69,selTransTbl[7],i));

if((objcT70=sp,(*(BOOL(*)(id,SEL))_imp(objcT70,selTransTbl[10]))(objcT70,selTransTbl[10])))
continue;
if( !(objcT71=sp,(*(BOOL(*)(id,SEL))_imp(objcT71,selTransTbl[23]))(objcT71,selTransTbl[23])))
return(BOOL)0;
}
return(BOOL)1;
}else{
return(BOOL)0;
}
}
}

static BOOL i_Type_canforward(struct Type_PRIVATE *self,SEL _cmd)
{
id objcT72;

# 315 "type.m"
if((objcT72=self->decl,(*(BOOL(*)(id,SEL))_imp(objcT72,selTransTbl[22]))(objcT72,selTransTbl[22]))){
return(BOOL)1;
}else{
id objcT73;

# 318 "type.m"
if(self->decl==(id)0||(objcT73=self->decl,(*(BOOL(*)(id,SEL))_imp(objcT73,selTransTbl[24]))(objcT73,selTransTbl[24]))){
id objcT74;

# 319 "type.m"
int i,n;


for(i=0,n=(objcT74=self->specs,(*(unsigned(*)(id,SEL))_imp(objcT74,selTransTbl[6]))(objcT74,selTransTbl[6]));i<n;i++){
id objcT75,objcT76,objcT77;

# 323 "type.m"
id sp=(objcT75=self->specs,(*(id(*)(id,SEL,unsigned))_imp(objcT75,selTransTbl[7]))(objcT75,selTransTbl[7],i));

if((objcT76=sp,(*(BOOL(*)(id,SEL))_imp(objcT76,selTransTbl[10]))(objcT76,selTransTbl[10])))
continue;
if( !(objcT77=sp,(*(BOOL(*)(id,SEL))_imp(objcT77,selTransTbl[24]))(objcT77,selTransTbl[24])))
return(BOOL)0;
}
return(BOOL)1;
}else{
return(BOOL)0;
}
}
}

static BOOL i_Type_isselptr(struct Type_PRIVATE *self,SEL _cmd)
{
id objcT78;

# 339 "type.m"
if((objcT78=self->decl,(*(BOOL(*)(id,SEL))_imp(objcT78,selTransTbl[22]))(objcT78,selTransTbl[22]))){
return(BOOL)1;
}else{
if(self->decl==(id)0){
id objcT79;

# 343 "type.m"
int i,n;


for(i=0,n=(objcT79=self->specs,(*(unsigned(*)(id,SEL))_imp(objcT79,selTransTbl[6]))(objcT79,selTransTbl[6]));i<n;i++){
id objcT80,objcT81,objcT82;

# 347 "type.m"
id sp=(objcT80=self->specs,(*(id(*)(id,SEL,unsigned))_imp(objcT80,selTransTbl[7]))(objcT80,selTransTbl[7],i));

if((objcT81=sp,(*(BOOL(*)(id,SEL))_imp(objcT81,selTransTbl[10]))(objcT81,selTransTbl[10])))
continue;
if( !(objcT82=sp,(*(BOOL(*)(id,SEL))_imp(objcT82,selTransTbl[25]))(objcT82,selTransTbl[25])))
return(BOOL)0;
}
return(BOOL)1;
}else{
return(BOOL)0;
}
}
}

static id i_Type_synth(struct Type_PRIVATE *self,SEL _cmd)
{
return(id)self;
}

static id i_Type_gen(struct Type_PRIVATE *self,SEL _cmd)
{
id objcT83,objcT84;

# 368 "type.m"
if(self->specs)
(objcT83=self->specs,(*(id(*)(id,SEL,SEL))_imp(objcT83,selTransTbl[26]))(objcT83,selTransTbl[26],selTransTbl[27]));
if(self->decl)
(objcT84=self->decl,(*_imp(objcT84,selTransTbl[27]))(objcT84,selTransTbl[27]));
return(id)self;
}

static id i_Type_genabstrtype(struct Type_PRIVATE *self,SEL _cmd)
{
id objcT85;

# 377 "type.m"
return(objcT85=(id)self,(*_imp(objcT85,selTransTbl[28]))(objcT85,selTransTbl[28],(id)0));
}

static id i_Type_gendef_(struct Type_PRIVATE *self,SEL _cmd,id sym)
{
id objcT86;

# 382 "type.m"
o_nolinetags++;
if(self->specs)
(objcT86=self->specs,(*(id(*)(id,SEL,SEL))_imp(objcT86,selTransTbl[26]))(objcT86,selTransTbl[26],selTransTbl[27]));
if(self->decl){
id objcT87;

# 386 "type.m"
(objcT87=self->decl,(*_imp(objcT87,selTransTbl[28]))(objcT87,selTransTbl[28],sym));
}else{
id objcT88;

# 388 "type.m"
if(sym)
(objcT88=sym,(*_imp(objcT88,selTransTbl[27]))(objcT88,selTransTbl[27]));
}
o_nolinetags--;
return(id)self;
}

static id i_Type_dot_(struct Type_PRIVATE *self,SEL _cmd,id sym)
{
id objcT89,objcT90,objcT91;

# 397 "type.m"
if(self->decl)
return(id)0;
if((objcT89=self->specs,(*(unsigned(*)(id,SEL))_imp(objcT89,selTransTbl[6]))(objcT89,selTransTbl[6]))!=1)
return(id)0;
return(objcT90=(objcT91=self->specs,(*(id(*)(id,SEL,unsigned))_imp(objcT91,selTransTbl[7]))(objcT91,selTransTbl[7],0)),(*_imp(objcT90,selTransTbl[29]))(objcT90,selTransTbl[29],sym));
}

static id i_Type_star(struct Type_PRIVATE *self,SEL _cmd)
{
id objcT92,objcT93,objcT94,objcT95,objcT96;
id objcT97,objcT98;

# 406 "type.m"
if(self->decl==(id)0&&(objcT92=self->specs,(*(unsigned(*)(id,SEL))_imp(objcT92,selTransTbl[6]))(objcT92,selTransTbl[6]))==1)
return(objcT93=(objcT94=self->specs,(*(id(*)(id,SEL,unsigned))_imp(objcT94,selTransTbl[7]))(objcT94,selTransTbl[7],0)),(*_imp(objcT93,selTransTbl[30]))(objcT93,selTransTbl[30]));
if(self->decl==(id)0&&(objcT95=self->specs,(*(unsigned(*)(id,SEL))_imp(objcT95,selTransTbl[6]))(objcT95,selTransTbl[6]))!=1)
return(id)0;
return(objcT96=(objcT97=(id)self,(*_imp(objcT97,selTransTbl[31]))(objcT97,selTransTbl[31])),(*_imp(objcT96,selTransTbl[12]))(objcT96,selTransTbl[12],(objcT98=self->decl,(*_imp(objcT98,selTransTbl[30]))(objcT98,selTransTbl[30]))));
}

# 22 "pointer.h"
extern id  Pointer;

# 22 "stardecl.h"
extern id  StarDecl;

# 413 "type.m"
static id i_Type_ampersand(struct Type_PRIVATE *self,SEL _cmd)
{
id objcT99,objcT100,objcT101,objcT102,objcT103;
id objcT104;

# 415 "type.m"
id s,p;

p=(objcT99=Pointer,(*_imp(objcT99,selTransTbl[0]))(objcT99,selTransTbl[0]));
s=(objcT100=(objcT101=(objcT102=StarDecl,(*_imp(objcT102,selTransTbl[0]))(objcT102,selTransTbl[0])),(*_imp(objcT101,selTransTbl[32]))(objcT101,selTransTbl[32],p)),(*_imp(objcT100,selTransTbl[33]))(objcT100,selTransTbl[33],self->decl));
return(objcT103=(objcT104=(id)self,(*_imp(objcT104,selTransTbl[31]))(objcT104,selTransTbl[31])),(*_imp(objcT103,selTransTbl[12]))(objcT103,selTransTbl[12],s));
}

static id i_Type_funcall(struct Type_PRIVATE *self,SEL _cmd)
{
id objcT105,objcT106,objcT107,objcT108,objcT109;
id objcT110,objcT111;

# 424 "type.m"
if(self->decl==(id)0&&(objcT105=self->specs,(*(unsigned(*)(id,SEL))_imp(objcT105,selTransTbl[6]))(objcT105,selTransTbl[6]))==1)
return(objcT106=(objcT107=self->specs,(*(id(*)(id,SEL,unsigned))_imp(objcT107,selTransTbl[7]))(objcT107,selTransTbl[7],0)),(*_imp(objcT106,selTransTbl[34]))(objcT106,selTransTbl[34]));
if(self->decl==(id)0&&(objcT108=self->specs,(*(unsigned(*)(id,SEL))_imp(objcT108,selTransTbl[6]))(objcT108,selTransTbl[6]))!=1)
return(id)0;
return(objcT109=(objcT110=(id)self,(*_imp(objcT110,selTransTbl[31]))(objcT110,selTransTbl[31])),(*_imp(objcT109,selTransTbl[12]))(objcT109,selTransTbl[12],(objcT111=self->decl,(*_imp(objcT111,selTransTbl[34]))(objcT111,selTransTbl[34]))));
}

# 24 "scalar.h"
extern id  Scalar;

# 22 "arydecl.h"
extern id  ArrayDecl;

# 431 "type.m"
static id i_Type_zero(struct Type_PRIVATE *self,SEL _cmd)
{
id objcT112,objcT113,objcT114,objcT115,objcT116;
id objcT117,objcT118,objcT125;

# 433 "type.m"
if((objcT112=(id)self,(*(BOOL(*)(id,SEL,id))_imp(objcT112,selTransTbl[16]))(objcT112,selTransTbl[16],t_id)))return(id)0;
if((objcT113=(id)self,(*(BOOL(*)(id,SEL,id))_imp(objcT113,selTransTbl[16]))(objcT113,selTransTbl[16],t_str)))return(objcT114=(objcT115=Scalar,(*_imp(objcT115,selTransTbl[0]))(objcT115,selTransTbl[0])),(*(id(*)(id,SEL,char*))_imp(objcT114,selTransTbl[35]))(objcT114,selTransTbl[35],NULL));
if((objcT116=self->decl,(*(BOOL(*)(id,SEL,id))_imp(objcT116,selTransTbl[3]))(objcT116,selTransTbl[3],(id)(objcT117=ArrayDecl,(*_imp(objcT117,selTransTbl[4]))(objcT117,selTransTbl[4]))))&&(objcT118=self->specs,(*(unsigned(*)(id,SEL))_imp(objcT118,selTransTbl[6]))(objcT118,selTransTbl[6]))==1){
id objcT119,objcT120,objcT121,objcT122,objcT123;
id objcT124;

# 436 "type.m"
id s;
int n=(objcT119=(objcT120=self->decl,(*_imp(objcT120,selTransTbl[36]))(objcT120,selTransTbl[36])),(*(int(*)(id,SEL))_imp(objcT119,selTransTbl[37]))(objcT119,selTransTbl[37]));
s=(objcT121=Symbol,(*(id(*)(id,SEL,unsigned))_imp(objcT121,selTransTbl[38]))(objcT121,selTransTbl[38],n));
return(objcT122=(objcT123=Scalar,(*_imp(objcT123,selTransTbl[0]))(objcT123,selTransTbl[0])),(*(id(*)(id,SEL,char*))_imp(objcT122,selTransTbl[35]))(objcT122,selTransTbl[35],(objcT124=s,(*(STR(*)(id,SEL))_imp(objcT124,selTransTbl[39]))(objcT124,selTransTbl[39]))));
}
if(self->decl==(id)0&&(objcT125=self->specs,(*(unsigned(*)(id,SEL))_imp(objcT125,selTransTbl[6]))(objcT125,selTransTbl[6]))==1){
id objcT126,objcT127;

# 442 "type.m"
return(objcT126=(objcT127=self->specs,(*(id(*)(id,SEL,unsigned))_imp(objcT127,selTransTbl[7]))(objcT127,selTransTbl[7],0)),(*_imp(objcT126,selTransTbl[40]))(objcT126,selTransTbl[40]));
}
return(id)0;
}

static id i_Type_peekAt_(struct Type_PRIVATE *self,SEL _cmd,char*ptr)
{
id objcT128;

# 449 "type.m"
if(self->decl==(id)0&&(objcT128=self->specs,(*(unsigned(*)(id,SEL))_imp(objcT128,selTransTbl[6]))(objcT128,selTransTbl[6]))==1){
id objcT129,objcT130;

# 450 "type.m"
return(objcT129=(objcT130=self->specs,(*(id(*)(id,SEL,unsigned))_imp(objcT130,selTransTbl[7]))(objcT130,selTransTbl[7],0)),(*(id(*)(id,SEL,char*))_imp(objcT129,selTransTbl[41]))(objcT129,selTransTbl[41],ptr));
}else{
id objcT131;

# 452 "type.m"
(objcT131=(id)self,(*(id(*)(id,SEL,SEL))_imp(objcT131,selTransTbl[42]))(objcT131,selTransTbl[42],_cmd));
return 0;
}
}

static id i_Type_poke_at_(struct Type_PRIVATE *self,SEL _cmd,id v,char*ptr)
{
id objcT132;

# 459 "type.m"
if(self->decl==(id)0&&(objcT132=self->specs,(*(unsigned(*)(id,SEL))_imp(objcT132,selTransTbl[6]))(objcT132,selTransTbl[6]))==1){
id objcT133,objcT134;

# 460 "type.m"
return(objcT133=(objcT134=self->specs,(*(id(*)(id,SEL,unsigned))_imp(objcT134,selTransTbl[7]))(objcT134,selTransTbl[7],0)),(*(id(*)(id,SEL,id,char*))_imp(objcT133,selTransTbl[43]))(objcT133,selTransTbl[43],v,ptr));
}else{
id objcT135;

# 462 "type.m"
(objcT135=(id)self,(*(id(*)(id,SEL,SEL))_imp(objcT135,selTransTbl[42]))(objcT135,selTransTbl[42],_cmd));
return 0;
}
}

static int i_Type_bytesize(struct Type_PRIVATE *self,SEL _cmd)
{
id objcT136;

# 469 "type.m"
if(self->decl==(id)0&&(objcT136=self->specs,(*(unsigned(*)(id,SEL))_imp(objcT136,selTransTbl[6]))(objcT136,selTransTbl[6]))==1){
id objcT137,objcT138;

# 470 "type.m"
return(objcT137=(objcT138=self->specs,(*(id(*)(id,SEL,unsigned))_imp(objcT138,selTransTbl[7]))(objcT138,selTransTbl[7],0)),(*(int(*)(id,SEL))_imp(objcT137,selTransTbl[44]))(objcT137,selTransTbl[44]));
}else{
id objcT139;

# 472 "type.m"
(objcT139=(id)self,(*(id(*)(id,SEL,SEL))_imp(objcT139,selTransTbl[42]))(objcT139,selTransTbl[42],_cmd));
return 0;
}
}
# 479 "type.m"
#ident "acomp: Sun C 5.10 SunOS_i386 2009/06/03"

extern id  Object;
extern struct _SHARED _Object;
extern struct _SHARED __Object;
extern id  Node;
extern struct _SHARED _Node;
extern struct _SHARED __Node;
static struct _SLT _Type_clsDispatchTbl[] ={
{"commontypes",(id (*)())c_Type_commontypes},
{(char*)0,(id (*)())0}
};
static struct _SLT _Type_nstDispatchTbl[] ={
{"specs",(id (*)())i_Type_specs},
{"decl",(id (*)())i_Type_decl},
{"abstrspecs:",(id (*)())i_Type_abstrspecs_},
{"checkspec:",(id (*)())i_Type_checkspec_},
{"lineno",(id (*)())i_Type_lineno},
{"filename",(id (*)())i_Type_filename},
{"specs:",(id (*)())i_Type_specs_},
{"addspec:",(id (*)())i_Type_addspec_},
{"abstrdecl:",(id (*)())i_Type_abstrdecl_},
{"decl:",(id (*)())i_Type_decl_},
{"haslistinit",(id (*)())i_Type_haslistinit},
{"isstatic",(id (*)())i_Type_isstatic},
{"isextern",(id (*)())i_Type_isextern},
{"definesocu",(id (*)())i_Type_definesocu},
{"isstatic:",(id (*)())i_Type_isstatic_},
{"isextern:",(id (*)())i_Type_isextern_},
{"haslistinit:",(id (*)())i_Type_haslistinit_},
{"max:",(id (*)())i_Type_max_},
{"hash",(id (*)())i_Type_hash},
{"isEqual:",(id (*)())i_Type_isEqual_},
{"isvoid",(id (*)())i_Type_isvoid},
{"isid",(id (*)())i_Type_isid},
{"isrefcounted",(id (*)())i_Type_isrefcounted},
{"isscalartype",(id (*)())i_Type_isscalartype},
{"canforward",(id (*)())i_Type_canforward},
{"isselptr",(id (*)())i_Type_isselptr},
{"synth",(id (*)())i_Type_synth},
{"gen",(id (*)())i_Type_gen},
{"genabstrtype",(id (*)())i_Type_genabstrtype},
{"gendef:",(id (*)())i_Type_gendef_},
{"dot:",(id (*)())i_Type_dot_},
{"star",(id (*)())i_Type_star},
{"ampersand",(id (*)())i_Type_ampersand},
{"funcall",(id (*)())i_Type_funcall},
{"zero",(id (*)())i_Type_zero},
{"peekAt:",(id (*)())i_Type_peekAt_},
{"poke:at:",(id (*)())i_Type_poke_at_},
{"bytesize",(id (*)())i_Type_bytesize},
{(char*)0,(id (*)())0}
};
id Type = (id)&_Type;
id  *OBJCCLASS_Type(void) { return &Type; }
struct _SHARED  _Type = {
  (id)&__Type,
  (id)&_Node,
  "Type",
  0,
  sizeof(struct Type_PRIVATE),
  38,
  _Type_nstDispatchTbl,
  41,
  &type_modDesc,
  0,
  (id)0,
  &Type,
};
id  OBJCCFUNC_Type(void) { return (id)&_Type; }
id  OBJCCSUPER_Type(void) { return _Type.clsSuper; }
struct _SHARED __Type = {
  (id)&__Object,
  (id)&__Node,
  "Type",
  0,
  sizeof(struct _SHARED),
  1,
  _Type_clsDispatchTbl,
  34,
  &type_modDesc,
  0,
  (id)0,
  0,
};
id  OBJCMFUNC_Type(void) { return (id)&__Type; }
id  OBJCMSUPER_Type(void) { return __Type.clsSuper; }
static char *_selTransTbl[] ={
"new",
"addspec:",
"add:",
"isKindOf:",
"class",
"name",
"size",
"at:",
"lineno",
"filename",
"isstorageclass",
"abstrspecs:",
"abstrdecl:",
"abstrdecl",
"hash",
"specs",
"isEqual:",
"decl",
"isvoid",
"isid",
"isvolatile",
"isrefcounted",
"ispointer",
"isscalartype",
"canforward",
"isselptr",
"elementsPerform:",
"gen",
"gendef:",
"dot:",
"star",
"copy",
"pointer:",
"decl:",
"funcall",
"u_str:",
"expr",
"asInt",
"new:",
"strCopy",
"zero",
"peekAt:",
"notImplemented:",
"poke:at:",
"bytesize",
0
};
struct modDescriptor type_modDesc = {
  "type",
  "objc3.2.11",
  0L,
  0,
  0,
  &Type,
  45,
  _selTransTbl,
  0
};
struct modDescriptor *_OBJCBIND_type(void)
{
  selTransTbl = _selTransTbl;
  return &type_modDesc;
}
int _OBJCPOSTLINK_type = 1;


