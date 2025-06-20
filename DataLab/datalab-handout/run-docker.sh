#!/bin/bash
docker run --rm --platform linux/amd64 \
  -v "$(pwd):/lab" \
  datalab-x86 "$@"
