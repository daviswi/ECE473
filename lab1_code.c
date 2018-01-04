// lab1_code.c
// R. Traylor
// 7.21.08

//This program increments a binary display of the number of button pushes
on switch
//S0 on the mega128 board.

#include <avr/io.h>
#include <util/delay.h>

//***********************************************************************
********
// debounce_switch
// Adapted from Ganssel's "Guide to Debouncing"
// Checks the state of pushbutton S0 It shifts in ones till the button is pushed.
// Function returns a 1 only once per debounced button push so a debounce and toggle
// function can be implemented at the same time. Expects active low pushbutton on
// Port D bit zero. Debounce time is determined by external loop delay times 12.
//***********************************************************************
********
int8_t debounce_switch() {
	 static uint16_t state = 0; //holds present state
	 state = (state << 1) | (! bit_is_clear(PIND, 0)) | 0xE000;
	 if (state == 0xF000) return 1;
 	return 0;
}

//*******************************************************************************
// Check switch S0. When found low for 12 passes of "debounce_switch(), increment
// PORTB. This will make an incrementing count on the port B LEDS.
//*******************************************************************************
int main()
{
DDRB = 0xFF; //set port B to all outputs

//Temporary Variables, Initialization
int temp = 0; //Placeholder for button count
int LSB = 0; //Least significant bit value
int MSB = 0; //Most significant bit value

while(1){ //do forever
 if(debounce_switch()) {

	 temp++; //Button count is increased
 	LSB = temp % 10; //LSB is determined, leftover 

 	if(temp / 10 == 0) //MSB is determined, if high enought for one
 	{
		 MSB = temp / 10;
 	

 	if(temp <= 9) //checks count, moves LSB and MSB to needed value
 	{
 		PORTB = LSB;
 		PORTB |= (0<<PB4)|(0<<PB5)|(0<<PB6)|(0<<PB7); //MSB is Zero
 	}
 	else if(temp >= 10 && temp <= 19)
 	{
 		PORTB = LSB;
 		PORTB |= (1<<PB4)|(0<<PB5)|(0<<PB6)|(0<<PB7); //MSB is One
 	}	
 	else if(temp >= 20 && temp <= 29)
 	{
 		PORTB = LSB;
 		PORTB |= (0<<PB4)|(1<<PB5)|(0<<PB6)|(0<<PB7); //MSB is Two
 	}
 	else if(temp >= 30 && temp <= 39)
 	{
 		PORTB = LSB;
 		PORTB |= (1<<PB4)|(1<<PB5)|(0<<PB6)|(0<<PB7); //MSB is Three
 	}
 	else if(temp >= 40 && temp <= 49)
 	{
 		PORTB = LSB;
 		PORTB |= (0<<PB4)|(0<<PB5)|(1<<PB6)|(0<<PB7); //MSB is Four
 	}		
	else if(temp >= 50 && temp <= 59)
	 {
 		PORTB = LSB;
 		PORTB |= (1<<PB4)|(0<<PB5)|(1<<PB6)|(0<<PB7); //MSB is Five
 	}
 	else if(temp >= 60 && temp <= 69)
 	{
 		PORTB = LSB;
 		PORTB |= (1<<PB4)|(1<<PB5)|(1<<PB6)|(0<<PB7); //MSB is Six
 	}
 	else if(temp >= 70 && temp <= 79)
 	{
 		PORTB = LSB;
 		PORTB |= (0<<PB4)|(0<<PB5)|(0<<PB6)|(1<<PB7); //MSB is Seven
 	}
 	else if(temp >= 80 && temp <= 89)
 	{
 		PORTB = LSB;
 		PORTB |= (1<<PB4)|(0<<PB5)|(0<<PB6)|(1<<PB7); //MSB is Eight
 	}
 	else if(temp >= 90 && temp <= 99)
 	{
 		PORTB = LSB; 
 		PORTB |= (1<<PB4)|(1<<PB5)|(0<<PB6)|(1<<PB7); //MSB is Nine
 	}
 	else if(temp == 100)
 	{
 		PORTB = LSB;
 		PORTB |= (1<<PB4)|(1<<PB5)|(1<<PB6)|(1<<PB7); //MSB is Ten
		temp = 0; //Loop after value of 100
 	}
} //if switch true for 12 passes, increment port B
 _delay_ms(2); //keep in loop to debounce 24ms
 } //while
} //main 