#!/bin/bash
figlet "Build"
echo "Building Firmware in ./keyboards/keebio/iris/keymaps/brunzefb-v8"
source .venv/bin/activate && PYTHONWARNINGS=ignore qmk compile -kb keebio/iris/rev8 -km brunzefb-v8
if [ $? -ne 0 ]; then
  figlet "Compile Error"
  exit 1
fi
figlet "Done"
