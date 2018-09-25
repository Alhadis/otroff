#
#include "ne.h"
#include "y.tab.c"

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
	"fat",	FAT,
	"roman",	ROMAN,
	"italic",	ITALIC,
	"bold",	BOLD,
	"left",	LEFT,
	"right",	RIGHT,
	"delim",	DELIM,
	"define",	DEFINE,
	"tdefine",	TDEFINE,
	"ndefine",	DEFINE,
	"gsize",	GSIZE,
	".gsize",	GSIZE,
	"gfont",	GFONT,
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
int	peek	-1;
#define	SSIZE	400
char	token[SSIZE];
int	sp;
int speek[10];
char *swt[10];
int sw -1;

getc(){
  loop:
	if(sw >= 0){
		lastchar = (peek<0) ? *swt[sw]++ : peek;
		peek = -1;
		if(lastchar != '\0')return(lastchar);
		peek = speek[sw--];
		return(' ');
		}
	lastchar = (peek<0) ? getchar() : peek;
	if( lastchar=='\n' )
		linect++;
	peek = -1;
	if( lastchar!= '\0' )
		return(lastchar);
	if( ++ifile > svargc ){
		peek = '\0';
		return('\0');
	}
	close(fin);
	linect = 1;
	if( (fin=open(svargv[ifile],0)) >= 0 )
		goto loop;
	error(FATAL,"can't open file %s\n", svargv[ifile]);
}

yylex(){
	int c, type;
  beg:
	while( (c=getc())==' ' || c=='\n');
	yylval=c;
	switch(c){

	case '\0':
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
		for(sp=0; (c=getc())!='"'; ){
			if(c !='\\')token[sp++]=c;
			else { if((c=getc())!= '"')token[sp++]='\\';
				token[sp++] = c; }
			if( sp>=SSIZE )
				error(FATAL,"quoted string %.20s... too long", token);
		}
		token[sp]='\0';
		yylval= &token[0];
		return(QTEXT);
	}
	if( c==righteq )
		return('\0');

	getstr(token, c);
	if((type = lookup(token,deftab)) >= 0){
		if(sw >= 9)
			error(FATAL,"definitions nested > 9", sw);
		swt[++sw] = deftab[type].sptr;
		speek[sw] = peek;
		peek = -1;
		goto beg;
		}
	type = lookup(token,keytab);
	if( type < 0 )
		return(CONTIG);
	if( keytab[type].keyval==DEFINE || keytab[type].keyval==TDEFINE ) {
		define(keytab[type].keyval);
		goto beg;
	}
	else if( keytab[type].keyval==DELIM ) {
		delim();
		goto beg;
	}
	else if( keytab[type].keyval==GSIZE ){
		globsize();
		goto beg;
	}
	else if( keytab[type].keyval==GFONT ) {
		globfont();
		goto beg;
	}
	else
		return( keytab[type].keyval );
}

getstr(s,c) char *s, c; {
	for (sp=0; c!=' ' && c!='\t' && c!='\n' && c!='{' && c!='}'
		&& c!='"' && c!='~' && c!='^' && c!=righteq; ) {
		if(c == '\\') if((c = getc()) != '"')s[sp++] = '\\';
		s[sp++] = c;
		if( sp>=SSIZE )
			error(FATAL,"token %.20s... too long",s);
		c = getc();
		}
	if( c=='{' || c=='}' || c=='"' || c=='~' || c=='^' || c=='\t' || c==righteq )
		peek = c;
	s[sp]='\0';
	yylval = s;
}

lookup(str,tbl)
char *str;
struct { char *name; char *val; } tbl[];
{
	register i,j, r;
	for(i=0; tbl[i].name!=0; i++){ /* table of tbl wds */
		for( j=0; (r=tbl[i].name[j])==str[j] && r!='\0'; j++);
		if( r == str[j] )
			return(i);
	}
	return( -1 );
}

cstr(s,quote) char *s; int quote; {
	int del,c,i;
	while((del=getc()) == ' ' || del == '\t' || del == '\n');
	if(quote)
		for(i=0; (c=getc()) != del;)
			s[i++] = c;
	else {
		s[0] = del;
		for(i=1; (c=getc())!=' ' && c!= '\t' && c!='\n';)
			s[i++]=c;
	}
	s[i] = '\0';
	return(s);
}

define(type) int type; {
	/*	char *alloc (); */
	int i, c;
	while( (c=getc())==' ' || c=='\n' );
	getstr(token,c);
	if( type == DEFINE ) {
		if((i = lookup(token,deftab)) >= 0){
			yyval = i;
			free(deftab[yyval].sptr);
		} else {
			yyval = ptr++;
			for(i=0; token[i] != '\0'; i++);
			deftab[yyval].nptr = alloc(i+1);
			for(i=0; deftab[yyval].nptr[i]=token[i]; i++);
		}
		if(dbg)printf(".\tdefine %s\n",deftab[yyval].nptr);
	}
	cstr(token,1);
	if( type != DEFINE )
		return;
	for(i=0; token[i] != '\0'; i++);
	deftab[yyval].sptr = alloc(i+1);
	for(i=0; deftab[yyval].sptr[i] = token[i]; i++);
	if(dbg)printf(".\tname %s defined as %s\n",
		deftab[yyval].sptr, deftab[yyval].sptr);
}

delim() {
	char *s;
	yyval = eqnreg = 0;
	cstr(token,0);
	lefteq = token[0];
	righteq = token[1];
	if( (lefteq == 'o' && righteq == 'f') || (lefteq == 'O' && righteq == 'F') )
		lefteq = righteq = '\0';
}

globsize() {
	extern int gsize;
	int c;
	while( (c=getc())==' ' || c=='\n' );
	getstr(token,c);
	gsize = numb(token);
	yyval = eqnreg = 0;
	setps(gsize);
}

globfont() {
	extern int gfont;
	while( (gfont=getc())==' ' || gfont=='\n' );
	yyval = eqnreg = 0;
	printf(".ft %c\n", gfont);
}
