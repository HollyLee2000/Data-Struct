#include "seqnode.h"

void init(NodeList* list){
  list->first = (Node*)malloc(sizeof(Node));
  list->last = list->first;
  list->first->next = NULL;
  list->size = 0;
}

void push_back(NodeList* list, ElemType val){
  Node* p = (Node*)malloc(sizeof(Node));
  assert(NULL != p);
  p->data = val;
  p->next = NULL;
  /*
  if(list->first->next == NULL){
    list->first->next = p;
    list->last = p;
    list->size++;
    return;
  }
  */

  list->last->next = p;
  list->last = p;
  list->size++;
}

void push_front(NodeList* list, ElemType val){
  Node* p = (Node*)malloc(sizeof(Node));
  p->data = val;
  p->next = list->first->next;
  list->first->next = p;
  if(list->size == 0){
    list->last = p;
  }
  list->size++;
}

void show_list(NodeList* list){
  Node* tmp = list->first->next;
  while(tmp != NULL){
    printf("%d->", tmp->data);
    tmp = tmp->next;
  }
  printf("NULL\n");
}

void pop_back(NodeList* list){
  if(list->size == 0)return;
  Node* p = list->first;
  while(p->next != list->last){
    p = p->next;
  }
  p->next = NULL;
  free(list->last);
  list->last = p;
  list->size--;
}
void pop_front(NodeList* list){
  if(list->size == 0)return;
  Node* p = list->first->next;
  list->first->next = p->next;
  if(list->size == 1){
    list->last = list->first;
  }
  list->size--;
  free(p);
}
void insert_val(NodeList* list, ElemType val){
  if(list->size == 0){
    push_back(list, val);
    return;
  }
  Node* p = (Node*)malloc(sizeof(Node));
  p->data = val;
  Node* t = list->first;
  do{
    if(val >= t->data && t->next != NULL && val <= t->next->data){
      p->next = t->next;
      t->next = p;
      break;
    }
    if(t->next == NULL){
      list->last->next = p;
      list->last = p;
      list->last->next = NULL;
      break;
    }
    t = t->next;
  }
  while(1);
  list->size++;
}
Node* find(NodeList* list, ElemType val){
  if(0 == list->size){
    return NULL;
  }
  Node* p = list->first->next;
  do{
    if(val == p->data){
      return p;
      break;
    }
    p = p->next;
  }
  while(NULL != p);
}
void delete_val(NodeList* list, ElemType val){
  if(0 == list->size)return;
  Node* p = list->first;
  do{
    if(p->next->data == val){
      if(NULL == p->next->next){
	list->last = p;
      }
      free(p->next);
      p->next = p->next->next;
      list->size--;
      break;
    }
    p = p->next;
  }while(NULL != p->next);
}
void delete_val1(NodeList* list, ElemType val){
  if(0 == list->size)return;
  Node* p = find(list, val);
  if(NULL == p)return;
  if(p == list->last){
    pop_back(list);
  }
  else{
    p->data = p->next->data;
    free(p->next);
    p->next = p->next->next;
    if(NULL == p->next){
      list->last = p;
    }
    list->size--;
  }
}
void sort(NodeList* list){
  if(list->size == 0 || list->size == 1)return;
  Node* p = list->first->next;
  for(int i = 0; i < list->size-1; ++i){
    for(int j = 0; j < list->size-i-1; ++j){
      if(p->data > p->next->data){
	p->data = p->data + p->next->data;
	p->next->data = p->data - p->next->data;
	p->data = p->data - p->next->data;
      }
      p = p->next;
    }
    p = list->first->next;
  }
}

void insert_pnt(NodeList* list, Node* node){
  Node* t = list->first;
  do{
    if(t->next != NULL && node->data <= t->next->data){
      node->next = t->next;
      t->next = node;
      break;
    }
    if(t->next == NULL){
      list->last->next = node;
      list->last = node;
      list->last->next = NULL;
      break;
    }
    t = t->next;
  }
  while(1);
  list->size++;
}
void sort1(NodeList* list){
  if(list->size == 0 || list->size == 1)return;

  Node* n = list->first->next->next;

  list->size = 1;
  list->last = list->first->next;
  list->last->next = NULL;

  Node* t;
  while(NULL != n){
    t = n->next;
    insert_pnt(list, n);
    n = t;
  }
}
