#include "e.h"
#include "y.tab.c"

#define	MAXDEFS	200	/* max number of definitions */
struct {
	char *nptr;	/* name pointer */
	char *sptr;	/* defining string */
} deftab[MAXDEFS];
int	defptr	0;	/* next free slot in deftab */

struct	{
	char	*key;
	int	keyval;
} keytab[] {
	"sub",	SUB,
	"sup",	SUP,
	".EN",	0,
	"from",	FROM,
	"to",	TO,
	"sum",	SUM,
	"hat",	HAT,
	"vec", VEC,
	"dyad", DYAD,
	"dot",	DOT,
	"dotdot",	DOTDOT,
	"bar",	BAR,
	"tilde",	TILDE,
	"under",	UNDER,
	"prod",	PROD,
	"int",	INT,
	"integral",	INT,
	"union",	UNION,
	"inter",	INTER,
	"pile",	PILE,
	"lpile",	LPILE,
	"cpile",	CPILE,
	"rpile",	RPILE,
	"over",	OVER,
	"sqrt",	SQRT,
	"above",	ABOVE,
	"size",	SIZE,
	"font",	FONT,
	"fat", FAT,
	"roman",	ROMAN,
	"italic",	ITALIC,
	"bold",	BOLD,
	"left",	LEFT,
	"right",	RIGHT,
	"delim",	DELIM,
	"define",	DEFINE,
	"tdefine",	DEFINE,
	"ndefine",	NDEFINE,
	"gsize",	GSIZE,
	".gsize",	GSIZE,
	"gfont",	GFONT,
	"include",	INCLUDE,
	"up",	UP,
	"down",	DOWN,
	"fwd",	FWD,
	"back",	BACK,
	"mark",	MARK,
	"lineup",	LINEUP,
	"matrix",	MATRIX,
	"col",	COL,
	"lcol",	LCOL,
	"ccol",	CCOL,
	"rcol",	RCOL,
	0,	0
};
#define	SSIZE	400
char	token[SSIZE];
int	sp;
#define	putbak(c)	*ip++ = c;
#define	PUSHBACK	300	/* maximum pushback characters */
char	ibuf[PUSHBACK+SSIZE];	/* pushback buffer for definitions, etc. */
char	*ip	ibuf;

gtc() {
  loop:
	if (ip > ibuf)
		return(*--ip);	/* already present */
	lastchar = getc(curfile);
	if (lastchar=='\n')
		linect++;
	if (lastchar != EOF)
		return(lastchar);
	if (++ifile > svargc) {
		return(EOF);
	}
	fclose(curfile);
	linect = 1;
	if ((curfile=fopen(svargv[ifile],"r")) != NULL)
		goto loop;
	error(FATAL,"can't open file %s\n", svargv[ifile]);
}

pbstr(str)
register char *str;
{
	register char *p;

	p = str;
	while (*p++);
	--p;
	if (ip >= &ibuf[PUSHBACK])
		error( FATAL, "eqn pushback overflow\n");
	while (p > str)
		putbak(*--p);
}

yylex() {
	int c, type;
  beg:
	while ((c=gtc())==' ' || c=='\n');
	yylval=c;
	switch(c) {

	case EOF:
		return('\0');
	case '~':
		return(SPACE);
	case '^':
		return(THIN);
	case '\t':
		return(TAB);
	case '{':
		return(MQ);
	case '}':
		return(MQ1);
	case '"':
		for (sp=0; (c=gtc())!='"'; ) {
			if(c !='\\')token[sp++]=c;
			else { if((c=gtc())!= '"')token[sp++]='\\';
				token[sp++] = c; }
			if (sp>=SSIZE)
				error(FATAL,"quoted string %.20s... too long", token);
		}
		token[sp]='\0';
		yylval= &token[0];
		return(QTEXT);
	}
	if (c==righteq)
		return('\0');

	getstr(token, c);
	if(dbg)printf(".\tlex token = |%s|\n", token);
	if((type = lookup(token,deftab)) >= 0) {
		putbak(' ');
		pbstr(deftab[type].sptr);
		putbak(' ');
		if(dbg)
			printf(".\tfound %s=|%s|\n", token, deftab[type].sptr);
		goto beg;
		}
	type = lookup(token,keytab);
	if (type < 0)
		return(CONTIG);
	switch (keytab[type].keyval) {

	case DEFINE: case NDEFINE:
		define(keytab[type].keyval);
		goto beg;
	case DELIM:
		delim();
		goto beg;
	case GSIZE:
		globsize();
		goto beg;
	case GFONT:
		globfont();
		goto beg;
	case INCLUDE:
		include();
		goto beg;
	default:
		return( keytab[type].keyval );
	}
}

