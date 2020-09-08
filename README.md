# `Arduino`

`Arduino` is low energy consuming `microcontroller`, C-like programming language makes it super easy to learn and development for IOT device.

Its scenario is very different with the `Raspberry PI`, that’s why its price is not very cheap (compared to `Raspberry PI` which got more powerful hardware spec). As it focuses on **fast boot, no OS needed, no damage with frequent power outages** edge IOT device development. It got a very wide range of hardware product line, you can find your own needed product from [here](https://www.arduino.cc/en/Main/Products).

A lot of exists libs you can choose to support fast development, even include the `Firebase` support which is great.

But its drawback also very explicitly which you can't build a very complex program which needs more CPU power or memory size. If you do need that requirement, then you better to go to Raspberry PI.

<hr>

## DEV environment setup

- Go to [here](https://www.arduino.cc/en/main/OldSoftwareReleases) download the DEV IDE.

- On `Mac`, you have to install the [USB-To-Serail-Driver](https://github.com/wisonye/arduino/blob/master/mac-usb-driver/CH34x_Install_V1.5.pkg). 
Otherwise, you won't see the board serial port when u connected to the hardware. [Here](https://www.youtube.com/watch?v=4tOAwJ8Rn9c) is the detail explanation.

## Demo videos

1. [74HC595IC Bit shift LED demo](74HC595IC-control-LEDs/74HC595IC-control-LEDs.ino)

    ![Bit shift LED demo](preview-videos/bit-shift-led.gif)

2. [Ultrasonic distance measurement demo](ultrasonic-display-in-LCD/ultrasonic-display-in-LCD.ino)

    ![Distance measurement demo](preview-videos/distance-measurement.gif)
