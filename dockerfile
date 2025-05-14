# Build stage
FROM ubuntu:22.04 AS builder

RUN apt-get update && \
    apt-get install -y g++ cmake build-essential git && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN cmake -B build -S . -DBUILD_TESTING=OFF && \
    cmake --build build --config Release

# Runtime stage - much smaller!
FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y libstdc++6 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

COPY --from=builder /app/build/enigma /usr/local/bin/enigma

ENTRYPOINT ["enigma"]