# build wut
FROM devkitpro/devkitarm AS libndsbuild

ENV PATH=$DEVKITARM/bin:$PATH

WORKDIR /
RUN git clone https://github.com/devkitPro/libnds
WORKDIR /libnds
RUN make -j$(nproc)
RUN make install
WORKDIR /

# set up builder image
FROM devkitpro/devkitarm AS builder

RUN apt-get update && apt-get -y install --no-install-recommends wget tar autoconf automake libtool && rm -rf /var/lib/apt/lists/*
COPY --from=libndsbuild /opt/devkitpro/libnds /opt/devkitpro/libnds

# build nitro engine
WORKDIR /devkitPro
RUN git clone https://github.com/devkitPro/wut
WORKDIR /nitro-engine/devkitPro
RUN make
RUN make NE_DEBUG=1
WORKDIR /

