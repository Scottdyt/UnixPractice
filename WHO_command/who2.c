/*================================================================
*   Copyright (C) 2018 . All rights reserved.
*   
*   文件名称：who2.c
*   创 建 者：scottdyt
*   创建日期：2018年05月31日
*   描    述：调用utmplib.c实现一次性读入多个utmp
*
================================================================*/

#include <stdio.h>
#include <unistd.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include "utmplib.c"

#ifndef UTMP_FILE
#define UTMP_FILE "/var/run/utmp"
#endif

/**
 * display time in a format fit for human consumption 
 * uses ctime to build a string then picks parts out of it 
 * Note: %12.12s prints a string 12 chars wide and LIMITS it to 12 chars
 */

void showtime(long timeval)
{
    char *cp;
    cp = ctime(&timeval);
    // conver time to string like Mon Feb 4 00:46:11 EST 2018
    printf("%12.12s", cp + 4);
}

/**
 *show info()
 * displays the contents of the utmp struct
 * in human readable form
 * displays nothing if record has no user name
 */
void show_info(struct utmp *utbufp)
{
    if (utbufp->ut_type != USER_PROCESS)
        return;
    printf("%-8.8s", utbufp->ut_user); // user name
    printf(" ");
    printf("%-8.8s", utbufp->ut_line); // Devicename
    printf(" ");
    showtime(utbufp->ut_time);
    printf("\n");
}

int main()
{
    struct utmp *utbufp, *utmp_next();
    if (utmp_open(UTMP_FILE) == -1)
    {
        perror(UTMP_FILE);
        exit(1);
    }
    while ((utbufp = utmp_next()) != ((struct utmp *)NULL))
        show_info(utbufp);
    utmp_close();
    return 0;
}