Car have 3 modes 
🔷️Mode 1: direct driving by controlling the motors via Bluetooth without any limits and can go anywhere 
🔷️Mode 2: It is a mode to prevent the car from colliding with objects. When the second mode is activated, the servo and ultrasonic sensor ( that's like radar) works to determine the distance from car to any objects in 180 degree's to automatically stop the car from moving in the direction in which the collision will occur only and allow it to move in other directions.
🔷️Mode 3: It makes the car run without controlling it via Bluetooth, ultrasonic sensor calculates distances and If there is something in front of it, it stops, then the servo rotates on its own from 90 to 180 degrees, then from 180 to 90, then from 90 to 0, then from 0 to 90 to get the largest distance and then go in its direction. If the two distances are not enough, it comes back and then rotates to go to another direction

🔷️Project Hardware:

-arduino uno
-Bluetooth Module (HC05)
-2 Dc Geared Motor with wheels
-L293d IC
-Servo Motor (SG90)
-Ultrasonic Sensor (HC-sr04)
-Battery


How Ultrasonic Sensors Work
Ultrasonic sensors work by emitting high-frequency sound waves by setting High on trigger for 10µs so after hitting an object. it return to receiver (echo) so it becomes high for time by measuring this time we can detect time of go and return so  divide it by 2 We get the time taken by the wave to collide with the object and we have the speed of sound so we can now calculates the distance. 

I made function for distance that make this process and return the distance so can use is in code.

I made a function Self_Driving that take a pointers to store the last value of each.
