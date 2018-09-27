# include "e.h"

boverb(p1, p2) int p1, p2; {
	int h, b, treg, d;
	treg = oalloc();
	yyval = p1;
	d = (ps*6*3) / 10;	/* 0.3m */
	h = eht[p1] + eht[p2] + VERT(d);
	b = eht[p2] - d;
	if(dbg)printf(".\tb:bob: S%d <- S%d over S%d; b=%d, h=%d\n", 
		yyval, p1, p2, b, h);
	nrwid(p1, ps, p1);
	nrwid(p2, ps, p2);
	printf(".nr %d \\n(%d\n", treg, p1);
	printf(".if \\n(%d>\\n(%d .nr %d \\n(%d\n", p2, treg, treg, p2);
	printf(".nr %d \\n(%d+\\s%d.5m\\s0\n", treg, treg, ps);
	printf(".ds %d \\v'%du'\\h'\\n(%du-\\n(%du/2u'\\*(%d\\\n", 
		yyval, eht[p2]-ebase[p2]-d, treg, p2, p2);
	printf("\\h'-\\n(%du-\\n(%du/2u'\\v'%du'\\*(%d\\\n", 
		p2, p1, -(eht[p2]-ebase[p2]+d+ebase[p1]), p1);
	printf("\\h'-\\n(%du-\\n(%du/2u+.1m'\\v'%du'\\l'\\n(%du-.2m'\\h'.1m'\\v'%du'\n", 
		 treg, p1, ebase[p1]+d, treg, d);
	ebase[yyval] = b;
	eht[yyval] = h;
	lfont[yyval] = rfont[yyval] = 0;
	ofree(p2);
	ofree(treg);
}

bshiftb(p1, dir, p2) int p1, dir, p2; {
	int shval, sh1, sh2, effps, effps2, d1, h1, b1, h2, b2, h;
	int diffps;
	yyval = p1;
	h1 = eht[p1]; b1 = ebase[p1];
	h2 = eht[p2]; b2 = ebase[p2];
	effps = ps>6 ? ps : 6;
	effps2 = (ps+deltaps)>6 ? ps+deltaps : 6;
	diffps = deltaps;
	sh1 = sh2 = "";
	if( dir > 0 ) {	/* subscript */
		/* top 1/2m above bottom of main box */
		d1 = VERT( (effps2*6)/2 );
		shval = - d1 + h2 - b2;
		if( d1+b1 > h2 ) /* move little sub down */
			shval = b1-b2;
		ebase[yyval] = b1 + max(0, h2-b1-d1);
		eht[yyval] = h1 + max(0, h2-b1-d1);
		if (rfont[p1] == ITAL && lfont[p2] == ROM)
			sh1 = "\\|";
		if (rfont[p2] == ITAL)
			sh2 = "\\|";
	} else {	/* superscript */
		/* 4/10 up main box */
		d1 = VERT( (effps*6*2)/10 );
		ebase[yyval] = b1;
		shval = -VERT( (4 * (h1-b1)) / 10 ) - b2;
		if( VERT(4*(h1-b1)/10) + h2 < h1-b1 )	/* raise little super */
			shval = -(h1-b1) + h2-b2 - d1;
		eht[yyval] = h1 + max(0, h2-VERT((6*(h1-b1))/10));
		if (rfont[p1] == ITAL)
			sh1 = "\\|";
	}
	if(dbg)printf(".\tb:b shift b: S%d <- S%d vert %d S%d vert %d; b=%d, h=%d\n", 
		yyval, p1, shval, p2, -shval, ebase[yyval], eht[yyval]);
	printf(".as %d \\v'%du'\\s-%d%s\\*(%d%s\\s+%d\\v'%du'\n", 
		yyval, shval, diffps, sh1, p2, sh2, diffps, -shval);
	ps =+ deltaps;
	if (rfont[p2] == ITAL)
		rfont[p1] = 0;
	else
		rfont[p1] = rfont[p2];
	ofree(p2);
}

eqnbox(p1, p2, lu) {
	int b, h, sh;
	yyval = p1;
	b = max(ebase[p1], ebase[p2]);
	eht[yyval] = h = b + max(eht[p1]-ebase[p1], 
		eht[p2]-ebase[p2]);
	ebase[yyval] = b;
	if(dbg)printf(".\te:eb: S%d <- S%d S%d; b=%d, h=%d\n", 
		yyval, p1, p2, b, h);
	if (rfont[p1] == ITAL && lfont[p2] == ROM)
		sh = "\\|";
	else
		sh = "";
	if (lu) {
		printf(".nr %d \\w'\\s%d\\*(%d%s'\n", p1, ps, p1, sh);
		printf(".ds %d \\h'|\\n(97u-\\n(%du'\\*(%d\n", p1, p1, p1);
	}
	printf(".as %d \"%s\\*(%d\n", yyval, sh, p2);
	rfont[p1] = rfont[p2];
	ofree(p2);
}

