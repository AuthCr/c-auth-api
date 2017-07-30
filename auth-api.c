#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "auth-api.h"

#define MAXDATASIZE 256 // max number of bytes we can get at once

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa) {
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in*)sa)->sin_addr);
  }
  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

#define auth_api_send(format, ...)              \
  {                                             \
    char cmd[256] = {0};                          \
    snprintf(cmd, 256, format "\n", __VA_ARGS__);        \
    send(api->socket, cmd, strlen(cmd), 0);     \
  }

int auth_api_success(auth_api_t *api) {
  char buf[256] = {0};
  int numbytes;
  if ((numbytes = recv(api->socket, buf, 255, 0)) == -1) {
    perror("recv");
    return 0;
  }
  return 1;
}

int auth_api_auth(auth_api_t *api, char const *username, char const *password) {
  auth_api_send("AUTH : %s %s", username, password);
  return 0;
}

int auth_api_user_has_access_to(auth_api_t *api, char const *perm, char const *res) {
  auth_api_send("USER HAS ACCESS TO : %s %s", perm, res);
  return 0;
}

auth_api_t *auth_api_init(char const *host, short unsigned int port) {
  int sockfd, numbytes;
  struct addrinfo hints, *servinfo, *p;
  int rv;
  char s[INET6_ADDRSTRLEN];

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  char port_string[6] = {0};
  snprintf(port_string, 5, "%i", port);
  printf("Connect to: %s:%s\n", host, port_string);
  if ((rv = getaddrinfo(host, port_string, &hints, &servinfo)) != 0) {
    perror("getaddrinfo");
    return NULL;
  }

  // loop through all the results and connect to the first we can
  for(p = servinfo; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
      perror("socket");
      continue;
    }

    if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      perror("connect");
      continue;
    }

    break;
  }

  if (p == NULL) {
    fprintf(stderr, "client: failed to connect\n");
    return NULL;
  }

  inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
  printf("client: connecting to %s\n", s);

  freeaddrinfo(servinfo); // all done with this structure

  auth_api_t *api = malloc(sizeof(auth_api_t));
  api->socket = sockfd;
  return api;
}

int auth_api_free(auth_api_t *api) {
  close(api->socket);
  free(api);
  return 0;
}
