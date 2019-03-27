#ifndef __WWDG_H__
#define __WWDG_H__

extern void wwdg_init(void);
extern void wwdg_kick(void);
extern int wwdg_is_reset(void);
extern void Watchdog_WWDGIsr(void);

#endif /* end of __WWDG_H__ */
