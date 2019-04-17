/************************************************************************/
/* Author: Marc Spieler                                                 */
/* Team: noOS                                                           */
/* Created: 30.03.2019                                                  */
/************************************************************************/

#include "sd.h"
#include "asf.h"
#include "string.h"
#include "timing.h"
#include "lcd.h"
#include "menu.h"
#include "comm.h"
#include "compass.h"

char test_file_name[] = "0:sd_mmc_test.txt";
Ctrl_status status;
FRESULT res;
FATFS fs;
FIL file_object;

void sd_init(void)
{
    do
    {
        status = sd_mmc_test_unit_ready(0);
        
        if (CTRL_FAIL == status)
        {
            while (CTRL_NO_PRESENT != sd_mmc_check(0));
        }
    } while (CTRL_GOOD != status);

    memset(&fs, 0, sizeof(FATFS));
    res = f_mount(LUN_ID_SD_MMC_0_MEM, &fs);
        
    if (FR_INVALID_DRIVE == res)
    {
        while(1);
    }

    test_file_name[0] = LUN_ID_SD_MMC_0_MEM + '0';
}

void open_file_match(void)
{
    res = f_open(&file_object, (char const *)test_file_name, FA_CREATE_ALWAYS | FA_WRITE);
    
    if (res != FR_OK)
    {
        while(1);
    }
}

void close_file_match(void)
{
    f_close(&file_object);
}

void write_data(void)
{
    uint32_t bytes_written;
    //uint32_t start_time = getTicks();
    ioport_set_pin_level(LED_ONBOARD, 0);

    for(int i = 0; i < 10000; i++)
    {
        f_write(&file_object, "Test SD/MMC stack\n", 18, &bytes_written);
    }
    
    //uint32_t diff = getTicks() - start_time;
    close_file_match();
}

void write_time_test(void)
{
    res = f_open(&file_object, (char const *)test_file_name, FA_CREATE_ALWAYS | FA_WRITE);
    
    if (res != FR_OK)
    {
        while(1);
    }

    uint32_t bw;
    uint32_t sta;
    uint32_t diff = 0;
    char sprintf_buf[8];
    set_led(LED_ONBOARD, 0);
    for(int i = 0; i < 10000; i++)
    {
        sta = getTicks();
        sprintf(sprintf_buf, "%4d\r\n", (int)diff);
        f_write(&file_object, sprintf_buf, strlen(sprintf_buf), &bw);
        //f_sync(&file_object);
        diff = getTicks() - sta;
    }
    sta = getTicks();
    f_sync(&file_object);
    diff = getTicks() - sta;
    f_write(&file_object, "\r\n", 2, &bw);
    sprintf(sprintf_buf, "%4d\r\n", (int)diff);
    f_write(&file_object, sprintf_buf, strlen(sprintf_buf), &bw);
    f_close(&file_object);
    set_led(LED_ONBOARD, 1);
    while(1);
}