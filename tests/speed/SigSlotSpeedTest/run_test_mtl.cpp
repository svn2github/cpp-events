#define SIGSLOT_DEFAULT_MT_POLICY multi_threaded_local
#include "main.inl"
extern void main_mtl() { runTest(); }