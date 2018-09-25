# include "ne.h"

boverb(p1, p2) int p1, p2; {
	int h, b, treg;
	treg = oalloc();
	yyval = p1;
	h = eht[p1] + eht[p2];
	b = eht[p2] - VERT(1);
	if(dbg)printf(".\tb:bob: S%d <- S%d over S%d; b=%d, h=%d\n", 
		yyval, p1, p2, b, h);
	nrwid(p1, ps, p1);
	nrwid(p2, ps, p2);
	printf(".nr %d \\n(%d\n", treg, p1);
	printf(".if \\n(%d>\\n(%d .nr %d \\n(%d\n", p2, treg, treg, p2);
	printf(".ds %d \\v'%du'\\h'\\n(%du-\\n(%du/2u'\\*(%d\\\n", 
		yyval, eht[p2]-ebase[p2]-VERT(1), treg, p2, p2);
	printf("\\h'-\\n(%du-\\n(%du/2u'\\v'%du'\\*(%d\\\n", 
		p2, p1, -eht[p2]+ebase[p2]-ebase[p1], p1);
	printf("\\h'-\\n(%du-\\n(%du-2u/2u'\\v'%du'\\l'\\n(%du'\\v'%du'\n", 
		 treg, p1, ebase[p1], treg, VERT(1));
	ebase[yyval] = b;
	eht[yyval] = h;
	ofree(p2);
	ofree(treg);
}

bshiftb(p1, dir, p2) int p1, dir, p2; {
	int shval, sh1, sh2, effps, effps2, d1, h1, b1, h2, b2, h;
	int diffps;
	yyval = p1;
	h1 = eht[p1]; b1 = ebase[p1];
	h2 = eht[p2]; b2 = ebase[p2];
	if( dir > 0 ) {	/* subscript */
		d1 = VERT(1);
		shval = - d1 + h2 - b2;
		if( d1+b1 > h2 ) /* move little sub down */
			shval = b1-b2;
		ebase[yyval] = b1 + max(0, h2-b1-d1);
		eht[yyval] = h1 + max(0, h2-b1-d1);
	} else {	/* superscript */
		d1 = VERT(1);
		ebase[yyval] = b1;
		shval = -VERT(1) - b2;
		if( VERT(1) + h2 < h1-b1 )	/* raise little super */
			shval = -(h1-b1) + h2-b2 - d1;
		eht[yyval] = h1 + max(0, h2 - VERT(1));
	}
	if(dbg)printf(".\tb:b shift b: S%d <- S%d vert %d S%d vert %d; b=%d, h=%d\n", 
		yyval, p1, shval, p2, -shval, ebase[yyval], eht[yyval]);
	printf(".as %d \\v'%du'\\*(%d\\v'%du'\n", 
		yyval, shval, p2, -shval);
	ofree(p2);
}

eqnbox(p1, p2) int p1, p2; {
	int b, h;
	yyval = p1;
	b = max(ebase[p1], ebase[p2]);
	eht[yyval] = h = b + max(eht[p1]-ebase[p1], 
		eht[p2]-ebase[p2]);
	ebase[yyval] = b;
	if(dbg)printf(".\te:eb: S%d <- S%d S%d; b=%d, h=%d\n", 
		yyval, p1, p2, b, h);
	printf(".as %d \"\\*(%d\n", yyval, p2);
	ofree(p2);
}

size(p1, p2) {
	yyval = p2;
}

numb(p1) char *p1; {
	int i, n, c;
	for(i=n=0; (c=p1[i++])!='\0'; )
		if( c>='0' && c<='9' )
			n = n*10 + c-'0';
	if(dbg)printf(".\tnumb: %s %d\n", p1, n);
	return( n );
}

font(p1, p2) {
	yyval = p2;
}

shift(p1) int p1; {
	yyval = p1;
	if(dbg)printf(".\tshift: %d;ps=%d\n", yyval, ps);
}

sqrt(p2) int p2; {
	yyval = p2;
	nrwid(p2, ps, p2);
	printf(".ds %d \\v'%du'\\e\\L'%du'\\l'\\n(%du'",
		p2, ebase[p2], -eht[p2], p2);
	printf("\\v'%du'\\h'-\\n(%du'\\*(%d\n", eht[p2]-ebase[p2], p2, p2);
	eht[p2] =+ VERT(1);
	if(dbg)printf(".\tsqrt: S%d <- S%d;b=%d, h=%d\n", 
		p2, p2, ebase[p2], eht[p2]);
}

lpile(type, p1, p2) int type, p1, p2; {
	int bi, hi, i, gap, h, b, j, nlist, nlist2, mid;
	yyval = oalloc();
	gap = VERT(1);
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
			: b - VERT(1) - gap;
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
		type=='R' ? 1 : 0, yyval);
	for(i = p2-1; i >=p1; i--) {
		hi = eht[lp[i]]; 
		bi = ebase[lp[i]];
	switch(type) {

	case 'L':
		printf("\\v'%du'\\*(%d\\h'-\\n(%du'\\v'0-%du'\\\n", 
			-bi, lp[i], lp[i], hi-bi+gap);
		continue;
	case 'R':
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
		type!='R' ? 1 : 0, yyval);
	for( i=p1; i<p2; i++ )
		ofree(lp[i]);
}

shift2(p1, p2, p3) int p1, p2, p3; {
	int effps, effps2, h1, h2, h3, b1, b2, b3, subsh, d1, d2, supsh;
	int treg;
	treg = oalloc();
	yyval = p1;
	if(dbg)printf(".\tshift2 s%d <- %d %d %d\n", yyval, p1, p2, p3);
	h1 = eht[p1]; b1 = ebase[p1];
	h2 = eht[p2]; b2 = ebase[p2];
	h3 = eht[p3]; b3 = ebase[p3];
	d1 = VERT(1);
	subsh = -d1+h2-b2;
	if( d1+b1 > h2 ) /* move little sub down */
		subsh = b1-b2;
	supsh = - VERT(1) - b3;
	d2 = VERT(1);
	if( VERT(1)+h3 < h1-b1 )
		supsh = -(h1-b1) + (h3-b3) - d2;
	eht[yyval] = h1 + max(0, h3-VERT(1)) + max(0, h2-b1-d1);
	ebase[yyval] = b1+max(0, h2-b1-d1);
	nrwid(p2, effps, p2);
	nrwid(p3, effps, p3);
	printf(".nr %d \\n(%d\n", treg, p3);
	printf(".if \\n(%d>\\n(%d .nr %d \\n(%d\n", p2, treg, treg, p2);
	printf(".as %d \\v'%du'\\*(%d\\h'-\\n(%du'\\v'%du'\\\n", 
		p1, subsh, p2, p2, -subsh+supsh);
	printf("\\*(%d\\h'-\\n(%du+\\n(%du'\\v'%du'\n", 
		p3, p3, treg, -supsh);
	ps =+ 2;
	ofree(p2); ofree(p3); ofree(treg);
}
