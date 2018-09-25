 /* t1.c: main control and input switching */
#
# include "t..c"
# define BROKPIPE 13

# if unix
# define MACROS "/usr/lib/tmac.s"
# endif

# if gcos
# define MACROS "cc/troff/smac"
# endif

# define ever (;;)

main(argc,argv)
	char *argv[];
{
# if gcos
if(!intss()) tabout = fopen("qq", "w"); /* default media code is type 5 */
#endif
# if unix
int badsig();
signal(BROKPIPE, badsig);
# endif
exit(tbl(argc,argv));
}


tbl(argc,argv)
	char *argv[];
{
char line[512];
setinp(argc,argv);
while (gets1(line))
	{
	fprintf(tabout, "%s\n",line);
	if (prefix(".TS", line))
		tableput();
	}
fclose(tabin);
return(0);
}
int sargc;
char **sargv;
setinp(argc,argv)
	char **argv;
{
	sargc = argc;
	sargv = argv;
	sargc--; sargv++;
	if (sargc>0)
		swapin();
}
swapin()
{
	if (sargc<=0) return(0);
	if (match("-ms", *sargv))
		*sargv = MACROS;
	if (tabin!=stdin) fclose(tabin);
	tabin = fopen(ifile= *sargv, "r");
	iline=1;
	fprintf(tabout, ".ds f. %s\n",ifile);
	if (tabin==NULL)
		error("Can't open file");
	sargc--;
	sargv++;
	return(1);
}
# if unix
badsig()
{
signal(BROKPIPE, 1);
 exit(0);
}
# endif
