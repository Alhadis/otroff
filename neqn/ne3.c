# include "ne.h"

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
	"inf",	"\\(if",
	"infinity",	"\\(if",
	"partial",	"\\(pd",
	"half",	"\\fR\\(12\\fP",
	"prime",	"\\(fm",
	"approx",	"~\b\\d~\\u",
	"nothing",	"",
	"cdot",	"\\v'-.5'.\\v'.5'",
	"times",	"\\|\\(mu\\|",
	"del",	"\\(gr",
	"grad",	"\\(gr",
	"...",	"\\v'-.3m'\\|\\|.\\|\\|.\\|\\|.\\|\\|\\v'.3m'",
	",...,",	",\\|\\|.\\|\\|.\\|\\|.\\|\\|,\\|",

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

text(t,p1) int t; char *p1; {
	int i,j,c;
	yyval = oalloc();
	ebase[yyval] = 0;
	eht[yyval] = VERT(2);
	if( t=='q' )
		j = p1;
	else if ( t == '~' )
		j = &"\\ ";
	else if ( t == '^' )
		j = &"";
	else if ( t == '\t' )
		j = &"\\t";
	else if( (i=lookup(p1,restab))>=0 )
		j = restab[i].resval;
	else {
		for( csp=psp=0; (c=p1[psp++])!='\0'; ){
			trans(c,p1);
			if( csp>CSSIZE ){
				p1[25] = '\0';
				error(FATAL,"converted token %s... too long",p1);
			}
		}
		cs[csp] = '\0';
		j = cs;
	}
	if(dbg)printf(".\t%ctext: S%d <- %s; b=%d,h=%d\n",
		t, yyval, j, ebase[yyval], eht[yyval]);
	printf(".ds %d \"%s\n", yyval, j);
}

trans(c,p1) int c; char *p1; {
	switch( c){
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	case ':': case ';': case '!':
		roman(c); break;
	case '(': case '[': case ')': case ']':
		shim(); roman(c); break;
	case '+': case '|':
		shim(); roman(c); shim(); break;
	case '=': case '>': case '<':
		if( p1[psp]=='=' ){	/* look ahead for == <= >= */
			name4(c,'=');
			psp++;
		} else {
			shim(); cs[csp++] = c; shim(); 
		}
		break;
	case '-':
		if( p1[psp]=='>' ){
			shim(); name4('-','>'); psp++;
		} else {
			shim(); name4('m','i'); shim();
		}
		break;
	case '/':
		name4('s','l');
		break;
	case '~': case ' ':
		shim(); shim(); break;
	case '^':
		shim(); break;
	case '\\':	/* troff - pass 2 or 3 more chars */
		cs[csp++] = c; cs[csp++] = c = p1[psp++]; cs[csp++] = p1[psp++];
		if( c=='(' ) cs[csp++] = p1[psp++];
		if( c=='*' && cs[csp-1] == '(' ){
			cs[csp++] = p1[psp++];
			cs[csp++] = p1[psp++];
		}
		break;
	case '\'':
		name4('f','m'); break;
	default:
		cs[csp++] = c; break;
	}
}

shim() {
	;
}

roman(c) int c; {
	cs[csp++] = c;
}

name4(c1,c2) int c1,c2; {
	cs[csp++] = '\\';
	cs[csp++] = '(';
	cs[csp++] = c1;
	cs[csp++] = c2;
}
