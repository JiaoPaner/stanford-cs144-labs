For build prereqs, see [the CS144 VM setup instructions](https://web.stanford.edu/class/cs144/vm_howto).

## Sponge quickstart

To set up your build directory:

	$ mkdir -p <path/to/sponge>/build
	$ cd <path/to/sponge>/build
	$ cmake ..

**Note:** all further commands listed below should be run from the `build` dir.

To build:

    $ make

You can use the `-j` switch to build in parallel, e.g.,

    $ make -j$(nproc)

To test (after building; make sure you've got the [build prereqs](https://web.stanford.edu/class/cs144/vm_howto) installed!)

    $ make check

The first time you run `make check`, it will run `sudo` to configure two
[TUN](https://www.kernel.org/doc/Documentation/networking/tuntap.txt) devices for use during
testing.

### build options

You can specify a different compiler when you run cmake:

    $ CC=clang CXX=clang++ cmake ..

You can also specify `CLANG_TIDY=` or `CLANG_FORMAT=` (see "other useful targets", below).

Sponge's build system supports several different build targets. By default, cmake chooses the `Release`
target, which enables the usual optimizations. The `Debug` target enables debugging and reduces the
level of optimization. To choose the `Debug` target:

    $ cmake .. -DCMAKE_BUILD_TYPE=Debug

The following targets are supported:

- `Release` - optimizations
- `Debug` - debug symbols and `-Og`
- `RelASan` - release build with [ASan](https://en.wikipedia.org/wiki/AddressSanitizer) and
  [UBSan](https://developers.redhat.com/blog/2014/10/16/gcc-undefined-behavior-sanitizer-ubsan/)
- `RelTSan` - release build with
  [ThreadSan](https://developer.mozilla.org/en-US/docs/Mozilla/Projects/Thread_Sanitizer)
- `DebugASan` - debug build with ASan and UBSan
- `DebugTSan` - debug build with ThreadSan

Of course, you can combine all of the above, e.g.,

    $ CLANG_TIDY=clang-tidy-6.0 CXX=clang++-6.0 .. -DCMAKE_BUILD_TYPE=Debug

**Note:** if you want to change `CC`, `CXX`, `CLANG_TIDY`, or `CLANG_FORMAT`, you need to remove
`build/CMakeCache.txt` and re-run cmake. (This isn't necessary for `CMAKE_BUILD_TYPE`.)

### other useful targets

To generate documentation (you'll need `doxygen`; output will be in `build/doc/`):

    $ make doc

To lint (you'll need `clang-tidy`):

    $ make -j$(nproc) tidy

To run cppcheck (you'll need `cppcheck`):

    $ make cppcheck

To format (you'll need `clang-format`):

    $ make format

To see all available targets,

    $ make help

### lab0

```bash
(base) jiaopan@master:~/projects/c++/stanford-cs144-labs/cmake-build-debug/apps$ ./webget cs144.keithw.org /hello
HTTP/1.1 200 OK
Date: Wed, 02 Sep 2020 05:35:31 GMT
Server: Apache
Last-Modified: Thu, 13 Dec 2018 15:45:29 GMT
ETag: "e-57ce93446cb64"
Accept-Ranges: bytes
Content-Length: 14
Content-Type: text/plain

Hello, CS144!

(base) jiaopan@master:~/projects/c++/stanford-cs144-labs/cmake-build-debug$ make check_webget
[100%] Testing webget...
Test project /home/jiaopan/projects/c++/stanford-cs144-labs/cmake-build-debug
    Start 27: t_webget
1/1 Test #27: t_webget .........................   Passed    0.59 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.59 sec
[100%] Built target check_webget


(base) jiaopan@master:~/projects/c++/stanford-cs144-labs/cmake-build-debug$ make check_lab0
[100%] Testing Lab 0...
Test project /home/jiaopan/projects/c++/stanford-cs144-labs/cmake-build-debug
    Start 22: t_byte_stream_construction
1/9 Test #22: t_byte_stream_construction .......   Passed    0.00 sec
    Start 23: t_byte_stream_one_write
2/9 Test #23: t_byte_stream_one_write ..........   Passed    0.00 sec
    Start 24: t_byte_stream_two_writes
3/9 Test #24: t_byte_stream_two_writes .........   Passed    0.00 sec
    Start 25: t_byte_stream_capacity
4/9 Test #25: t_byte_stream_capacity ...........   Passed    0.00 sec
    Start 26: t_byte_stream_many_writes
5/9 Test #26: t_byte_stream_many_writes ........   Passed    0.01 sec
    Start 27: t_webget
6/9 Test #27: t_webget .........................   Passed    3.05 sec
    Start 47: t_address_dt
7/9 Test #47: t_address_dt .....................   Passed    0.04 sec
    Start 48: t_parser_dt
8/9 Test #48: t_parser_dt ......................   Passed    0.00 sec
    Start 49: t_socket_dt
9/9 Test #49: t_socket_dt ......................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 9

Total Test time (real) =   3.12 sec
[100%] Built target check_lab0

```
