# include "e.h"

fromto(p1, p2, p3) int p1, p2, p3; {
	int h, b, h1, b1, pss;
	yyval = oalloc();
	lfont[yyval] = rfont[yyval] = 0;
	h1 = eht[yyval] = eht[p1];
	b1 = ebase[p1];
	b = 0;
	pss = ps;
	ps =+ 3;
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
		printf("\\v'%du'\\h'\\n(%du-\\n(%du/2u'\\s%d\\*(%d\\s%d", 
			eht[p2]-ebase[p2]+b1, yyval, p2, pss, p2, ps);
		printf("\\h'-\\n(%du-\\n(%du/2u'\\v'%du'\\\n", 
			yyval, p2, -(eht[p2]-ebase[p2]+b1));
	}
	printf("\\h'\\n(%du-\\n(%du/2u'\\*(%d\\h'\\n(%du-\\n(%du/2u'\\\n", 
		yyval, p1, p1, yyval, p1);
	if( p3>0 ) {
		printf("\\v'%du'\\h'-\\n(%du-\\n(%du/2u'\\s%d\\*(%d\\s%d\\h'\\n(%du-\\n(%du/2u'\\v'%du'\\\n", 
			-(h1-b1+ebase[p3]), yyval, p3, pss, p3, ps, yyval, p3, (h1-b1+ebase[p3]));
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
	lfont[yyval] = rfont[yyval] = 0;
	n = (h1+(6*ps-1))/(6*ps);
	if( n<2 ) n = 1;
	m = n-2;
	if( leftc=='{' ){
		n = n%2 ? n : ++n;
		if( n<3 ) n=3;
		m = n-3;
	}
	eht[yyval] = VERT(6 * ps * n);
	ebase[yyval] = b1 + (eht[yyval]-h1)/2;
	v = b1 - h1/2 + VERT( (ps*6*4)/10 );
	printf(".ds %d \\|\\v'%du'", yyval, v);
	switch( leftc ) {
		case 'n':	/* nothing */
		case '\0':
			break;
		case 'f':	/* floor */
			if (n <= 1)
				printf("\\(lf");
			else
				brack(m, "\\(bv", "\\(bv", "\\(lf");
			break;
		case 'c':	/* ceiling */
			if (n <= 1)
				printf("\\(lc");
			else
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
		case '|':
			brack(m, "|", "|", "|");
			break;
		default:
			brack(m, &leftc, &leftc, &leftc);
			break;
		}
	printf("\\v'%du'\\*(%d", -v, p1);
	if( rightc ) {
		printf("\\|\\v'%du'", v);
		switch( rightc ) {
			case 'f':	/* floor */
				if (n <= 1)
					printf("\\(rf");
				else
					brack(m, "\\(bv", "\\(bv", "\\(rf");
				break;
			case 'c':	/* ceiling */
				if (n <= 1)
					printf("\\(rc");
				else
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
			case '|':
				brack(m, "|", "|", "|");
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
	int c, t, effps;
	c = oalloc();
	t = oalloc();
	effps = ps < 6 ? 6 : ps;
	nrwid(p1, effps, p1);
	printf(".nr 10 %du\n", VERT(max(eht[p1]-ebase[p1]-6*ps,0)));	/* vertical shift if high */
	printf(".if \\n(ct>1 .nr 10 \\n(10+\\s%d.25m\\s0\n", effps);
	printf(".nr %d \\s%d.1m\\s0\n", t, effps);	/* horiz shift if high */
	printf(".if \\n(ct>1 .nr %d \\s%d.15m\\s0\n", t, effps);
	switch(type) {
		case 'V':	/* vec */
			printf(".ds %d \\v'-.4m'\\s%d\\(->\\s0\\v'.4m'\n", c, max(effps-3, 6));
			break;
		case 'Y':	/* dyad */
			printf(".ds %d \\v'-.4m'\\s%d\\z\\(<-\\(->\\s0\\v'.4m'\n", c, max(effps-3, 6));
			break;
		case 'H':	/* hat */
			printf(".ds %d ^\n", c);
			break;
		case 'T':	/* tilde */
			printf(".ds %d ~\n", c);
			break;
		case 'D':	/* dot */
			printf(".ds %d \\s%d\\v'-.67m'.\\v'.67m'\\s0\n", c, effps);
			break;
		case 'U':	/* umlaut = dotdot */
			printf(".ds %d \\s%d\\v'-.67m'..\\v'.67m\\s0'\n", c, effps);
			break;
		case 'B':	/* bar */
			printf(".ds %d \\s%d\\v'.18m'\\h'.05m'\\l'\\n(%du-.1m\\(rn'\\h'.05m'\\v'-.18m'\\s0\n",
				c, effps, p1);
			break;
		case 'N':	/* under */
			printf(".ds %d \\l'\\n(%du\\(ul'\n", c, p1);
			printf(".nr %d 0\n", t);
			printf(".nr 10 0-%d\n", -ebase[p1]);
			break;
		}
	nrwid(c, ps, c);
	if (lfont[p1] != ITAL)
		printf(".nr %d 0\n", t);
	printf(".as %d \\h'-\\n(%du-\\n(%du/2u+\\n(%du'\\v'0-\\n(10u'\\*(%d", 
		p1, p1, c, t, c);
	printf("\\v'\\n(10u'\\h'-\\n(%du+\\n(%du/2u-\\n(%du'\n", c, p1, t);
	if (type != 'N')
		eht[p1] =+ VERT( (6*ps*15) / 100);	/* 0.15m */
	if(dbg)printf(".\tdiacrit: %c over S%d, lf=%c, rf=%c, h=%d,b=%d\n",
		type, p1, lfont[p1], rfont[p1], eht[p1], ebase[p1]);
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
	t = 'S';
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
		t = 'I';
		printf(".ds %d \\s%d\\v'.1m'\\s+4%s\\s-4\\v'-.1m'\\s%d\n", 
			yyval, ps, f, ps);
		eht[yyval] = VERT( (((ps+4)*12)/10)*6 );
		ebase[yyval] = VERT( (ps*6*3)/10 );
		break;
	default:
		t = 0;
	}
	if( t == 'S' ) {
		printf(".ds %d \\s%d\\v'.3m'\\s+5%s\\s-5\\v'-.3m'\\s%d\n", 
			yyval, ps, f, ps);
		eht[yyval] = VERT( (ps+5)*6 -(ps*6*2)/10 );
		ebase[yyval] = VERT( (ps*6*3)/10 );
	}
	if(dbg)printf(".\tfunny: S%d <- %s; h=%d b=%d\n", 
		yyval, f, eht[yyval], ebase[yyval]);
	lfont[yyval] = rfont[yyval] = ROM;
}


integral(p, p1, p2) {
	if (p1 != 0)
		printf(".ds %d \\h'-0.4m'\\v'0.4m'\\*(%d\\v'-0.4m'\n", p1, p1);
	if (p2 != 0)
		printf(".ds %d \\v'-0.3m'\\*(%d\\v'0.3m'\n", p2, p2);
	if (p1 != 0 & p2 != 0)
		shift2(p, p1, p2);
	else if (p1 != 0)
		bshiftb(p, 1, p1);
	else if (p2 != 0)
		bshiftb(p, -1, p2);
	if(dbg)printf(".\tintegral: S%d; h=%d b=%d\n", 
		p, eht[p], ebase[p]);
	lfont[p] = ROM;
}

setintegral() {
	int f;
	yyval = oalloc();
	f = "\\(is";
	printf(".ds %d \\s%d\\v'.1m'\\s+4%s\\s-4\\v'-.1m'\\s%d\n", 
		yyval, ps, f, ps);
	eht[yyval] = VERT( (((ps+4)*12)/10)*6 );
	ebase[yyval] = VERT( (ps*6*3)/10 );
	lfont[yyval] = rfont[yyval] = ROM;
}
