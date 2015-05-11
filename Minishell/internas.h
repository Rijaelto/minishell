#ifndef INTERNAS_H
#define INTERNAS_H

struct tipointerna
{
  char *nombre;
  void (*func)(const char *);
};

int ord_interna(const char *);

#endif
