/* Screen editor:  prompt line module
 *
 * Source:  ed7.c
 * Version: May 15, 1981.
 */

/* define globals */

//#include ed1.h

/* globals used by this module -----

char pmtln[MAXLEN];		mode
char pmtfn[SYSFNMAX];		file name

----- */

/* put error message on prompt line.
 * wait for response.
 */

pmtmess(s1,s2) char *s1, *s2;
{
int x,y;
	/* save cursor */
	x=outgetx();
	y=outgety();
	outxy(0,0);
	/* make sure line is correct */
	outdelln();
	pmtlin1();
	pmtcol1(x);
	/* output error message */
	fmtsout(s1,outgetx());
	fmtsout(s2,outgetx());
	/* wait for input from console */
	syscin();
	/* redraw prompt line */
	pmtlin1();
	pmtcol1(x);
	pmtfil1(pmtfn);
	pmtmod1(pmtln);
	pmtbufsz1();
	/* restore cursor */
	outxy(x,y);
}

/* write new mode message on prompt line */

pmtmode(s) char *s;
{
int x,y;		/* save cursor on entry */
	/* save cursor */
	x=outgetx();
	y=outgety();
	/* redraw whole line */
	outxy(0,0);
	outdelln();
	pmtlin1();
	pmtcol1(x);
	pmtfil1(pmtfn);
	pmtmod1(s);
	pmtbufsz1();
	/* restore cursor */
	outxy(x,y);
}

/* update file name on prompt line */

pmtfile(s) char *s;
{
int x, y;
	/* save cursor */
	x=outgetx();
	y=outgety();
	/* update whole line */
	outxy(0,0);
	outdelln();
	pmtlin1();
	pmtcol1();
	pmtfil1(s);
	pmtmod1(pmtln);
	pmtbufsz1();
	/* restore cursor */
	outxy(x,y);
}

/* change mode on prompt line to edit: */

pmtedit()
{
	pmtmode("edit:");
}

/* update line and column numbers on prompt line */

pmtline()
{
int x,y;
	/* save cursor */
	x=outgetx();
	y=outgety();
	/* redraw whole line */
	outxy(0,0);
	outdelln();
	pmtlin1();
	pmtcol1(x);
	pmtfil1(pmtfn);
	pmtmod1(pmtln);
	pmtbufsz1();
	/* restore cursor */
	outxy(x,y);
}

/* update just the column number on prompt line */

pmtcol()
{
int x,y;
	/* save cursor */
	x=outgetx();
	y=outgety();
	/* update column number */
	pmtcol1(x);
	/* update cursor */
	outxy(x,y);
}

/* update mode.  call getcmnd() to write on prompt line */

pmtcmnd(mode,buffer) char *mode, *buffer;
{
int x,y;
	/* save cursor */
	x=outgetx();
	y=outgety();
	pmtmod1(mode);
	/* user types command on prompt line */
	getcmnd(buffer,outgetx());
	/* restore cursor */
}


/* update and print remaining buffer size information */
pmtbufsz1()
{
	outxy(68,0);
	fmtsout("buffer:",68);
	putdec((bufend-bufpmax), 5);
}




/* update and print mode */

pmtmod1(s) char *s;
{
int i;
	outxy(40,0);
	fmtsout(s,40);
	i=0;
	while (pmtln[i++]= *s++) {
		;
	}
}

/* print the file name on the prompt line */

pmtfil1(s) char *s;
{
int i;
	outxy(25,0);
	if (*s==EOS) {
		fmtsout("no file",25);
	}
	else {
		fmtsout(s,25);
	}
	i=0;
	while (pmtfn[i++]= *s++) {
		;
	}
}

/* print the line number on the prompt line */

pmtlin1()
{
	outxy(0,0);
	fmtsout("line: ",0);
	putdec(bufline,5);
}


/* print column number of the cursor */

pmtcol1(x) int x;
{
	outxy(12,0);
	fmtsout("column: ",12);
	putdec(x,3);
}

