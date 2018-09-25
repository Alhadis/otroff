# include "ne.h"

fromto(p1, p2, p3) int p1, p2, p3; {
	int h, b, h1, b1, pss;
	yyval = oalloc();
	h1 = eht[yyval] = eht[p1];
	b1 = ebase[p1];
	b = 0;
	nrwid(p1, ps, p1);
	printf(".nr %d \\n(%d\n", yyval, p1);
	if( p2>0 ) {
		nrwid(p2, pss, p2);
		printf(".if \\n(%d>\\n(%d .nr %d \\n(%d\n", p2, yyval, yyval, p2);
		eht[yyval] =+ eht[p2];
		b = eht[p2];
	}
	if( p3>0 ) {
		nrwid(p3, pss, p3);
		printf(".if \\n(%d>\\n(%d .nr %d \\n(%d\n", p3, yyval, yyval, p3);
		eht[yyval] =+ eht[p3];
	}
	printf(".ds %d ", yyval);	/* bottom of middle box */
	if( p2>0 ) {
		printf("\\v'%du'\\h'\\n(%du-\\n(%du/2u'\\*(%d", 
			eht[p2]-ebase[p2]+b1, yyval, p2, p2);
		printf("\\h'-\\n(%du-\\n(%du/2u'\\v'%du'\\\n", 
			yyval, p2, -(eht[p2]-ebase[p2]+b1));
	}
	printf("\\h'\\n(%du-\\n(%du/2u'\\*(%d\\h'\\n(%du-\\n(%du+2u/2u'\\\n", 
		yyval, p1, p1, yyval, p1);
	if( p3>0 ) {
		printf("\\v'%du'\\h'-\\n(%du-\\n(%du/2u'\\*(%d\\h'\\n(%du-\\n(%du/2u'\\v'%du'\\\n", 
			-(h1-b1+ebase[p3]), yyval, p3, p3, yyval, p3, (h1-b1+ebase[p3]));
	}
	printf("\n");
	ebase[yyval] = b + b1;
	if(dbg)printf(".\tfrom to: S%d <- %d f %d t %d; h=%d b=%d\n", 
		yyval, p1, p2, p3, eht[yyval], ebase[yyval]);
	ofree(p1);
	if( p2>0 ) ofree(p2);
	if( p3>0 ) ofree(p3);
}

paren(leftc, p1, rightc) int p1, leftc, rightc; {
	int n, m, h1, j, b1, v;
	h1 = eht[p1]; b1 = ebase[p1];
	yyval = p1;
	n = max(b1+VERT(1), h1-b1-VERT(1)) / VERT(1);
	if( n<2 ) n=2;
	m = n-2;
	if (leftc=='{' || rightc == '}'){
		n = n%2 ? n : ++n;
		if( n<3 ) n=3;
		m = n - 3;
	}
	eht[yyval] = VERT(2 * n);
	ebase[yyval] = (n)/2 * VERT(2);
	if (n%2 == 0)
		ebase[yyval] =- VERT(1);
	v = b1 - h1/2 + VERT(1);
	printf(".ds %d \\v'%du'", yyval, v);
	switch( leftc ) {
		case 'n':	/* nothing */
		case '\0':
			break;
		case 'f':	/* floor */
			brack(m, "\\(bv", "\\(bv", "\\(lf");
			break;
		case 'c':	/* ceiling */
			brack(m, "\\(lc", "\\(bv", "\\(bv");
			break;
		case '{':
			printf("\\b'\\(lt");
			for(j = 0; j < m; j =+ 2) printf("\\(bv");
			printf("\\(lk");
			for(j = 0; j < m; j =+ 2) printf("\\(bv");
			printf("\\(lb'");
			break;
		case '(':
			brack(m, "\\(lt", "\\(bv", "\\(lb");
			break;
		case '[':
			brack(m, "\\(lc", "\\(bv", "\\(lf");
			break;
		default:
			brack(m, &leftc, &leftc, &leftc);
			break;
		}
	printf("\\v'%du'\\*(%d", -v, p1);
	if( rightc ) {
		printf("\\v'%du'", v);
		switch( rightc ) {
			case 'f':	/* floor */
				brack(m, "\\(bv", "\\(bv", "\\(rf");
				break;
			case 'c':	/* ceiling */
				brack(m, "\\(rc", "\\(bv", "\\(bv");
				break;
			case '}':
				printf("\\b'\\(rt");
				for(j = 0; j< m; j =+ 2)printf("\\(bv");
				printf("\\(rk");
				for(j = 0; j< m; j =+ 2) printf("\\(bv");
				printf("\\(rb'");
				break;
			case ']':
				brack(m, "\\(rc", "\\(bv", "\\(rf");
				break;
			case ')':
				brack(m, "\\(rt", "\\(bv", "\\(rb");
				break;
			default:
				brack(m, &rightc, &rightc, &rightc);
				break;
		}
		printf("\\v'%du'", -v);
	}
	printf("\n");
	if(dbg)printf(".\tcurly: h=%d b=%d n=%d v=%d l=%c, r=%c\n", 
		eht[yyval], ebase[yyval], n, v, leftc, rightc);
}

