 /* t7.c: control to write table entries */
# include "t..c"
# define realsplit ((ct=='a'||ct=='n') && table[i][c].rcol)
runout()
{
int i, c;
if (boxflg || allflg || dboxflg) need();
if (ctrflg)
	{
	fprintf(tabout, ".nr #I \\n(.i\n");
	fprintf(tabout, ".in +(\\n(.lu-\\n(TWu-\\n(.iu)/2u\n");
	}
fprintf(tabout, ".fc %c %c\n", F1, F2);
fprintf(tabout, ".nr #T 0-1\n");
deftail();
for(i=0; i<nlin; i++)
	putline(i,i);
if (leftover)
	yetmore();
fprintf(tabout, ".fc\n");
fprintf(tabout, ".nr T. 1\n");
fprintf(tabout, ".T# 1\n");
if (ctrflg)
	fprintf(tabout, ".in \\n(#Iu\n");
}
runtabs(i)
{
int c, ct;
fprintf(tabout, ".ta ");
for(c=0; c<ncol; c++)
	{
	if (fspan(i,c))
		continue;
	switch(ct=ctype(i,c))
		{
		case 'n':
		case 'a':
			if (table[i][c].rcol)
			  if (lused[c]) /*Zero field width*/
				fprintf(tabout, "\\n(%du ",c+CMID);
		case 'c':
		case 'l':
		case 'r':
		    if (realsplit? rused[c]: used[c])
			fprintf(tabout, "\\n(%du ",c+CRIGHT);
			continue;
		case 's':
			if (lspan(i,c))
				fprintf(tabout, "\\n(%du ", c+CRIGHT);
			continue;
		}
	}
fprintf(tabout, "\n");
}
ifline(s)
	char *s;
{
if (s[1] ) return(0);
if (s[0] == '_') return('-');
if (s[0] == '=') return('=');
return(0);
}
need()
{
int texlin, horlin, i;
for(texlin=horlin=i=0; i<nlin; i++)
	{
	if (fullbot[i]!=0)
		horlin++;
	else
	if (instead[i]!=0)
		continue;
	else
		texlin++;
	}
fprintf(tabout, ".ne %dv+%dp\n",texlin,2*horlin);
}
deftail()
{
int i, c, lf, lwid;
for(i=0; i<MAXHEAD; i++)
	if (linestop[i])
		fprintf(tabout, ".nr #%c 0-1\n", linestop[i]+'a'-1);
fprintf(tabout, ".nr #a 0-1\n");
fprintf(tabout, ".eo\n");
fprintf(tabout, ".de T#\n");
fprintf(tabout, ".ds #d .d\n");
fprintf(tabout, ".if \\(ts\\n(.z\\(ts\\(ts .ds #d nl\n");
	fprintf(tabout, ".mk ##\n");
	fprintf(tabout, ".nr ## -1v\n");
	fprintf(tabout, ".ls 1\n");
	for(i=0; i<MAXHEAD; i++)
		if (linestop[i])
			fprintf(tabout, ".if \\n(#T>=0 .nr #%c \\n(#T\n",linestop[i]+'a'-1);
if (boxflg || allflg || dboxflg) /* bottom of table line */
	if (fullbot[nlin-1]==0)
		{
		fprintf(tabout, ".if \\n(T. .vs2p\n");
		fprintf(tabout, ".if \\n(T. ");
		drawline(nlin-1,0,ncol, dboxflg ? '=' : '-',1);
		fprintf(tabout, "\n.if \\n(T. .vs\n");
		/* T. is really an argument to a macro but because of 
		   eqn we don't dare pass it as an argument and reference by $1 */
		}
	for(c=0; c<ncol; c++)
		{
		if ((lf=left(nlin-1,c, &lwid))>=0)
			{
			fprintf(tabout, ".if \\n(#%c>=0 .sp -1\n",linestop[lf]+'a'-1);
			fprintf(tabout, ".if \\n(#%c>=0 ", linestop[lf]+'a'-1);
			tohcol(c);
			drawvert(lf, nlin-1, c, lwid);
			fprintf(tabout, "\\h'|\\n(TWu'\n");
			}
		}
	if (boxflg || allflg || dboxflg) /* right hand line */
		{
		fprintf(tabout, ".if \\n(#a>=0 .sp -1\n");
		fprintf(tabout, ".if \\n(#a>=0 \\h'|\\n(TWu'");
		drawvert (0, nlin-1, ncol, dboxflg? 2 : 1);
		fprintf(tabout, "\n");
		}
fprintf(tabout, ".ls\n");
fprintf(tabout, "..\n");
fprintf(tabout, ".ec\n");
} 