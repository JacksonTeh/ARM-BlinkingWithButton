#ifndef Button_H
#define Button_H

typedef struct ListElement_t ListElement;
struct ListElement_t
{
  ListElement *next;
  void *data;
};

typedef struct
{
  ListElement *head;
  ListElement *tail;
  int length;
} List;

#endif // Button_H