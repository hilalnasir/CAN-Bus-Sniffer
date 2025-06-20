# CAN Bus Sniffer with ESP32

This project uses the ESP32's built-in CAN controller to passively **sniff** and display real-time CAN bus messages over Serial. It's useful for debugging vehicle ECUs, reverse-engineering message formats, or validating CAN data timing.

---

## Requirements

### Hardware:
- **ESP32** development board (with built-in CAN controller)
- **CAN transceiver module** (e.g., SN65HVD230 or TJA1050)
- **Jumper wires**
- **Breadboard**
- **12V or 5V power source (if connecting to real vehicle CAN)**

### Wiring Example:
| ESP32 Pin | Transceiver Pin |
|-----------|-----------------|
| GPIO22    | CAN_RX          |
| GPIO21    | CAN_TX          |
| GND       | GND             |
| 3.3V/5V   | VCC             |

Connect **CAN-H** and **CAN-L** from the transceiver to the vehicle/system's CAN bus.

---

## Setup Options

### Option 1: PlatformIO (Recommended)

1. **Install PlatformIO** in VS Code or as standalone
2. **Clone this repository**
3. **Install dependencies** - PlatformIO will automatically install the required libraries
4. **Build and upload** using PlatformIO

### Option 2: Arduino IDE

#### Libraries Required:
Install these libraries in Arduino IDE:

1. **ESP32 CAN Library** - Search for "ESP32 CAN" in Library Manager
2. **Alternative**: Use the built-in ESP32 CAN driver (see `main_alternative.ino`)

#### Installation Steps:
1. Open Arduino IDE
2. Go to **Tools > Manage Libraries**
3. Search for "ESP32 CAN" and install
4. Or manually install from: https://github.com/miwagner/ESP32-Arduino-CAN

---

## How to Run

### 1. **Choose Your Code**
- `main.ino` - Uses ESP32CAN library
- `main_alternative.ino` - Uses built-in ESP32 CAN driver

### 2. **Board Settings**
- Select **Board**: ESP32 Dev Module (or your specific board)
- Select the correct **COM Port**

### 3. **Upload and Monitor**
- Click **Upload**
- Open **Serial Monitor** at **115200 baud**

You should begin seeing raw CAN frame data like this:

```
ID: 0x18DAF110 Data: 02 10 03 00 00 00 00 00 | DLC: 8 | RTR: No
ID: 0x0CF00400 Data: 01 FF 2A 00 00 5A 00 C0 | DLC: 8 | RTR: No
```

## Features

- **Passive CAN-bus sniffing** (safe for live vehicle networks)
- **Real-time message display** with:
  - Message ID (formatted as hex)
  - Data Length Code (DLC)
  - Raw Data Bytes (formatted)
  - RTR (Remote Transmission Request) status
  - Extended frame detection (in alternative version)
- **UART-based logging** via Serial Monitor
- **Error handling** for initialization failures

## Troubleshooting

### Common Issues:

1. **"Cannot open source file" errors**: Install the required libraries
2. **No messages received**: Check wiring and CAN bus activity
3. **Initialization failed**: Verify pin assignments and transceiver connections

### Testing:
- Connect to a working CAN bus (vehicle, industrial equipment, etc.)
- Or use a CAN bus simulator/another ESP32 sending test messages

## Code Versions

- **`main.ino`**: Uses ESP32CAN library, simpler setup
- **`main_alternative.ino`**: Uses built-in ESP32 CAN driver, more features
- **`platformio.ini`**: PlatformIO configuration for automatic dependency management