#/bin/bash
figlet "Build"
echo "Building Firmware in ./keyboards/keebio/iris/keymaps/brunzefb-v8"
make keebio/iris/rev8:brunzefb-v8
if [ $? -ne 0 ]; then
  figlet "Compile Error"
  exit 1
fi
figlet "Done"
