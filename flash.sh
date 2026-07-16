#!/bin/bash
mac_path="/Volumes/RPI-RP2"

for i in {1..2}; do
  figlet "Flash #$i"
  echo "Get ready to put keyboard side #$i in flash mode..."
  echo "You have 10 seconds to put the keyboard in bootloader mode"
  sleep 10
  
  # Wait for the device to appear and mount it
  echo "Waiting for RPI-RP2 device..."
  for attempt in {1..10}; do
    # Find the RPI-RP2 disk
    DISK=$(diskutil list | grep "RPI-RP2" | awk '{print $NF}')
    if [ -n "$DISK" ]; then
      echo "Found RPI-RP2 at $DISK"
      # Mount it if not already mounted
      if [ ! -d "$mac_path" ]; then
        diskutil mount $DISK
        sleep 1
      fi
      break
    fi
    echo "Attempt $attempt: Device not found, waiting..."
    sleep 1
  done
  
  # Check if mounted
  if [ ! -d "$mac_path" ]; then
    figlet "Mount Error"
    echo "Error: Could not find or mount RPI-RP2 device"
    exit 1
  fi
  
  # Copy firmware
  cp .build/keebio_iris_rev8_brunzefb-v8.uf2 $mac_path/
  if [ $? -ne 0 ]; then
    figlet "Copy Error"
    exit 1
  fi
  
  echo "[Ok] Firmware #$i flashed!"
  echo "Waiting for keyboard to reboot..."
  sleep 3
done

figlet "Done"

