FROM ubuntu:22.04 AS base

RUN apt update && apt install git build-essential gcc-12 g++-12 zlib1g-dev libbz2-dev xorg-dev libgl1-mesa-dev  \
    libasound2-dev libpulse-dev -y

FROM base AS mkxp-z

SHELL ["/bin/bash", "-c"]

WORKDIR /app

RUN apt update && apt install ruby cmake meson autoconf automake xxd wget libtool pkg-config bison -y

COPY ./linux/Makefile linux/Makefile
WORKDIR linux
ENV CMAKE_EXTRA_ARGS='-DCMAKE_POSITION_INDEPENDENT_CODE=ON'
ENV EXTRA_CONFIG_OPTIONS='--with-pic'
RUN make

WORKDIR ..
COPY . .
RUN source linux/vars.sh; meson build -Dbuild_gem=true --buildtype debug

WORKDIR build
RUN ninja

WORKDIR ..
RUN cp build/mkxpz.so lib/mkxp-z

FROM base AS run-environment

SHELL ["/bin/bash", "-c"]

RUN apt update && apt-get install -y curl bzip2 libssl-dev libreadline-dev gdb

RUN curl -fsSL https://github.com/rbenv/rbenv-installer/raw/main/bin/rbenv-installer | bash
ENV PATH="/root/.rbenv/bin:$PATH"
RUN echo 'export PATH="$HOME/.rbenv/bin:$PATH"' >> ~/.bashrc
RUN echo 'eval "$(rbenv init -)"' >> ~/.bashrc
RUN rbenv install 3.1.4
RUN rbenv global 3.1.4

RUN apt install -y pulseaudio libportaudio2 dbus-x11

WORKDIR /app
COPY --from=mkxp-z /app/lib ./lib
COPY --from=mkxp-z /app/tests ./tests
COPY --from=mkxp-z /app/Rakefile .