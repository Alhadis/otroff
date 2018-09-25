#include "ne.h"
#define	SIGPIPE	13	/* troff has stopped reading */

int	gsize	10;
int	gfont	'R';

char	in[600];	/* input buffer */
int	exit();
int noeqn;

main(argc,argv) int argc; char *argv[];{
	int i, type;
	first = 0;
	lefteq = righteq = '\0';
	signal(SIGPIPE, &exit);
	setfile(argc,argv);
	while( (type=getline(in)) != '\0' ){
		eqline = linect;
		if( in[0]=='.' && in[1]=='E' && in[2]=='Q' ){
			for( i=11; i<100; used[i++]=0 );
			printf("%s",in);
			printf(".nr 99 \\n(.s\n.nr 98 \\n(.f\n");
			init();
			yyparse();
			if( eqnreg>0 ){
			printf("'nr %d \\w'\\*(%d'\n", eqnreg, eqnreg);
				printf(".if %d>\\n(.v .ne %du\n", eqnht, eqnht);
				printf(".rn %d 10\n", eqnreg);
				if(!noeqn)printf("\\*(10\n");
			}
			printf(".ps \\n(99\n.ft \\n(98\n");
			printf(".EN");
			if( lastchar == '\0' ){
				putchar('\n');
				break;
			}
			if( putchar(lastchar) != '\n' )
				while( putchar(getc()) != '\n' );
			flush();
		}
		else if( type == lefteq )
			inline();
		else
			printf("%s",in);
	}
	flush();
	exit(0);
}

getline(s) char *s; {
	char c;
	while((*s++=c=getc())!='\n' && c!='\0' && c!=lefteq );
	if( c==lefteq )
		s--;
	*s++ = '\0';
	return(c);
}

inline() {
	int i,j,ds,t;
	printf(".nr 99 \\n(.s\n.nr 98 \\n(.f\n");
	ds = oalloc();
	printf(".ds %d \"\n", ds);
	do{
		printf(".as %d \"%s\n", ds, in);
		init();
		yyparse();
		if( eqnreg > 0 ) {
			printf(".as %d \\*(%d\n", ds, eqnreg);
			ofree(eqnreg);
		}
		printf(".ps \\n(99\n.ft \\n(98\n");
	} while( (t=getline(in)) == lefteq );
	printf(".as %d \"%s", ds, in);
	printf(".ps \\n(99\n.ft \\n(98\n");
	printf("\\*(%d\n", ds);
	ofree(ds);
	flush();
}

putout(p1) int p1; {
	extern int gsize, gfont;
	int before, after;
	eqnht = eht[p1];
	printf(".ds %d \\x'0'", p1);
	before = eht[p1] - ebase[p1] - VERT(3);	/* 3 = 1.5 lines */
	if( before > 0 )
		printf("\\x'0-%du'", before);
	printf("\\f%c\\s%d\\*(%d\\s\\n(99\\f\\n(98",gfont,gsize,p1);
	after = ebase[p1] - VERT(1);
	if( after > 0 )
		printf("\\x'%du'", after);
	putchar('\n');
	eqnreg = p1;
	if(dbg)printf(".\tanswer <- S%d: h=%d, b=%d, before=%d, after=%d\n",
		p1, eht[p1], ebase[p1], before, after);
}

max(i,j) int i,j; {
	return( i>j ? i : j );
}

oalloc(){
	int i;
	for( i=11; i<100; i++)
		if( used[i]++ == 0 ) return(i);
	error( FATAL, "no strings left", i);
}

ofree(n) int n; {
	used[n] = 0;
}

setps(p) int p; {
	printf(".ps %d\n", p);
}

nrwid(n1, p, n2) int n1, p, n2; {
	printf(".nr %d \\w'\\*(%d'\n", n1, n2);
}

setfile(argc, argv) int argc; char *argv[]; {
	svargc = --argc;
	svargv = argv;
	while( svargc > 0 && svargv[1][0] == '-'){
		switch( svargv[1][1] ){

		case 'd': lefteq=svargv[1][2]; righteq=svargv[1][3]; break;
		case 's': gsize = numb(&svargv[1][2]); break;
		case 'f': gfont = svargv[1][2]; break;
		case 'e': noeqn++; break;
		default: dbg = 1;
		}
		svargc--;
		svargv++;
	}
	ptr = 0;
	fout = dup(1);
	ifile = 1;
	linect = 1;
	if( svargc <= 0 )
		fin = dup(0);
	else if( (fin = open(svargv[1], 0)) < 0)
		error( FATAL,"can't open file %s", svargv[1]);
}

yyerror(){;}

init(){
	ct = 0;
	ps = gsize;
	ft = gfont;
	first++;
}

error(fatal, s1, s2) int fatal; char *s1, *s2; {
	int sfout;
	if( fatal>0 )
		printf("fatal error: ");
	printf(s1,s2);
	printf(" file %s, between lines %d and %d\n",
		 svargv[ifile], eqline, linect);
	flush(fout);
	sfout = fout;
	fout = 2;
	if( fatal>0 )
		printf("fatal error: ");
	printf(s1,s2);
	printf(" file %s, between lines %d and %d\n",
		 svargv[ifile], eqline, linect);
	flush(2);
	fout = sfout;
	if( fatal > 0 )
		exit(1);
}
