#include <SPI.h>
#include <Ethernet.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 10, 1, 1, 155 };
byte gateway[] = { 10, 1, 1, 1 };
byte subnet[] = { 255, 255, 255, 0 };
EthernetServer server(80);
void setup() {
  while (!Serial) {
  }
  Serial.begin(9600);
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("Servidor web em: ");
  Serial.println(Ethernet.localIP());
}
void loop() {
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          //client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html lang='pt-BR'>");
          client.println("<head>");
          client.println("<title>Automação</title>");
          client.println("<meta charset='utf-8'>");
          client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
          client.println("<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'>");
          client.println("<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js'></script>");
          client.println("<script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js'></script>");
          client.println("</head>");
          client.println("<body>");
          client.println("<div class='container'>");
          client.println("<h1 class='text-center'>Automação</h1>");
          client.println("<p class='text-center'>Ip atual:");
          client.println(Ethernet.localIP());
          client.println("</p><br>");
          client.println("</div>");
          client.println("</body>");
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    client.stop();
    Serial.println("client disconnected");
  }
}

