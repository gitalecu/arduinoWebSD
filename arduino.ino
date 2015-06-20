/*--------------------------------------------------------------
  Program:      two_temperatures

  Description:  Arduino web server web page displays two
                temperature values on two gauges.
                The web page is stored on the SD card.
                Ajax is used to update the analog values on the
                web page.
  
  Hardware:     Arduino Uno and official Arduino Ethernet
                shield. Should work with other Arduinos and
                compatible Ethernet shields.
                2Gb micro SD card formatted FAT16.
                MCP9700 temperature sensors interfaced to
                A2 & A3 analog inputs.
                
  Software:     Developed using Arduino 1.0.5 software
                Should be compatible with Arduino 1.0 +
                SD card contains web page called index.htm
  
  References:   - WebServer example by David A. Mellis and 
                  modified by Tom Igoe
                - SD card examples by David A. Mellis and
                  Tom Igoe
                - Ethernet library documentation:
                  http://arduino.cc/en/Reference/Ethernet
                - SD Card library documentation:
                  http://arduino.cc/en/Reference/SD
                - Gauge from:
                  https://github.com/Mikhus/canv-gauge

  Date:         3 August 2014
 
  Author:       W.A. Smith, http://startingelectronics.org
--------------------------------------------------------------*/

#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>

// size of buffer used to capture HTTP requests
#define REQ_BUF_SZ   100

// MAC address from Ethernet shield sticker under board
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(10, 0, 0, 19); // IP address, may need to change depending on network
EthernetServer server(80);  // create a server at port 80
EthernetClient client1;
int temp;
char serveradddress[] = "10.0.0.14";
File webFile;               // the web page file on the SD card
char HTTP_req[REQ_BUF_SZ] = {0}; // buffered HTTP request stored as null terminated string
char req_index = 0;              // index into HTTP_req buffer

    int pwmValue[20];
    int digitalValue[10];
    int analog_val_1 = 111;
    int analog_val_2 = 222;
    int analog_val_3 = 333;
    int analog_val_4 = 444;
    int analog_val_5 = 555;
    int analog_val_6 = 666;
    int digital_val_0 = 10;
    int digital_val_1 = 11;
    int digital_val_2 = 12;
    int digital_val_3 = 13;
    int digital_val_4 = 14;
    int digital_val_5 = 6;
    int digital_val_6 = 7;
    int pwm_val_0 = 100;
    int pwm_val_1 = 101;
    int pwm_val_2 = 102;
    int pwm_val_3 = 175;
    int pwm_val_4 = 185;
    int pwm_val_5 = 195;
    int pwm_val_6 = 145;

void setup()
{
    // disable Ethernet chip
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);

    Serial.begin(9600);       // for debugging
    
    // initialize SD card
    Serial.println("Initializing SD card...");
    if (!SD.begin(4)) {
        Serial.println("ERROR - SD card initialization failed!");
        return;    // init failed
    }
    Serial.println("SUCCESS - SD card initialized.");
    // check for index.htm file
    if (!SD.exists("index.htm")) {
        Serial.println("ERROR - Can't find index.htm file!");
        return;  // can't find index file
    }
    Serial.println("SUCCESS - Found index.htm file.");
    
    Ethernet.begin(mac, ip);  // initialize Ethernet device
    server.begin();           // start to listen for clients
}

