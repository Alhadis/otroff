# define CONTIG 257
# define QTEXT 258
# define SPACE 259
# define THIN 260
# define TAB 261
# define MATRIX 262
# define LCOL 263
# define CCOL 264
# define RCOL 265
# define COL 266
# define ABOVE 267
# define MARK 268
# define LINEUP 269
# define SUM 270
# define INT 271
# define PROD 272
# define UNION 273
# define INTER 274
# define DEFINE 275
# define TDEFINE 276
# define NDEFINE 277
# define DELIM 278
# define GSIZE 279
# define GFONT 280
# define INCLUDE 281
# define IFDEF 282
# define DOTEQ 283
# define DOTEN 284
# define FROM 285
# define TO 286
# define OVER 287
# define SQRT 288
# define SUP 289
# define SUB 290
# define SIZE 291
# define FONT 292
# define ROMAN 293
# define ITALIC 294
# define BOLD 295
# define FAT 296
# define UP 297
# define DOWN 298
# define BACK 299
# define FWD 300
# define LEFT 301
# define RIGHT 302
# define DOT 303
# define DOTDOT 304
# define HAT 305
# define TILDE 306
# define BAR 307
# define LOWBAR 308
# define HIGHBAR 309
# define UNDER 310
# define VEC 311
# define DYAD 312
# define UTILDE 313

# line 17 "eqn.y"
#include "e.h"
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern short yyerrflag;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
#ifndef YYSTYPE
#define YYSTYPE int
#endif
YYSTYPE yylval, yyval;
# define YYERRCODE 256

# line 138 "eqn.y"

short yyexca[] ={
-1, 0,
	0, 3,
	-2, 0,
-1, 1,
	0, -1,
	-2, 0,
	};
# define YYNPROD 90
# define YYLAST 527
short yyact[]={

   6,  51,  52,  48, 118,  50,  49,  72,  71, 102,
 130, 103,  51, 122,  48, 124,  50,  49, 116,  61,
  64,  54,  62,  57,  58,  59,  60,  55,  56,  63,
  61,  64,  54,  62,  57,  58,  59,  60,  55,  56,
  63,  50,  49,  80,  81, 105,   6, 119,  97,  40,
 114,  78, 120,  49,  26,  61,  64,  54,  62,  57,
  58,  59,  60,  55,  56,  63,  61,  64,  54,  62,
  57,  58,  59,  60,  55,  56,  63,  61,  64,  54,
  62,  57,  58,  59,  60,  55,  56,  63,  41,  42,
  43,  44,   6,  25, 104,   2,  24,  23,  27,  53,
 100,  65,  22,  96,  95,  99,  98,  21,  94,  93,
  18,  17, 113,  89, 121,  84,  46,  73,   1,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
 127,   0,   0,   0,   8,   7,   9,  10,  11,  28,
  41,  42,  43,  44,   6,  16,  47,  12,  34,  13,
  14,  15, 117,  41,  42,  43,  44,   0, 123,   0,
 117,   0,   0,   0,   0,  20,   0,   0,  29,  33,
  30,  31,  32,  19,  37,  39,  38,  36,  35, 101,
   8,   7,   9,  10,  11,  28,  41,  42,  43,  44,
   6,  16,  47,  12,  34,  13,  14,  15,   0,   0,
   0, 115,   0,   0,   0,   0,   0,   0,   0,   0,
   0,  20, 126, 125,  29,  33,  30,  31,  32,  19,
  37,  39,  38,  36,  35,   3,   8,   7,   9,  10,
  11,  28,  41,  42,  43,  44,   6,  16,   5,  12,
  34,  13,  14,  15,  80,  81,   0,  80,  81,  80,
  81,   0,   0,   0,   0,   0,   0,  20,   0,   0,
  29,  33,  30,  31,  32,  19,  37,  39,  38,  36,
  35,   0,   0,   0,   0,   0,   0,   0,   8,   7,
   9,  10,  11,  28,  41,  42,  43,  44,   0,  16,
  47,  12,  34,  13,  14,  15,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,  20,
   0,   0,  29,  33,  30,  31,  32,  19,  37,  39,
  38,  36,  35,   0,   8,   7,   9,  10,  11,  28,
  41,  42,  43,  44,   0,  16,   5,  12,  34,  13,
  14,  15,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,  79,  20,   0,   0,  29,  33,
  30,  31,  32,  19,  37,  39,  38,  36,  35,   0,
   8,   7,   9,  10,  11,  28,  41,  42,  43,  44,
   0,  16,   0,  12,  34,  13,  14,  15,  82,   0,
  83,  85,  86,  87,  88,  90,   0,   0,   0,   4,
   0,  20,  45,   0,  29,  33,  30,  31,  32,  19,
  37,  39,  38,  36,  35,   0,  66,  67,  68,  69,
  70,   0,   0,  74,  75,  76,  77,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,  91,  92,   0,
   0,   0,   0,   0,   0,   0, 112,   0,   0,   0,
   0,   0,   0,   0,   0,  45,   0,   0,   0,   0,
   0,   0,   0,  45,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0, 106, 107, 108, 109,   0, 110, 111,
   0,   0,   0,   0,  45,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
 128,   0, 129,   0,   0,   0,  45 };
