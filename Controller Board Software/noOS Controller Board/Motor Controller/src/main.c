/************************************************************************/
/* Author: Marc Spieler                                                 */
/* Team: noOS                                                           */
/* Created: 01.07.2018                                                  */
/************************************************************************/

#include "asf.h"
#include "string.h"
#include "timing.h"
#include "lcd.h"
#include "menu.h"
#include "comm.h"
#include "compass.h"
#include "sd.h"
#include "motor.h"
#include "iniparser.h"
#include "support.h"
#include "math.h"

Bool blink_level;
uint32_t ticks_blink_update;
uint32_t ticks_dot_update;
uint8_t dots = 0;
Bool update_dots = 1;

uint8_t trn = 5;

void noOS_bootup_sequence(void);

int main(void)
{
    event_t act_event;

    sysclk_init();

    board_init();
    SysTick_Config(sysclk_get_cpu_hz() / 1000);
    
    //motor_init();
    //init_battery_warning();

    //sd_mmc_init();
    //sd_init();
    //write_time_test_2();
    //create_default_ini_file();
    //parse_ini_file();
    //set_led(LED_ONBOARD, 1);
    //while(1);
    //spi_init();
    
    //compass_init();
    //lcd_init();

    //noOS_bootup_sequence();
    while (ioport_get_pin_level(PB_MID) == 1);
    motor_init();
    enable_motor();
    //disable_motor();
	//mts.line_cal_value = 7;

    while (1)
    {
        #if 1
            float dir = -30;
            float robot_speed = 30;
            dir *= (3.14159265359f / 180.0f);
        
            mleft = robot_speed * (cos(dir) * CosinMA1 - sin(dir) * SinMA1);
            mright = robot_speed * (cos(dir) * CosinMA2 - sin(dir) * SinMA2);
            mrear = robot_speed * (cos(dir) * CosinMA3 - sin(dir) * SinMA3);
        
            /*mleft += (float)rel_deviation;
            mright += (float)rel_deviation;
            mrear += (float)rel_deviation;*/
        
            update_motor(mleft, mright, mrear);
            while (ioport_get_pin_level(PB_RETURN) == 1);
            update_motor(0, 0, 0);
            while(1);
        #else
        
            /*update_comm();
            update_heartbeat();
            check_battery();
        
            if (stm.ibit.heartbeat)
            {
                set_led(LED_M2, 1);
            }
            else
            {
                set_led(LED_M2, 0);
            }*/

            update_motor(trn, trn, trn);
            mdelay(1000);
            update_motor(-trn, -trn, -trn);
            mdelay(1000);
            //PrepareValuesToSend();

            //act_event = button_events();
            //menu(act_event);
        #endif
    }
}

void noOS_bootup_sequence(void)
{
    while (!ioport_get_pin_level(RPI2) && ioport_get_pin_level(PB_MID))
    {
        if (getTicks() >= (ticks_blink_update + 800))
        {
            ticks_blink_update = getTicks();
            
            if (blink_level)
            {
                blink_level = 0;
            }
            else
            {
                blink_level = 1;
            }
            
            ioport_set_pin_level(LED_BAT, blink_level);
        }
        
        if (getTicks() >= (ticks_dot_update + 500))
        {
            ticks_dot_update = getTicks();
            
            if (dots < 3)
            {
                dots++;
            }
            else
            {
                dots = 0;
            }
            
            update_dots = 1;
        }
        
        if (update_dots)
        {
            update_dots = 0;
            
            switch (dots)
            {
                case 0:
                lcd_print_s(2, 2, "booting noOS   ");
                break;
                case 1:
                lcd_print_s(2, 14, ".");
                break;
                case 2:
                lcd_print_s(2, 15, ".");
                break;
                case 3:
                lcd_print_s(2, 16, ".");
                break;
                default:
                break;
            }
        }
    }
    
    for(int i = 0; i< 3; i++)
    {
        ioport_set_pin_level(LED_ONBOARD, 1);
        ioport_set_pin_level(LED_BAT, 1);
        ioport_set_pin_level(LED_M1, 1);
        ioport_set_pin_level(LED_M2, 1);
        ioport_set_pin_level(LED_M3, 1);
        mdelay(100);
        ioport_set_pin_level(LED_ONBOARD, 0);
        ioport_set_pin_level(LED_BAT, 0);
        ioport_set_pin_level(LED_M1, 0);
        ioport_set_pin_level(LED_M2, 0);
        ioport_set_pin_level(LED_M3, 0);
        mdelay(100);
    }
}
