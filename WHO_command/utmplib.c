/*================================================================
*   Copyright (C) 2018 . All rights reserved.
*   
*   文件名称：utmplib.c
*   创 建 者：scottdyt
*   创建日期：2018年05月31日
*   描    述：实现一次性将utmp取出多个，减少磁盘read个数
*
================================================================*/

#include <stdio.h>
#include <unistd.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>

#define NUM 16
#define NULLPOINT ((struct utmp *)NULL)
#define UTSIZE (sizeof(struct utmp))

static char utmpbuf[NUM * UTSIZE]; /* storage */
static int all;                    /* num stored */
static int cur;                    /* next to go */
static int fd_utmp = -1;           /* read from fd opinter*/

/**
 *  try to open a utmp file 
 *  return file descriptor
 */
int utmp_open(char *filename)
{
    fd_utmp = open(filename, O_RDONLY);
    cur = all = 0;
    return fd_utmp;
}

/**
 * read next bunch of records into buffer
 * 
 */
int utmp_reload()
{
    int fd_read;
    fd_read = read(fd_utmp, utmpbuf, NUM * UTSIZE);
    all = fd_read / UTSIZE;
    cur = 0;
    return all;
}

/**
 *  get next utmp struct
 *  return struct pointer if exist
 */
struct utmp *utmp_next()
{
    struct utmp *tmp;
    // open error
    if (fd_utmp == -1)
        return NULLPOINT;
    // no more
    if (cur == all && utmp_reload() == 0)
        return NULLPOINT;
    // get address of next record
    tmp = (struct utmp *)&utmpbuf[cur * UTSIZE];
    cur++;
    return tmp;
}

void utmp_close()
{
    if (fd_utmp != -1)
        close(fd_utmp);
}
