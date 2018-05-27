# Auth-Api C binding

## Build

    cmake CMakeLists.txt
    make

## Install

You can copy `libcredid.so` into you lib path (`/usr/lib`) and `auth-api.h` into your include dir (`/usr/include`).

## Usage

*Note: Each command is blocking (waits for the server to respond)*

You can create a new api entry-point with:

    credid_api_t *api = auth_api_init("127.0.0.1", 8999);

Then you have to authenticate the connection:

    creid_api_auth(api, "root", "toor");

You can verify the result of the last command with (0 = failure, 1 = success):

    credid_api_success(api)

You can check if you have access to a resource with:

    credid_api_user_has_access_to(api, "write", "/test");
    if (credid_api_success(api) == 1) {
      printf("Success\n");
    }

You can define query's options by specifing them as optional arguments:

    credid_api_group_list(api, "PAGE=1", "COUNT=1");

## More features

The api provide a implementation of the full credid RFC v0.2.

* Group management
* User management
* Authentication
* Failure and success check

And also

* Logs (see the header file `credid.h`)

## Security

* No memory leaks
* Most of the system calls and memory allocation are verified
* Usage of secure stdlib (strNcmp etc.)
* Thread safe for one resource (can manage each connection in one thread, but **NOT one connection in more than ONE thread**)
* Password are not logged
