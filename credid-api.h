#pragma once

#define MAXDATASIZE 4096

/*
 * The query is a malloc() allocated string
 * The status is an int (0=success, 1=failure, other=network error)
 */
typedef struct credid_api_log_s {
  char  *query;
  int   status;
} credid_api_log_t ;

typedef struct credid_api_logs_link_s {
  credid_api_log_t  *line;
  struct credid_api_logs_link_s* next;
} credid_api_logs_link_t;

typedef struct {
  int   socket;
  char  *last_command_result;
  int   logs_enabled;
  credid_api_logs_link_t *logs;
  credid_api_logs_link_t *logs_end;
} credid_api_t;

/* Initialize the API */
credid_api_t *credid_api_init(char const *host, short unsigned int port);

/* Free the API */
int credid_api_free(credid_api_t *api);

/* Return 1 if the last query returned success, else 0 */
int credid_api_success(credid_api_t const *api);

/*
 * Get the last result (data after "success" or "failure").
 * This data is freed after each call to the API, you might need to copy it.
 */
char *credid_api_last_result(credid_api_t const *api);

#define COUNT_VA_ARG(...)  sizeof((char*[]){0, ##__VA_ARGS__})/sizeof(char*)-1

/* Send AUTH ids */
int _credid_api_auth(credid_api_t *api,                 char const *username, char const *password,                 int options, ...);
/* Request access to a resource */
int _credid_api_user_has_access_to(credid_api_t *api,   char const *perm, char const *res,                          int options, ...);
int _credid_api_group_add(credid_api_t *api,            char const *group, char const *perm, char const *resource,  int options, ...);
int _credid_api_group_remove(credid_api_t *api,         char const *group, char const *resource,                    int options, ...);
int _credid_api_group_list(credid_api_t *api,                                                                       int options, ...);
int _credid_api_group_list_perms(credid_api_t *api,     char const *group,                                          int options, ...);
int _credid_api_group_get_perm(credid_api_t *api,       char const *group, char const *resource,                    int options, ...);
int _credid_api_user_list(credid_api_t *api,                                                                        int options, ...);
int _credid_api_user_add(credid_api_t *api,             char const *username, char const *password,                 int options, ...);
int _credid_api_user_remove(credid_api_t *api,          char const *username,                                       int options, ...);
int _credid_api_user_add_group(credid_api_t *api,       char const *username, char const *group,                    int options, ...);
int _credid_api_user_remove_group(credid_api_t *api,    char const *username, char const *group,                    int options, ...);
int _credid_api_user_list_groups(credid_api_t *api,     char const *username,                                       int options, ...);
int _credid_api_user_change_password(credid_api_t *api, char const *username, char const *newpassword,              int options, ...);

#define credid_api_auth(api, username, password, ...)                    _credid_api_auth(api, username, password,                     COUNT_VA_ARG(__VA_ARGS__), ##__VA_ARGS__)
#define credid_api_user_has_access_to(api, perm, res, ...)               _credid_api_user_has_access_to(api, perm, res,                COUNT_VA_ARG(__VA_ARGS__), ##__VA_ARGS__)
#define credid_api_group_add(api, group, perm, resource, ...)            _credid_api_group_add(api, group, perm, resource,             COUNT_VA_ARG(__VA_ARGS__), ##__VA_ARGS__)
#define credid_api_group_remove(api, group, resource, ...)               _credid_api_group_remove(api, group, resource,                COUNT_VA_ARG(__VA_ARGS__), ##__VA_ARGS__)
#define credid_api_group_list(api, ...)                                  _credid_api_group_list(api,                                   COUNT_VA_ARG(__VA_ARGS__), ##__VA_ARGS__)
#define credid_api_group_list_perms(api, group, ...)                     _credid_api_group_list_perms(api, group,                      COUNT_VA_ARG(__VA_ARGS__), ##__VA_ARGS__)
#define credid_api_group_get_perm(api, group, resource, ...)             _credid_api_group_get_perm(api, group, resource,              COUNT_VA_ARG(__VA_ARGS__), ##__VA_ARGS__)
#define credid_api_user_list(api, ...)                                   _credid_api_user_list(api,                                    COUNT_VA_ARG(__VA_ARGS__), ##__VA_ARGS__)
#define credid_api_user_add(api, username, password, ...)                _credid_api_user_add(api, username, password,                 COUNT_VA_ARG(__VA_ARGS__), ##__VA_ARGS__)
#define credid_api_user_remove(api, username, ...)                       _credid_api_user_remove(api, username,                        COUNT_VA_ARG(__VA_ARGS__), ##__VA_ARGS__)
#define credid_api_user_add_group(api, username, group, ...)             _credid_api_user_add_group(api, username, group,              COUNT_VA_ARG(__VA_ARGS__), ##__VA_ARGS__)
#define credid_api_user_remove_group(api, username, group, ...)          _credid_api_user_remove_group(api, username, group,           COUNT_VA_ARG(__VA_ARGS__), ##__VA_ARGS__)
#define credid_api_user_list_groups(api, username, ...)                  _credid_api_user_list_groups(api, username,                   COUNT_VA_ARG(__VA_ARGS__), ##__VA_ARGS__)
#define credid_api_user_change_password(api, username, newpassword, ...) _credid_api_user_change_password(api, username, newpassword,  COUNT_VA_ARG(__VA_ARGS__), ##__VA_ARGS__)

/* Enable or disable the logging (1 or 0) */
int credid_api_setup_logs(credid_api_t *api, int enable);

/*
 * Return the first log of the logs (and remove it from the logs).
 * The returned pointer must be freed with free().
 */
credid_api_log_t *credid_api_fetch_log(credid_api_t *api);

/* Remove and free the logs. Called by credid_api_free() */
int credid_api_free_logs(credid_api_t *api);
