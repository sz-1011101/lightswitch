#!/bin/bash

BUILDDIR="build/";

if [ -d "$BUILDDIR" ]; then
	echo "Found "$BUILDDIR
else
	echo "Created "$BUILDDIR
	mkdir $BUILDDIR;
fi
cd build

cmake ..;
make;
