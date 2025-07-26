# controller

A physical two-knob controller for the Zhiyun Crane 2S gimbal, supporting Wi-Fi and Bluetooth control with onboard configuration.



## Features
- **Analog Control**: Knobs to control the pan and tilt axis of the gimbal
- **Two Connection Modes**: Either connects directly to the gimbal via Bluetooth or connects via our app 
- **Knob Locks**: Lock each of the knobs individually.


LED Colors:

🔵 Blue = Config mode  
🟢 Green = Wi-Fi mode  
🟣 Purple = BLE mode  
🔴 Red = Error 

Working Principle:

The box will have 2 knobs which have springs within them such that they return to the equilibrium position once 
you stop applying force.
The angular displacement of the knob from the equilibrium position defines the speed of axis movement in that direction.

It'll have a lock for each knob, a config button and a switch to toggle between the modes of connection.

It will have ways of controlling the gimbal. The former is connecting through our mobile app (which also has 
object tracking built, and can stream your camera footage). Essentially our app also functions as a hub for such
accessories. Second, connecting it directly to the gimbal via BTE. 

If the config button is toggled, it creates a Wi-Fi network which contains a captive portal. The user can edit the 
settings there. 

