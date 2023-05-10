//!
//! Tlien_c.h
//!
#ifndef TLIEN_C_H
#define TLIEN_C_H

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

//== 模板生成(放在头文件会重复包含) ==
//基本类型
////Tlist_create(Tchar,char)
////Tlist_create(Tshort,short)
////Tlist_create(Tint,int)
////Tlist_create(Tlong,long)
////Tlist_create(Tlonglong,long long)
////Tlist_create(Tfloat,float)
////Tlist_create(Tdouble,double)
////Tlist_create(Tcharp,char *) //字符串
//== 模板生成 ==

#endif // TLIEN_C_H
