#include "stm32f4xx.h" 
// 定义定时器类
typedef struct {
    TIM_HandleTypeDef* htim; // 定时器句柄
    uint16_t arr;           // 自动重装载寄存器
    uint16_t psc;           // 预分频器
    uint32_t counter;       // 计数器值
} Timer3;
// 初始化定时器
void Timer3::Init(uint16_t arr, uint16_t psc) {
    // 初始化定时器句柄
    this->htim = new TIM_HandleTypeDef();
    // 设置定时器参数
    this->arr = arr;
    this->psc = psc;
    this->counter = 0;
    // 配置定时器
    TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    TIM_BaseInitStructure.TIM_Period = arr - 1;
    TIM_BaseInitStructure.TIM_Prescaler = psc - 1;
    TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM3, &TIM_BaseInitStructure);
    // 配置中断
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    // 使能定时器更新中断
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    // 启动定时器
    TIM_Cmd(TIM3, ENABLE);
}
// 中断处理函数
void TIM3_IRQHandler(void) {
    // 获取定时器句柄
    Timer3* timer = reinterpret_cast<Timer3*>(TIM3->Instance);
    // 检查更新中断
    if (TIM_GetITStatus(timer->htim, TIM_IT_Update) == SET) {
        timer->counter++; // 增加计数器
    }
    // 清除中断标志位
    TIM_ClearITPendingBit(timer->htim, TIM_IT_Update);
}
int main(void) {
    // 实例化定时器对象
    Timer3 timer3;
    // 初始化定时器
    timer3.Init(1000, 72 - 1); // 假设系统时钟为72MHz，设置ARR为1000，PSC为72-1
    // ... 其余的程序代码 ...
    while (1) {
        
    }
}