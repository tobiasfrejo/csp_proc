# Stage 1: clang-format 17.x
FROM ubuntu:22.04 AS clang-format-builder

RUN apt-get update && apt-get install -y \
    wget \
    xz-utils

RUN wget -O clang-format.tar.xz https://github.com/llvm/llvm-project/releases/download/llvmorg-17.0.6/clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04.tar.xz
RUN tar -xf clang-format.tar.xz clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04/bin/clang-format && \
    mv clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04/bin/clang-format ./clang-format && \
    chmod +x clang-format

# Stage 2: Build csp_proc and dependencies (including test dependencies)
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    python3 \
    python3-pip \
    ninja-build \
    gcc \
    g++ \
    git \
    meson \
    libcriterion-dev

COPY --from=clang-format-builder /clang-format /usr/bin/

WORKDIR /csp_proc/
RUN git clone https://github.com/spaceinventor/libcsp.git lib/csp
RUN git clone https://github.com/spaceinventor/libparam.git lib/param
RUN git clone https://github.com/spaceinventor/slash.git lib/slash
RUN git clone https://github.com/FreeRTOS/FreeRTOS-Kernel.git lib/freertos

COPY . /csp_proc/

RUN meson setup builddir \
    && meson compile -C builddir
