//!
//! C++工具：仿C++STL接口的C风格链表--支持函数泛型
//!
//! == 工具简介 ==
//! 提供纯C风格的链表，操作接口类似C++STL容器，提供泛型宏接口，统一各类型操作
//! 	模板 Tlist_create(Tapi,Tvalue) Tapi是接口定义，Tvalue是具体类型
//! 		模板生成例子：
//! 			Tlist_create(Tint,int)  	->  Tlist_Tint head;
//! 			Tlist_create(Tcharp,char *)  	->  Tlist_Tcharp head;
//! 			Tlist_Tint head;
//! == 工具简介 ==
//!
//!
//! == 展示顺序 ==
//! 1.Tlien_c.h 头文件
//! 2.基本类型与接口测试 main测试
//! 3.字符串测试
//! 4.自定义类型测试
//! 5.参考头文件（用于新功能添加与测试）
//! == 展示顺序 ==
//!
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//===== Tlien_c =====
#define Tlist_for(head,it,Tapi) for(Tlist_##Tapi *it = head.next;it != NULL;it = it->next)
#define Tlist_for_p(head,it,Tapi) for(Tlist_##Tapi *it = head->next;it != NULL;it = it->next)

#define Tlist_create(Tapi,Tvalue)                                                          \
typedef struct Tlist_##Tapi Tlist_##Tapi;                                                   \
struct Tlist_##Tapi                                                                         \
{                                                                                           \
    Tvalue value;                                                                           \
    size_t size;                                                                            \
    Tlist_##Tapi *prev;                                                                     \
    Tlist_##Tapi *next;                                                                     \
};                                                                                          \
                                                                                            \
void list_init_##Tapi(Tlist_##Tapi *head)                                                   \
{                                                                                           \
    if(head == NULL) return;                                                                \
    head->size = 0;                                                                         \
    head->prev = NULL;                                                                      \
    head->next = NULL;                                                                      \
}                                                                                           \
                                                                                            \
void list_push_back_##Tapi(Tlist_##Tapi *head,Tvalue value)                                 \
{                                                                                           \
    if(head == NULL) return;                                                                \
    Tlist_##Tapi *new_value = (Tlist_##Tapi *)malloc(sizeof(Tlist_##Tapi));                 \
    list_init_##Tapi(new_value);                                                            \
                                                                                            \
    if(head->size == 0)                                                                     \
    {                                                                                       \
        head->prev = new_value;                                                             \
        head->next = new_value;                                                             \
        new_value->prev = head;                                                             \
    }                                                                                       \
    else                                                                                    \
    {                                                                                       \
        new_value->prev = head->prev;                                                       \
        head->prev->next = new_value;                                                       \
        head->prev = new_value;                                                             \
    }                                                                                       \
    head->size += 1;                                                                        \
    new_value->value = value;                                                               \
}                                                                                           \
                                                                                            \
void list_push_front_##Tapi(Tlist_##Tapi *head,Tvalue value)                                \
{                                                                                           \
    if(head == NULL) return;                                                                \
    Tlist_##Tapi *new_value = (Tlist_##Tapi *)malloc(sizeof(Tlist_##Tapi));                 \
    list_init_##Tapi(new_value);                                                            \
                                                                                            \
    if(head->size == 0)                                                                     \
    {                                                                                       \
        head->prev = new_value;                                                             \
        head->next = new_value;                                                             \
        new_value->prev = head;                                                             \
    }                                                                                       \
    else                                                                                    \
    {                                                                                       \
        head->next->prev = new_value;                                                       \
        new_value->next = head->next;                                                       \
        new_value->prev = head;                                                             \
        head->next = new_value;                                                             \
    }                                                                                       \
    head->size += 1;                                                                        \
    new_value->value = value;                                                               \
}                                                                                           \
                                                                                            \
