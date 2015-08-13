# USB Gizmos

A simple Arduino project to turn on and off those little USB powered gizmos like lights and fans.

## Arduino

Simply upload the Arduino sketch onto your board of choice using the Arduino IDE.
The address/pin assignments can be changed using the `pins` array. Each address is an array offset pointing at a pin. I've made pin 13 (built-in led) address 0 by default for testing.
The default pin assignments are intended for the Arduino Pro Mini and are all the digital pins exposed on the side with the ground pin.

## Usage

First start a screen session called `gizmos` to your Arduino's serial device, usually `/dev/tty.usbserial.*`. Eg:

```
[you@host ~]$ screen -S gizmos /dev/tty.usbserial.A50285BI 9600
```

Then you can use the `gizmo` script to turn gizmos on and off. Eg:

```
[you@host ~]$ ./bin/gizmo off 0
[you@host ~]$ ./bin/gizmo on 1
```

