#/bin/bash
figlet "Install"
echo "Put keyboard side in flash mode in next 7s (Raise + \`), then press enter, ctrl+c to cancel"
sleep 7
# install keyboard firmware by copying it to the mounted drive of the keyboard
cp .build/keebio_iris_rev8_brunzefb-v8.uf2 /Volumes/RPI-RP2/keebio_iris_rev8_brunzefb-v8.uf2
if [ $? -ne 0 ]; then
  figlet "Copy Error"
  exit 1
fi
read -r -p "Change the USB connector to the second keyboard, press enter" key
echo "Put other./ keyboard side in flash mode in next 7s (Raise + \`), then press enter, ctrl+c to cancel"
sleep 7
# install keyboard firmware by copying it to the mounted drive of the keyboard
cp .build/keebio_iris_rev8_brunzefb-v8.uf2 /Volumes/RPI-RP2/keebio_iris_rev8_brunzefb-v8.uf2
if [ $? -ne 0 ]; then
  figlet "Copy Error"
  exit 1
fi
figlet "Done"
