#ifndef _WIN32
#   include <unistd.h>
#endif
#include <napi.h>

namespace cdaemon {

using Napi::CallbackInfo;
using Napi::Object;
using Napi::String;
using Napi::Boolean;

void Daemonize(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    int nochdir = 0, noclose = 0;

    if (info.Length() > 2) {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return;
    }

    if (info.Length() > 0) {
        if (!info[0].IsBoolean()) {
            Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
            return;
        }

        nochdir = info[0].As<Napi::Boolean>().Value() ? 1 : 0;
    }  

    if (info.Length() > 1) {
        if (!info[1].IsBoolean()) {
            Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
            return;
        }

        noclose = info[1].As<Napi::Boolean>().Value() ? 1 : 0;
    }  

#ifndef _WIN32
    daemon(nochdir, noclose);
#endif
}


Napi::Object Initialize(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "daemonize"), Napi::Function::New(env, Daemonize));
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}