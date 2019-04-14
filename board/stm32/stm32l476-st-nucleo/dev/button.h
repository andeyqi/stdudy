#ifndef __BUTTON_H__
#define __BUTTON_H__
typedef void(*button_callback)(void);
extern void button_init(void);
extern void Buttons_Exti13Isr(void);
extern void register_user_button_func(button_callback func);
#endif /* end of __BUTTON_H__ */
