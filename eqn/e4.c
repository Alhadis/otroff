# include "e.h"
# define	SIGPIPE	13	/* troff has stopped reading */
#define	MAXLINE	600	/* maximum input line */

char	in[MAXLINE];	/* input buffer */
int	eqnexit();
int noeqn;

main(argc,argv) int argc; char *argv[];{

	eqnexit(eqn(argc, argv));
}

eqnexit(n) {
#ifdef gcos
	if (n)
		fprintf(stderr, "run terminated due to eqn error\n");
	exit(0);
#endif
	exit(n);
}

eqn(argc,argv) int argc; char *argv[];{
	int i, type;

#ifdef unix
	signal(SIGPIPE, &eqnexit);
#endif

	setfile(argc,argv);
	while ((type=getline(in)) != EOF) {
		eqline = linect;
		if (in[0]=='.' && in[1]=='E' && in[2]=='Q') {
			for (i=11; i<100; used[i++]=0);
			printf("%s",in);
			printf(".nr 99 \\n(.s\n.nr 98 \\n(.f\n");
			init();
			yyparse();
			if (eqnreg>0) {
				printf(".nr %d \\w'\\*(%d'\n", eqnreg, eqnreg);
				printf(".if \\n(%d>\\n(.l .tm too-long eqn, file %s, between lines %d-%d\n",
					eqnreg, svargv[ifile], eqline, linect);
				printf(".if %d>\\n(.v .ne %du\n", eqnht, eqnht);
				printf(".rn %d 10\n", eqnreg);
				if(!noeqn)printf("\\*(10\n");
			}
			printf(".ps \\n(99\n.ft \\n(98\n");
			printf(".EN");
			if (lastchar == EOF) {
				putchar('\n');
				break;
			}
			if (putchar(lastchar) != '\n')
				while (putchar(gtc()) != '\n');
		}
		else if (type == lefteq)
			inline();
		else
			printf("%s",in);
	}
	return(0);
}

getline(s) char *s; {
	char c;
	while((*s++=c=gtc())!='\n' && c!=EOF && c!=lefteq)
		if (s >= in+MAXLINE) {
			error( !FATAL, "input line too long: %.20s\n", in);
			in[MAXLINE] = '\0';
			break;
		}
	if (c==lefteq)
		s--;
	*s++ = '\0';
	return(c);
}

inline() {
	int i,j,ds,t;
	printf(".nr 99 \\n(.s\n.nr 98 \\n(.f\n");
	ds = oalloc();
	printf(".rm %d \n", ds);
	do{
		if (*in)
			printf(".as %d \"%s\n", ds, in);
		init();
		yyparse();
		if (eqnreg > 0) {
			printf(".as %d \\*(%d\n", ds, eqnreg);
			ofree(eqnreg);
		}
		printf(".ps \\n(99\n.ft \\n(98\n");
	} while ((t=getline(in)) == lefteq);
	if (*in)
		printf(".as %d \"%s", ds, in);
	printf(".ps \\n(99\n.ft \\n(98\n");
	printf("\\*(%d\n", ds);
	ofree(ds);
}

putout(p1) int p1; {
	extern int gsize, gfont;
	int before, after;
	if(dbg)printf(".\tanswer <- S%d, h=%d,b=%d\n",p1, eht[p1], ebase[p1]);
	eqnht = eht[p1];
	printf(".ds %d \\x'0'", p1);
	/* suppposed to leave room for a subscript or superscript */
	before = eht[p1] - ebase[p1] - VERT((ps*6*12)/10);
	if (before > 0)
		printf("\\x'0-%du'", before);
	printf("\\f%c\\s%d\\*(%d\\s\\n(99\\f\\n(98",gfont,gsize,p1);
	after = ebase[p1] - VERT((ps*6*2)/10);
	if (after > 0)
		printf("\\x'%du'", after);
	putchar('\n');
	eqnreg = p1;
}

max(i,j) int i,j; {
	return (i>j ? i : j);
}

oalloc() {
	int i;
	for (i=11; i<100; i++)
		if (used[i]++ == 0) return(i);
	error( FATAL, "no eqn strings left", i);
}

ofree(n) int n; {
	used[n] = 0;
}

setps(p) int p; {
	printf(".ps %d\n", p);
}

nrwid(n1, p, n2) int n1, p, n2; {
	printf(".nr %d \\w'\\s%d\\*(%d'\n", n1, p, n2);
}

setfile(argc, argv) int argc; char *argv[]; {
	svargc = --argc;
	svargv = argv;
	while (svargc > 0 && svargv[1][0] == '-') {
		switch (svargv[1][1]) {

		case 'd': lefteq=svargv[1][2]; righteq=svargv[1][3]; break;
		case 's': gsize = numb(&svargv[1][2]); break;
		case 'p': deltaps = numb(&svargv[1][2]); break;
		case 'f': gfont = svargv[1][2]; break;
		case 'e': noeqn++; break;
		default: dbg = 1;
		}
		svargc--;
		svargv++;
	}
	ifile = 1;
	linect = 1;
	if (svargc <= 0)
		curfile = stdin;
	else if ((curfile = fopen(svargv[1], "r")) == NULL)
		error( FATAL,"can't open file %s", svargv[1]);
}

yyerror() {;}

init() {
	ct = 0;
	ps = gsize;
	ft = gfont;
	setps(ps);
	printf(".ft %c\n", ft);
}

error(fatal, s1, s2) int fatal; char *s1, *s2; {
	if (fatal>0)
		printf("eqn fatal error: ");
	printf(s1,s2);
	printf("\nfile %s, between lines %d and %d\n",
		 svargv[ifile], eqline, linect);
	if (fatal>0)
		fprintf(stderr, "eqn fatal error: ");
	fprintf(stderr, s1, s2);
	fprintf(stderr, "\nfile %s, between lines %d and %d\n",
		 svargv[ifile], eqline, linect);
	if (fatal > 0)
		eqnexit(1);
}
