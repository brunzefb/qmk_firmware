#/bin/bash
linux_path=/home/friedrich/git/opensource/qmk_firmware/usbmount
device=/dev/sdb1

for i in {1..2}; do
  echo "Get ready to put keyboard side in flash mode. Press any key to continue."
  read -n 1 -s -r -p ""
  echo "Need Flash mode in 10 seconds"
  # user needs to put keyboard in flash mode
  # it will take the user a few seconds to do this
  # and a further few seconds for the system to
  # detect the new mass stoarge device (from the keyboard)
  sleep 10
  mkdir -p usbmount
  # we have to mount the keyboard mass storage device
  # explicitly, as it is not mounted automatically
  sudo mount $device $linux_path
  # install keyboard firmware by copying it to the mounted drive of the keyboard
  sudo cp .build/keebio_iris_rev8_brunzefb-v8.uf2 $linux_path/
  if [ $? -ne 0 ]; then
    figlet "Copy Error"
    exit 1
  fi
  echo "[Ok] Firmware #$i!"
done

