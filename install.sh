#/bin/bash
figlet "Build and Install"
echo "Building Firmware in ./keyboards/keebio/iris/keymaps/brunzefb-v8"
make keebio/iris/rev8:brunzefb-v8
if [ $? -ne 0 ]; then
  figlet "Compile Error"
  exit 1
fi
echo "Updating Firmware."
echo "Put Left keyboard side in flash mode in next 5s (Raise + \`), then press enter, ctrl+c to cancel"
sleep 5
# install keyboard firmware by copying it to the mounted drive of the keyboard
cp .build/keebio_iris_rev8_brunzefb-v8.uf2 /Volumes/RPI-RP2/keebio_iris_rev8_brunzefb-v8.uf2
if [ $? -ne 0 ]; then
  figlet "Copy Error"
  exit 1
fi
echo "Change the USB connector to the second keyboard, press enter"
read -r -p "Press enter to continue" key
echo "Put right keyboard side in flash mode in next 5s (Raise + \`), then press enter, ctrl+c to cancel"
sleep 5
# install keyboard firmware by copying it to the mounted drive of the keyboard
cp .build/keebio_iris_rev8_brunzefb-v8.uf2 /Volumes/RPI-RP2/keebio_iris_rev8_brunzefb-v8.uf2
if [ $? -ne 0 ]; then
  figlet "Copy Error"
  exit 1
fi
figlet "Done"
