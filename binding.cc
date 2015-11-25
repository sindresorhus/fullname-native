#define UNICODE
#include <iostream>
#include <string>

#ifdef _WIN32
#	define SECURITY_WIN32
#	include <windows.h>
#	include <security.h>
#	include <secext.h>
#	include <lmcons.h>
#	include <tchar.h>
#else
#	include <sys/types.h>
#	include <unistd.h>
#	include <pwd.h>
#endif

#include <node.h>
#include <nan.h>

using namespace v8;


NAN_METHOD(name) {
	Nan::HandleScope scope;

#ifdef _WIN32
	TCHAR username[UNLEN+1];
	ULONG size = sizeof(username);

	if (GetUserNameEx(NameDisplay, username, &size) != 0) {
		info.GetReturnValue().Set(Nan::New<String>((uint16_t*)username).ToLocalChecked());
		return;
	}
#else
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
#endif

	info.GetReturnValue().Set(Nan::Null());
}

void init(Handle<Object> exports, Handle<Object> module) {
	Nan::SetMethod(module, "exports", name);
}

NODE_MODULE(binding, init)
