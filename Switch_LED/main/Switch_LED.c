#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    // สร้างตัวแปรเพื่อเก็บสถานะของสวิตช์และ LED
    int SW1_Status = 0;
    int LED1_Status = 0;
    int SW2_Status = 0;
    int LED2_Status = 0;

    // 1. ตั้งค่า GPIO 16,17 เป็น Output สำหรับ LED
    gpio_set_direction(16, GPIO_MODE_OUTPUT);
    gpio_set_direction(17, GPIO_MODE_OUTPUT);

    // 2. ตั้งค่า GPIO 15,18 เป็น Input สำหรับ Switch
    gpio_set_direction(15, GPIO_MODE_INPUT);
    gpio_set_direction(18, GPIO_MODE_INPUT);

    while (1)
    {
        // อ่านค่าจากสวิตช์
        SW1_Status = gpio_get_level(15);
        SW2_Status = gpio_get_level(18);

        // กดปุ่ม = ไฟติด (กลับ logic ด้วย !)
        LED1_Status = !SW1_Status;
        LED2_Status = !SW2_Status;

        // ส่งค่าไปที่ LED
        gpio_set_level(16, LED1_Status);
        gpio_set_level(17, LED2_Status);

        // delay เล็กน้อย
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
