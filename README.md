# Arduino Robot Line Follower Project

This guide explains how to set up and work with this Arduino project using either Visual Studio Code with PlatformIO or the Arduino IDE.

## Libraries Used

This project includes the following libraries in the `lib/` folder:

- **FreeRTOS** - Real-time operating system for multitasking and task scheduling
- **KauLab** - Custom library for lab-specific functionality
- **MakeBlockDrive** - Library for controlling MakeBlock motors and sensors (includes line following capabilities)

These libraries are automatically included when cloning the repository and using PlatformIO in vscode. For Arduino IDE users, the libraries needs to be setup in the IDE.

## Quick Start (Recommended: VS Code + PlatformIO)

### Prerequisites
- Visual Studio Code installed
- Git for cloning the repository

### Setup Steps
1. **Install PlatformIO Extension**
   - Open Visual Studio Code
   - Go to Extensions view (Ctrl+Shift+X)
   - Search for "PlatformIO IDE" and install it

2. **Clone and Open Project**
   - Clone this repository to your local machine
   - Open the project folder in VS Code
   - PlatformIO will automatically recognize the project configuration

3. **Build and Upload**
   - **Compile**: Click the checkmark (✓) icon in the status bar
   - **Upload**: Click the right-arrow (→) icon next to the checkmark

## Alternative Setup (Arduino IDE)

If you prefer the Arduino IDE, follow these additional steps:

### File Setup
1. **Copy Project Files**
   - Copy contents from `src/`, `include/`, and `test/` folders
   - Place all files in a single new sketch folder
   - Ensure `main.cpp` and header files are included

2. **Install Libraries**
   - Go to `Sketch` → `Include Library` → `Manage Libraries...`
   - Install any required external libraries

3. **Configure and Build**
   - Select `Tools` → `Board` → `Arduino Mega 2560`
   - Click "Verify" (✓) to compile the code

## Deploying Compiled Firmware

For programming boards without a development environment:

### Locate the Firmware File
After a successful PlatformIO build, find the compiled firmware at:
```
.pio/build/megaatmega2560/firmware.hex
```

### Transfer and Flash
- Copy `firmware.hex` to a USB drive
- Use a programmer like `avrdude` to flash the firmware to the board
- This `.hex` file contains the complete, ready-to-flash binary

## Project Structure
```
RobotLineFollower/
├── src/           # Source code files
├── include/       # Header files
├── test/          # Test files
├── platformio.ini # PlatformIO configuration
└── README.md      # This file
```