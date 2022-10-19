/* -----------------------------------------------------------------------------------------
[FILE NAME]    :	APP.c

[AUTHOR]       :	Mohamed Karam Fouad

[DATA CREATED] :	26/09/2022

[DESCRIPTION]  :	Source file for the application.
------------------------------------------------------------------------------------------*/

#include "../MCAL/GPIO/GPIO.h"
#include "../MCAL/Timer/timer.h"
#include "../MCAL/Interrupt/Interrupt.h"
#include "../ECUAL/Button/button.h"
#include "../ECUAL/Led/Led.h"
#include "../Helpers/common_macros.h"

#include"App.h"

#define SEC(x)	x * 1000

st_Led carGreen  = { .port = PORTA_ID, .pin =PIN0_ID};		// The Car's Green Light
st_Led carYellow = { .port = PORTA_ID, .pin = PIN1_ID};		// The Car's Yellow Light
st_Led carRed    = { .port = PORTA_ID, .pin = PIN2_ID};		// The Car's Red light

st_Led pedGreen  = { .port = PORTB_ID, .pin = PIN0_ID};		// Pedestrian's Green Light
st_Led pedYellow = { .port = PORTB_ID, .pin = PIN1_ID};		// Pedestrian's Yellow Light
st_Led pedRed    = { .port = PORTB_ID, .pin = PIN2_ID};		// Pedestrian's Red Light
st_Button button={.port = PORTD_ID, .pin = PIN2_ID};

uint8 normalmode = 1; //1 normal 0 pedestrian
uint8 carLED=0;    //0 green 1 yellow 2 red
uint8 prevcarLED=1;


void APP_init(void){
	//Car LED initialization
	LED_Init(&carGreen);
	LED_Init(&carYellow);
	LED_Init(&carRed);

	//Pedestrian LED initialization
	LED_Init(&pedGreen);
	LED_Init(&pedYellow);
	LED_Init(&pedRed);

	//Button initialization
	BUTTON_Init(&button);
	//Timer initialization
	Timer1_Init(WGM0_NORMAL, COM0_DISCONNECTED, 0);

	//Enable Global interrupts & setup rising edge detection for button
	INT_ENABLE_ALL();
	INT0_Init(ISC0_RISING_EDGE);

}



/* each blink is hard coded for 500ms for the blinking purpose. _seconds is
 the number of seconds to blink.*/
void Blink(st_Led* _led1, st_Led* _led2, uint8 _seconds)
{
	Timer1_Init(WGM1_CTC, COM1_DISCONNECTED, 0);

	for(int i = 0; i < _seconds * 2; i++){
		LED_Toggle(_led1);   /* the two leds will blink at the same time*/
		LED_Toggle(_led2);
		Timer1_Start(CS1_8, 62500);	// 500ms

		while(!BIT_IS_SET(TIFR, OCF1A));

		SET_BIT(TIFR, OCF1A);		// clear the flag
	}

	Timer1_Stop();
}


void APP_start(void){
	uint8 i;

	//if normal mode or need transition (i.e. car green led or yellow is on)
	if(normalmode || carLED==0 || carLED==1){
		if(!normalmode){
			carLED=1;
		}
		//Configuring Pedestrian LEDs
		LED_Off(&pedGreen);
		LED_Off(&pedYellow);

		switch(carLED){
		//Case GREEN LED
		case 0:
			LED_On(&carGreen);
			LED_Off(&carYellow);
			LED_Off(&carRed);

			for(i=0;i<1;i++){
				Timer0_Sleep(SEC(5), CS0_1024); // delay for 1 seconds
				if(!normalmode)break;          //check if ISR was called
			}
			carLED=1;
			prevcarLED=0;
			break;
			//Case YELLOW LED
		case 1:
			//if not normalmode then we need to blink both

			if(!normalmode){
				if(prevcarLED!=2){
					LED_On(&pedRed);
					//blink both yellow leds
					Blink(&carYellow, &pedYellow, 5);
				}
				prevcarLED=1;//to go to Ped lights logic
				carLED=2;
				LED_On(&carRed);
			}else{
				//blink car yellow led
				for(i=0;i<1;i++){
					Blink(&carYellow, NULL,  5);	// blinks for 5 seconds. BLOCKS
					if(!normalmode){//check if ISR was called
						prevcarLED=1;
						break;
					}
				}
			}
			LED_Off(&carYellow);
			LED_Off(&pedYellow);
			//Configure variables for correct switching
			if(prevcarLED==0){
				carLED=2;
				prevcarLED=1;
			}else if(prevcarLED==2){
				carLED=0;
				prevcarLED=1;
			}
			break;
			//Case RED LED
		case 2:
			LED_Off(&carGreen);
			LED_Off(&carYellow);
			LED_On(&carRed);
			for(i=0;i<1;i++){
				Timer0_Sleep(SEC(5), CS0_1024); // delay for 1 seconds
				if(!normalmode)break;          //check if ISR was called
			}
			prevcarLED=2;
			carLED=1;
			break;
		default:
			carLED=2;
			prevcarLED=1;
			break;
		}
	}else{
		//Configure PED LEDs
		LED_On(&pedGreen);
		LED_Off(&pedYellow);
		LED_Off(&pedRed);

		//Configure CAR LEDs
		LED_Off(&carGreen);
		LED_Off(&carYellow);
		LED_On(&carRed);
		Timer0_Sleep(SEC(5), CS0_1024); // delay for 5 seconds
		//make sure car red light is off
		LED_Off(&carRed);

		//blink both yellow while ped green is on
		Blink(&carYellow, &pedYellow, 5);	// blinks for 5 seconds. BLOCKS

		//Turn off yellow LEDs
		LED_Off(&carYellow);
		LED_Off(&pedYellow);
		//turn on PED red LED
		LED_On(&pedRed);
		//reset normalmode
		normalmode=1;
		//Configure carLED variables
		carLED=0;
		prevcarLED=1;
	}
}

ISR(INT0_vect){
	normalmode=0;
}
