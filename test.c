#include "auth-api.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
  auth_api_t *api = auth_api_init("127.0.0.1", 8999);
  if (api == NULL) {
    printf("Cannot init\n");
    return 1;
  }
  printf("Init done\n");

  printf("Try to auth\n");
  auth_api_auth(api, "root", "toor");
  if (auth_api_success(api) == 0) {
    printf("Cannot auth\n");
    auth_api_free(api);
    return 2;
  }
  printf("Authenticated\n");

  printf("Try has access to\n");
  auth_api_user_has_access_to(api, "write", "/test");
  if (auth_api_success(api) == 0) {
    printf("Don't have access\n");
    auth_api_free(api);
    return 3;
  }
  printf("Access auth\n");

  printf("Try to list groups\n");
  auth_api_group_list(api);
  if (auth_api_success(api) == 0) {
    printf("Don't have access\n");
    auth_api_free(api);
    return 4;
  }

  printf("Groups: %s\n", auth_api_last_result(api));
  auth_api_group_list_perms(api, "root");
  printf("Perms: %s\n", auth_api_last_result(api));
  auth_api_group_list_perms(api, "user");
  printf("Perms: %s\n", auth_api_last_result(api));

  printf("Everything worked fine !\n");
  auth_api_free(api);
  return 0;
}
