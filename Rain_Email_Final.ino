#include <ESP8266WiFi.h>
#include <ESP_Mail_Client.h>  // Correct library for sending emails via SMTP
#include <Servo.h>

#define RAIN_SENSOR_PIN 4  // GPIO pin connected to DO of rain sensor
Servo s1;

// WiFi credentials
const char* ssid = "Your Wifi Name ";           
const char* password = "Your Password";  

// SMTP server settings
const char* smtp_server = "smtp.gmail.com";  
const int smtp_port = 587;                    
const char* smtp_user = "Your Email";  
const char* smtp_pass = "Your Aap Password ";  
const char* recipient_email = "Recipient Email"; 

// SMTP session
SMTPSession smtp;  // Correct object for the session

void setup() {
  s1.attach(14);
  Serial.begin(115200); 
  pinMode(RAIN_SENSOR_PIN, INPUT);  
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() { 
  int rainStatus = digitalRead(RAIN_SENSOR_PIN);  // Read the digital output from the sensor

  if (rainStatus == LOW) {  // Sensor outputs LOW when water is detected
    Serial.println("Water Detected!"); 
    s1.write(180);  

    sendEmail();
    
  } else {
    Serial.println("No Water Detected.");
    s1.write(0);  
  }

  delay(1000);  
}

void sendEmail() {

  ESP_Mail_Session session;
  session.server.host_name = smtp_server;
  session.server.port = smtp_port;
  session.login.email = smtp_user;
  session.login.password = smtp_pass;
  //session.server.ssl = true;  // Use SSL for port 465

  SMTP_Message message;
  message.sender.name = "ESP8266 Rain Sensor";
  message.sender.email = smtp_user;
  message.subject = "Water Detected by Rain Sensor";
  message.addRecipient("Recipient", recipient_email);
  message.text.content = "Rain sensor has detected water.";
  
  // Connect and send the email
  if (!smtp.connect(&session)) {
    Serial.println("Could not connect to the mail server");
    return;
  }

  if (!MailClient.sendMail(&smtp, &message)) {
    Serial.println("Error sending email, reason: " + smtp.errorReason());
  } else {
    Serial.println("Email sent successfully");
  }

  // Terminate the SMTP session
  smtp.closeSession();
}