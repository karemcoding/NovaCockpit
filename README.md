Markdown

# NovaCockpit 🏎️

NovaCockpit is a modern, real-time Automotive Human-Machine Interface (HMI) dashboard simulation built with C++ and Qt 6. It visualizes vehicle telemetry data (Speed, RPM, Gear state) by interfacing directly with a Controller Area Network (CAN bus) via Linux SocketCAN.

## 🌟 Features
* **Real-time Telemetry:** Smooth, hardware-accelerated QML animations for Speed and RPM gauges.
* **Gear Selector:** Dynamic P-R-N-D state visualization.
* **CAN Bus Integration:** Decoupled C++ backend that listens and parses raw CAN frames using Qt SerialBus.
* **Modern Tooling:** Built with CMake and Qt 6.8 using the latest `qt_add_qml_module` standards.

## 🏗️ Architecture
The project follows a strict Software-Defined Vehicle (SDV) decoupled architecture:
1. **Presentation Layer (QML):** Dumb UI strictly for rendering and animation.
2. **Application Layer (C++):** State management and property bindings (MOC).
3. **Connectivity Layer (Qt SerialBus):** SocketCAN event-driven listeners and payload parsing.
4. **OS Layer (Linux):** Virtual CAN interface (`vcan`).

## 🛠️ Prerequisites
To build and run this project on a Linux machine (Ubuntu recommended), you need:
* **C++ Compiler:** GCC or Clang (C++17 standard or higher)
* **CMake:** Version 3.16 or newer
* **Qt 6:** Specifically Qt 6.8 with `Quick`, `Location`, `Positioning`, and `SerialBus` modules.
* **Linux CAN Utilities:** ```bash
  sudo apt update
  sudo apt install can-utils qt6-serialbus-dev

🚀 Build Instructions

    Clone the repository:
    Bash

    git clone git@github.com:karemcoding/NovaCockpit.git
    cd NovaCockpit

    Build the project using CMake:
    Bash

    mkdir build && cd build
    cmake ..
    cmake --build .

    Run the executable:
    Bash

    ./appNovaCockpit

🎮 Simulation & Usage

NovaCockpit listens to the vcan0 network interface. To simulate vehicle data, you need to set up the virtual CAN and send frames via the terminal.

1. Setup Virtual CAN (vcan0)
Open a terminal and run:
Bash

sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0

2. Send CAN Frames (Inject Data)
With the NovaCockpit application running, open a terminal and use cansend to inject telemetry data:

    Speed (Frame ID: 0x123, Byte 0):
    Bash

    cansend vcan0 123#3C  # Sets speed to 60 km/h (0x3C = 60)
    cansend vcan0 123#78  # Sets speed to 120 km/h (0x78 = 120)

    RPM (Frame ID: 0x124, Bytes 0-1):
    Bash

    cansend vcan0 124#0BB8  # Sets RPM to 3000 (0x0BB8 = 3000)
    cansend vcan0 124#1F40  # Sets RPM to 8000 (0x1F40 = 8000)

    Gear Selector (Frame ID: 0x125, Byte 0):

        00 = Park (P)

        01 = Reverse (R)

        02 = Neutral (N)

        03 = Drive (D)
    Bash

    cansend vcan0 125#03  # Shifts to Drive

📄 License

This project is open-source and available under the MIT License.
