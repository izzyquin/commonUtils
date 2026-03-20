#!/usr/bin/env bash
set -euo pipefail

MODULE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PARENT_DIR="$(cd "${MODULE_DIR}/.." && pwd)"
BUILD_DIR="${PARENT_DIR}/build"

mkdir -p "${BUILD_DIR}"

cmake -S "${PARENT_DIR}" -B "${BUILD_DIR}" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_STANDARD=20

cmake --build "${BUILD_DIR}" -j

(cd "${BUILD_DIR}" && ctest --output-on-failure -R "^dijkstra_tests$")

