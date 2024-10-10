# Rain-Notification-Using-Email-IOT
This project implements a rain detection system using the ESP8266 microcontroller, a rain sensor, and a servo motor. When water is detected by the rain sensor, the system sends an email notification via Gmail's SMTP server, and a servo motor is triggered

Features:

    Detects rain using a rain sensor connected to the ESP8266.
    Sends an automated email alert using the ESP_Mail_Client library when rain is detected.
    Controls a servo motor based on the sensor's readings (e.g., to cover or uncover something when rain is detected).
    Connects to WiFi for email functionality.

Components:

    ESP8266 Microcontroller
    Rain Sensor
    Servo Motor
    WiFi for sending emails

Libraries Used:

    ESP_Mail_Client for SMTP email communication
    ESP8266WiFi for WiFi connectivity
    Servo library for controlling the servo motor

How it Works:

    The system constantly monitors the rain sensor.
    When rain is detected (sensor outputs LOW), the servo motor is triggered, and an email notification is sent.
    If no rain is detected, the servo resets, and the system returns to its idle state.

Setup:

    Replace the WiFi credentials, email details, and recipient email in the code.
    Make sure to use an App Password for secure email sending via Gmail.
