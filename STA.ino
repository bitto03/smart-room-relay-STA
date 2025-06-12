#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define RELAY_PIN D1
const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";
ESP8266WebServer server(80);

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <title>Relay Controller - BHB</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    :root {
      --bg: #f4f4f4;
      --text: #222;
      --btn-on: #28a745;
      --btn-off: #dc3545;
    }
    body.dark {
      --bg: #121212;
      --text: #eee;
    }
    body {
      font-family: 'Segoe UI', sans-serif;
      background: var(--bg);
      color: var(--text);
      text-align: center;
      padding: 30px;
      transition: background 0.3s, color 0.3s;
    }
    .button {
      background-color: var(--btn-on);
      border: none;
      color: white;
      padding: 15px 35px;
      margin: 10px;
      font-size: 18px;
      border-radius: 10px;
      cursor: pointer;
    }
    .off {
      background-color: var(--btn-off);
    }
    input[type="time"], select {
      padding: 10px;
      font-size: 16px;
      border-radius: 5px;
      border: none;
      margin: 10px;
    }
    .dark-toggle {
      position: fixed;
      top: 10px;
      right: 10px;
      padding: 10px 20px;
      background: #444;
      color: white;
      border: none;
      border-radius: 8px;
      cursor: pointer;
    }
    footer {
      margin-top: 40px;
      font-size: 14px;
      color: #888;
    }
  </style>
</head>
<body>
  <h1>Relay Control Panel</h1>
  <button class="button" onclick="location.href='/on'">Turn ON</button>
  <button class="button off" onclick="location.href='/off'">Turn OFF</button>

  <h2>Scheduler</h2>
  <label>Set Time:</label><br>
  <input type="time" id="scheduleTime"><br>
  <select id="action">
    <option value="on">Turn ON</option>
    <option value="off">Turn OFF</option>
  </select><br>
  <button class="button" onclick="setSchedule()">Schedule</button>

  <p id="scheduleMsg"></p>
  <button class="dark-toggle" onclick="toggleDark()">Dark Mode</button>
  <footer>Dev by Mr. BHB</footer>

  <script>
    let scheduledTime = "";
    let scheduledAction = "";

    function setSchedule() {
      scheduledTime = document.getElementById("scheduleTime").value;
      scheduledAction = document.getElementById("action").value;
      document.getElementById("scheduleMsg").innerText = 
        `Scheduled to turn ${scheduledAction.toUpperCase()} at ${scheduledTime}`;
    }

    setInterval(() => {
      const now = new Date();
      const currentTime = now.toTimeString().substr(0, 5);
      if (scheduledTime === currentTime) {
        window.location.href = '/' + scheduledAction;
        scheduledTime = "";
      }
    }, 1000);

    function toggleDark() {
      document.body.classList.toggle("dark");
    }
  </script>
</body>
</html>
)=====";

void handleRoot() {
  server.send_P(200, "text/html", MAIN_page);
}

void handleOn() {
  digitalWrite(RELAY_PIN, LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleOff() {
  digitalWrite(RELAY_PIN, HIGH);
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.begin();
}

void loop() {
  server.handleClient();
}
