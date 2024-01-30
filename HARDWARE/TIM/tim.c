#include "stm32f4xx.h" 
// ���嶨ʱ����
typedef struct {
    TIM_HandleTypeDef* htim; // ��ʱ�����
    uint16_t arr;           // �Զ���װ�ؼĴ���
    uint16_t psc;           // Ԥ��Ƶ��
    uint32_t counter;       // ������ֵ
} Timer3;
// ��ʼ����ʱ��
void Timer3::Init(uint16_t arr, uint16_t psc) {
    // ��ʼ����ʱ�����
    this->htim = new TIM_HandleTypeDef();
    // ���ö�ʱ������
    this->arr = arr;
    this->psc = psc;
    this->counter = 0;
    // ���ö�ʱ��
    TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    TIM_BaseInitStructure.TIM_Period = arr - 1;
    TIM_BaseInitStructure.TIM_Prescaler = psc - 1;
    TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM3, &TIM_BaseInitStructure);
    // �����ж�
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    // ʹ�ܶ�ʱ�������ж�
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    // ������ʱ��
    TIM_Cmd(TIM3, ENABLE);
}
// �жϴ�����
void TIM3_IRQHandler(void) {
    // ��ȡ��ʱ�����
    Timer3* timer = reinterpret_cast<Timer3*>(TIM3->Instance);
    // �������ж�
    if (TIM_GetITStatus(timer->htim, TIM_IT_Update) == SET) {
        timer->counter++; // ���Ӽ�����
    }
    // ����жϱ�־λ
    TIM_ClearITPendingBit(timer->htim, TIM_IT_Update);
}
int main(void) {
    // ʵ������ʱ������
    Timer3 timer3;
    // ��ʼ����ʱ��
    timer3.Init(1000, 72 - 1); // ����ϵͳʱ��Ϊ72MHz������ARRΪ1000��PSCΪ72-1
    // ... ����ĳ������ ...
    while (1) {
        
    }
}