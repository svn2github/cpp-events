#define SIGSLOT_DEFAULT_MT_POLICY single_threaded
#include "main.inl"
extern void main_st() { runTest(); }