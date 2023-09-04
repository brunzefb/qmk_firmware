#!/bin/bash
rm -rf venv
python3 -m venv venv
source ./venv/bin/activate
python -m pip install english_words 
qmk generate-autocorrect-data autocorrect_dictionary.txt -o ./autocorrect_data.h
