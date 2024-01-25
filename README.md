<a href="#"><img src="https://raw.githubusercontent.com/vshymanskyy/StandWithUkraine/main/banner2-no-action.svg" /></a>

# ʳussian losses watch for ESP32

The watch displays the ʳussian losses in the current war in Ukraine. It uses the [API](https://russianwarship.rip/api-documentation/v2) to get the correct information.

<a href="#"><img src="https://github.com/rublin/rlw32/blob/main/images/clock.jpg?raw=true" /></a>

## Get started

1. Turn on the watch (using micro usb cable)
2. Wait for the message **WiFi status: NOT connected**. It's an initial config mode.
3. Use your smartphone to connect to the access point **GloryToUkraine**
4. Open your browser and enter http://192.168.4.1

<a href="#"><img src="https://github.com/rublin/rlw32/blob/main/images/WiFiManager_configure_wifi.jpg?raw=true" width="213" height="304"/></a>

5. Configure the WiFi to use your home network (SSID and password)
6. Enjoy the usage after the reboot
7. Press reset if the time is incorrect or there is no data

<a href="#"><img src="https://github.com/rublin/rlw32/blob/main/images/reset.jpg?raw=true" /></a>

## Update the firmware using OTA

1. The new [release](https://github.com/rublin/rlw32/releases) is available
2. Download the new release (you are interested in **.bin** file)
3. Enter the initial config mode using "double reset" (press reset twice with a couple of seconds delay)

<a href="#"><img src="https://github.com/rublin/rlw32/blob/main/images/reset.jpg?raw=true" /></a>

4. Wait for the message **WiFi status: NOT connected**. 
5. Open your browser and enter http://192.168.4.1

<a href="#"><img src="https://github.com/rublin/rlw32/blob/main/images/WiFiManager_ota.jpg?raw=true" width="213" height="304"/></a>

6. Upload and update new release
7. Enjoy the usage after the reboot