short yypact[]={

 -31,-1000,  21,-1000,-284,-1000,  67,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000, 113, 113, 113, 113,
 113,-282,  67, 113, 113, 113, 113,-1000,-1000,-214,
-1000,-1000,-1000,-214,-1000,  -8,-214,-214,-214,-214,
 -10,-1000,-1000,-1000,-1000,-284,-1000, 113, 113,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000, -77,-284,-226,-226,-226,
-248,-1000,-1000,-123,-226,-226,-226,-226,-114,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,  67,
-1000,-284,-248, 113, 113, 113, 113,-1000, 113, 113,
-1000, -13,-175,-107,  21,-119,-237,-248,-273,-284,
-237,-248,-1000,-1000,-110,-1000,-1000,  67,  67,-1000,
 113,-1000, 113,-1000,-1000,-1000,  21,-115,-248,-284,
-1000 };
short yypgo[]={

   0, 118,  94, 399, 116,  47, 114, 111, 110, 109,
 108, 107, 106, 105, 104, 103, 102, 100,  99,  97,
  96,  93,  54,  98,  51,  50, 354,  49,  11,  45 };
short yyr1[]={

   0,   1,   1,   1,   2,   2,   2,   2,   4,   5,
   5,   6,   6,   3,   3,   3,   3,   3,   3,   3,
   3,   3,   3,   3,   3,   3,   3,   3,   3,   9,
   3,  10,   3,  12,   3,  13,   3,   3,  14,   3,
  15,   3,   3,   3,   3,   3,   3,   3,   3,   3,
  24,   3,  11,  19,  20,  21,  22,  18,  18,  18,
  18,  18,  18,  18,  18,  18,  18,  18,  16,  16,
  17,  17,  25,  25,  23,  29,  23,  27,  27,  27,
  27,  28,  28,   7,   8,   8,   8,   8,  26,  26 };
short yyr2[]={

   0,   1,   1,   0,   1,   2,   2,   1,   2,   2,
   0,   2,   0,   3,   1,   1,   1,   1,   1,   1,
   1,   1,   1,   3,   2,   2,   2,   2,   2,   0,
   5,   0,   4,   0,   5,   0,   4,   1,   0,   5,
   0,   4,   3,   2,   2,   2,   2,   2,   2,   1,
   0,   5,   1,   2,   2,   2,   2,   1,   1,   1,
   1,   1,   1,   1,   1,   1,   1,   1,   2,   2,
   2,   2,   1,   2,   4,   0,   6,   1,   1,   1,
   1,   1,   3,   2,   1,   1,   1,   2,   1,   1 };