int list_insert_##Tapi(Tlist_##Tapi *head,size_t pos,Tvalue value)                          \
{                                                                                           \
    if(head == NULL || pos >= head->size) return 0;                                         \
    Tlist_##Tapi *new_value = (Tlist_##Tapi *)malloc(sizeof(Tlist_##Tapi));                 \
    list_init_##Tapi(new_value);                                                            \
                                                                                            \
    size_t count = 0;                                                                       \
    Tlist_##Tapi *it = head->next;                                                          \
    for(;it != NULL;it = it->next)                                                          \
    {                                                                                       \
        if(count == pos) break;                                                             \
        count++;                                                                            \
    }                                                                                       \
                                                                                            \
    new_value->next = it;                                                                   \
    new_value->prev = it->prev;                                                             \
    it->prev->next = new_value;                                                             \
    it->prev = new_value;                                                                   \
                                                                                            \
    head->size += 1;                                                                        \
    new_value->value = value;                                                               \
    return 1;                                                                               \
}                                                                                           \
                                                                                            \
void list_pop_back_##Tapi(Tlist_##Tapi *head)                                               \
{                                                                                           \
    if(head == NULL || head->size == 0) return ;                                            \
    head->size -= 1;                                                                        \
                                                                                            \
    Tlist_##Tapi *end = head->prev;                                                         \
    head->prev = end->prev;                                                                 \
    end->prev->next = NULL;                                                                 \
    free(end);                                                                              \
}                                                                                           \
                                                                                            \
void list_pop_front_##Tapi(Tlist_##Tapi *head)                                              \
{                                                                                           \
    if(head == NULL || head->size == 0) return ;                                            \
    head->size -= 1;                                                                        \
                                                                                            \
    if(head->size == 0)                                                                     \
    {                                                                                       \
        Tlist_##Tapi *begin = head->next;                                                   \
        head->next = NULL;                                                                  \
        free(begin);                                                                        \
    }                                                                                       \
    else                                                                                    \
    {                                                                                       \
        Tlist_##Tapi *begin = head->next;                                                   \
        head->next = begin->next;                                                           \
        begin->next->prev = head;                                                           \
        free(begin);                                                                        \
    }                                                                                       \
}                                                                                           \
                                                                                            \
int list_erase_##Tapi(Tlist_##Tapi *head,size_t pos)                                        \
{                                                                                           \
    if(head == NULL || head->size == 0 || pos >= head->size) return 0;                      \
    head->size -= 1;                                                                        \
                                                                                            \
    size_t count = 0;                                                                       \
    Tlist_##Tapi *it = head->next;                                                          \
    for(;it != NULL;it = it->next)                                                          \
    {                                                                                       \
        if(count == pos) break;                                                             \
        count++;                                                                            \
    }                                                                                       \
                                                                                            \
    if(pos == head->size || head->size == 0)                                                \
    {                                                                                       \
        Tlist_##Tapi *now = it;                                                             \
        it->prev->next = NULL;                                                              \
        head->prev = it->prev;                                                              \
        free(now);                                                                          \
        return 1;                                                                           \
    }                                                                                       \
                                                                                            \
    Tlist_##Tapi *now = it;                                                                 \
    it->prev->next = it->next;                                                              \
    it->next->prev = it->prev;                                                              \
    free(now);                                                                              \
    return 1;                                                                               \
}                                                                                           \
                                                                                            \
void list_clear_##Tapi(Tlist_##Tapi *head)                                                  \
{                                                                                           \
    if(head == NULL) return;                                                                \
    while(1)                                                                                \
    {                                                                                       \
        Tlist_##Tapi *begin = head->next;                                                   \
        if(begin == NULL) break;                                                            \
        head->next = head->next->next;                                                      \
        free(begin);                                                                        \
    }                                                                                       \
    head->size = 0;                                                                         \
}                                                                                                                                                                                \
//===== Tlien_c =====


typedef struct dire dire;
struct dire
{
    int x;
    int y;
    int z;
};

