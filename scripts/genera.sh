#!/bin/bash

# Genera el executable principal
echo ""
echo "Generant el Executable del programa"
cd src
make
cd ..
ln -s src/MST

# Genera els ps amb el codi font
echo ""
echo "Generant arxiu postcript del codi per a impressió"
cd srcdoc
for i in ../src/*.cc ../src/*.h
do
	enscript < $i -Ecpp -o $(echo $i | cut -d/ -f3).ps
done
cd ..

# Genera la memoria usant pdflatex
echo ""
echo "Generant la memoria en PDF"
cd tex
pdflatex -interaction=nonstopmode 'memoria.tex'
pdflatex -interaction=nonstopmode 'memoria.tex'
cd ..
ln -s tex/memoria.pdf

echo ""
echo "Generación finalizada"
