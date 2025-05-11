#!/bin/bash
# Build and create a .deb package for the Wisp interpreter
set -e

# Variables
PKG_NAME=wisp
PKG_VERSION=0.3.0
BUILD_DIR=build
PKG_DIR=packaging
DEB_DIR=$PKG_DIR/${PKG_NAME}_${PKG_VERSION}_amd64

# Clean previous packaging
rm -rf "$DEB_DIR"

# Build the project
cmake -S . -B $BUILD_DIR
cmake --build $BUILD_DIR --config Release

# Install to packaging directory
cmake --install $BUILD_DIR --prefix="$DEB_DIR/usr"

# Copy DEBIAN control files
mkdir -p "$DEB_DIR/DEBIAN"
cp -r $PKG_DIR/DEBIAN/* "$DEB_DIR/DEBIAN/"

# Build the .deb package
fakeroot dpkg-deb --build "$DEB_DIR"

# Move the .deb to the project root
mv "$DEB_DIR.deb" "$PKG_NAME-$PKG_VERSION-dev-amd64.deb"

echo "\nDebian package created: $PKG_NAME-$PKG_VERSION-amd64.deb"
