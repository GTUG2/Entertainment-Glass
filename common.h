#ifndef COMMON_H
#define COMMON_H

#include "stdint.h"

struct packet{
  uint8_t start;
  uint8_t app_id;
  union{
    struct xox_data{
      uint8_t cell_states[9];
      uint8_t increase;
      uint8_t position;
    }xox;
    uint8_t _[30];
  }data;
};
#endif // COMMON_H