size(p1, p2) int p1, p2; {
		/* old size in p1, new in ps */
	yyval = p2;
	if(dbg)printf(".\tb:sb: S%d <- \\s%d S%d \\s%d; b=%d, h=%d\n", 
		yyval, ps, p2, p1, ebase[yyval], eht[yyval]);
	printf(".ds %d \\s%d\\*(%d\\s%d\n", 
		yyval, ps, p2, p1);
	ps = p1;
}

numb(p1) char *p1; {
	int i, n, c;
	for(i=n=0; (c=p1[i++])!='\0'; )
		if( c>='0' && c<='9' )
			n = n*10 + c-'0';
	if(dbg)printf(".\tnumb: %s %d\n", p1, n);
	return( n );
}

setfont(ch1) char ch1; {
	/* use number '1', '2', '3' for roman, italic, bold */
	yyval = ft;
	ft = ch1;
	printf(".ft %c\n", ch1);
	if(dbg)printf(".\tsetfont %c\n", ch1);
}

font(p1, p2) int p1, p2; {
		/* old font in p1, new in ft */
	yyval = p2;
	lfont[yyval] = rfont[yyval] = ft==ITAL ? ITAL : ROM;
	if(dbg)printf(".\tb:fb: S%d <- \\f%c S%d \\f%c b=%d,h=%d,lf=%c,rf=%c\n", 
		yyval, ft, p2, p1, ebase[yyval], eht[yyval], lfont[yyval], rfont[yyval]);
	printf(".ds %d \\f%c\\*(%d\\f%c\n", 
		yyval, ft, p2, p1);
	ft = p1;
	printf(".ft %c\n", ft);
}

fatbox(p) int p; {
	int sh;
	yyval = p;
	sh = ps / 4;
	nrwid(p, ps, p);
	printf(".ds %d \\*(%d\\h'-\\n(%du+%du'\\*(%d\n", p, p, p, sh, p);
	if(dbg)printf(".\tfat %d, sh=%d\n", p, sh);
}

shift(p1) int p1; {
	ps =- deltaps;
	yyval = p1;
	if(dbg)printf(".\tshift: %d;ps=%d\n", yyval, ps);
}

sqrt(p2) int p2; {
	int nps;
	nps = ((eht[p2]*9)/10+5)/6;
	yyval = p2;
	eht[yyval] = VERT( (nps*6*12)/10 );
	if(dbg)printf(".\tsqrt: S%d <- S%d;b=%d, h=%d\n", 
		yyval, p2, ebase[yyval], eht[yyval]);
	if (rfont[yyval] == ITAL)
		printf(".as %d \\|\n", yyval);
	nrwid(p2, ps, p2);
	printf(".ds %d \\v'%du'\\s%d\\v'-.2m'\\(sr\\l'\\n(%du\\(rn'\\v'.2m'\\s%d", 
		yyval, ebase[p2], nps, p2, ps);
	printf("\\v'%du'\\h'-\\n(%du'\\*(%d\n", -ebase[p2], p2, p2);
}