//== 模板生成 ==
//基本类型
Tlist_create(Tchar,char)
Tlist_create(Tshort,short)
Tlist_create(Tint,int)
Tlist_create(Tlong,long)
Tlist_create(Tlonglong,long long)
Tlist_create(Tfloat,float)
Tlist_create(Tdouble,double)
Tlist_create(Tcharp,char *) //字符串
Tlist_create(Tdire,dire) //自定义类型
//== 模板生成 ==

void list_show_Tint(Tlist_Tint *head)
{
    printf("== size: %ld ==\n",head->size);
    Tlist_for_p(head,it,Tint)
    {
        printf("%d\n",it->value);
    }
    printf("== end ==\n");
}

//基础类型
void test_1()
{
    printf("== test_1 ==\n");

    //提供类似C++STL容器接口的C风格链表，支持泛型
    Tlist_Tint head;
    list_init_Tint(&head); //需要初始化才能使用

    list_push_back_Tint(&head,1);
    list_push_back_Tint(&head,12);
    list_push_back_Tint(&head,123);
    printf("\n== list_push_back ==\n");
    list_show_Tint(&head);

    list_push_front_Tint(&head,100);
    list_push_front_Tint(&head,200);
    list_push_front_Tint(&head,300);
    printf("\n== list_push_front ==\n");
    list_show_Tint(&head);

    list_pop_front_Tint(&head);
    printf("\n== list_pop_front ==\n");
    list_show_Tint(&head);

    list_pop_back_Tint(&head);
    printf("\n== list_pop_back ==\n");
    list_show_Tint(&head);

    list_erase_Tint(&head,2);
    printf("\n== list_pop_back ==\n");
    list_show_Tint(&head);

    list_insert_Tint(&head,2,400);
    printf("\n== list_insert ==\n");
    list_show_Tint(&head);

    list_clear_Tint(&head);
    printf("\n== list_clear ==\n");
    list_show_Tint(&head);
}

void list_show_Tcharp(Tlist_Tcharp *head)
{
    printf("== size: %ld ==\n",head->size);
    Tlist_for_p(head,it,Tcharp)
    {
        printf("%s\n",it->value);
    }
    printf("== end ==\n");
}

char *func_malloc_charp(size_t size,void *data)
{
    char *pstr = (char*)malloc(size);
    char *str = (char*)data;
    strncpy(pstr,str,size);
    return pstr;
}

//字符串
void test_2()
{
    printf("\n== test_2 ==\n");

    Tlist_Tcharp head;
    list_init_Tcharp(&head); //需要初始化才能使用

    list_push_back_Tcharp(&head,"100");
    list_push_back_Tcharp(&head,"101");
    list_push_back_Tcharp(&head,"111");
    list_push_front_Tcharp(&head,"999");
    list_push_front_Tcharp(&head,"888");

    //字符串问题：指针存在的问题，栈内存指向同一块,指针类型需要手动分配内存
    char buf[]="qweqwe";
    list_push_front_Tcharp(&head,buf);
    strcpy(buf,"p1");
    list_push_front_Tcharp(&head,buf);
    strcpy(buf,"p2");
    list_push_front_Tcharp(&head,buf);

    //字符串问题:解决方法
    char *buf2 = (char*)malloc(64);
    strcpy(buf2,"ac_123");
    list_push_front_Tcharp(&head,buf2);

    buf2 = (char*)malloc(64);
    strcpy(buf2,"ac_456");
    list_push_front_Tcharp(&head,buf2);

    buf2 = (char*)malloc(64);
    strcpy(buf2,"ac_789");
    list_push_front_Tcharp(&head,buf2);

    char *buf3 = func_malloc_charp(strlen("1234"),"1234");
    list_push_front_Tcharp(&head,buf3);

    buf3 = func_malloc_charp(strlen("1234qwe"),"1234qwe");
    list_push_front_Tcharp(&head,buf3);

    buf3 = func_malloc_charp(strlen("qweasd"),"qweasd");
    list_push_front_Tcharp(&head,buf3);

    list_show_Tcharp(&head);

    //释放内存
    Tlist_for(head,it,Tcharp)
    {
        free(it);
    }
}

