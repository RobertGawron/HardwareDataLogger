#ifndef MyApplication_h
#define MyApplication_h

// A wrapper from C++ to C, neither business nor low-level logic should be in
// this class.

#ifdef __cplusplus
extern "C" {
#endif

void app_init();
void app_start();
void app_tick();

#ifdef __cplusplus
}
#endif

#endif
