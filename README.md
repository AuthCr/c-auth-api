# Auth-Api C binding

## Build

    cmake CMakeLists.txt
    make

## Install

You can copy `libauth-api.so` into you lib path (`/usr/lib`) and `auth-api.h` into your include dir (`/usr/include`).

## Usage

*Note: Each command is blocking (waits for the server to respond)*

You can create a new api entry-point with:

    auth_api_t *api = auth_api_init("127.0.0.1", 8999);

Then you have to authenticate the connection:

    auth_api_auth(api, "root", "toor");

You can verify the result of the last command with (0 = failure, 1 = success):

    auth_api_success(api)

You can check if you have access to a resource with:

    auth_api_user_has_access_to(api, "write", "/test");
    if (auth_api_success(api) == 1) {
      printf("Success\n");
    }
