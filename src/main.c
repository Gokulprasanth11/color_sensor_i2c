/* 
 * Copyright (c) 2025
 * GOKUL PRASANTH(GP😉) 
 * All rights reserved.
 */
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/devicetree.h>
#include <zephyr/sys/printk.h>

#define SYSTEM_CONTROL 0x40
#define MODE_CONTROL1  0x41
#define MODE_CONTROL2  0x42
#define MODE_CONTROL3  0x44
#define RED_DATA_LSB   0x50

#define BH1745NUB_CONTROL1_DEFAULT  0x00
#define BH1745NUB_CONTROL2_DEFAULT  0x90
#define BH1745NUB_CONTROL3_DEFAULT  0x02

#define COLOR_SENSOR DT_NODELABEL(bh1745nuc)

int main(){
    //Initialize the I2C sensor
    static const struct i2c_dt_spec color_sensor_dev = I2C_DT_SPEC_GET(COLOR_SENSOR);
    if(!device_is_ready(color_sensor_dev.bus)){
        printk("Color sensor/I2C bus %s is not ready!\n\r", color_sensor_dev.bus->name);
        return -1;
    };
    
    int ret;

    char buff1[]={MODE_CONTROL1, BH1745NUB_CONTROL1_DEFAULT};
    ret = i2c_write_dt(&color_sensor_dev, buff1, sizeof(buff1));
    if(ret !=0){
        printk("Failed to write to I2C device address 0x%X at registor 0x%X\n",color_sensor_dev.addr, MODE_CONTROL1);
    }

    char buff2[]={MODE_CONTROL2, BH1745NUB_CONTROL2_DEFAULT};
    ret = i2c_write_dt(&color_sensor_dev, buff2, sizeof(buff2));
    if(ret !=0){
        printk("Failed to write to I2C device address 0x%X at registor 0x%X\n",color_sensor_dev.addr, MODE_CONTROL2);
    }

    char buff3[]={MODE_CONTROL3, BH1745NUB_CONTROL3_DEFAULT};
    ret = i2c_write_dt(&color_sensor_dev, buff3, sizeof(buff3));
    if(ret !=0){
        printk("Failed to write to I2C device address 0x%X at Reg. 0x%X\n",color_sensor_dev.addr, MODE_CONTROL2);
    }

    while(1){
        uint8_t rgb_val[6]={0};
        ret = i2c_burst_read_dt(&color_sensor_dev, RED_DATA_LSB, rgb_val, sizeof(rgb_val));
        if(ret!=0){
            printk("Failed to read to I2C device address 0x%c at Reg. 0x%c\n",color_sensor_dev.addr, RED_DATA_LSB);
        }
        uint16_t red_value   = rgb_val[0] | (rgb_val[1] << 8);
        uint16_t green_value = rgb_val[2] | (rgb_val[3] << 8);
        uint16_t blue_value  = rgb_val[4] | (rgb_val[5] << 8);

        printk("___________________________________\n");
        printk("Red Value: %d\n",   red_value);
        printk("Green Value: %d\n", green_value);
        printk("Blue Value: %d\n",  blue_value);
    }
    return 0;
} 