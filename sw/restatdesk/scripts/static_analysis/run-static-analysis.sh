#!/usr/bin/env bash
#
# @brief   Run static analysis: build, cppcheck, clang-tidy.
# @version ver.1.0
# @date    Sat May 16 09:42:09 AM CEST 2026
# @company None, free software to use 2026
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT_DIR"

OUT_DIR="${ROOT_DIR}/build/static-analysis"
mkdir -p "$OUT_DIR"

NPROC=$(nproc || echo 4)
PKGCFG="$(pkg-config --cflags-only-I gtkmm-4.0 libserial 2>/dev/null || true)"

echo "[1/3] Building project (make -j${NPROC} -C build)"
make -j"${NPROC}" --directory=build

echo "[2/3] Running cppcheck on ${NPROC} threads"
CPPOUT="$OUT_DIR/cppcheck.txt"

cppcheck -j"${NPROC}" --enable=all --std=c++23 --inline-suppr \
    -i build -I. $PKGCFG . 2> "$CPPOUT" || true
echo "cppcheck output -> $CPPOUT"

echo "[3/3] Running clang-tidy-18 in parallel"
CLANGOUT="$OUT_DIR/clang-tidy.txt"
echo "clang-tidy run started at $(date)" > "$CLANGOUT"

find . -name '*.cc' -not -path "./build/*" -print0 | xargs -0 -n 1 -P "${NPROC}" -I {} \
    clang-tidy-18 {} -checks='-*,cppcoreguidelines-*' -- -std=gnu++23 -I. -I.. $PKGCFG >> "$CLANGOUT" 2>&1 || true

echo "clang-tidy output -> $CLANGOUT"
echo "Done. Reports saved under $OUT_DIR"