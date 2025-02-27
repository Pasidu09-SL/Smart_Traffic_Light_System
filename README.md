# Smart Traffic Light System

## Overview
The **Smart Traffic Light System** is an advanced traffic management solution that uses sensors and image processing to optimize traffic flow. It detects vehicles, pedestrians, and emergency vehicles (such as ambulances) to dynamically adjust signal timings for improved efficiency and safety.

## Features
- **Vehicle & Pedestrian Detection**: Uses ultrasonic and PIR sensors to detect traffic density and pedestrians.
- **Emergency Vehicle Recognition**: Utilizes YOLOv8-based image processing to prioritize ambulances.
- **Automated Signal Control**: Adjusts traffic lights dynamically based on real-time data.
- **Arduino Mega Integration**: Manages sensors and LEDs using an Arduino Mega board.
- **Prototype Implementation**: Developed and tested at the Extru Innovation Exhibition.

## Hardware Components
- **Arduino Mega 2560** (Main controller)
- **6 Ultrasonic Sensors** (Vehicle detection)
- **4 PIR Sensors** (Pedestrian detection)
- **44 LED Lights** (Traffic signals)
- **Camera Module** (Image processing for emergency vehicles)

## Sensor Pin Configuration
### PIR Sensors:
- North PIR Sensor: A2
- East PIR Sensor: A9

### Ultrasonic Sensors:
#### North Road:
- Left Lane: A3 (Trigger), A4 (Echo)
- Middle Lane: A5 (Trigger), A6 (Echo)
- Right Lane: A7 (Trigger), A8 (Echo)

#### East Road:
- Left Lane: A10 (Trigger), A11 (Echo)
- Middle Lane: A12 (Trigger), A13 (Echo)
- Right Lane: A14 (Trigger), A15 (Echo)

## Software & Tools Used
- **Arduino IDE** (Microcontroller programming)
- **Python (Jupyter Notebook)** (YOLOv8 model for object detection)
- **YOLOv8** (Image processing for emergency vehicle detection)
- **C++** (Embedded system programming for Arduino)

## Installation & Setup
### 1. Clone the Repository
```sh
 git clone https://github.com/Pasidu09-SL/Smart_Traffic_Light_System.git
 cd Smart_Traffic_Light_System
```

### 2. Setup Arduino Code
- Open the Arduino code in `Traffic_Light_System_2.0`
- Upload the code to **Arduino Mega** using the **Arduino IDE**

### 3. Install Required Python Packages
```sh
pip install ultralytics opencv-python numpy
```

### 4. Run Image Processing (YOLOv8)
```sh
python YOLO_Train/detect.py --weights best.pt --source 0
```

## Project Structure
```
Smart_Traffic_Light_System/
│── Traffic_Light_System_2.0/   # Updated Arduino code
│── Trafic_Light_System_1.0/    # Initial version
│── UltrasonicSonic_Sensor_Checker/ # Sensor testing scripts
│── YOLO_Train/                 # Image processing scripts
│── images/                     # Traffic signal diagrams
│── Budget.rtf                   # Project budget details
```

## Future Enhancements
- Implement real-time cloud-based traffic monitoring
- Improve AI-based traffic prediction
- Optimize emergency vehicle priority logic

## Contributors
- **Pasindu** ([GitHub](https://github.com/Pasidu09-SL))

## License
This project is licensed under the MIT License - see the LICENSE file for details.

