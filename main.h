#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>

#define CONVERT_UNSIGNED 2

typedef struct lists
{
	int *num;
	char *str;
	struct lists *next;
}list_t;

typedef struct infot
{
	int argc;
	char *arg;
	char **argv;
	int status;
	char *history;
	char *alias;
	char **environ;
	char *fname;
	int line_count;
	char *buffer;
	int buffer_type;
	char *path;
	char **cmd_buf;
	list_t *env;
	int readfd;
	int histcount;
}info_t;

int _interpreter(char *s);
int is_interactive(void);
int is_delimiter(char c);
int has_alphabets(char *s);

int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);

int _shellhistory(info_t *);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int print_alias(list_t *node);
int _myalias(info_t *info);

void add_node_end(list_t **head, char *str);
void print_list_str(list_t *head);
char *find_str_in_list(list_t *head, const char *str);
int my_setenv(info_t *info);
int my_unsetenv(info_t *info);
int populate_env_list(info_t *info);

void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

int _strconvert(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

char* my_strncpy(char* dest, const char* src, size_t n);
char* my_strncat(char* dest, const char* src, size_t n);

int input_buffer(info_t *info, char **buffer, size_t *x);
int get_input(info_t *info, char **command);
int read_buffer(int fd, char *buffer, size_t *i);
void sigintHandler(int sig_num);

void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

list_t *add_node(list_t **head, const char *str, int num);
void add_node_end(list_t **head, char *str);
void print_list_str(list_t *head);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head);

int _free(void **ptr);

int _pathbuilt(info_t *info, char *path);
char find_path(info_t *info, char *pathstr, char *index);

char *setMem(char *ptr, char b, unsigned int num);
void freestr(char **str);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *starts(const char *haystack, const char *subs);
char *_strcat(char *dest, char *src);

char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void shellputs(char *str);
int shellputchar(char c);

char *_strtok(char *str, const char *delim);
char **splitstr(char *str, char *delim);
char *_strchr(const char *s, int c);

size_t listLen(const list_t *head);
char **strlist(list_t *head);
size_t print_list(const list_t *head);
list_t *strNode(list_t *head, char *pre, char c);
ssize_t strindexOf(list_t *head, list_t *node);

#endif