getstr(s,c) char *s, c; {
	for (sp=0; c!=' ' && c!='\t' && c!='\n' && c!='{' && c!='}'
		&& c!='"' && c!='~' && c!='^' && c!=righteq; ) {
		if(c == '\\') if((c = gtc()) != '"')s[sp++] = '\\';
		s[sp++] = c;
		if (sp>=SSIZE)
			error(FATAL,"token %.20s... too long",s);
		c = gtc();
		}
	if (c=='{' || c=='}' || c=='"' || c=='~' || c=='^' || c=='\t' || c==righteq)
		putbak(c);
	s[sp]='\0';
	yylval = s;
}

lookup(str,tbl)
char *str;
struct { char *name; char *val; } tbl[];
{
	register i,j, r;
	for (i=0; tbl[i].name!=0; i++) { /* table of tbl wds */
		for ( j=0; (r=tbl[i].name[j])==str[j] && r!='\0'; j++);
		if (r == str[j])
			return(i);
	}
	return( -1 );
}

cstr(s,quote) char *s; int quote; {
	int del,c,i;
	while((del=gtc()) == ' ' || del == '\t' || del == '\n');
	if(quote)
		for (i=0; (c=gtc()) != del;)
			s[i++] = c;
	else {
		s[0] = del;
		for (i=1; (c=gtc())!=' ' && c!= '\t' && c!='\n';)
			s[i++]=c;
	}
	s[i] = '\0';
	return(s);
}

define(type) int type; {
	/*	char *calloc (); */
	int i, c, index;
	while ((c=gtc())==' ' || c=='\n');
	getstr(token,c);
	if (type == DEFINE) {
		if((index = lookup(token,deftab)) >= 0) {
			cfree(deftab[index].sptr);
		} else {
			index = defptr++;
			if (index >= MAXDEFS)
				error(FATAL, "Too many definitions at %s\n", token);
			for (i=0; token[i] != '\0'; i++);
			deftab[index].nptr = calloc(i+1,1);
			for (i=0; deftab[index].nptr[i]=token[i]; i++);
		}
		if(dbg)printf(".\tdefine %s\n",deftab[index].nptr);
	}
	cstr(token,1);
	if (type != DEFINE)
		return;
	for (i=0; token[i] != '\0'; i++);
	deftab[index].sptr = calloc(i+1,1);
	for (i=0; deftab[index].sptr[i] = token[i]; i++);
	if(dbg)printf(".\tname %s defined as %s\n",
		deftab[index].nptr, deftab[index].sptr);
}

include() {
	error(!FATAL, "Include not yet implemented\n");
}

delim() {
	char *s;
	yyval = eqnreg = 0;
	cstr(token,0);
	lefteq = token[0];
	righteq = token[1];
	if (lefteq == 'o' && righteq == 'f')
		lefteq = righteq = '\0';
}

globsize() {
	extern int gsize;
	int c;
	while ((c=gtc())==' ' || c=='\n');
	getstr(token,c);
	if (token[0] == '+')
		gsize =+ numb(token);
	else if (token[0] == '-')
		gsize =- numb(token);
	else
		gsize = numb(token);
	yyval = eqnreg = 0;
	setps(gsize);
	ps = gsize;
	if (gsize >= 12)	/* sub and sup size change */
		deltaps = gsize / 4;
	else
		deltaps = gsize / 3;
}

globfont() {
	extern int gfont;
	while ((gfont=gtc())==' ' || gfont=='\n');
	getstr(token, gfont);
	yyval = eqnreg = 0;
	switch (gfont) {
	case 'r': case 'R':
		gfont = '1';
		break;
	case 'i': case 'I':
		gfont = '2';
		break;
	case 'b': case 'B':
		gfont = '3';
		break;
	}
	printf(".ft %c\n", gfont);
	ft = gfont;
}
