/************************************************************************/
/* Author: Marc Spieler                                                 */
/* Team: noOS                                                           */
/* Created: 24.04.2019                                                  */
/************************************************************************/

#include "support.h"
#include "comm.h"

dictionary* noOS_ini_dict;

uint16_t robot_id = 1;
uint16_t speed_preset = 15;
Bool heartbeat = false;
Bool allow_leds = true;

inline void set_led(ioport_pin_t pin, Bool level)
{
    if (allow_leds)
    {
        ioport_set_pin_level(pin, level);
    }
    else
    {
        ioport_set_pin_level(pin, 0);
    }
}

void create_default_ini_file(void)
{
    FIL noOS_ini_file;

    if (f_open(&noOS_ini_file, "noOS.ini", FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
    {
        while(1);
    }

    f_printf(&noOS_ini_file,
    "[general]\n"\
    "robot_id = 1\n"\
    "speed = 15\n"\
    "heartbeat = 0\n"\
    "line_cal = 12\n");
    f_close(&noOS_ini_file);
}

void parse_ini_file(void)
{
    //char val;

    noOS_ini_dict = iniparser_load("noOS.ini");

    if (noOS_ini_dict==NULL)
    {
        //fprintf(stderr, "cannot parse file: %s\n", "noOS.ini");
        set_led(LED_M3, 1);
        while(1);
    }

    if(noOS_ini_dict->n == 0)
    {
        create_default_ini_file();
        noOS_ini_dict = iniparser_load("noOS.ini");
    }
    robot_id = iniparser_getint(noOS_ini_dict, "general:robot_id", 1);
    speed_preset = iniparser_getint(noOS_ini_dict, "general:speed", 15);
    heartbeat = iniparser_getboolean(noOS_ini_dict, "general:heartbeat", false);
    mts.line_cal_value = iniparser_getint(noOS_ini_dict, "general:line_cal", 12);
}