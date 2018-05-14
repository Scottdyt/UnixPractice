#include <stdio.h>
#include <stdlib.h>
#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *);
int see_more(FILE *);

int main(int argc, char *argv[])
{
    FILE *fp;
    if (argc == 1)
    {
        do_more(stdin);
    }
    else
    {
        while (--argc) /* how many file to read */
        {
            if ((fp = fopen(*(++argv), "r")) != NULL)
            {
                do_more(fp);
                fclose(fp);
            }
            else
                exit(1);
        }
    }
}

void do_more(FILE *fp)
/*
 * read PAGELINE lines, the call see_more() for futher instructions
 */
{
    char line[LINELEN];
    int num_of_line = 0;
    int reply;
    FILE *fp_tty; /* read from /dev/tty */
    fp_tty = fopen("/dev/tty", "r");
    if (fp_tty == NULL) /* if open fails */
        exit(1);
    while (fgets(line, LINELEN, fp))
    {
        if (num_of_line == PAGELEN) /* full screen? */
        {
            reply = see_more(fp_tty);
            if (reply == 0) /* done */
                break;
            num_of_line -= reply; /* reset count */
        }
        if (fputs(line, stdout) == EOF)
            exit(1);
        num_of_line++; /* count it  */
    }
}

int see_more(FILE *cmd)
/*
 * print message, wait for response, return # of lines to advance
 * q means no, space means yes, CR means one line
 */
{
    int c;
    printf("\033[7m more?\033[m"); /* reverse color */
    while ((c = getc(cmd)) != EOF)
    {
        if (c == 'q')
            return 0;
        if (c == ' ')
            return PAGELEN;
        if (c == '\n')
            return 1;
    }
    return 0;
}