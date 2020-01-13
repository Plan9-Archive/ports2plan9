
#define abc 1234
#define def -1234
#define xyz 0x12345678ul
#define xyz1 0xffffffffull

#if xyz == 0x12345678
#warning match1
#endif

#if xyz1 == 0xffffffffull
#warning match2
#endif

#if -1ll == 0xffffffffll
#warning match2
#endif

#if -1llu == 0xffffffffllu
#warning match2
#endif
