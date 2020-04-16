# More
this is the naive complement of `more` command in Unix.

## usage

```shell
ls /bin | more2
```



# Function

- enter `q` to quit
- enter `space` to next page
- enter `CR` to next line

# Key

- [x] when consider *pipe*, how to get input from keyboard(changed original standard input)

> use */dev/tty* to get input from keyboard even the I/O has been redirect by command `<` or `>`

- [ ] input `q`, need to exit immediately, no need to enter `Enter`
- [ ] print `more?` use reverse color, refer [here](http://www.bitscn.com/os/linux/200904/158492.html).