///EMBEDDED SYSTEMS 2020-1///
///PEDRO ROMANO SPLENDORE///
///T02///
//COMMENTS ABOUT THE PROJECT///////////////////////////
///UART IS FINE///
///PWM AND LED D4 ARE FINE, BUT SOMETIMES WHEN YOU RELEASE A BUTTON, IT COUNTS TWICE FOR SOME REASON///
///LED'S FROM PERON BOOSTER PACK ARE NOT WORKING (they dont light up)///

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
// includes da biblioteca driverlib
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/pin_map.h"
#include "utils/uartstdio.h"

#include "system_TM4C1294.h" 

uint8_t LED_D1 = 0;

extern void UARTStdioIntHandler(void);

void SysTick_Handler(void){
//  LED_D1 ^= GPIO_PIN_1; // Troca estado do LED D1
//  GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, LED_D1); // Acende ou apaga LED D1
} // SysTick_Handler

void UARTInit(void){
  // Enable the GPIO Peripheral used by the UART.
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));

  // Enable UART0
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0));

  // Configure GPIO Pins for UART mode.
  GPIOPinConfigure(GPIO_PA0_U0RX);
  GPIOPinConfigure(GPIO_PA1_U0TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

  // Initialize the UART for console I/O.
  UARTStdioConfig(0, 9600, SystemCoreClock);
} // UARTInit

void UART0_Handler(void){
  UARTStdioIntHandler();
} // UART0_Handler

void GPIOInicialization(void){
  ///GPIO A///////////////////////////////
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); //Habilita o GPIO A
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)); // Aguarda final da habilitação
  GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_6 | GPIO_PIN_7); //A7 = led 1 e a6 = led 2
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6); 
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);
  ///GPIO B/////////////////////////////////
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); //Habilita o GPIO B (TRANSISTOR DOS DISPLAYS)
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB));  // Aguarda final da habilitação
  GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5); //PB4 = DS1 e PB 5 = DS2
  GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0); //DEIXA DESATIVADO
  GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0);
  /// GPIO F/////////////////////////////
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Habilita GPIO F (LED D3 = PF4, LED D4 = PF0)
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)); // Aguarda final da habilitação
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4); // LEDs D3 e D4 como saída
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, 0); // LEDs D3 e D4 apagados
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);
  ///GPIO J//////////////////////////////
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ); // Habilita GPIO J (push-button SW1 = PJ0, push-button SW2 = PJ1)
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ)); // Aguarda final da habilitação
  GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1); // push-buttons SW1 e SW2 como entrada
  GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
  ///GPIO M////////////////////////////////
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM); //Habilita o GPIO M (transistor dos LED's)
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOM)); // Aguarda final da habilitação
  GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, GPIO_PIN_6); //pino que esta no transistor
  GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_6, GPIO_PIN_6); //ativa o PM6
  //GPIOPadConfigSet(GPIO_PORTM_BASE, GPIO_PIN_6, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);
  ///GPIO N/////////////////////////////////
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION); // Habilita GPIO N (LED D1 = PN1, LED D2 = PN0)
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)); // Aguarda final da habilitação
  GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1); // LEDs D1 e D2 como saída
  GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1, 0); // LEDs D1 e D2 apagados
  GPIOPadConfigSet(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);
  ///GPIO Q////////////////////////////////
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ); //Habilita GPIO Q
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOQ)); // Aguarda final da habilitação
  GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE, GPIO_PIN_0 | GPIO_PIN_1); //Q0 led 8 e Q1 led 7
  GPIOPinWrite(GPIO_PORTQ_BASE, GPIO_PIN_0, GPIO_PIN_0); 
  GPIOPinWrite(GPIO_PORTQ_BASE, GPIO_PIN_1, GPIO_PIN_1); 
  //GPIOPadConfigSet(GPIO_PORTQ_BASE, GPIO_PIN_0 | GPIO_PIN_1 , GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);  
}

void main(void){
  
  UARTInit();
  SysTickPeriodSet(12000000); // f = 1Hz para clock = 24MHz
  
  GPIOInicialization();
  SysTickIntEnable();
  SysTickEnable();

  int i, ToLog, PWM, Previous_State;
  GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1); // Acende LED D1

  ToLog = (GPIOPinRead(GPIO_PORTM_BASE, GPIO_PIN_6));
  UARTprintf ("gpio M 6 %d\n", ToLog);
  ToLog = (GPIOPinRead(GPIO_PORTQ_BASE, GPIO_PIN_0));
  UARTprintf ("gpio Q 0 %d\n", ToLog);
  ToLog = (GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_6));
  UARTprintf ("gpio A 6 %d\n", ToLog);
  PWM = 500;
  UARTprintf("Starting PWM value = %d%%\n", PWM/10);
  Previous_State = ((GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_1)) && (GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_0))); //le o estado inicial dos botoes
  while(1){
    for (i=0;i<1000;i++){
      if(i==0 && PWM !=0)
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0); // Acende LED D4
      else if (i==PWM)
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0); // Apaga LED D4
      if (!Previous_State)//ve se precisa ler novamente ou nao (caso SW1 e SW2 estejam soltos, nao le novamente)
        Previous_State = ((GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_1)) && (GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_0)));
      if (Previous_State){
        if (GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_1) == 0){ //testa se o SW2 foi pressionado
          if(PWM!=1000){
            PWM += 100;
            UARTprintf("SW2 pressed and PWM = %d%%\n", PWM/10);
            Previous_State = 0; //algum botao pressionado, seta como 0 e entao o && entre os botoes sera zero e ele nao ira entrar novamente no previous state
          }
        }   
        if ((GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_0) == 0)){ //testa se o SW1 foi pressionado
          if (PWM!=0){
            PWM -= 100;
            UARTprintf("SW1 pressed and PWM = %d%%\n", PWM/10);
            Previous_State = 0;
          } //if
        } //if
      } //if
    } // for
    i=0;    
  } //while
   // UARTprintf("%d", Previous_State);
} // main