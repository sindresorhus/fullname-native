#define UNICODE
#include <iostream>
#include <string>

#include <node.h>
#include <nan.h>

using namespace v8;


#ifdef _WIN32
#define SECURITY_WIN32
#include <windows.h>
#include <security.h>
#include <secext.h>
#include <lmcons.h>
#include <tchar.h>
NAN_METHOD(name) {
	Nan::HandleScope scope;

	TCHAR username[UNLEN+1];
	ULONG size = sizeof(username);

	if (GetUserNameEx(NameDisplay, username, &size) != 0) {
		info.GetReturnValue().Set(Nan::New<String>((uint16_t*)username).ToLocalChecked());
	} else {
		info.GetReturnValue().Set(Nan::Null());
	}
}
#else
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
NAN_METHOD(name) {
	Nan::HandleScope scope;

	struct passwd *pw = getpwuid(getuid());

	if (pw != NULL && pw->pw_gecos != NULL && strlen(pw->pw_gecos) > 0) {
		const std::string gecos(pw->pw_gecos);

		// get everything before the first comma
		// since `gecos` is defined as a comma seperated list
		const std::string name = gecos.substr(0, gecos.find(",", 0));

		if (name.length() > 0) {
			info.GetReturnValue().Set(Nan::New<String>(name).ToLocalChecked());
			return;
		}
	}

	info.GetReturnValue().Set(Nan::Null());
}
#endif

void init(Handle<Object> exports, Handle<Object> module) {
	Nan::SetMethod(module, "exports", name);
}

NODE_MODULE(binding, init)
