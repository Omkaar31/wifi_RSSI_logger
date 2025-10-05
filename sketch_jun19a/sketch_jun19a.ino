
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// 🔐 Your Home WiFi credentials
const char* ssid = "omrenuka";
const char* password = "ruthuparna";

ESP8266WebServer server(80);
String lastReply = "ESPBot: Hello! Ask me something.";

String htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head><title>ESP8266 Chatbot</title></head>
<body>
<h2>ESP8266 Chatbot 🤖</h2>
<div id="chat" style="white-space:pre-wrap; border:1px solid #ccc; padding:10px; height:200px; overflow:auto;">
ESPBot: Hello! Ask me something.
</div>
<input type="text" id="msg">
<button onclick="send()">Send</button>
<script>
function send() {
  let msg = document.getElementById('msg').value;
  fetch('/ask?msg=' + encodeURIComponent(msg))
    .then(response => response.text())
    .then(reply => {
      let chatBox = document.getElementById('chat');
      chatBox.innerText += "\\nYou: " + msg + "\\n" + reply;
      document.getElementById('msg').value = '';
      chatBox.scrollTop = chatBox.scrollHeight;
    });
}
</script>
</body>
</html>
)rawliteral";

// Simple rule-based chatbot logic
String getBotReply(String userMsg) {
  userMsg.toLowerCase();

  if (userMsg.indexOf("hi") >= 0 || userMsg.indexOf("hello") >= 0)
    return "ESPBot: Hello there! 👋";
  else if (userMsg.indexOf("how are you") >= 0)
    return "ESPBot: I'm doing great! Running at 160MHz! 😊";
  else if (userMsg.indexOf("bye") >= 0)
    return "ESPBot: Goodbye! See you soon. 👋";
  else if (userMsg.indexOf("name") >= 0)
    return "ESPBot: I’m ESPBot, your WiFi buddy!";
  else
    return "ESPBot: I didn't get that. Try saying hi, or ask me how I am!";
}

void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void handleAsk() {
  String msg = server.arg("msg");
  String reply = getBotReply(msg);
  lastReply = reply;
  server.send(200, "text/plain", reply);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/ask", handleAsk);
  server.begin();
  Serial.println("Chatbot server started.");
}

void loop() {
  server.handleClient();
}
