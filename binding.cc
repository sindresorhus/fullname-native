#define UNICODE
#include <iostream>
#include <string>

#include <node.h>
#include "nan.h"

using namespace v8;


#ifdef _WIN32
#define SECURITY_WIN32
#include <windows.h>
#include <security.h>
#include <secext.h>
#include <lmcons.h>
#include <tchar.h>
NAN_METHOD(name) {
	NanScope();

	TCHAR username[UNLEN+1];
	ULONG size = sizeof(username);

	if (GetUserNameEx(NameDisplay, username, &size) != 0) {
		NanReturnValue(String::New((uint16_t*)username, wcslen(username)));
	}

	NanReturnNull();
}
#else
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
NAN_METHOD(name) {
	NanScope();

	struct passwd *pw = getpwuid(getuid());

	if (pw != NULL && pw->pw_gecos != NULL && strlen(pw->pw_gecos) > 0) {
		std::string gecos(pw->pw_gecos);

		// get everything before the first comma
		// since `gecos` is defined as a comma seperated list
		std::string name = gecos.substr(0, gecos.find(",", 0));

		if (name.length() > 0) {
			NanReturnValue(String::New(gecos.c_str()));
		}
	}

	NanReturnNull();
}
#endif

void init(Handle<Object> exports, Handle<Object> module) {
	NODE_SET_METHOD(module, "exports", name);
}

NODE_MODULE(binding, init)