brack(m, t, c, b) int m; char *t, *c, *b; {
	int j;
	printf("\\b'%s", t);
	for( j=0; j<m; j++)
		printf("%s", c);
	printf("%s'", b);
}

diacrit(p1, type) int p1, type; {
	int c, t;
	if(dbg)printf(".\tdiacrit: %ctype over S%d\n", type, p1);
	c = oalloc();
	t = oalloc();
	nrwid(p1, ps, p1);
	switch(type) {
		case 'V':	/* vec */
		case 'Y':	/* dyad */
			printf(".ds %d \\v'-1'_\\v'1'\n", c);
			break;
		case 'H':
			printf(".ds %d ^\n", c);
			break;
		case 'T':
			printf(".ds %d ~\n", c);
			break;
		case 'D':
			printf(".ds %d \\v'-1'.\\v'1'\n", c);
			break;
		case 'U':
			printf(".ds %d \\v'-1'..\\v'1'\n", c);
			break;
		case 'B':
			printf(".ds %d \\v'-1'\\l'\\n(%du'\\v'1'\n", 
				c, p1);
			break;
		case 'N':
			printf(".ds %d \\l'\\n(%du'\n", c, p1);
			break;
		}
	nrwid(c, ps, c);
	printf(".as %d \\h'-\\n(%du-\\n(%du/2u'\\*(%d", 
		p1, p1, c, c);
	printf("\\h'-\\n(%du+\\n(%du/2u'\n", c, p1);
	eht[p1] =+ VERT(1);
	ofree(c); ofree(t);
}

move(dir, amt, p) int dir, amt; char *p; {
	/* 0=fwd, 1=up, 2=back, 3=down */
	int a, a1, a2;
	yyval = p;
	a1 = amt/100;
	a2 = amt%100;
	printf(".ds %d ", yyval);
	if( dir==0 || dir==2 )	/* fwd, back */
		printf("\\h'%s%d.%dm'\\*(%d\n", (dir==2) ? "-" : "", a1, a2, p);
	else if (dir == 1)
		printf("\\v'-%d.%dm'\\*(%d\\v'%d.%dm'\n",
			a1, a2, p, a1, a2);
	else if (dir == 3)
		printf("\\v'%d.%dm'\\*(%d\\v'-%d.%dm'\n",
			a1, a2, p, a1, a2);
	a = (ps * 6 * amt) / 100;
/*
	if (dir == 1 || dir == 3)
		eht[yyval] =+ a;
	if( dir==1 )
		ebase[yyval] =- a;
	else if( dir==3 )
		ebase[yyval] =+ a;
*/
	if(dbg)printf(".\tmove %d dir %d amt %d; h=%d b=%d\n", 
		p, dir, amt, eht[yyval], ebase[yyval]);
}

funny(n) int n; {
	int f, t;
	yyval = oalloc();
	switch(n) {
	case 'S':
		f = "\\(*S"; break;
	case 'U':
		f = "\\(cu"; break;
	case 'A':	/* intersection */
		f = "\\(ca"; break;
	case 'P':
		f = "\\(*P"; break;
	case 'I':
		f = "\\(is";
		break;
	}
	printf(".ds %d %s\n", yyval, f);
	eht[yyval] = VERT(2);
	ebase[yyval] = 0;
	if(dbg)printf(".\tfunny: S%d <- %s; h=%d b=%d\n", 
		yyval, f, eht[yyval], ebase[yyval]);
}