lpile(type, p1, p2) int type, p1, p2; {
	int bi, hi, i, gap, h, b, j, nlist, nlist2, mid;
	yyval = oalloc();
	gap = VERT( (ps*6*4)/10 ); /* 4/10 m between blocks */
	if( type=='-' ) gap = 0;
	nlist = p2 - p1;
	nlist2 = (nlist+1)/2;
	mid = p1 + nlist2 -1;
	h = 0;
	for( i=p1; i<p2; i++ )
		h =+ eht[lp[i]];
	eht[yyval] = h + (nlist-1)*gap;
	b = 0;
	for( i=p2-1; i>mid; i-- )
		b =+ eht[lp[i]] + gap;
	ebase[yyval] = (nlist%2) ? b + ebase[lp[mid]]
			: b - VERT( (ps*6*5)/10 ) - gap;
	if(dbg) {
		printf(".\tS%d <- %c pile of:", yyval, type);
		for( i=p1; i<p2; i++)
			printf(" S%d", lp[i]);
		printf(";h=%d b=%d\n", eht[yyval], ebase[yyval]);
	}
	nrwid(lp[p1], ps, lp[p1]);
	printf(".nr %d \\n(%d\n", yyval, lp[p1]);
	for( i = p1+1; i<p2; i++ ) {
		nrwid(lp[i], ps, lp[i]);
		printf(".if \\n(%d>\\n(%d .nr %d \\n(%d\n", 
			lp[i], yyval, yyval, lp[i]);
	}
	printf(".ds %d \\v'%du'\\h'%du*\\n(%du'\\\n", yyval, ebase[yyval], 
		type==ROM ? 1 : 0, yyval);
	for(i = p2-1; i >=p1; i--) {
		hi = eht[lp[i]]; 
		bi = ebase[lp[i]];
	switch(type) {

	case 'L':
		printf("\\v'%du'\\*(%d\\h'-\\n(%du'\\v'0-%du'\\\n", 
			-bi, lp[i], lp[i], hi-bi+gap);
		continue;
	case ROM:
		printf("\\v'%du'\\h'-\\n(%du'\\*(%d\\v'0-%du'\\\n", 
			-bi, lp[i], lp[i], hi-bi+gap);
		continue;
	case 'C':
	case '-':
		printf("\\v'%du'\\h'\\n(%du-\\n(%du/2u'\\*(%d", 
			-bi, yyval, lp[i], lp[i]);
		printf("\\h'-\\n(%du-\\n(%du/2u'\\v'0-%du'\\\n", 
			yyval, lp[i], hi-bi+gap);
		continue;
		}
	}
	printf("\\v'%du'\\h'%du*\\n(%du'\n", eht[yyval]-ebase[yyval]+gap, 
		type!=ROM ? 1 : 0, yyval);
	for( i=p1; i<p2; i++ )
		ofree(lp[i]);
	lfont[yyval] = rfont[yyval] = 0;
}

shift2(p1, p2, p3) int p1, p2, p3; {
	int effps, effps2, h1, h2, h3, b1, b2, b3, subsh, d1, d2, supsh;
	int treg;
	treg = oalloc();
	yyval = p1;
	if(dbg)printf(".\tshift2 s%d <- %d %d %d\n", yyval, p1, p2, p3);
	effps = (ps+deltaps)>6 ? ps+deltaps:6;
	eht[p3] = h3 = VERT( (eht[p3] * effps) / (ps>6 ? ps : 6) );
	ps =+ deltaps;
	effps2 = (ps+deltaps)>6 ? ps+deltaps:6;
	h1 = eht[p1]; b1 = ebase[p1];
	h2 = eht[p2]; b2 = ebase[p2];
	b3 = ebase[p3];
	d1 = VERT( (effps2*6)/2 );
	subsh = -d1+h2-b2;
	if( d1+b1 > h2 ) /* move little sub down */
		subsh = b1-b2;
	supsh = -VERT( (4*(h1-b1))/10 ) - b3;
	d2 = VERT( (effps*6*2)/10 );
	if( VERT(4*(h1-b1)/10)+h3 < h1-b1 )
		supsh = -(h1-b1) + (h3-b3) - d2;
	eht[yyval] = h1 + max(0, h3-VERT( (6*(h1-b1))/10 )) + max(0, h2-b1-d1);
	ebase[yyval] = b1+max(0, h2-b1-d1);
	if (rfont[p1] == ITAL && lfont[p2] == ROM)
		printf(".ds %d \\|\\*(%d\n", p2, p2);
	if (rfont[p2] == ITAL)
		printf(".as %d \\|\n", p2);
	nrwid(p2, effps, p2);
	if (rfont[p1] == ITAL && lfont[p3] == ROM)
		printf(".ds %d \\|\\|\\*(%d\n", p3, p3);
	else
		printf(".ds %d \\|\\*(%d\n", p3, p3);
	nrwid(p3, effps, p3);
	printf(".nr %d \\n(%d\n", treg, p3);
	printf(".if \\n(%d>\\n(%d .nr %d \\n(%d\n", p2, treg, treg, p2);
	printf(".as %d \\v'%du'\\s%d\\*(%d\\h'-\\n(%du'\\v'%du'\\\n", 
		p1, subsh, effps, p2, p2, -subsh+supsh);
	printf("\\s%d\\*(%d\\h'-\\n(%du+\\n(%du'\\s%d\\v'%du'\n", 
		effps, p3, p3, treg, effps2, -supsh);
	ps =+ deltaps;
	if (rfont[p2] == ITAL)
		rfont[yyval] = 0;	/* lie */
	ofree(p2); ofree(p3); ofree(treg);
}
