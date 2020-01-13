/* defines stuff missing otherwise */

/* setenv and unsetenv from setenv.c */
void setenv(const char *name, const char *value, int rewrite);
void unsetenv(const char *name);

/* realpath from realpath.c */
char *realpath(const char *path, char *resolved);




