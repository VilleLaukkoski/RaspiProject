#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "wiringPi.h"
#include <lcd.h>
#include <ifaddrs.h>
#include <string.h>
#include <ctype.h>
#include <wiringPiI2C.h>
#include <stdbool.h>
//USE WIRINGPI PIN NUMBERS
#define LCD_RS  25               //Register select pin
#define LCD_E   24               //Enable Pin
#define LCD_D4  23               //Data pin D4
#define LCD_D5  22               //Data pin D5
#define LCD_D6  21               //Data pin D6
#define LCD_D7  14               //Data pin D7
void task1();
void task2();
void getIP(char* outStr);
void task2(){
        char led[64][64] = {"HIGH","LOW"};
        int lcd;
        wiringPiSetup();
        int tem = wiringPiI2CSetup (0x4a); 
        lcd = lcdInit (2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);
        char p[64] = "1";
        getIP(p);
        while(1){
                lcdClear(lcd);
                lcdPosition(lcd, 0, 0);
                int8_t value = wiringPiI2CReadReg8(tem, 0);
                char val[64];
                snprintf(val, sizeof(val), "%d", value);
                lcdPuts(lcd,val);
                lcdPosition(lcd, 0, 1);
                lcdPuts(lcd,"1");
                lcdPuts(lcd, p);
                pinMode (0, OUTPUT);
                if(value < 20){
                        digitalWrite (0, HIGH);
                } else{
                        digitalWrite (0, LOW);
                }
                
                sleep(1);
        }
}
void getIP(char* outStr){ //task3
    FILE *fp;
        char returnData[64];
        int count = 0;
        fp = popen("/sbin/ifconfig wlan0", "r");
        while (fgets(returnData, 64, fp) != NULL)
        {
                if (count == 2){
                        pclose(fp);
                        char *p;
                        p = strtok(returnData, " ");
                        int maxDi = 0;
                        for(int i=0;i<strlen(p);i++){
                                if(isdigit(p[i])){
                                        maxDi = i+1;
                                };
                        };
                        for(int i=0;i<maxDi;i++){
                                outStr[i] = p[i];
                        };
                        outStr[maxDi] = '\0';
                };
                count++;
        }
        pclose(fp);
}
/*void joeShit(){
    int lcd;
    wiringPiSetup();
    lcd = lcdInit (2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);
    lcdPosition(lcd, 0, 0);
    lcdPuts(lcd,"LOOK JOE");
    lcdPosition(lcd, 0, 1);
    lcdPuts(lcd, "HACKERMAN");
}
*/
int main()
{
        task2();
        printf("jtta\n");
 //       joeShit();
        return 0;
}


