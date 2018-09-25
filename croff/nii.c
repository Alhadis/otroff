#include "tdef.h"

/* typewriter driving table structure*/
#ifdef NROFF
struct {
	int bset;
	int breset;
	int Hor;
	int Vert;
	int Newline;
	int Char;
	int Em;
	int Halfline;
	int Adj;
	char *twinit;
	char *twrest;
	char *twnl;
	char *hlr;
	char *hlf;
	char *flr;
	char *bdon;
	char *bdoff;
	char *ploton;
	char *plotoff;
	char *up;
	char *down;
	char *right;
	char *left;
	char *codetab[256-32];
	int zzz;
	} t;
int pipeflg;
#endif
static char Sccsid[] "@(#)nii.c	1.4 of 4/26/77";
struct {int op,dnl,dimac,ditrap,ditf,alss,blss,nls,mkline,
		maxl,hnl,curd;} d[NDI];
struct {int pn,nl,yr,hp,ct,dn,mo,dy,dw,ln,dl,st,sb,cd;
	int vxx[NN-NNAMES];} v ;
int *vlist &v;
int *dip &d[0];

int level;
int stdi;
int waitf;
int nofeed;
int quiet;
int stop;
char ibuf[IBUFSZ];
char xbuf[IBUFSZ];
char *ibufp;
char *xbufp;
char *eibuf;
char *xeibuf;
int cbuf[NC];
int *cp;
int nx;
int mflg;
int ch;
int cps;
int suffid;
int sufind[26];
int ibf;
int ttyod;
int ttys[3];
int iflg;
int ioff;
char *enda;
int rargc;
char **argp;
char trtab[256];
int lgf;
int copyf;
int ch0;
int cwidth;
int ip;
int nlflg;
int *nxf;
int *ap;
int *frame;
int *stk;
int donef;
int nflush;
int nchar;
int rchar;
int nfo;
int ifile;
int padc;
int raw;
int ifl[NSO];
int offl[NSO];
int ipl[NSO];
int ifi;
int flss;
int nonumb;
int trap;
int *litlev;
int tflg;
int ejf;
int *ejl;
int lit;
int gflag;
int dilev;
int tlss;
int offset;
int em;
int ds;
int woff;
int app;
int ndone;
int lead;
int ralss;
int paper;
int nextb;
int *argtop;
int nrbits;
int nform;
int oldmn;
int newmn;
int macerr;
int apptr;
int aplnk;
int diflg;
int roff;
int wbfi;
int inc[NN];
int fmt[NN];
int evi;
int vflag;
int noscale;
int po1;
int nlist[NTRAP];
int mlist[NTRAP];
int evlist[EVLSZ];
int ev;
int tty;
int sfont;
int sv;
int esc;
int cs;
int bd;
int widthp;
int xpts;
int xfont;
int code;
int setwdf;
int ccs;
int xbitf;
int mfont;
int mpts;
int pfont;
int ppts;
int over;
int nhyp;
int **hyp;
int *olinep;
int *pslp;
int back;
int esct;
int mcase;
int psflg;
int verm;
int escm;
int ttysave;
int dotT;
int eqflg;
char *unlkp;
int no_out;
int hflg; 