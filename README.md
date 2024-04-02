# csp_proc
![Tests](https://github.com/discosat/csp_proc/actions/workflows/run-tests.yml/badge.svg)
[![clang-format](https://img.shields.io/badge/code%20style-clang--format-blue.svg)](https://clang.llvm.org/docs/ClangFormat.html)

Lightweight, programmable procedures with a libcsp- and libparam-native runtime. This provides remote control of libparam-based coordination between nodes in a CSP network, essentially exposing the network as single programmable unit.

The library has a relatively small footprint suitable for microcontrollers, requiring no external libraries other than libcsp and libparam themselves for the core of the library. However, currently, the only runtime implementation relies on FreeRTOS.

# Build environment
Refer to the Dockerfile for a reference build environment, including code formatter. It can be brought up like so:

```bash
docker build -t csp_proc .
docker run --rm -it csp_proc
```
E.g. the following command will run the test suite:
```bash
docker build -t csp_proc . && docker run --rm csp_proc meson test -C builddir --verbose
```
