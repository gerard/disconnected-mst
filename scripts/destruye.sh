#!/bin/bash

rm memoria.pdf MST srcdoc/*
cd tex
rm memoria.log memoria.out memoria.pdf memoria.aux memoria.toc
cd ..
cd src
make clean
cd ..
