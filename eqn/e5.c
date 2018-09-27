#include "e.h"

mark(p1) int p1; {
	printf(".ds %d \\k(97\\*(%d\n", p1, p1);
	yyval = p1;
	if(dbg)printf(".\tmark %d\n", p1);
}

lineup(p1, p2) {
	yyval = oalloc();
	printf(".ds %d \\h'|\\n(97u'\n", yyval);
	if(dbg)printf(".\tlineup %d and %d\n", p1, p2);
}
