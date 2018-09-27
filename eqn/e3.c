# include "e.h"

struct {
	char	*res;
	char	*resval;
} restab[] {
	">=",	"\\(>=",
	"<=",	"\\(<=",
	"==",	"\\(==",
	"!=",	"\\(!=",
	"+-",	"\\(+-",
	"->",	"\\(->",
	"<-",	"\\(<-",
	"<<",	"<\\h'-.3m'<",
	">>",	">\\h'-.3m'>",
	"inf",	"\\(if",
	"infinity",	"\\(if",
	"partial",	"\\(pd",
	"half",	"\\fR\\(12\\fP",
	"prime",	"\\fR\\(fm\\fP",
	"approx",	"\\v'-.2m'\\z\\(ap\\v'.25m'\\(ap\\v'-.05m'",
	"nothing",	"",
	"cdot",	"\\v'-.3m'.\\v'.3m'",
	"times",	"\\(mu",
	"del",	"\\(gr",
	"grad",	"\\(gr",
	"...",	"\\v'-.3m'\\ .\\ .\\ .\\ \\v'.3m'",
	",...,",	",\\ .\\ .\\ .\\ ,\\|",

	"alpha",	"\\(*a",
	"beta",	"\\(*b",
	"gamma",	"\\(*g",
	"GAMMA",	"\\(*G",
	"delta",	"\\(*d",
	"DELTA",	"\\(*D",
	"epsilon",	"\\(*e",
	"omega",	"\\(*w",
	"OMEGA",	"\\(*W",
	"lambda",	"\\(*l",
	"LAMBDA",	"\\(*L",
	"mu",	"\\(*m",
	"nu",	"\\(*n",
	"theta",	"\\(*h",
	"THETA",	"\\(*H",
	"phi",	"\\(*f",
	"PHI",	"\\(*F",
	"pi",	"\\(*p",
	"PI",	"\\(*P",
	"sigma",	"\\(*s",
	"SIGMA",	"\\(*S",
	"xi",	"\\(*c",
	"XI",	"\\(*C",
	"zeta",	"\\(*z",
	"iota",	"\\(*i",
	"eta",	"\\(*y",
	"kappa",	"\\(*k",
	"rho",	"\\(*r",
	"tau",	"\\(*t",
	"omicron",	"\\(*o",
	"upsilon",	"\\(*u",
	"UPSILON",	"\\(*U",
	"psi",	"\\(*q",
	"PSI",	"\\(*Q",
	"chi",	"\\(*x",
	"and",	"\\fRand\\fP",
	"for",	"\\fRfor\\fP",
	"if",	"\\fRif\\fP",
	"Re",	"\\fRRe\\fP",
	"Im",	"\\fRIm\\fP",
	"sin",	"\\fRsin\\fP",
	"cos",	"\\fRcos\\fP",
	"tan",	"\\fRtan\\fP",
	"arc",	"\\fRarc\\fP",
	"sinh",	"\\fRsinh\\fP",
	"coth",	"\\fRcoth\\fP",
	"tanh",	"\\fRtanh\\fP",
	"cosh",	"\\fRcosh\\fP",
	"lim",	"\\fRlim\\fP",
	"log",	"\\fRlog\\fP",
	"max",	"\\fRmax\\fP",
	"min",	"\\fRmin\\fP",
	"ln",	"\\fRln\\fP",
	"exp",	"\\fRexp\\fP",
	"det",	"\\fRdet\\fP",
	0,	0
};

int	csp;
int	psp;
#define	CSSIZE	400
char	cs[420];

int	lf, rf;	/* temporary spots for left and right fonts */