void loop()
{
    EthernetClient client = server.available();  // try to get client

    if (client) {  // got client? 
    client1.stop();
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {   // client data available to read
                char c = client.read(); // read 1 byte (character) from client
                 //Serial.write(c);
                // buffer first part of HTTP request in HTTP_req array (string)
                // leave last element in array as 0 to null terminate string (REQ_BUF_SZ - 1)
                if (req_index < (REQ_BUF_SZ - 1)) {
                    HTTP_req[req_index] = c;          // save HTTP request character
                    req_index++;
                }
                // last line of client request is blank and ends with \n
                // respond to client only after last line received
                if (c == '\n' && currentLineIsBlank) {
                    // send a standard http response header
                    client.println("HTTP/1.1 200 OK");
                    // remainder of header follows below, depending on if
                    // web page or XML page is requested
                    // Ajax request - send XML file
                    if (StrContains(HTTP_req, "ajax_inputs")) {
                        // send rest of HTTP header
                        client.println("Content-Type: text/xml");
                        client.println("Connection: keep-alive");
                        client.println("Access-Control-Allow-Origin: *");
                        //client.println("Access-Control-Allow-Methods: GET");
                        client.println();
                        //client.print("<?xml version = \"1.0\" ?>");
                        // send XML file containing input states
                       XML_response(client);
                    } else if (StrContains(HTTP_req, "data.txt"))
                      {
                      client.println("Content-Type: text/html");
                        client.println("Connection: keep-alive");
                        client.println();
                        client.println("<!DOCTYPE HTML>");
                        client.println("<html>");
                        // send web page
                        webFile = SD.open("data.txt");        // open web page file
                        if (webFile) { Serial.println(" Pushing data.txt");
                            while(webFile.available()) {
                                client.write(webFile.read()); // send web page to client
                            }
                            webFile.close();
                        }
                        client.println("</html>");
                      }
                    else {  // web page request
                        // send rest of HTTP header
                        client.println("Content-Type: text/html");
                        client.println("Connection: keep-alive");
                        client.println();
                        // send web page
                        webFile = SD.open("lesson4.htm");        // open web page file
                        if (webFile) {
                            while(webFile.available()) {
                                client.write(webFile.read()); // send web page to client
                            }
                            webFile.close();
                        }
                    }
                    // display received HTTP request on serial port
                    Serial.println(HTTP_req);
   if (StrContains(HTTP_req, "ajax_inputs") and StrContains(HTTP_req, "pwm") or StrContains(HTTP_req, "digital")) {
                    Serial.write(StrContains1(HTTP_req, "="));
                   }
                    // reset buffer index and all buffer elements to 0
                    req_index = 0;
                    StrClear(HTTP_req, REQ_BUF_SZ);
                    break;
                }
                // every line of text received from the client ends with \r\n
                if (c == '\n') {
                    // last character on line of received text
                    // starting new line with next character read
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    // a text character was received from client
                    currentLineIsBlank = false;
                }
            } // end if (client.available())
        } // end while (client.connected())
        delay(1);      // give the web browser time to receive the data
        client.stop(); // close the connection
        sendget();
    } // end if (client)
    else {// if no client on serve
         }
}


// sets every element of str to 0 (clears array)
void StrClear(char *str, char length)
{
    for (int i = 0; i < length; i++) {
        str[i] = 0; 
    }
}

// searches for the string sfind in the string str
// returns 1 if string found
// returns 0 if string not found
char StrContains(char *str, char *sfind)
{
    char found = 0;
    char index = 0;
    char len;

    len = strlen(str);
    
    if (strlen(sfind) > len) {
        return 0;
    }
    while (index < len) {
        if (str[index] == sfind[found]) {
          //Serial.print(str[index]);
            found++;
            if (strlen(sfind) == found) {
                return 1;
            }
        }
        else {
            found = 0;
        }
        index++;
    }
    return 0;
}

