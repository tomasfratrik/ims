#ifndef __MACROS_H__
#define __MACROS_H__

#ifdef DEBUG
#define DEBUG(...) do { fprintf( stderr, "[DBG]: %s\n", __VA_ARGS__ ); } while(0)
#else
#define DEBUG(...) do {} while (0)
#endif // DEBUG

#endif // __MACROS_H__