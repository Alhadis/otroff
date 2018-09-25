 /* tu.c: draws horizontal lines */
# include "t..c"
makeline(i,c,lintype)
{
int cr, type;
type = thish(i,c);
if (type==0) return;
if (c>0 && thish(i,c-1) == type)return;
for(cr=c; cr < ncol && (ctype(i,cr)=='s'||type==thish(i,cr)); cr++);
drawline(i, c, cr-1, lintype,0);
}
fullwide(i, lintype)
{
int cr, cl;
fprintf(tabout, ".vs 2p\n");
cr= 0;
while (cr<ncol)
	{
	cl=cr;
	while (i>0 && vspand(i-1,cl))
		cl++;
	for(cr=cl; cr<ncol; cr++)
		if (i>0 && vspand(i-1,cr))
			break;
	if (cl<ncol)
	drawline(i,cl,cr,lintype,1);
	}
fprintf(tabout, "\n.vs\n");
}

drawline(i, cl, cr, lintype, noheight)
{
	char *exhr, *exhl;
	int lcount, ln, linpos, oldpos, nodata;
lcount=0;
exhr=exhl= "";
switch(lintype)
	{
	case '-': lcount=1;break;
	case '=': lcount=2;break;
	}
if (lcount<=0) return;
nodata = cr-cl>=ncol || noheight || allh(i);
	if (!nodata)
		fprintf(tabout, "\\v'-.5m'");
for(ln=oldpos=0; ln<lcount; ln++)
	{
	linpos = 2*ln - lcount +1;
	if (linpos != oldpos)
		fprintf(tabout, "\\v'%dp'", linpos-oldpos);
	oldpos=linpos;
	tohcol(cl);
	if (lcount>1)
		{
		switch(interv(i,cl))
			{
			case TOP: exhl = ln==0 ? "1p" : "-1p"; break;
			case BOT: exhl = ln==1 ? "1p" : "-1p"; break;
			case THRU: exhl = "-1p"; break;
			}
		if (exhl[0])
		fprintf(tabout, "\\h'%s'", exhl);
		}
	else if (lcount==1)
		{
		switch(interv(i,cl))
			{
			case TOP: case BOT: exhl = "-1p"; break;
			case THRU: exhl = "1p"; break;
			}
		if (exhl[0])
		fprintf(tabout, "\\h'%s'", exhl);
		}
	if (lcount>1)
		{
		switch(interv(i,cr+1))
			{
			case TOP: exhr = ln==0 ? "-1p" : "+1p"; break;
			case BOT: exhr = ln==1 ? "-1p" : "+1p"; break;
			case THRU: exhr = "-1p"; break;
			}
		}
	else if (lcount==1)
		{
		switch(interv(i,cr+1))
			{
			case TOP: case BOT: exhr = "+1p"; break;
			case THRU: exhr = "-1p"; break;
			}
		}
	fprintf(tabout, "\\s\\n(%d",LSIZE);
	if (cr+1>=ncol)
		fprintf(tabout, "\\l'|\\n(TWu%s\\(ul'", exhr);
	else
		fprintf(tabout, "\\l'(|\\n(%du+|\\n(%du)/2u%s\\(ul'", cr+CRIGHT, cr+1+CLEFT, exhr);
	fprintf(tabout, "\\s0");
	}
if (oldpos!=0)
	fprintf(tabout, "\\v'%dp'", -oldpos);
if (!nodata)
	fprintf(tabout, "\\v'+.5m'");
}
getstop()
{
int i,c,k,junk, stopp;
stopp=1;
for(i=0; i<MAXLIN; i++)
	linestop[i]=0;
for(i=0; i<nlin; i++)
	for(c=0; c<ncol; c++)
		{
		k = left(i,c,&junk);
		if (k>=0 && linestop[k]==0)
			linestop[k]= ++stopp;
		}
if (boxflg || allflg || dboxflg)
	linestop[0]=1;
}
left(i,c, lwidp)
	int *lwidp;
{
int kind, li;
	/* returns -1 if no line to left */
	/* returns number of line where it starts */
	/* stores into lwid the kind of line */
*lwidp=0;
kind = lefdata(i,c);
if (kind==0) return(-1);
if (i+1<nlin)
if (lefdata(next(i),c)== kind) return(-1);
while (i>=0 && lefdata(i,c)==kind)
	i=prev(li=i);
if (prev(li)== -1) li=0;
*lwidp=kind;
return(li);
}
lefdata(i,c)
{
int ck;
if (i>=nlin) i=nlin-1;
if (ctype(i,c) == 's')
	{
	for(ck=c; ctype(i,ck)=='s'; ck--);
	if (thish(i,ck)==0)
		return(0);
	}
i =stynum[i];
i = lefline[i][c];
if (i>0) return(i);
if (dboxflg && c==0) return(2);
if (allflg)return(1);
if (boxflg && c==0) return(1);
return(0);
}
next(i)
{
while (i+1 <nlin)
	{
	i++;
	if (!fullbot[i] && !instead[i]) break;
	}
return(i);
}
prev(i)
{
while (--i >=0  && (fullbot[i] || instead[i]))
	;
return(i);
}
