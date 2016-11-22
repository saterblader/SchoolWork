!#/bin/bash
echo /lib/firmware/BB-UART1 > /sys/devices/bone_capemgr.9/slots
echo /lib/firmware/BB-UART2 > /sys/devices/bone_capemgr.9/slots
echo /lib/firmware/BB-SPIDEV1 > /sys/devices/bone_capemgr.9/slots
cd /home/debian/EmbeddedProject
./System&
