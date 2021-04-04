#include <MD_MAX72xx.h>
 #include <MD_Parola.h>
  #include <SPI.h>
   #include <MD_Parola.h>
  #include <SimpleTimer.h>
 #include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 8 //panjang device
#define CLK_PIN D5
#define DATA_PIN D7
#define CS_PIN D0

MD_Parola P =MD_Parola(HARDWARE_TYPE,CS_PIN, MAX_DEVICES);

char auth[] = "TOKEN blynk"; // token seko blynk 
const char *ssid = "wifi"; // nama hotspot yang
const char *pass = "12345678";// password hotspot
char cstr[100] = {"ISI TEXT"};
unsigned int mlength;
String mymessage;

int ani_one = 3;
int ani_two = 3;

struct Catalog
{
textEffect_t  effect;   // text effect to display
};


Catalog effect[] =
{ { PA_PRINT},//0 
{ PA_SCROLL_UP},//1
{ PA_SCROLL_DOWN},//2
{ PA_SCROLL_LEFT},//3
{ PA_SCROLL_RIGHT},//4
{ PA_SPRITE},//5
{ PA_SLICE},//6
{ PA_MESH},//7
{ PA_FADE},//8
{ PA_DISSOLVE},//9
{ PA_BLINDS},//10
{ PA_RANDOM},//11
{ PA_WIPE},//12
{ PA_WIPE_CURSOR},//13
{ PA_SCAN_HORIZ},//14
{ PA_SCAN_HORIZX},//15
{ PA_SCAN_VERT},//16
{ PA_SCAN_VERTX},//17
{ PA_OPENING},//18
{ PA_OPENING_CURSOR},//19
{ PA_CLOSING},//20
{ PA_CLOSING_CURSOR},//21
{ PA_SCROLL_UP_LEFT},//22
{ PA_SCROLL_UP_RIGHT},//23
{ PA_SCROLL_DOWN_LEFT},//24
{ PA_SCROLL_DOWN_RIGHT},//25
{ PA_GROW_UP},//26
{ PA_GROW_DOWN},};//27



SimpleTimer timer;

void setup ()
{
Serial.begin(9600);
delay(10);Serial.print(" Connect to : ");
Serial.println(ssid);WiFi.begin(ssid, pass);
while (WiFi.status() != WL_CONNECTED)

{
delay(500);
Serial.print("….");
}
Serial.print("\n");
Serial.print("IP address : ");
Serial.print(WiFi.localIP());
Serial.print("\n");
Serial.print("Connect to : ");
Serial.println(ssid);
Blynk.begin(auth, ssid, pass, "blynk-cloud.com",8080);
timer.setInterval (5L,message);

P.begin();
}

BLYNK_WRITE(V0)
{
mymessage = param.asStr();
mlength = mymessage.length()+1;
mymessage.toCharArray(cstr,mlength);
}

BLYNK_WRITE(V1)
{
ani_one = param.asInt();

}

BLYNK_WRITE(V2)
{
ani_two = param.asInt();
}


void message() {
if (P.displayAnimate())
{
P.displayText(cstr, PA_CENTER, 50, 50, effect[ani_one].effect , effect[ani_two].effect);
P.displayReset();
  Serial.print(cstr);


}
}

void loop()
{
Blynk.run();
timer.run();
}
