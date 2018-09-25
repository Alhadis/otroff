 /* te.c: error message control, input line count */
# include "t..c"
error(s)
	char *s;
{
fprintf(stderr, "\n%s: line %d: %s\n", ifile, iline, s);
# ifdef unix
fprintf(stderr, "tbl quits\n");
exit(1);
# endif
# ifdef gcos
fprintf(stderr, "run terminated due to error condition detected by tbl preprocessor\n");
exit(0);
# endif
}
gets1(s)
	char *s;
{
char *p;
iline++;
p=fgets(s,512,tabin);
if (p==0)
	{
	if (swapin()==0 || (p=fgets(s,512,tabin))==0)
		return(0);
	}
	while (*s) s++;
	s--;
	if (*s == '\n') *s-- =0;
	if (*s == '\\')
		gets1(s);
return(p);
}
# define BACKMAX 500
char backup[BACKMAX];
char *backp backup;
un1getc(c)
{
if (c=='\n')
	iline--;
*backp++ = c;
if (backp >= backup+BACKMAX)
	error("too much backup");
}
get1char()
{
int c;
if (backp>backup)
	c = *--backp;
else
	c=getc(tabin);
if (c== EOF) /* EOF */
	{
	if (swapin() ==0)
		error("unexpected EOF",0);
	c = getc(tabin);
	}
if (c== '\n')
	iline++;
return(c);
}
