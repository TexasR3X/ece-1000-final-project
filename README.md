# ECE 1000 &mdash; Final Project

This project illistrates how one can build a remote control car using Arduino, and then control the car using either a remote or a desktop app.

## Project Structure

The software of the project is broken up into four major parts, each part running as a seperate process.

| Process Name      | Location         | Language   | Runs On |
| ----------------- | ---------------- | ---------- | ------- |
| Arduino Process   | `arduino/`       | C++        | Arduino |
| Main Process      | `app/`           | TypeScript | App     |
| Frontend Process  | `app/frontend/`  | TypeScript | App     |
| Bluetooth Process | `app/bluetooth/` | Python     | App     |

## Credits

This project was based on a different [project](https://projecthub.arduino.cc/lee_curiosity/a-beginners-guide-controlling-an-arduino-car-with-a-remote-5d4418) developed by Lee Curiosity. While my project has had signifcant changes made to it, the circuit design and Arduino sketch were orginally developed by him.

The `INO` files in `arduino/` were based on Curiosity's orginal work but were altered. The `arduino/chassis.stl` and `arduino/chassis.3mf` files were entirely his design.
