#include "contiki.h"
#define SECONDSRED 5
#define SECONDSBLUE 3
#define SECONDSGREEN 7
#include "dev/button-sensor.h"
#include "dev/leds.h"
#include <stdio.h> 

PROCESS(exercise_2_process, "Excercise 2 IoT");
AUTOSTART_PROCESSES(&exercise_2_process);

PROCESS_THREAD(exercise_2_process, ev, data)
{
  PROCESS_BEGIN();
  static unsigned char btn;
  static struct etimer etR;
  static struct etimer etG;
  static struct etimer etB;
  SENSORS_ACTIVATE(button_sensor);  
  etimer_set(&etB, CLOCK_SECOND*SECONDSBLUE);
  etimer_set(&etR, CLOCK_SECOND*SECONDSRED);
  etimer_set(&etG, CLOCK_SECOND*SECONDSGREEN);
  btn = 0;
  while (1) {
	PROCESS_WAIT_EVENT();
	if((ev == PROCESS_EVENT_TIMER)&&(btn)){
		if(etimer_expired(&etB)){
			leds_toggle(LEDS_BLUE);
			//printf("pasaron 3 segundos!\n");
			etimer_reset(&etB);
		}
		else if(etimer_expired(&etR)){
			leds_toggle(LEDS_RED);
			//printf("pasaron 5 segundos!\n");
			etimer_reset(&etR);
		}
		else if(etimer_expired(&etG)){
			leds_toggle(LEDS_GREEN);
			//printf("pasaron 7 segundos!\n");
			etimer_reset(&etG);
		}
	}else if((ev == sensors_event) && (data == &button_sensor)){
		//printf("Boton apretado\n");
		if (btn) btn = 0;
		else {
		  btn = 1;
		  etimer_reset(&etB);
		  etimer_reset(&etR);
		  etimer_reset(&etG);		
		}				
		//printf("%d\n", btn);
	}
  }
  PROCESS_END();
}
