# 引脚
| ID   | Type |
| ---- | ---- |
| AIN1 | GPIO |
| AIN2 | GPIO |
| BIN1 | GPIO |
| BIN2 | GPIO |
| PWMA | PWM  |
| PWMB | PWM  |

# 真值表
TB6612与普通H桥不同的地方在于他用4个GPIO换到了2路PWM信号。
当然 理论上你也可以吧PWMA PWMB接高电平当普通H桥使用。
不过本库是针对PWMA PWMB提供信号的接线方法的库。

真值表:
```
PWMA -> 通道A PWM信号
PWMB -> 通道B PWM信号

AIN1, AIN2 -> 通道A正反转信号
BIN1, BIN2 -> 通道B正反转信号
```
**Channel A**
| 引脚 | 电平  | 电平 | 电平 | 电平 |
| ---- | ---- | ---- | ---- | ---- |
| AIN1 | 1    | 0    | 1    | 0    |
| AIN2 | 0    | 1    | 1    | 0    |
| 状态 | 反转  | 正转 | 刹车 | 悬空 |
**Channel B**
| 引脚 | 电平  | 电平 | 电平 | 电平 |
| ---- | ---- | ---- | ---- | ---- |
| BIN  | 1    | 0    | 1    | 0    |
| BIN2 | 0    | 1    | 1    | 0    |
| 状态 | 反转  | 正转 | 刹车 | 悬空 |

# Example
```
#include "TB6612.h"

int main()
{
    TB6612_t motor;

	motor.TimPort = TIM4;
	motor.PWMA_Channel = LL_TIM_CHANNEL_CH1;
	motor.PWMB_Channel = LL_TIM_CHANNEL_CH2;

	motor.AIN1Port = GPIOB;
	motor.AIN1Pin  = LL_GPIO_PIN_15;

	motor.AIN2Port = GPIOB;
	motor.AIN2Pin  = LL_GPIO_PIN_14;

	motor.BIN1Port = GPIOB;
	motor.BIN1Pin  = LL_GPIO_PIN_13;

	motor.BIN2Port = GPIOB;
	motor.BIN2Pin  = LL_GPIO_PIN_12;

    motor.DeadZone = 0;
	motor.MaxPWM_Value = 1000;

	TB6612Init(&motor);

    SetPWMA_Value(&motor, 500);
}
```