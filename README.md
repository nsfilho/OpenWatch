# Introduction

This is a opensource watch interface for M5Stick-C hardware.

[M5Stick-C Hardware](https://youtu.be/ppXkl0046dc)

# Features

1. Change watch faces when press M5 Home button;
1. Light Sleep after "N" milleseconds without interaction;
1. In most of Watch Interfaces when you press `button B`, you change the brightness;
1. All configurations are stored in SPIFFS File (`/config.json`)
1. Easly to add new watch interfaces;
1. Added a Wi-Fi connection (status notification) overlay;

# Next Features

1. Add a BLE Support;
1. Add notification system from Smartphone;
1. Companion app to configure;

# Developers

As requisite you need:

1. Visual Studio Code
1. PlatformIO IDE Plugin

It is highly recommend to install PlatformIO CLI.

## Tips and Tricks

You will need initialize libraries directory. For do this, open a `terminal` in project folder and execute the bellow commands:

```sh
cd lib
sh initialize.sh
```

This command will execute some `git clone` dependencies, as:

1. M5StickC
2. NTPClient (Taranis Fork)

### MacOS Developers

Sometimes, you can't write your firmware directly to M5Stick-C. You need do a jumper between `GPIO0` and `GND` before try to upload your code.

# Interfaces

Some interfaces was derivated or literally copied from anothers sources, as listed bellow:

1. Watch Interface: 1 [Nixed Tube](https://github.com/McOrts/M5StickC_Nixie_tube_Clock.git)
1. Watch Interface: 2 [Nixed Tube](https://github.com/McOrts/M5StickC_Nixie_tube_Clock.git)
1. Watch Interface: 3 [Nixed Tube](https://github.com/McOrts/M5StickC_Nixie_tube_Clock.git)
1. Watch Interface: 4 - Battery Information
1. Watch Interface: 5 - Simple Digital Clock
1. Watch Interface: 6 - NTP Update
