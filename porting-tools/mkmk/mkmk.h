
/*
 * Most controls the fraction of source files that a header file must be
 * included in for it to appear in HFILES= rather than have an explicit
 * dependency
 */
#define Most		0.66

/*
 * Default collumn to wrap file lists at, 78 gives wide but short mkfiles,
 * some people prefer a value of 1 which gives one file name per line
 * and thus long, narrow mkfiles.
 * A command line option can override this anyway.
 */
#define Defwrap		78

/*
 * Catch self-referential dependencies, stop recuring at this depth,
 * ANSI requires at least 15, GCC imposes a limit of 200.
 */
#define Maxdepth	16

/*
 * max nesting depth of #if, #ifdef, #ifndef statments, ANSI
 * requires 4095.
 */
#define Ifstack	4096

enum {
	Tunk = 0,		/* unknown file type */
	Thdr,			/* header file */
	Tsrc,			/* general source */
	Tyacc,			/* yacc source */
	Tlex,			/* lex source */
	Tman1,			/* man page, command */
	Tman3,			/* man page, library */
	Tdir			/* directory */
};

typedef struct File File;
struct File {			/* files we are interested in */
	File *next;
	char *name;		/* file name */
	int ref;		/* reference count for missed source files */
	int type;		/* enum above */
	int sysdir;		/* a "system" header file */
	int global;		/* this dependency is handled in HFILES= */
};

typedef struct Depend Depend;
struct Depend {			/* dependency graph */
	Depend *next;		/* next on list */
	File *file;		/* real file info */
	Depend *child;		/* dependent file(s) */
};

typedef struct List List;
struct List {			/* general name list */
	List *next;
	char *name;
};

typedef struct Symb Symb;
struct Symb {			/* preprocessor symbol */
	Symb *next;
	char *name;		/* name */
	char *val;		/* value */
};

typedef struct State State;
struct State {			/* pre-processor parser state */
	Biobuf *bp;		/* include file */
	int line;		/* current line for debug */
	char *file;		/* current file for debug */
	Depend **dep;		/* dependency list to attach any includes to */
	List *langincdirs;	/* language specific include directories */
	int stk[Ifstack];	/* #ifdef/#if state stack */
	int sp;			/* stack pointer */
};

typedef struct Lang Lang;
struct Lang {
	char *ext;		/* file name extension */
	int type;		/* type *enum above */
	List **incdirp;		/* system include dirs to check */
	void (*parser)(State *s); /* parse func */
};

extern Biobuf *op;
extern int Debug;
extern int Wrap;
extern List *Lochints;
extern List *Glbhints;
extern List *Incdir;
extern List *Pragmalib;
extern char *Objname;
extern char Objletter;
extern int Autoconf;

extern char *findinc(char *, char, List *, int *);
extern void wrap(int *, char *, ...);
extern File *addfile(char *, int);
extern int scanfile(Depend **, File *, char *, int);

extern void parse_cpp(State *);
extern void parse_f77(State *);

extern int rmsym(char *);
extern void setsym(char *, char *);
extern char *looksym(char *, List *);
extern void freesyms(Symb *);
extern void dumpvars(void);

extern void includehint(char *);
extern void filehint(char *);
extern char *macrohint(char *, List *);
extern void prhints(int *);
extern void scanincludes(char *);
extern void gnu_pkgvers(void);

extern int expr(State *, char *);

extern void *emallocz(long, int);
extern void *erealloc(void *, long);
extern char *estrdup(char *);
extern void wrap(int *, char *, ...);
extern int trimfmt(Fmt *);
extern int addlist(List **, char *);
extern uint hash(char *, int);

extern void parse_ar(char *);
extern int inlibrary(char *);