short yychk[]={

-1000,  -1,  -2, 256,  -3, 269, 123, 258, 257, 259,
 260, 261, 270, 272, 273, 274, 268,  -7,  -8, 296,
 288, -11, -16, -19, -20, -21, -22, -23, 262, 291,
 293, 294, 295, 292, 271, 301, 300, 297, 299, 298,
 -27, 263, 264, 265, 266,  -3,  -4, 269, 287, 290,
 289, 285, 286, -18, 305, 311, 312, 307, 308, 309,
 310, 303, 306, 313, 304,  -2,  -3,  -3,  -3,  -3,
  -3, 290, 289,  -2,  -3,  -3,  -3,  -3, -24, -26,
 257, 258, -26, -26, 123, -26, -26, -26, -26, 123,
 -26,  -3,  -3,  -9, -10, -14, -15, 125, -12, -13,
 -17, 302, 123, -28,  -2, -29,  -3,  -3,  -3,  -3,
  -3,  -3, -26, 125, -25, -23, 125, 267, 123,  -5,
 289,  -6, 286,  -5, 125, -23,  -2, -28,  -3,  -3,
 125 };
short yydef[]={

  -2,  -2,   1,   2,   4,   7,   0,  14,  15,  16,
  17,  18,  19,  20,  21,  22,   0,   0,   0,   0,
   0,  37,   0,   0,   0,   0,   0,  49,  50,   0,
  84,  85,  86,   0,  52,   0,   0,   0,   0,   0,
   0,  77,  78,  79,  80,   5,   6,   0,   0,  29,
  31,  38,  40,  44,  57,  58,  59,  60,  61,  62,
  63,  64,  65,  66,  67,   0,  24,  25,  26,  27,
  28,  33,  35,  43,  45,  46,  47,  48,   0,  83,
  88,  89,  87,  68,  69,  53,  54,  55,  56,   0,
  75,   8,  23,   0,   0,   0,   0,  13,   0,   0,
  42,   0,   0,   0,  81,   0,  10,  32,  12,  41,
  10,  36,  70,  71,   0,  72,  74,   0,   0,  30,
   0,  39,   0,  34,  51,  73,  82,   0,   9,  11,
  76 };
# ifdef YYDEBUG
# include "y.debug"
# endif

# define YYFLAG -1000
# define YYERROR goto yyerrlab
# define YYACCEPT return(0)
# define YYABORT return(1)

/*	parser for yacc output	*/

#ifdef YYDEBUG
int yydebug = 0; /* 1 for debugging */
#endif
YYSTYPE yyv[YYMAXDEPTH]; /* where the values are stored */
int yychar = -1; /* current input token number */
int yynerrs = 0;  /* number of errors */
short yyerrflag = 0;  /* error recovery flag */

