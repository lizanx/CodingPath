#include "bfd.h"
#include <stdio.h>

int main() {
  const char **target_platform = bfd_target_list();
  while (*target_platform++) {
    printf("Target platform: %s\n", *target_platform);
  }

  return 0;
}