dire build_dire(int x,int y,int z)
{
    dire tm;
    tm.x = x;
    tm.y = y;
    tm .z = z;
    return tm;
}

void list_show_Tdire(Tlist_Tdire *head)
{
    printf("== size: %ld ==\n",head->size);
    Tlist_for_p(head,it,Tdire)
    {
        printf("[%d:%d:%d]\n",it->value.x,it->value.y,it->value.z);
    }
    printf("== end ==\n");
}

dire *func_malloc_dire(size_t size,void *data)
{
    dire *pct = (dire*)malloc(size);
    dire ct = *(dire*)&data;
    pct->x =ct.x;
    pct->y =ct.y;
    pct->z =ct.z;
    return pct;
}

//自定义类型
void test_3()
{
    printf("\n== test_3 ==\n");

    Tlist_Tdire head;
    list_init_Tdire(&head); //需要初始化才能使用

    list_push_back_Tdire(&head,build_dire(0,1,2));
    list_push_back_Tdire(&head,build_dire(1,2,3));
    list_push_back_Tdire(&head,build_dire(3,3,3));
    list_push_front_Tdire(&head,build_dire(9,0,0));
    list_push_front_Tdire(&head,build_dire(123,456,789));

    dire d1 = build_dire(9,9,9);
    list_push_front_Tdire(&head,d1);
    d1.x = 8;
    d1.y = 8;
    d1.z = 8;
    list_push_front_Tdire(&head,d1);
    d1.x = 7;
    d1.y = 7;
    d1.z = 7;
    list_push_front_Tdire(&head,d1);

    list_show_Tdire(&head);
}

int main()
{
    printf("== begin ==\n");
    test_1();
    test_2();
    test_3();
    printf("== end ==\n");
    return 0;
}


#if 0
//===== Tlien_c =====
//遍历宏: 参数为带数据的链表指针
#define Tlist_for(it,head) for(Tlist_c *it = head.next;it != NULL;it = it->next)
#define Tlist_for_p(it,head) for(Tlist_c *it = head->next;it != NULL;it = it->next)

//类型宏
#define Tvalue int

typedef struct Tlist_c Tlist_c;
struct Tlist_c
{
    Tvalue value;
    size_t size;
    Tlist_c *prev;
    Tlist_c *next;
};

void list_init(Tlist_c *head)
{
    if(head == NULL) return;
    head->size = 0;
    head->prev = NULL;
    head->next = NULL;
}

void list_push_back(Tlist_c *head,Tvalue value)
{
    //分配空间
    if(head == NULL) return;
    Tlist_c *new_value = (Tlist_c *)malloc(sizeof(Tlist_c));
    list_init(new_value);

    //连接到头节点
    if(head->size == 0)
    {
        //1.头节点的前后指针,指到新节点
        //2.新节点前指针,指到头节点
        head->prev = new_value;
        head->next = new_value;
        new_value->prev = head;
    }
    else
    {
        //1.新节点前节点,指向头节点前指针(头节点前指针等于尾节点)
        //2.尾节点的后指针,指到新节点
        //3.头节点前指针,指到新节点(等于将新节点当做尾节点)
        new_value->prev = head->prev;
        head->prev->next = new_value;
        head->prev = new_value;
    }
    head->size += 1;           //计数
    new_value->value = value;  //赋值
}