yyparse()
{	short yys[YYMAXDEPTH];
	int yyj, yym;
	register YYSTYPE *yypvt;
	register int yystate, yyn;
	register short *yyps;
	register YYSTYPE *yypv;
	register short *yyxi;

	yystate = 0;
	yychar = -1;
	yynerrs = 0;
	yyerrflag = 0;
	yyps= &yys[-1];
	yypv= &yyv[-1];

yystack:    /* put a state and value onto the stack */
#ifdef YYDEBUG
	if(yydebug >= 3)
		if(yychar < 0 || yytoknames[yychar] == 0)
			printf("char %d in %s", yychar, yystates[yystate]);
		else
			printf("%s in %s", yytoknames[yychar], yystates[yystate]);
#endif
	if( ++yyps >= &yys[YYMAXDEPTH] ) { 
		yyerror( "yacc stack overflow" ); 
		return(1); 
	}
	*yyps = yystate;
	++yypv;
	*yypv = yyval;
yynewstate:
	yyn = yypact[yystate];
	if(yyn <= YYFLAG) goto yydefault; /* simple state */
	if(yychar<0) {
		yychar = yylex();
#ifdef YYDEBUG
		if(yydebug >= 2) {
			if(yychar <= 0)
				printf("lex EOF\n");
			else if(yytoknames[yychar])
				printf("lex %s\n", yytoknames[yychar]);
			else
				printf("lex (%c)\n", yychar);
		}
#endif
		if(yychar < 0)
			yychar = 0;
	}
	if((yyn += yychar) < 0 || yyn >= YYLAST)
		goto yydefault;
	if( yychk[ yyn=yyact[ yyn ] ] == yychar ){ /* valid shift */
		yychar = -1;
		yyval = yylval;
		yystate = yyn;
		if( yyerrflag > 0 ) --yyerrflag;
		goto yystack;
	}
yydefault:
	/* default state action */
	if( (yyn=yydef[yystate]) == -2 ) {
		if(yychar < 0) {
			yychar = yylex();
#ifdef YYDEBUG
			if(yydebug >= 2)
				if(yychar < 0)
					printf("lex EOF\n");
				else
					printf("lex %s\n", yytoknames[yychar]);
#endif
			if(yychar < 0)
				yychar = 0;
		}
		/* look through exception table */
		for(yyxi=yyexca; (*yyxi!= (-1)) || (yyxi[1]!=yystate);
			yyxi += 2 ) ; /* VOID */
		while( *(yyxi+=2) >= 0 ){
			if( *yyxi == yychar ) break;
		}
		if( (yyn = yyxi[1]) < 0 ) return(0);   /* accept */
	}
	if( yyn == 0 ){ /* error */
		/* error ... attempt to resume parsing */
		switch( yyerrflag ){
		case 0:   /* brand new error */
#ifdef YYDEBUG
			yyerror("syntax error\n%s", yystates[yystate]);
			if(yytoknames[yychar])
				yyerror("saw %s\n", yytoknames[yychar]);
			else if(yychar >= ' ' && yychar < '\177')
				yyerror("saw `%c'\n", yychar);
			else if(yychar == 0)
				yyerror("saw EOF\n");
			else
				yyerror("saw char 0%o\n", yychar);
#else
			yyerror( "syntax error" );
#endif
yyerrlab:
			++yynerrs;
		case 1:
		case 2: /* incompletely recovered error ... try again */
			yyerrflag = 3;
			/* find a state where "error" is a legal shift action */
			while ( yyps >= yys ) {
				yyn = yypact[*yyps] + YYERRCODE;
				if( yyn>= 0 && yyn < YYLAST && yychk[yyact[yyn]] == YYERRCODE ){
					yystate = yyact[yyn];  /* simulate a shift of "error" */
					goto yystack;
				}
				yyn = yypact[*yyps];
				/* the current yyps has no shift onn "error", pop stack */
#ifdef YYDEBUG
				if( yydebug ) printf( "error recovery pops state %d, uncovers %d\n", *yyps, yyps[-1] );
#endif
				--yyps;
				--yypv;
			}
			/* there is no state on the stack with an error shift ... abort */
yyabort:
			return(1);
		case 3:  /* no shift yet; clobber input char */
#ifdef YYDEBUG
			if( yydebug ) {
				printf("error recovery discards ");
				if(yytoknames[yychar])
					printf("%s\n", yytoknames[yychar]);
				else if(yychar >= ' ' && yychar < '\177')
					printf("`%c'\n", yychar);
				else if(yychar == 0)
					printf("EOF\n");
				else
					printf("char 0%o\n", yychar);
			}
#endif
			if( yychar == 0 ) goto yyabort; /* don't discard EOF, quit */
			yychar = -1;
			goto yynewstate;   /* try again in the same state */
		}
	}
	/* reduction by production yyn */
#ifdef YYDEBUG
	if(yydebug) {	char *s;
		printf("reduce %d in:\n\t", yyn);
		for(s = yystates[yystate]; *s; s++) {
			putchar(*s);
			if(*s == '\n' && *(s+1))
				putchar('\t');
		}
	}
#endif
	yyps -= yyr2[yyn];
	yypvt = yypv;
	yypv -= yyr2[yyn];
	yyval = yypv[1];
	yym=yyn;
	/* consult goto table to find next state */
	yyn = yyr1[yyn];
	yyj = yypgo[yyn] + *yyps + 1;
	if( yyj>=YYLAST || yychk[ yystate = yyact[yyj] ] != -yyn ) yystate = yyact[yypgo[yyn]];
	switch(yym){
		
case 1:
# line 22 "eqn.y"
{ putout(yypvt[-0]); } break;
case 2:
# line 23 "eqn.y"
{ error(!FATAL, "syntax error"); } break;
case 3:
# line 24 "eqn.y"
{ eqnreg = 0; } break;
case 5:
# line 28 "eqn.y"
{ eqnbox(yypvt[-1], yypvt[-0], 0); } break;
case 6:
# line 29 "eqn.y"
{ eqnbox(yypvt[-1], yypvt[-0], 1); } break;
case 7:
# line 30 "eqn.y"
{ lineup(0); } break;
case 8:
# line 33 "eqn.y"
{ yyval = yypvt[-0]; lineup(1); } break;
case 9:
# line 36 "eqn.y"
{ yyval = yypvt[-0]; } break;
case 10:
# line 37 "eqn.y"
{ yyval = 0; } break;
case 11:
# line 40 "eqn.y"
{ yyval = yypvt[-0]; } break;
case 12:
# line 41 "eqn.y"
{ yyval = 0; } break;
case 13:
# line 44 "eqn.y"
{ yyval = yypvt[-1]; } break;
case 14:
# line 45 "eqn.y"
{ text(QTEXT, (char *) yypvt[-0]); } break;
case 15:
# line 46 "eqn.y"
{ text(CONTIG, (char *) yypvt[-0]); } break;
case 16:
# line 47 "eqn.y"
{ text(SPACE, 0); } break;
case 17:
# line 48 "eqn.y"
{ text(THIN, 0); } break;
case 18:
# line 49 "eqn.y"
{ text(TAB, 0); } break;
case 19:
# line 50 "eqn.y"
{ funny(SUM); } break;
case 20:
# line 51 "eqn.y"
{ funny(PROD); } break;
case 21:
# line 52 "eqn.y"
{ funny(UNION); } break;
case 22:
# line 53 "eqn.y"
{ funny(INTER); } break;
case 23:
# line 54 "eqn.y"
{ boverb(yypvt[-2], yypvt[-0]); } break;
case 24:
# line 55 "eqn.y"
{ mark(yypvt[-0]); } break;
case 25:
# line 56 "eqn.y"
{ size(yypvt[-1], yypvt[-0]); } break;
case 26:
# line 57 "eqn.y"
{ font(yypvt[-1], yypvt[-0]); } break;
case 27:
# line 58 "eqn.y"
{ fatbox(yypvt[-0]); } break;
case 28:
# line 59 "eqn.y"
{ sqrt(yypvt[-0]); } break;
case 29:
# line 60 "eqn.y"
{ps -= deltaps;} break;
case 30:
# line 60 "eqn.y"
{ subsup(yypvt[-4], yypvt[-1], yypvt[-0]); } break;
case 31:
# line 61 "eqn.y"
{ps -= deltaps;} break;
case 32:
# line 61 "eqn.y"
{ subsup(yypvt[-3], 0, yypvt[-0]); } break;
case 33:
# line 62 "eqn.y"
{ps -= deltaps;} break;
case 34:
# line 62 "eqn.y"
{ integral(yypvt[-4], yypvt[-1], yypvt[-0]); } break;
case 35:
# line 63 "eqn.y"
{ps -= deltaps;} break;
case 36:
# line 63 "eqn.y"
{ integral(yypvt[-3], 0, yypvt[-0]); } break;
case 37:
# line 64 "eqn.y"
{ integral(yypvt[-0], 0, 0); } break;
case 38:
# line 65 "eqn.y"
{ps -= deltaps;} break;
case 39:
# line 65 "eqn.y"
{ fromto(yypvt[-4], yypvt[-1], yypvt[-0]); } break;
case 40:
# line 66 "eqn.y"
{ps -= deltaps;} break;
case 41:
# line 66 "eqn.y"
{ fromto(yypvt[-3], 0, yypvt[-0]); } break;
case 42:
# line 67 "eqn.y"
{ paren(yypvt[-2], yypvt[-1], yypvt[-0]); } break;
case 43:
# line 68 "eqn.y"
{ paren(yypvt[-1], yypvt[-0], 0); } break;
case 44:
# line 69 "eqn.y"
{ diacrit(yypvt[-1], yypvt[-0]); } break;
case 45:
# line 70 "eqn.y"
{ move(FWD, yypvt[-1], yypvt[-0]); } break;
case 46:
# line 71 "eqn.y"
{ move(UP, yypvt[-1], yypvt[-0]); } break;
case 47:
# line 72 "eqn.y"
{ move(BACK, yypvt[-1], yypvt[-0]); } break;
case 48:
# line 73 "eqn.y"
{ move(DOWN, yypvt[-1], yypvt[-0]); } break;
case 49:
# line 74 "eqn.y"
{ pile(yypvt[-0]); ct = yypvt[-0]; } break;
case 50:
# line 75 "eqn.y"
{yyval=ct;} break;
case 51:
# line 75 "eqn.y"
{ matrix(yypvt[-3]); ct = yypvt[-3]; } break;
case 52:
# line 78 "eqn.y"
{ setintegral(); } break;
case 53:
# line 81 "eqn.y"
{ yyval = atoi((char *) yypvt[-1]); } break;
case 54:
# line 82 "eqn.y"
{ yyval = atoi((char *) yypvt[-1]); } break;
case 55:
# line 83 "eqn.y"
{ yyval = atoi((char *) yypvt[-1]); } break;
case 56:
# line 84 "eqn.y"
{ yyval = atoi((char *) yypvt[-1]); } break;
case 57:
# line 86 "eqn.y"
{ yyval = HAT; } break;
case 58:
# line 87 "eqn.y"
{ yyval = VEC; } break;
case 59:
# line 88 "eqn.y"
{ yyval = DYAD; } break;
case 60:
# line 89 "eqn.y"
{ yyval = BAR; } break;
case 61:
# line 90 "eqn.y"
{ yyval = LOWBAR; } break;
case 62:
# line 91 "eqn.y"
{ yyval = HIGHBAR; } break;
case 63:
# line 92 "eqn.y"
{ yyval = UNDER; } break;
case 64:
# line 93 "eqn.y"
{ yyval = DOT; } break;
case 65:
# line 94 "eqn.y"
{ yyval = TILDE; } break;
case 66:
# line 95 "eqn.y"
{ yyval = UTILDE; } break;
case 67:
# line 96 "eqn.y"
{ yyval = DOTDOT; } break;
case 68:
# line 99 "eqn.y"
{ yyval = ((char *)yypvt[-0])[0]; } break;
case 69:
# line 100 "eqn.y"
{ yyval = '{'; } break;
case 70:
# line 103 "eqn.y"
{ yyval = ((char *)yypvt[-0])[0]; } break;
case 71:
# line 104 "eqn.y"
{ yyval = '}'; } break;
case 74:
# line 111 "eqn.y"
{ column(yypvt[-3], DEFGAP); } break;
case 75:
# line 112 "eqn.y"
{yyval=atoi((char*)yypvt[-0]);} break;
case 76:
# line 112 "eqn.y"
{ column(yypvt[-5], yypvt[-3]); } break;
case 77:
# line 115 "eqn.y"
{ yyval = startcol(LCOL); } break;
case 78:
# line 116 "eqn.y"
{ yyval = startcol(CCOL); } break;
case 79:
# line 117 "eqn.y"
{ yyval = startcol(RCOL); } break;
case 80:
# line 118 "eqn.y"
{ yyval = startcol(COL); } break;
case 81:
# line 121 "eqn.y"
{ lp[ct++] = yypvt[-0]; } break;
case 82:
# line 122 "eqn.y"
{ lp[ct++] = yypvt[-0]; } break;
case 83:
# line 125 "eqn.y"
{ yyval = ps; setsize((char *) yypvt[-0]); } break;
case 84:
# line 128 "eqn.y"
{ setfont("R"); } break;
case 85:
# line 129 "eqn.y"
{ setfont("I"); } break;
case 86:
# line 130 "eqn.y"
{ setfont("B"); } break;
case 87:
# line 131 "eqn.y"
{ setfont((char *)yypvt[-0]); } break;
	}
	goto yystack;  /* stack new state and value */
}
