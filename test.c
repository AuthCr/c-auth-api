#include "credid-api.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
  credid_api_t *api = credid_api_init("127.0.0.1", 8999);
  if (api == NULL) {
    printf("Cannot init\n");
    return 1;
  }
  credid_api_setup_logs(api, 1);
  printf("Init done\n");

  printf("Try to auth\n");
  credid_api_auth(api, "root", "toor");
  if (credid_api_success(api) == 0) {
    printf("Cannot auth\n");
    credid_api_free(api);
    return 2;
  }
  printf("Authenticated\n");

  printf("Try has access to\n");
  credid_api_user_has_access_to(api, "write", "/test");
  if (credid_api_success(api) == 0) {
    printf("Don't have access\n");
    credid_api_free(api);
    return 3;
  }

  credid_api_log_t *log = credid_api_fetch_log(api);
  if (log == NULL) {
    printf("no log found !\n");
    return 4;
  }
  if (strcmp(log->query, "AUTH : root toor\n") != 0) {
    printf("bad log found (%s) (%d)\n", log->query, log->success);
    return 5;
  }
  free(log->query);
  free(log);
  printf("Access auth\n");

  printf("Try to list groups\n");
  credid_api_group_list(api);
  if (credid_api_success(api) == 0) {
    printf("Don't have access\n");
    credid_api_free(api);
    return 6;
  }

  printf("Groups: %s\n", credid_api_last_result(api));
  credid_api_group_list_perms(api, "root");
  printf("Perms: %s\n", credid_api_last_result(api));
  credid_api_group_list_perms(api, "user");
  printf("Perms: %s\n", credid_api_last_result(api));

  printf("Everything worked fine !\n");
  credid_api_free(api);
  return 0;
}
