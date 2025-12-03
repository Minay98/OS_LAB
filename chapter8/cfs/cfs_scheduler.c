#include <stdio.h>
#include <stdlib.h>

#include "proc.h"
#include "red_black_tree/rb.h"
#include "red_black_tree/rb_data.h"

/* 1. تعداد پردازه‌ها با define در ابتدای فایل مشخص می‌شود
 *    (عدد فعلی 3 است، در صورت نیاز می‌توانید آن را تغییر دهید).
 */
#define PROCESS_COUNT 3

/* 2. تابع fill_process_array
 * ورودی: آرایه‌ای از اشاره‌گر به process که خالی است.
 * خروجی: این آرایه را با پردازه‌ها پر می‌کند.
 *
 * صورت سؤال نمونه‌کدی شبیه زیر داده بود که دانشجو باید خودش آن را کامل کند:
 *
 *  void fill_process_array(process *process_array[PROCESS_COUNT]){
 *      for(int i = 0; i < PROCESS_COUNT; i++){
 *          // process_array[i] = create_process(...);
 *      }
 *  }
 */
void fill_process_array(process *process_array[PROCESS_COUNT]) {
    /* TODO: این تابع را طبق صورت تمرین پیاده‌سازی کنید. */
}

/* 3. تابع insert_one_process_to_rbtree
 * یک process را به tree red-black اضافه می‌کند.
 *
 * طبق صورت تمرین، کدی شبیه زیر باید نوشته شود:
 *
 *  void insert_one_process_to_rbtree(rbtree *rbt, process* proc){
 *      mydata *data = makedata_with_object(proc->vruntime, proc);
 *      if(rb_insert(rbt, data) == NULL){
 *          fprintf(stderr, "insert %d: out of memory\n", proc->id);
 *      }
 *  }
 */
void insert_one_process_to_rbtree(rbtree *rbt, process *proc) {
    /* TODO: این تابع را طبق صورت تمرین پیاده‌سازی کنید. */
}

/* 4. تابع insert_processes_to_rbtree
 * همه‌ی process های موجود در آرایه را به tree اضافه می‌کند.
 *
 * صورت سؤال نمونه‌کد زیر را داده بود:
 *
 *  void insert_processes_to_rbtree(rbtree *rbt, process *process_array[PROCESS_COUNT]){
 *      process *proc;
 *      for(int i = 0; i < PROCESS_COUNT; i++){
 *          proc = process_array[i];
 *          insert_one_process_to_rbtree(rbt, proc);
 *      }
 *  }
 */
void insert_processes_to_rbtree(rbtree *rbt, process *process_array[PROCESS_COUNT]) {
    /* TODO: این تابع را طبق صورت تمرین پیاده‌سازی کنید. */
}

/* 5. تابع process_of_node
 * یک rbnode را گرفته و process داخل آن را برمی‌گرداند.
 *
 * طبق صورت سؤال چیزی شبیه:
 *
 *  process* process_of_node(rbnode* node){
 *      process* proc = (process *)((mydata *)(node->data))->object;
 *      return proc;
 *  }
 */
process *process_of_node(rbnode *node) {
    /* TODO: این تابع را طبق صورت تمرین پیاده‌سازی کنید. */
}

/* 6–10. تابع main: پیاده‌سازی حلقه زمان‌بندی CFS
 *
 * طبق صورت تمرین، مراحل به این صورت هستند:
 *
 * 6. تعریف و پرکردن آرایه‌ی پردازه‌ها با استفاده از fill_process_array
 *      process *processes[PROCESS_COUNT];
 *      fill_process_array(processes);
 *      printf("process array filled\n");
 *
 * 7. ساختن red-black tree با rb_create
 *      rbtree *rbt;
 *      if ((rbt = rb_create(compare_func, destroy_func)) == NULL) {
 *          fprintf(stderr, "create red-black tree failed\n");
 *      } else {
 *          printf("tree created\n");
 *      }
 *
 * 8. اضافه کردن پردازه‌های آرایه به درخت با insert_processes_to_rbtree
 *      insert_processes_to_rbtree(rbt, processes);
 *      printf("inserted processes to rbtree\n");
 *
 * 9. تعریف متغیرهای node, current_proc, current_tick
 *      rbnode *node;
 *      process *current_proc;
 *      int current_tick = 0;
 *
 * 10. حلقه‌ی اصلی:
 *      تا وقتی RB_MINIMAL(rbt) تهی نیست:
 *        - گره‌ی با کمترین vruntime را بگیرید
 *        - پردازه‌ی داخل آن را استخراج کنید
 *        - یک tick آن را اجرا کنید (run_process_for_one_tick)
 *        - گره را از درخت حذف کنید (rb_delete)
 *        - اگر پردازه تمام نشده بود، دوباره آن را با vruntime جدید به درخت وارد کنید
 *        - current_tick را در هر بار حلقه افزایش دهید
 */
int main(void) {
    /* TODO [مرحله 6]: آرایه‌ی پردازه‌ها را تعریف کرده و با fill_process_array آن را پر کنید. */

    /* TODO [مرحله 7]: درخت red-black را با rb_create بسازید و پیام مناسب چاپ کنید. */

    /* TODO [مرحله 8]: پردازه‌ها را به درخت اضافه کنید و پیام مناسب چاپ کنید. */

    /* TODO [مرحله 9]: متغیرهای node، current_proc و current_tick را تعریف و مقداردهی اولیه کنید. */

    /* TODO [مرحله 10]:
     *  - یک حلقه‌ی while بنویسید که تا زمانی که RB_MINIMAL(rbt) تهی نیست اجرا شود.
     *  - current_tick را چاپ و افزایش دهید.
     *  - از process_of_node برای گرفتن پردازه‌ی مربوط به node استفاده کنید.
     *  - یک tick پردازه را با run_process_for_one_tick اجرا کنید.
     *  - گره قدیمی را با rb_delete حذف کنید.
     *  - اگر is_terminated(current_proc) صفر بود، دوباره آن را با insert_one_process_to_rbtree وارد درخت کنید.
     *  - در صورت اتمام پردازه، پیامی مناسب چاپ کنید.
     */

    /* در انتها درخت را با rb_destroy آزاد کنید و پیام پایان را چاپ کنید. */

    return 0;
}
