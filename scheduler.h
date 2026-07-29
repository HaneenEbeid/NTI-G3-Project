#ifndef SCHEDULER_H
#define SCHEDULER_H

// تهيئة جدول المهام
void SCHEDULER_Init(void);

// الدالة الرئيسية التي يتم استدعاؤها بانتظام لتنفيذ المهام المجدولة
void SCHEDULER_Dispatch(void);

#endif