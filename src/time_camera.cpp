#include <time_camera.h>


void tick(int signo)
{
    // 使用二级指针删进行单链表的删除
    struct timer_node **cur = &timer.slot[timer.current];
    while (*cur) {
        struct timer_node *curr = *cur;
        if (curr->rotation > 0) {
            curr->rotation--;
            cur = &curr->next;
        } else {
            curr->proc();
            *cur = curr->next;
            free(curr);
        }
    }
    timer.current = (timer.current + 1) % TIME_WHEEL_SIZE;
    alarm(1);
}

void add_timer(int len, func action)
{
    int pos = (len + timer.current) % TIME_WHEEL_SIZE;
    struct_timer_node *node = (struct_timer_node*)malloc(sizeof(struct timer_node));

    // 插入到对应格子的链表头部即可, O(1)复杂度
    node->next = timer.slot[pos];
    timer.slot[pos] = node;
    node->rotation = len / TIME_WHEEL_SIZE;
    node->flag = 0;
    node->proc = action;
}

tm* Get_systemTime()
{
  time_t tt;
  time( &tt );
  tt = tt + 8*3600;  // transform the time zone
  tm* t= gmtime( &tt );
  t->tm_year += 1900;
  t->tm_mon += 1;
  return t;
}
