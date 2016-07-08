#ifndef _TEST1_H
#define _TEST1_H

#ifdef _TEST1_C
#define _TEST1_EXT
#else
#define _TEST1_EXT extern
#endif

_TEST1_EXT void test_display(void);
_TEST1_EXT void test_display_map(void);

#endif
