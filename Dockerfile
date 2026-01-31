FROM ubuntu:24.04 AS build

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential cmake \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release \
 && cmake --build build -j

FROM ubuntu:24.04
WORKDIR /app
COPY --from=build /app/build/tema9_note_scolare /app/tema9_note_scolare
CMD ["/app/tema9_note_scolare"]
