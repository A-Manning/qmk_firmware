#include "../../config.h"

#undef  TAPPING_TERM
#define TAPPING_TERM 150

// makes lsft ok
#define PERMISSIVE_HOLD

#define IGNORE_MOD_TAP_INTERRUPT

// set up auto shift
#define AUTO_SHIFT_TIMEOUT 150 //timeout to shift, works like TAPPING_TERM
#define NO_AUTO_SHIFT_SPECIAL // no shift symbols
#define NO_AUTO_SHIFT_NUMERIC // no shift numeric row

// Decreases debounce time. Units are keyboard scans. Each scan is around 3.5ms.
#undef  DEBOUNCE
#define DEBOUNCE 10