text(t,p1) int t; char *p1; {
	int i,j,c;
	yyval = oalloc();
	ebase[yyval] = 0;
	eht[yyval] = VERT(6 * ((ps>6)?ps:6));	/* ht in machine units */
	lfont[yyval] = rfont[yyval] = ROM;
	if( t=='q' )
		j = p1;
	else if ( t == '~' )
		j = &"\\|\\|";
	else if ( t == '^' )
		j = &"\\|";
	else if ( t == '\t' )
		j = &"\\t";
	else if( (i=lookup(p1,restab))>=0 ) {
		j = restab[i].resval;
	}
	else {
		lf = rf = 0;
		for( csp=psp=0; (c=p1[psp++])!='\0'; ){
			rf = trans(c, p1);
			if (lf == 0)
				lf = rf;	/* save first */
			if( csp>CSSIZE )
				error(FATAL,"converted token %.25s... too long",p1);
		}
		cs[csp] = '\0';
		j = cs;
		lfont[yyval] = lf;
		rfont[yyval] = rf;
	}
	if(dbg)printf(".\t%ctext: S%d <- %s; b=%d,h=%d,lf=%c,rf=%c\n",
		t, yyval, j, ebase[yyval], eht[yyval], lfont[yyval], rfont[yyval]);
	printf(".ds %d \"%s\n", yyval, j);
}

trans(c,p1) int c; char *p1; {
	int f;
	f = ROM;
	switch( c){
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	case ':': case ';': case '!': case '%':
	case '(': case '[': case ')': case ']':
		if (rf == ITAL)
			shim();
		roman(c); break;
	case '.':
		if (rf == ROM)
			roman(c);
		else
			cs[csp++] = c;
		f = rf;
		break;
	case '|':
		if (rf == ITAL)
			shim();
		shim(); roman(c); shim(); break;
	case '=':
		if (rf == ITAL)
			shim();
		name4('e','q');
		break;
	case '+':
		if (rf == ITAL)
			shim();
		name4('p', 'l');
		break;
	case '>': case '<':
		if (rf == ITAL)
			shim();
		if( p1[psp]=='=' ){	/* look ahead for == <= >= */
			name4(c,'=');
			psp++;
		} else {
			cs[csp++] = c;  
		}
		break;
	case '-':
		if (rf == ITAL)
			shim();
		if( p1[psp]=='>' ){
			name4('-','>'); psp++;
		} else {
			name4('m','i');
		}
		break;
	case '/':
		if (rf == ITAL)
			shim();
		name4('s','l');
		break;
	case '~': case ' ':
		shim(); shim(); break;
	case '^':
		shim(); break;
	case '\\':	/* troff - pass 2 or 3 more chars */
		if (rf == ITAL)
			shim();
		cs[csp++] = c; cs[csp++] = c = p1[psp++]; cs[csp++] = p1[psp++];
		if( c=='(' ) cs[csp++] = p1[psp++];
		if( c=='*' && cs[csp-1] == '(' ){
			cs[csp++] = p1[psp++];
			cs[csp++] = p1[psp++];
		}
		break;
	case '\'':
		cs[csp++] = '\\'; cs[csp++] = 'f'; cs[csp++] = rf==ITAL ? ITAL : ROM;
		name4('f','m');
		cs[csp++] = '\\'; cs[csp++] = 'f'; cs[csp++] = 'P';
		f = rf==ITAL ? ITAL : ROM;
		break;
	case 'f':

		if (ft == ITAL) {
			cs[csp++] = '\\'; cs[csp++] = '^';
			cs[csp++] = 'f';
			cs[csp++] = '\\'; cs[csp++] = '^';
			f = ITAL;
		}
		else
			cs[csp++] = 'f';
		break;
	case 'j':
		if (ft == ITAL) {
			cs[csp++] = '\\'; cs[csp++] = '^';
			cs[csp++] = 'j';
			f = ITAL;
		}
		else
			cs[csp++] = 'j';
		break;
	default:
		cs[csp++] = c;
		f = ft==ITAL ? ITAL : ROM;
		break;
	}
	return(f);
}

shim() {
	cs[csp++] = '\\'; cs[csp++] = '|';
}

roman(c) int c; {
	cs[csp++] = '\\'; cs[csp++] = 'f'; cs[csp++] = ROM;
	cs[csp++] = c;
	cs[csp++] = '\\'; cs[csp++] = 'f'; cs[csp++] = 'P';
}

name4(c1,c2) int c1,c2; {
	cs[csp++] = '\\';
	cs[csp++] = '(';
	cs[csp++] = c1;
	cs[csp++] = c2;
}
