#/bin/bash
linux_path=/home/friedrich/git/opensource/qmk_firmware/usbmount
echo "Get ready to put keyboard side in flash mode."
read -n 1 -s -r -p ""
echo "Need Flash mode in 10 seconds"
sleep 10
mkdir -p usbmount
sudo mount /dev/sdb1 $linux_path
# install keyboard firmware by copying it to the mounted drive of the keyboard
sudo cp .build/keebio_iris_rev8_brunzefb-v8.uf2 $linux_path/
if [ $? -ne 0 ]; then
  figlet "Copy Error"
  exit 1
fi
echo "Installed the Firmware #1!"
sleep 2
sudo umount /dev/sdb1
sleep 2
echo " "
echo "Get ready to put other keyboard side in flash mode."
read -n 1 -s -r -p ""
echo "Need Flash mode in 10 seconds"
sleep 10
sudo mount /dev/sdb1 $linux_path
# install keyboard firmware by copying it to the mounted drive of the keyboard
sudo cp .build/keebio_iris_rev8_brunzefb-v8.uf2 $linux_path/
if [ $? -ne 0 ]; then
  figlet "Copy Error"
  exit 1
fi
sudo umount /dev/sdb1
echo "Installed the Firmware #2!"

