#  Smart Room Relay Switch (ESP8266 + Web Control)

This is a Wi-Fi-based room light automation project using an ESP8266 (NodeMCU). You can turn your room light ON/OFF through a custom web interface, schedule actions, and even toggle dark mode for fun. Built entirely in **STA Mode**, the ESP8266 connects to your Wi-Fi and serves a clean UI accessible via browser.

##  Features

- Turn ON/OFF light from browser
- Schedule a time to toggle light (client-side)
- Dark mode toggle (just for fun)
- Connects to your existing Wi-Fi (STA Mode)
- Minimalist interface for fast load
- Works without internet (LAN only)

## Hardware Required

- ESP8266 NodeMCU
- Relay module (5V)
- Light bulb (or any load)
- Jumper wires
- Power supply (via USB or adapter)

## 🔌 Wiring

| ESP8266 Pin | Relay IN Pin |
|-------------|--------------|
| D1          | IN (Signal)  |
| 3.3V        | VCC          |
| GND         | GND          |

> *Ensure your relay is compatible with 3.3V logic or use a level shifter.*

##  Accessing the Web Panel

1. Upload the code to your ESP8266 (don’t forget to change your `ssid` and `password`).
2. Connect to the same Wi-Fi network.
3. Open Serial Monitor to get the IP address.
4. Open browser → `http://your_esp_ip`


##  Developed By

**Mr. BHB**  
A passionate developer from BHB Enterprise  
> _"When you're home alone , let your browser switch the light "

## License

MIT License
