/*
* SETR  23/24
* Hugo Verde, 72705, verde.hugo@ua.pt
*
* Implementation of a Vending Machine (Assignment_3)
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "../VendMachine/src/sc_types.h"
#include "../VendMachine/src-gen/VM.h"
#include "../VendMachine/src-gen/VM_required.h"	// Prototypes of external functions called by the SM
#include <zephyr/kernel.h>          /* for k_msleep() */
#include <zephyr/device.h>          /* for device_is_ready() and device structure */
#include <zephyr/devicetree.h>		/* for DT_NODELABEL() */
#include <zephyr/drivers/gpio.h>    /* for GPIO api*/

VM VMStateMachine;	// The statemachine structure variable

#define EVT_COIN1 	// Botão 1 
#define EVT_COIN2	// Botão 2
#define EVT_BROWSE	// Botão 3
#define EVT_ENTER	// Botão 4 

/* Get led0 ... led3 and button0..button3 node IDs. Refer to the DST file*/
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)
#define BUT0_NODE DT_ALIAS(sw0)
#define BUT1_NODE DT_ALIAS(sw1)
#define BUT2_NODE DT_ALIAS(sw2)
#define BUT3_NODE DT_ALIAS(sw3)

/* Get the device pointer, pin number, and configuration flags for led1..led4 and button 1... button4. A build error on this line means your board is unsupported. */

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec led3 = GPIO_DT_SPEC_GET(LED3_NODE, gpios);

static const struct gpio_dt_spec but0 = GPIO_DT_SPEC_GET(BUT0_NODE, gpios);
static const struct gpio_dt_spec but1 = GPIO_DT_SPEC_GET(BUT1_NODE, gpios);
static const struct gpio_dt_spec but2 = GPIO_DT_SPEC_GET(BUT2_NODE, gpios);
static const struct gpio_dt_spec but3 = GPIO_DT_SPEC_GET(BUT3_NODE, gpios);



void buttonPressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {

  if (pins & but0.pin) {
    vM_but_raise_coin1(&VMStateMachine); // Raise coin1 event
  } else if (pins & but1.pin) {
    vM_but_raise_coin2(&VMStateMachine); // Raise coin2 event
  } else if (pins & but2.pin) {
    vM_but_raise_browse(&VMStateMachine); // Raise browse event
  } else if (pins & but3.pin) {
    vM_but_raise_enter(&VMStateMachine); // Raise enter event
  } else {
    // Handle unexpected pin interrupt (optional)
  }
}



int main(void){

	int ret =0;
	
	

	
	/* Check if devices are ready */
	if (!device_is_ready(led1.port) || !device_is_ready(led2.port) || !device_is_ready(led3.port)  || !device_is_ready(led4.port) || !device_is_ready(but0.port) || !device_is_ready(but1.port) || !device_is_ready(but2.port) || !device_is_ready(but3.port)) {
		return 0;
	}	

	/* Configure the GPIO pins for input/output and set active logic */
	/* Note that the devicetree activates the internal pullup and sets the active low flag */
	/*   so an external resistor is not needed and pressing the button causes a logic level of 1*/

	ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_INACTIVE);
	ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);
	ret = gpio_pin_configure_dt(&led2, GPIO_OUTPUT_INACTIVE);
	ret = gpio_pin_configure_dt(&led3, GPIO_OUTPUT_INACTIVE);

	if (ret < 0) {
		return 0;
	}


	ret = gpio_pin_configure_dt(&but0, GPIO_INPUT);
	ret = gpio_pin_configure_dt(&but1, GPIO_INPUT);
	ret = gpio_pin_configure_dt(&but2, GPIO_INPUT);
	ret = gpio_pin_configure_dt(&but3, GPIO_INPUT);
	if (ret < 0) {
		return 0;
	}

	/* Set interrupt */
	ret = gpio_pin_interrupt_configure_dt(&but0, GPIO_INT_EDGE_TO_ACTIVE);
	ret = gpio_pin_interrupt_configure_dt(&but1, GPIO_INT_EDGE_TO_ACTIVE);
	ret = gpio_pin_interrupt_configure_dt(&but2, GPIO_INT_EDGE_TO_ACTIVE);
	ret = gpio_pin_interrupt_configure_dt(&but3, GPIO_INT_EDGE_TO_ACTIVE);

	
	/* Add the callback function by calling gpio_add_callback()   */
	gpio_add_callback(but.port, &button0CbData);
	ret = gpio_pin_interrupt_callback_set(&but0, buttonPressed);
	ret = gpio_pin_interrupt_callback_set(&but1, buttonPressed);
	ret = gpio_pin_interrupt_callback_set(&but2, buttonPressed);
	ret = gpio_pin_interrupt_callback_set(&but3, buttonPressed)


	// Initilize the state machine
	vM_init(&VMStateMachine);

	// Enter the state machine 
	vM_enter(&VMStateMachine);

	
	// Process button press events in the state machine
  	vM_handle_event(&VMStateMachine);

	// Example function to update LEDs based on state and credit
	while(1){

		// Process button press events in the state machine
        vM_handle_event(&VMStateMachine);
	
		// delay to avoid busy waiting
        k_msleep(10);

  		switch (VMStates) {
    	case VM_main_region_IDLE:
      	// Turn on all LEDS to indicate machine is ready
		gpio_pin_write(led0.port, led0.pin, 1);  /
      	gpio_pin_write(led1.port, led1.pin, 1);
      	gpio_pin_write(led2.port, led2.pin, 1);
      	gpio_pin_write(led3.port, led3.pin, 1);

		printk("Bem Vindo, máquina pronta para o servir");


      	break;
    	case VM_main_region_product_browse:
      	// Turn on LED0 and LED1

		gpio_pin_write(led0.port, led0.pin, 1);
      	gpio_pin_write(led1.port, led1.pin, 1);
      	gpio_pin_write(led2.port, led2.pin, 0);
      	gpio_pin_write(led3.port, led3.pin, 0);
     
      	break;
    	case VM_main_region_product_dispense:
      	// Turn on product dispense LED (LED2) ????
		gpio_pin_write(led0.port, led0.pin, 0);
      	gpio_pin_write(led1.port, led1.pin, 0);
      	gpio_pin_write(led2.port, led2.pin, 1);
      	gpio_pin_write(led3.port, led3.pin, 0);
      	break;
    	case VM_main_region_return_credit:
      	// Turn on credit return LED (LED3)
		gpio_pin_write(led0.port, led0.pin, 0);
      	gpio_pin_write(led1.port, led1.pin, 0);
      	gpio_pin_write(led2.port, led2.pin, 0);
      	gpio_pin_write(led3.port, led3.pin, 1);

      break;
	}
  }
  
	vM_exit(&VMStateMachine);

	/* At this stage, input events are capture via interruption
	   and processed by ...? */
	return 0;
}


/******************************************************************
* Implementation of externnal functions valled by the statemachine
* In this case, product selected and credit returned 
*/
void VM_select_product(const sc_integer product)
{
	
	printf("Product %d selected ! \n", product);
	
}

void VM_return_credit(const sc_integer credit)
{

	printf("Credit %d returned!", credit);
	
}
