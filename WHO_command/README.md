# Who
Rewrite the command `who` to print info of logged users

## usage

```shell
./who1
./who2
```



# Function

- show log-in user info 

# How it works

- `man who`

  use `man` to search information about `who`

  > If FILE is not specified, use /var/run/utmp.  /var/log/wtmp as FILE  is common. 

- `man -k utmp`

  so we can search `utmp` for more information

- `man 5 utmp`

  read carefully, you can find this:

  >The file is a sequence of utmp structures, declared as follows in <utmp.h> (note that thisis only one of several definitions around; details depend on the version of libc):

- `find /usr/include -name "utmp.h"`

  use `find` command to recursively look for `utmp.h` in `/usr/include`

  we can find two files:

  >```shell
  >/usr/include/x86_64-linux-gnu/bits/utmp.h
  >/usr/include/utmp.h
  >```

- read first file, you can understand the information of logged user is stored with a struct, so we need to read struct from `/var/run/utmp`, and abstract useful information. really simple ^.^


# Key

- how to print user process?

  ```C
  if ( t_utmp->ut_type != USER_PROCESS ) 
         return;
  ```

- how to convert `ut_time` to normal timestamp?

  ```C
  man 3 ctime
  ```

- use `cache` to read 16 `utmp` one time from disk

  `utmplib.c` complete the job

  run `who2` 

# Reference

- [linux man study](https://blog.csdn.net/losophy/article/details/7961958)

