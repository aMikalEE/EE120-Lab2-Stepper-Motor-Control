#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"


// These are the Hexadecimal values for coil magnetic excitation. The rotor tries to keep up with the changing magnetic field.
unsigned char FullStep[4] = {0xa, 0x9, 0x5, 0x6};
unsigned char HalfStep[8] = {0xa, 0x8, 0x9, 0x1, 0x5, 0x4, 0x6, 0x2};

void GPIO_Init(void);

// Four pins to control the stepper motor: PC 5, PC 6, PC 8, and PC 9
#define PIN1 5
#define PIN2 6
#define PIN3 8
#define PIN4 9

#define MPORT GPIOC

// Counter-clock-wise 
// 1000, 1100, 0100, 0110, 0010, 0011, 0001, 1001
// Clockwise
// 0001, 0011, 0010, 0110, 0100, 1100, 1000, 1001

#define DELAY 60000


void Full_Stepping_Clockwise(void){
	int i, j;
	uint32_t output;
	for(i = 0; i < 4; i++){	
			for(j = 0; j < DELAY; j++); // delay
			output = MPORT->ODR;
			output &= ~( 1<< PIN1 | 1 << PIN2 | 1 << PIN3 | 1<< PIN4 );			
			output |= ((FullStep[i] & 0x8) >> 3) << PIN4;
			output |= ((FullStep[i] & 0x4) >> 2) << PIN3;
			output |= ((FullStep[i] & 0x2) >> 1) << PIN2;
			output |= ( FullStep[i] & 0x1) << PIN1;
			MPORT->ODR = output; 
		}	
}

//---------------Complete this function-------------------------------
void Full_Stepping_CounterClockwise(void){
	int i, j;
	uint32_t output;
	for(i = 3; i >= 0; i--){	
			for(j = 0; j < DELAY; j++); // delay
			output = MPORT->ODR;
			output &= ~( 1<< PIN1 | 1 << PIN2 | 1 << PIN3 | 1<< PIN4 );			
			output |= ((FullStep[i] & 0x8) >> 3) << PIN4;
			output |= ((FullStep[i] & 0x4) >> 2) << PIN3;
			output |= ((FullStep[i] & 0x2) >> 1) << PIN2;
			output |= ( FullStep[i] & 0x1) << PIN1;
			MPORT->ODR = output;
		}	
}

//---------------Complete this function-------------------------------
void Full_Stepping_CounterClockwise2(void){
		int i, j;
	uint32_t output;
	for(i = 0; i < 4; i++){	
			for(j = 0; j < DELAY; j++); // delay
			output = MPORT->ODR;
			output &= ~( 1<< PIN1 | 1 << PIN2 | 1 << PIN3 | 1<< PIN4 );			
			output |= ((FullStep[i] & 0x8) >> 3) << PIN1;
			output |= ((FullStep[i] & 0x4) >> 2) << PIN2;
			output |= ((FullStep[i] & 0x2) >> 1) << PIN3;
			output |= ( FullStep[i] & 0x1) << PIN4;
			MPORT->ODR = output; 
		}	
}

void Half_Stepping_Clockwise(void){
	int i, j;
	uint32_t output;
	for(i = 0; i < 8; i++){	
			for(j = 0; j < DELAY; j++); // delay
			output = MPORT->ODR;
			output &= ~( 1<< PIN1 | 1 << PIN2 | 1 << PIN3 | 1<< PIN4 );			
			output |= ((HalfStep[i] & 0x8) >> 3) << PIN4;
			output |= ((HalfStep[i] & 0x4) >> 2) << PIN3;
			output |= ((HalfStep[i] & 0x2) >> 1) << PIN2;
			output |= ( HalfStep[i] & 0x1) << PIN1;
			MPORT->ODR = output; 
	}		
}

//---------------Complete this function-------------------------------
void Half_Stepping_CounterClockwise(void){
	int i, j;
	uint32_t output;
	for(i = 7; i >= 0; i--){	
			for(j = 0; j < DELAY; j++); // delay
			output = MPORT->ODR;
			output &= ~( 1<< PIN1 | 1 << PIN2 | 1 << PIN3 | 1<< PIN4 );			
			output |= ((HalfStep[i] & 0x8) >> 3) << PIN4;
			output |= ((HalfStep[i] & 0x4) >> 2) << PIN3;
			output |= ((HalfStep[i] & 0x2) >> 1) << PIN2;
			output |= ( HalfStep[i] & 0x1) << PIN1;
			MPORT->ODR = output;
	}
}

//---------------Complete this function-------------------------------
void Half_Stepping_CounterClockwise2(void){
		int i, j;
	uint32_t output;
	for(i = 0; i < 8; i++){	
			for(j = 0; j < DELAY; j++); // delay
			output = MPORT->ODR;
			output &= ~( 1<< PIN1 | 1 << PIN2 | 1 << PIN3 | 1<< PIN4 );			
			output |= ((HalfStep[i] & 0x8) >> 3) << PIN1;
			output |= ((HalfStep[i] & 0x4) >> 2) << PIN2;
			output |= ((HalfStep[i] & 0x2) >> 1) << PIN3;
			output |= ( HalfStep[i] & 0x1) << PIN4;
			MPORT->ODR = output;
	}
}

int main(void){

	System_Clock_Init(); // Switch System Clock = 80 MHz
	LED_Init();
	GPIO_Init();
	
	int k=0;
	while(k<512){
		//Half_Stepping_Clockwise();		
		//Half_Stepping_CounterClockwise();
		//Half_Stepping_CounterClockwise2();
		//Full_Stepping_Clockwise();
		//Full_Stepping_CounterClockwise();
		//Full_Stepping_CounterClockwise2();
		k++;
	}
}


void GPIO_Init(void){	
	
	/* Enable GPIOs clock */ 	
	RCC->AHB2ENR |=   RCC_AHB2ENR_GPIOCEN;
	
	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	MPORT->MODER &= ~(3U<<(2*PIN1) | 3U<<(2*PIN2) | 3U<<(2*PIN3) | 3U<<(2*PIN4));  
	MPORT->MODER |=  1U<<(2*PIN1) | 1U<<(2*PIN2) | 1U<<(2*PIN3) | 1U<<(2*PIN4);      //  Output(01)
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	MPORT->OSPEEDR &= ~(3U<<(2*PIN1) | 3U<<(2*PIN2) | 3U<<(2*PIN3) | 3U<<(2*PIN4));
	MPORT->OSPEEDR |=   2U<<(2*PIN1) | 2U<<(2*PIN2) | 2U<<(2*PIN3) | 2U<<(2*PIN4);  // Fast speed
	
	// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	MPORT->OTYPER &= ~(1U<<PIN1 | 1U<<PIN2 | 1U<<PIN3 | 1U<<PIN4);       // Push-pull
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	MPORT->PUPDR  &= ~(3U<<(2*PIN1) | 3U<<(2*PIN2) | 3U<<(2*PIN3) | 3U<<(2*PIN4));  // No pull-up, no pull-down
}
