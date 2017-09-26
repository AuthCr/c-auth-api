#include "auth-api.h"
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

int main() {
  dlopen("libauth-api.so", RTLD_NOW | RTLD_GLOBAL);
  credid_api_t *api = credid_api_init("127.0.0.1", 8999);
  if (api == NULL) {
    printf("Cannot init\n");
    return 1;
  }
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
  printf("Access auth\n");

  printf("Everything worked fine !\n");
  credid_api_free(api);
  return 0;
}
