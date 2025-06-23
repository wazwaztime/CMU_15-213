#!/bin/bash
docker run --rm --platform linux/amd64 \
  -v "$(pwd):/lab" \
  bomblab-x86 "$@"