char StrContains1(char *str1, char *sfind)
{ char *cmd1[10];
  char *cmd2[20];
  char *cmd3[10];
  char *pwmNr[10];
  char *a;
  char *p;
  char *p1;  
  int index1 = 0;
  int index2 = 0;
  char index3 = 0;
  
  p = strtok(str1, ",.-=&");
  /* separa sirul in "tokeni" si afiseaza-i pe linii separate. */
  while (p != NULL) { 
    //Serial.print(index1); 
    cmd1[index1] = p;    
    //Serial.println(cmd1[index1]);
    p = strtok(NULL, "&"); // desfacerea cuvintelor dupa caracterul &
    index1++;
  } 
  
  for (int i = 0; i < index1; i++) {
      p1 = strtok(cmd1[i], ",.-=&");
      //Serial.print(" cmd1["); Serial.print(i);Serial.print("]");
       //Serial.print(cmd1[i]); 
       while (p1 != NULL) { 
         Serial.print("   cmd2["); Serial.print(index2);Serial.print("]"); 
           cmd2[index2] = p1;    
            Serial.println(cmd2[index2]);
           p1 = strtok(NULL, "=");  // desfacerea cuvintelor dupa caracterul =
        index2++;
        } 
    }
     // conversia in float si atribuirea valorilor uni vector
     for (int j = 0; j < index2; j++) {
        //Serial.print(" atof");Serial.print(atof(cmd2[j]));
        if(StrContains(cmd2[j], "pwm0")){Serial.print(" find pwm0=");
          pwmValue[0] = atof(cmd2[j+1]); Serial.println(pwmValue[0]);
         }
         if(StrContains(cmd2[j], "pwm1")){ Serial.print(" find pwm1=");
          pwmValue[1] = atof(cmd2[j+1]); Serial.println(pwmValue[1]);
         }
         else if(StrContains(cmd2[j], "pwm2")){ Serial.print(" find pwm2=");
          pwmValue[2] = atof(cmd2[j+1]);  Serial.println(pwmValue[2]);
        }
        else if(StrContains(cmd2[j], "pwm3")){ Serial.print(" find pwm3=");
          pwmValue[3] = atof(cmd2[j+1]);  Serial.println(pwmValue[3]);
        }
        else if(StrContains(cmd2[j], "pwm4")){ Serial.print(" find pwm4=");
          pwmValue[4] = atof(cmd2[j+1]);  Serial.println(pwmValue[4]);
        }
        else if(StrContains(cmd2[j], "pwm5")){ Serial.print(" find pwm5=");
          pwmValue[5] = atof(cmd2[j+1]);  Serial.println(pwmValue[5]);
        }
         else if(StrContains(cmd2[j], "digital0")){ Serial.print(" find digital0=");
          digitalValue[0] = atof(cmd2[j+1]);  Serial.println(digitalValue[0]);
        }
        else if(StrContains(cmd2[j], "digital1")){ Serial.print(" find digital1=");
          digitalValue[1] = atof(cmd2[j+1]);  Serial.println(digitalValue[1]);
        }
        else if(StrContains(cmd2[j], "digital2")){  Serial.print(" find digital2=");
          digitalValue[2] = atof(cmd2[j+1]);  Serial.println(digitalValue[2]);
        }
        else if(StrContains(cmd2[j], "digital3")){  Serial.print(" find digital3=");
          digitalValue[3] = atof(cmd2[j+1]);  Serial.println(digitalValue[3]);
        }
        else if(StrContains(cmd2[j], "digital4")){  Serial.print(" find digital4=");
          digitalValue[4] = atof(cmd2[j+1]);  Serial.println(digitalValue[4]);
        }
        else if(StrContains(cmd2[j], "digital5")){  Serial.print(" find digital5=");
          digitalValue[5] = atof(cmd2[j+1]);  Serial.println(digitalValue[5]);
        }
        else if(StrContains(cmd2[j], "digital6")){  Serial.print(" find digital6=");
          digitalValue[6] = atof(cmd2[j+1]);  Serial.println(digitalValue[6]);
        }
     
     }
    digital_val_0 = digitalValue[0];
    digital_val_1 = digitalValue[1];
    digital_val_2 = digitalValue[2];
    digital_val_3 = digitalValue[3];
    digital_val_4 = digitalValue[4];
    pwm_val_0 = pwmValue[0];
    pwm_val_1 = pwmValue[1];
    pwm_val_2 = pwmValue[2];

  return 1;
}

