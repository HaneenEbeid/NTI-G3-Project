#include "scheduler.h"
#include <avr/io.h>

// دالة تهيئة المهام (تُستدعى مرة واحدة في البداية)
void SCHEDULER_Init(void)
{
    // تهيئة أي مؤقتات (Timers) أو إعدادات أولية للجدول الزمني إن وجدت
}

// دالة إدارة وتنفيذ المهام بشكل دوري (Super Loop Schedule)
void SCHEDULER_Dispatch(void)
{
    // هنا يتم وضع المهام التي ستعمل بانتظام
    // مثال: 
    // 1. قراءة لوحة المفاتيح (Keypad Task)
    // 2. تحديث نظام الأمان (Security Task)
    // 3. تحديث الشاشة أو الليدات (Display/LED Task)
}
