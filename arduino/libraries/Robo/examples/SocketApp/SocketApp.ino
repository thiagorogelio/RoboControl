/*
 * Socket App
 *
 * A simple socket application example using the WiShield 1.0
 */

#include <WiShield.h>
#include <Robo.h>

Robo robo;

#define WIRELESS_MODE_INFRA	1
#define WIRELESS_MODE_ADHOC	2

// Wireless configuration parameters ----------------------------------------
unsigned char local_ip[] = {192,168,1,10};	// IP address of WiShield
unsigned char gateway_ip[] = {192,168,1,1};	// router or gateway IP address
unsigned char subnet_mask[] = {255,255,255,0};	// subnet mask for the local network
const prog_char ssid[] PROGMEM = {"Robo"};		// max 32 bytes

unsigned char security_type = 0;	// 0 - open; 1 - WEP; 2 - WPA; 3 - WPA2

// WPA/WPA2 passphrase
const prog_char security_passphrase[] PROGMEM = {"furmdjcj"};	// max 64 characters

// WEP 128-bit keys
// sample HEX keys
const prog_uchar wep_keys[] PROGMEM = {	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,	// Key 0
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	0x00,	// Key 1
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	0x00,	// Key 2
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	0x00	// Key 3
								};

// setup the wireless mode
// infrastructure - connect to AP
// adhoc - connect to another WiFi device
unsigned char wireless_mode = WIRELESS_MODE_ADHOC;

unsigned char ssid_len;
unsigned char security_passphrase_len;
//---------------------------------------------------------------------------

char *strin, command[3], value[5];
char *strout;
boolean auton;
int aut_typ;

void setup()
{
        command[2] = '\0';
        auton = false;
        robo.inicializa();
        robo.motor.stop();
	WiFi.init();
        Serial.begin(9600);
}

void comandoRobo(){
 
    if(strcmp(strin,"wh") == 0) // Autentificacao
       strout = "robot!\n";
    else {
       command[0] = strin[0];
       command[1] = strin[1];
       
       if(strcmp(command, "st") == 0) // Stop
           robo.motor.stop();
       else {
         
           if(strcmp(command, "rd") == 0) { // Read
             int line = 0, ultra = 0;
             if(strin[3] == '1')
               line = robo.linefinder.read();
             if(strin[5] == '1')
               ultra = robo.ultrassonic.read();
             sprintf(strout, "vl %d %d\n",line,ultra);
           }
           else {
               int i, ivalue;
               for(i=3;i<strlen(strin);i++)
                 value[i-3] = strin[i];
               value[i++] = '\0';
               
               if(strcmp(command, "at") == 0) { //Autonomo
                 if(strcmp(value,"off"))
                   auton = false;
                 else {
                   auton = true;
                 if(strcmp(value,"fol"))
                   aut_typ = 0;
                 if(strcmp(value,"cap"))
                   aut_typ = 1;
                 if(strcmp(value,"avo"))
                   aut_typ = 2;
                 }
               } else {
                 ivalue = atoi(value);
                 if(strin[0] == 'm') {
                   if(strin[1] == 'u')
                     robo.motor.front(ivalue);
                   else if(strin[1] == 'd')
                     robo.motor.back(ivalue);
                   else if(strin[1] == 'l')
                     robo.motor.walk(59,60);
                   else if(strin[1] == 'r')
                     robo.motor.walk(70,73);
                 }
                 if(strin[1] == 'a')
                   robo.manipulador.setRotacao(map(ivalue, 0, 100, 0, 180));
                 else if(strin[1] == 'l')
                   robo.manipulador.setAltura(map(ivalue, 0, 100, 0, 180));
                 else if(strin[1] == 'g')
                   robo.manipulador.setRotPulso(map(ivalue, 0, 100, 0, 180));
                 else if(strin[1] == 'b')
                   robo.manipulador.setAbertura(map(ivalue, 0, 100, 0, 180));
               }
           }
       }
    }

   /*     if(strin[0] == 'u')
            robo.motor.walk(70,60);
        if(strin[0] == 'd')
            robo.motor.walk(50,80);*/
}

void loop()
{
        strout = "\n";
        if(strlen(strin) > 1)
          if(strin[strlen(strin-1)] == '*'){
            strin[strlen(strin-1)] = '\0';
            comandoRobo();
          }

        // Auton
        if(auton){
          switch(aut_typ){
            case 0: robo.autonomy.lineFollow(); break;
            case 1: robo.autonomy.lineCatch(); break;
            case 2: robo.autonomy.avoidObstacle(); break;
          }
        }
        
	WiFi.run();
}
