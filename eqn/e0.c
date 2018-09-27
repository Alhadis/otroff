#include "e.h"
int	dbg;	/* debugging print if non-zero */
int	lp[80];	/* stack for things like piles and matrices */
int	ct;	/* pointer to lp */
int	used[100];	/* available registers */
int	ps;	/* default init point size */
int	deltaps	3;	/* default change in ps */
int	gsize	10;
int	gfont	'2';	/* italic */
int	ft;	/* default font */
FILE	*curfile;	/* current input file */
int	ifile;
int	linect;	/* line number in file */
int	eqline;	/* line where eqn started */
int	svargc;
char	**svargv;
int	eht[100];
int	ebase[100];
int	lfont[100];
int	rfont[100];
int	tht[30];
int	tbase[30];
int	eqnreg, eqnht;
int	lefteq	'\0';	/* left in-line delimiter */
int	righteq	'\0';	/* right in-line delimiter */
int	lastchar;	/* last character read by lex */
