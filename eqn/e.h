#include "stdio.h"

#define	FATAL	1
#define	ROM	'1'
#define	ITAL	'2'
#define	BLD	'3'

#define	VERT(n)	((((n)+1)/3)*3)

extern int	dbg;
extern int	ct;
extern int	lp[];
extern int	used[];	/* available registers */
extern int	ps;	/* dflt init pt size */
extern int	deltaps;	/* default change in ps */
extern int	gsize;	/* global size */
extern int	gfont;	/* global font */
extern int	ft;	/* dflt font */
extern FILE	*curfile;	/* current input file */
extern int	ifile;	/* input file number */
extern int	linect;	/* line number in current file */
extern int	eqline;	/* line where eqn started */
extern int	svargc;
extern char	**svargv;
extern int	eht[];
extern int	ebase[];
extern int	lfont[];
extern int	rfont[];
struct { char c1; char c2; };
extern int	yyval;
extern int	*yypv;
extern int	yylval;
extern int	tht[];
extern int	tbase[];
extern int	eqnreg, eqnht;
extern int	lefteq, righteq;
extern int	lastchar;	/* last character read by lex */