int isNumeric (const char * s)
{
  if (s == NULL || *s == '\0' || isspace(*s)) return 0; // extra protection
  if (*s == '-' || *s == '+') s++; // allow a + or - in the first char space
  while(*s)
  {
    if(!isdigit(*s))
      return 0;
    s++;
  }
  return 1;
}

  
// send the XML file containing analog value
void XML_response(EthernetClient cl)
{
    char sample;
    
    webFile = SD.open("data.txt", FILE_READ);//FILE_WRITE

  // if the file opened okay, write to it:
  if (webFile) {
    Serial.print("Writing to test.txt...");
    webFile.print("<table><tr><td>");
    webFile.print("pmw0=");webFile.print(pwm_val_0);
    webFile.print("  pmw1=");webFile.print(pwm_val_1);
    webFile.print("  pmw2=");webFile.print(pwm_val_2);
    webFile.println("</td><tr></table>");
    // close the file:
    webFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
    
    
    // get the sum of 10 samples from analog inputs 2 and 3
    for (sample = 0; sample < 10; sample++) {
        analog_val_1 += analogRead(2);
        delay(2);
        analog_val_2 += analogRead(3);
        delay(2);
        analog_val_3 += analogRead(4);
        delay(2);
        analog_val_4 += analogRead(5);
        delay(2);
    }
    // calculate the average of the 10 samples
    analog_val_1 /= 10;
    analog_val_2 /= 10;
    analog_val_3 /= 10;
    analog_val_4 /= 10;
    Serial.print("SEND :");
    cl.print("<?xml version = \"1.0\" ?>");    Serial.print("<?xml version = \"1.0\" ?>");
    cl.print("<inputs>");     Serial.print("<inputs>");
    // read analog pin A2
//    analog_val = analogRead(2);
    cl.print("<analog>");     Serial.print("<analog>");
    cl.print(analog_val_1);     Serial.print(analog_val_1);
    cl.print("</analog>");     Serial.print("</analog>");
//    analog_val = analogRead(3);
    cl.print("<analog>");     //Serial.print("<analog>");
    cl.print(analog_val_2);    // Serial.print(analog_val_2);
    cl.print("</analog>");     //Serial.print("</analog>");
    cl.print("<analog>");    // Serial.print("<analog>");
    cl.print(analog_val_3);  //   Serial.print(analog_val_3);
    cl.print("</analog>");    // Serial.print("</analog>");
    cl.print("<analog>");    // Serial.print("<analog>");
    cl.print(analog_val_4);  //   Serial.print(analog_val_4);
    cl.print("</analog>");    // Serial.print("</analog>");
    cl.print("<analog>");     //Serial.print("<analog>");
    cl.print(analog_val_5);  //   Serial.print(analog_val_5);
    cl.print("</analog>");    // Serial.print("</analog>");
    cl.print("<analog>");    // Serial.print("<analog>");
    cl.print(analog_val_6);   //  Serial.print(analog_val_6);
    cl.print("</analog>");    // Serial.print("</analog>");
    cl.print("<analog>");    // Serial.print("<analog>");
    cl.print(digital_val_0); //    Serial.print(digital_val_0);
    cl.print("</analog>");    // Serial.print("</analog>");    
    cl.print("<analog>");     //Serial.print("<analog>");
    cl.print(digital_val_1);  //   Serial.print(digital_val_1);
    cl.print("</analog>");    // Serial.print("</analog>");
    cl.print("<analog>");     //Serial.print("<analog>");
    cl.print(digital_val_2);  //   Serial.print(digital_val_2);
    cl.print("</analog>");    // Serial.print("</analog>");
    cl.print("<analog>");     //Serial.print("<analog>");
    cl.print(digital_val_3);  //   Serial.print(digital_val_3);
    cl.print("</analog>");    // Serial.print("</analog>");
    cl.print("<analog>");     //Serial.print("<analog>");
    cl.print(digital_val_4);  //   Serial.print(digital_val_4);
    cl.print("</analog>");    // Serial.print("</analog>");
    cl.print("<analog>");     //Serial.print("<analog>");
    cl.print( pwm_val_0);     //Serial.print( pwm_val_0);
    cl.print("</analog>");    // Serial.print("</analog>");
    cl.print("<analog>");     //Serial.print("<analog>");
    cl.print( pwm_val_1);     //Serial.print( pwm_val_1);
    cl.print("</analog>");   //  Serial.print("</analog>");
    cl.print("<analog>");    // Serial.print("<analog>");
    cl.print( pwm_val_2);    // Serial.print( pwm_val_2);
    cl.print("</analog>");   //  Serial.print("</analog>");
 
   
    cl.print("</inputs>");      Serial.println("</inputs>");
}
void sendget(){
 
  if (client1.connect("10.0.0.14", 80)) {
    Serial.println("-> Connected to MYSQL 10.0.0.14");
    // Make a HTTP request:
    client1.print( "GET /php/add_data1.php?");
    client1.print("analog1="); client1.print( analog_val_1 );
    client1.print("&&analog2="); client1.print( analog_val_2 );
    client1.print("&&analog3="); client1.print( analog_val_3 );
    client1.print("&&analog4="); client1.print( analog_val_4 );
    client1.print("&&analog5="); client1.print( analog_val_5 );
    client1.print("&&analog6="); client1.print( analog_val_6 );
    client1.print("&&digital0="); client1.print( digital_val_0);
    client1.print("&&digital1="); client1.print( digital_val_1);
    client1.print("&&digital2="); client1.print( digital_val_2);
    client1.print("&&digital3="); client1.print( digital_val_3);
    client1.print("&&digital4="); client1.print( digital_val_4);
    client1.print("&&pwm0="); client1.print( pwm_val_0);
    client1.print("&&pwm1="); client1.print( pwm_val_1);
    client1.print("&&pwm2="); client1.print( pwm_val_2);   
    
    client1.println( " HTTP/1.1");
    client1.print( "Host: " );
    client1.println("10.0.0.14");
    client1.println( "Connection: close" );
    client1.println();
    client1.println();
    client1.stop();
  }
  else {
    // you didn't get a connection to the server:
    Serial.println("--> connection failed to http://10.0.0.14/php/add_data.php? /n");
  }
  if (client1.available()) {
    char c = client1.read();
    Serial.print(c);
  }

  //delay(5000);
  
}
