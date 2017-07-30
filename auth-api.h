#pragma once

typedef struct {
  int socket;
} auth_api_t;

/* Initialize the API */
auth_api_t *auth_api_init(char const *host, short unsigned int port);
/* Free the API */
int auth_api_free(auth_api_t *api);

/* Get the last result (after "success" or "failure") */
char *auth_api_last_result(auth_api_t *api);

/* Send AUTH ids */
int auth_api_auth(auth_api_t *api, char const *username, char const *password);

/* Request access to a resource */
int auth_api_user_has_access_to(auth_api_t *api, char const *perm, char const *res);

/* Return 1 if the last query returned success, else 0 */
int auth_api_success(auth_api_t *api);
