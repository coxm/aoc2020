# AoC 2020
Mixed C++/JS for Advent of Code, 2020.

Most days have C++ solutions; if I was busy that day, or fancied some code
golf, there is a JS solution instead or as well.


## Building
The JS solutions don't require building.

The C++ solutions are built as a single CMake project, with a separate binary
for each day. Set up is as usual for CMake projects: for example, on Linux and
using the makefile generator, I use the following.

```bash
build_dir=build/debug
mkdir -p "$build_dir"
cmake -DCMAKE_BUILD_TYPE=Release -B "$build_dir"
make -C "$build_dir"
```


## Running
You can each day's code as follows.

-   JS: `./$day/main.js [input-file]`
-   C++: `"$build_dir/$day/main" [input-file]`.

The input file is optional, and defaults to `$day/input.txt`. Where example
inputs are given, those examples are often included too, as e.g.
`$day/example.txt`, `$day/example-long.txt`, etc. Some programs allow for extra
input, where parameters for the example inputs differ from those for the
`input.txt`.
