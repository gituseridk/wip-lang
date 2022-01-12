#!/bin/bash

set -e

recurse() {
	for i in "$1"/*.c;do
		if [ -f "$i" ]; then
			printf "${i} $files"
		fi
	done
	for i in "$1"/*;do
		if [ -d "$i" ];then
			recurse "$i"
		fi
	done
}

ROOT=./src
SRC=$(recurse $ROOT)
OUT_FOLDER=./build
OUT=$OUT_FOLDER/out

mkdir -p $OUT_FOLDER

export FLAGS="-Wall -D_GNU_SOURCE -Wextra -Wno-unused-parameter -std=c11 -pedantic -ggdb"

cc $FLAGS $SRC -I $ROOT -o $OUT

echo successfully build to $OUT
