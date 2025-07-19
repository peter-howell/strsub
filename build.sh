#!/bin/bash


clang strsub.c -o strsub

x="here is some text. hi there, I am greeting you. hi!, how are you? hi again."
echo "X: ${x}"
echo "pattern: hi"
echo "sub: hello"

./strsub hi hello "$x"


