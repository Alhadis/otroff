 /* t8.c: write out one line of output table */
# include "t..c"
# define realsplit ((ct=='a'||ct=='n') && table[nl][c].rcol)
int watchout;
int once;
int topat[MAXCOL];
putline(i, nl)
	/* i is line number for deciding format */
	/* nl is line number for finding data   usually identical */
{
int c, lf, ct, form, lwid, vspf, ip, cmidx, exvspen;
char *s, *size, *fn;
watchout=vspf=exvspen=0;
if (i==0) once=0;
if (i==0 && ( allflg || boxflg || dboxflg))
	fullwide(0,   dboxflg? '=' : '-');
if (instead[nl]==0 && fullbot[nl] ==0)
for(c=0; c<ncol; c++)
	{
	s = table[nl][c].col;
	if (s==0) continue;
	if (vspen(s))
		{
		for(ip=nl; ip<nlin; ip=next(ip))
			if (!vspen(s=table[ip][c].col)) break;
		if (s>0 && s<128)
		fprintf(tabout, ".ne \\n(%c|u\n",s);
		continue;
		}
	if (point(s)) continue;
	fprintf(tabout, ".ne \\n(%c|u\n",s);
	}
if (linestop[nl])
	fprintf(tabout, ".mk #%c\n", linestop[nl]+'a'-1);
lf = prev(nl);
if (instead[nl])
	{
	puts(instead[nl]);
	return;
	}
if (fullbot[nl])
	{
	switch (ct=fullbot[nl])
		{
		case '=':
		case '-':
			fullwide(nl,ct);
		}
	return;
	}
for(c=0; c<ncol; c++)
	{
	if (instead[nl]==0 && fullbot[nl]==0)
	if (vspen(table[nl][c].col)) vspf=1;
	if (lf>=0)
		if (vspen(table[lf][c].col)) vspf=1;
	}
if (vspf)
	{
	fprintf(tabout, ".nr #^ \\n(\\*(#du\n");
	fprintf(tabout, ".nr #- \\n(#^\n"); /* current line position relative to bottom */
	}
vspf=0;
for(c=0; c<ncol; c++)
	{
	s = table[nl][c].col;
	if (s==0) continue;
	if (point(s) ) continue;
	lf=prev(nl);
	if (lf>=0 && vspen(table[lf][c].col))
		fprintf(tabout, ".if (\\n(%c|+\\n(^%c-1v)>\\n(#- .nr #- +(\\n(%c|+\\n(^%c-\\n(#--1v)\n",s,'a'+c,s,'a'+c);
	else
		fprintf(tabout, ".if (\\n(%c|+\\n(#^-1v)>\\n(#- .nr #- +(\\n(%c|+\\n(#^-\\n(#--1v)\n",s,s);
	}
if (allflg && once>0 )
	fullwide(i,'-');
once=1;
runtabs(i);
if (allh(i))
	fprintf(tabout, ".vs 2p\n");
fprintf(tabout, "\\&");
for(c=0; c<ncol; c++)
	{
	if (i+1<nlin && (lf=left(i,c, &lwid))>=0)
		{
		tohcol(c);
		drawvert(lf, i, c, lwid);
		}
	if (rightl && c+1==ncol) continue;
	if ((form=ctype(i,c))!='s')
		fprintf(tabout, "\\h'|\\n(%du'",
			 ((form=='n'||form=='a')&&lused[c]==0)?c+CMID:c+CLEFT);
	s= table[nl][c].col;
	fn = font[stynum[i]][c];
	size = csize[stynum[i]][c];
	if (*size==0)size=0;
	switch(ct=ctype(i, c))
		{
		case 'n':
		case 'a':
			if (table[nl][c].rcol)
				{
			   if (lused[c]) /*Zero field width*/
				{
				fprintf(tabout, "%c%c",F1,F2);
				puttext(table[nl][c].col,fn,size);
				fprintf(tabout, "%c",F1);
				}
				s= table[nl][c].rcol;
				form=1;
				break;
				}
		case 'c':
			form=3; break;
		case 'r':
			form=2; break;
		case 'l':
			form=1; break;
		case '-':
		case '=':
			if (real(table[nl][c].col))
				fprintf(stderr,"%s: line %d: Data ignored on table line %d\n", ifile, iline-1, i+1);
			makeline(i,c,ct);
			continue;
		default:
			continue;
		}
	if (realsplit ? rused[c]: used[c]) /*Zero field width*/
		; else continue;
	/* form: 1 left, 2 right, 3 center adjust */
	if (ifline(s))
		{
		makeline(i,c,ifline(s));
		continue;
		}
	ip = prev(nl);
	cmidx = ctop[stynum[nl]][c]==0;
	if (ip>=0)
	if (vspen(table[ip][c].col))
		{
		if (exvspen==0)
			{
			fprintf(tabout, "\\v'-(\\n(\\*(#du-\\n(^%cu", c+'a');
			if (cmidx)
				fprintf(tabout, "-((\\n(#-u-\\n(^%cu)/2u)", c+'a');
			fprintf(tabout, "'");
			}
		}
	fprintf(tabout, "%c", F1);
	if (form!= 1)
		fprintf(tabout, "%c", F2);
	if (vspen(s))
		vspf=1;
	else
	puttext(s, fn, size);
	if (form !=2)
		fprintf(tabout, "%c", F2);
	fprintf(tabout, "%c", F1);
	if (ip>=0)
	if (vspen(table[ip][c].col))
		{
		exvspen = (c+1 < ncol) && vspen(table[ip][c+1].col) &&
			(topat[c] == topat[c+1]) &&
			(cmidx == (ctop [stynum[nl]][c+1]==0)) && (left(i,c,&lwid)==0);
		if (exvspen==0)
			{
			fprintf(tabout, "\\v'(\\n(\\*(#du-\\n(^%cu", c+'a');
			if (cmidx)
				fprintf(tabout, "-((\\n(#-u-\\n(^%cu)/2u)", c+'a');
			fprintf(tabout, "'");
			}
		}
	else
		exvspen=0;
	/* if lines need to be split for gcos here is the place for a backslash */
	}
fprintf(tabout, "\n");
if (allh(i)) fprintf(tabout, ".vs\n");
if (watchout)
	funnies(i,nl);
if (vspf)
	{
	for(c=0; c<ncol; c++)
		if (vspen(table[nl][c].col) && (nl==0 || (lf=prev(nl))<0 || !vspen(table[lf][c].col)))
			{
			fprintf(tabout, ".nr ^%c \\n(#^u\n", 'a'+c);
			topat[c]=nl;
			}
	}
}
puttext(s,fn, size)
	char *s, *size, *fn;
{
if (point(s))
	{
	putfont(fn);
	putsize(size);
	fprintf(tabout, "%s",s);
	if (*fn>0) putfont("P");
	if (size!=0) putsize("0");
	}
else
	watchout=1;
}
funnies( stl, lin)
{
/* write out funny diverted things */
int c, s, pl;
char *fn;
fprintf(tabout, ".mk ##\n"); /* rmember current vertical position */
fprintf(tabout, ".nr %d \\n(##\n", S1); /* bottom position */
for(c=0; c<ncol; c++)
	{
	s = table[lin][c].col;
	if (point(s)) continue;
	if (s==0) continue;
	fprintf(tabout, ".sp |\\n(##u-1v\n");
	fprintf(tabout, ".nr %d ", SIND);
	switch(ctype(stl,c))
		{
		case 'n':
		case 'c':
			fprintf(tabout, "(\\n(%du+\\n(%du-\\n(%c-u)/2u\n",c+CLEFT,c-1+ctspan(lin,c)+CRIGHT, s);
			break;
		case 'l':
			fprintf(tabout, "\\n(%du\n",c+CLEFT);
			break;
		case 'a':
			fprintf(tabout, "\\n(%du\n",c+CMID);
			break;
		case 'r':
			fprintf(tabout, "\\n(%du-\\n(%c-u\n", c+CRIGHT, s);
			break;
		}
	fprintf(tabout, ".in +\\n(%du\n", SIND);
	fn=font[stynum[stl]][c];
	putfont(fn);
	pl = prev(stl);
	if (stl>0 && pl>=0 && vspen(table[pl][c].col))
		{
		fprintf(tabout, ".sp |\\n(^%cu\n", 'a'+c);
		if (ctop[stynum[stl]][c]==0)
			{
			fprintf(tabout, ".nr %d \\n(#-u-\\n(^%c-\\n(%c|+1v\n",TMP, 'a'+c, s);
			fprintf(tabout, ".if \\n(%d>0 .sp \\n(%du/2u\n", TMP, TMP);
			}
		}
	fprintf(tabout, ".%c+\n",s);
	fprintf(tabout, ".in -\\n(%du\n", SIND);
	if (*fn>0) putfont("P");
	fprintf(tabout, ".mk %d\n", S2);
	fprintf(tabout, ".if \\n(%d>\\n(%d .nr %d \\n(%d\n", S2, S1, S1, S2);
	}
fprintf(tabout, ".sp |\\n(%du\n", S1);
}
putfont(fn)
	char *fn;
{
if (fn && *fn)
	fprintf(tabout,  fn[1] ? "\\f(%.2s" : "\\f%.2s",  fn);
}
putsize(s)
	char *s;
{
if (s && *s)
	fprintf(tabout, "\\s%s",s);
}