void list_push_front(Tlist_c *head,Tvalue value)
{
    //分配空间
    if(head == NULL) return;
    Tlist_c *new_value = (Tlist_c *)malloc(sizeof(Tlist_c));
    list_init(new_value);

    //连接到头节点
    if(head->size == 0)
    {
        //参考: list_push_back
        head->prev = new_value;
        head->next = new_value;
        new_value->prev = head;
    }
    else
    {
        //1.第一个带数据节点的前指针,指向新节点
        //2.新节点的后指针,指向第一个带数据节点
        //3.新节点的前指针,指向头节点
        //4.头节点的后指针,指向新节点
        head->next->prev = new_value;
        new_value->next = head->next;
        new_value->prev = head;
        head->next = new_value;
    }
    head->size += 1;           //计数
    new_value->value = value;  //赋值
}

int list_insert(Tlist_c *head,size_t pos,Tvalue value)
{
    //分配空间
    if(head == NULL || pos >= head->size) return 0;
    Tlist_c *new_value = (Tlist_c *)malloc(sizeof(Tlist_c));
    list_init(new_value);

    //获取指定的当前节点
    size_t count = 0;
    Tlist_c *it = head->next;
    for(;it != NULL;it = it->next)
    {
        if(count == pos) break;
        count++;
    }

    //1.新节点后指针,指向当前节点
    //2.新节点前指针,指向当前节点的前指针(等于当前节点的前节点)
    //3.当前节点的前节点的后指针,指向新节点
    //4.当前节点前指针,指向新节点
    new_value->next = it;
    new_value->prev = it->prev;
    it->prev->next = new_value;
    it->prev = new_value;

    head->size += 1;           //计数
    new_value->value = value;  //赋值
    return 1;
}

void list_pop_back(Tlist_c *head)
{
    if(head == NULL || head->size == 0) return ;
    head->size -= 1; //计数移除

    //1.保留尾节点
    //2.头节点的前指针,指向尾节点的前一个
    //3.尾节点的前一个的后指针,指向空(新的尾节点指向空)
    //4.释放尾节点
    Tlist_c *end = head->prev;
    head->prev = end->prev;
    end->prev->next = NULL;
    free(end);

}

void list_pop_front(Tlist_c *head)
{
    if(head == NULL || head->size == 0) return ;
    head->size -= 1; //计数移除

    //最后一个节点
    if(head->size == 0)
    {
        Tlist_c *begin = head->next;
        head->next = NULL;
        free(begin);
    }
    else
    {
        //1.保留第一个带数据节点
        //2.头节点的后指针,指向第一个带数据的后指针(等于第二个带数据节点)
        //3.第二个带数据的前指针,指向头节点
        //4.释放第一个带数据节点
        Tlist_c *begin = head->next;
        head->next = begin->next;
        begin->next->prev = head;
        free(begin);
    }
}

int list_erase(Tlist_c *head,size_t pos)
{
    if(head == NULL || head->size == 0 || pos >= head->size) return 0;
    head->size -= 1; //计数移除

    //获取指定的当前节点
    size_t count = 0;
    Tlist_c *it = head->next;
    for(;it != NULL;it = it->next)
    {
        if(count == pos) break;
        count++;
    }

    //删除末尾节点和最后一个元素时,需要特殊处理,避免操作空指针
    if(pos == head->size || head->size == 0)
    {
        //1.保留当前节点
        //2.前一个节点的后指针,指向空(新尾节点)
        //3.头节点前指针,指向新尾节点
        //4.释放当前指针
        Tlist_c *now = it;
        it->prev->next = NULL;
        head->prev = it->prev;
        free(now);
        return 1;
    }

    //1.保留当前节点
    //2.前一个节点的后指针,指向后节点
    //3.后节点的前指针,指向前节点
    //4.释放当前指针
    Tlist_c *now = it;
    it->prev->next = it->next;
    it->next->prev = it->prev;
    free(now);
    return 1;
}

void list_clear(Tlist_c *head)
{
    if(head == NULL) return;
    while(1)
    {
        //1.保存第一个节点,获取下一个,然后依次释放
        Tlist_c *begin = head->next;
        if(begin == NULL) break;
        head->next = head->next->next;
        free(begin);
    }
    head->size = 0; //清空计数
}
//===== Tlien_c =====
#endif
