#pragma once

typedef struct {
  int socket;
} auth_api_t;

auth_api_t *auth_api_init(char const *host, short unsigned int port);
int auth_api_free(auth_api_t *api);

int auth_api_auth(auth_api_t *api, char const *username, char const *password);
int auth_api_user_has_access_to(auth_api_t *api, char const *perm, char const *res);
int auth_api_success(auth_api_t *api);
