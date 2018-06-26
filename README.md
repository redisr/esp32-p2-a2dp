ESP-IDF P2 - A2DP 
=================

Project to get P2 analog signal and transmit to bluetooth headset.
Based on esp-idf/examples/bluetooth/a2dp_source project.

In this project, the bluetooth device implements A2DP source.
The device permorms a discovery to find a targt device, In this first version the target device name is hardcoded.
After connection is established, the device then start media transmission. The raw PCM media stream to be encoded and transmited in this example is a sawtooth wave therefore continuous tone can be heard.
After a period of time, media stream suspend, disconnection and reconnection procedure will be performed.
