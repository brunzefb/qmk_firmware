#/bin/bash
mac_path="/Volumes/RPI-RP2"

figlet "Install"
echo "Get ready to put keyboard side in flash mode."
read -n 1 -s -r -p ""
echo "Need Flash mode in 10 seconds"
sleep 10
cp .build/keebio_iris_rev8_brunzefb-v8.uf2 $mac_path/
if [ $? -ne 0 ]; then
  figlet "Copy Error"
  exit 1
fi
echo "Installed the Firmware!"
sleep 2
echo " "
echo "Get ready to put other keyboard side in flash mode."
read -n 1 -s -r -p ""
echo "Need Flash mode in 10 seconds"
sleep 10
# install keyboard firmware by copying it to the mounted drive of the keyboard
cp .build/keebio_iris_rev8_brunzefb-v8.uf2 $mac_path/
if [ $? -ne 0 ]; then
  figlet "Copy Error"
  exit 1
fi
echo "Installed the Firmware!"
figlet "Done"
