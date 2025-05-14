FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && \
    apt-get install -y \
    g++ \
    cmake \
    build-essential \
    git \
    && apt-get clean && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy everything
COPY . .

# Build
RUN cmake -B build -S . -DBUILD_TESTING=OFF && \
    cmake --build build

ENTRYPOINT ["./build/enigma"]