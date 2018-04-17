# stm32-uid
Mbed helper to get UID as base64

# Example
```cpp
#include "mbed.h"
#include "stm32-uid.h"

STM32uid uid;

int main() {

    char id[12], base[16];
    uid.get(id);
    uid.get_base64(base);

    printf("uid: ");

    for (int i = 0; i < 12; ++i) {
        printf("%02X", id[i]);
    }

    printf("\n base64: ");

    for (int i = 0; i < 16; ++i) {
        printf("%c", base[i]);
    }

    printf("\n");
}

```
