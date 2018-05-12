# Installation

To compile it, go to project's root directory and type:

`cd shell`

`make`

It will compile the files which are inside *src* directory and will create an executable *shell* inside the *bin* directory.

## Errors

By default, posixeg library is intalled into */usr/local/lib* folder, but this folder isn't in the default search paths of most of the dynamic linkers

If you get some errors like

`unable to find libposixeg.s0.0`

run

`ldconfig /usr/local/lib`

to tell your dynamic linker to search in this path too. Alternatively, you can move all content of */usr/local/lib* folder to */usr/lib*, but this discouraged.
