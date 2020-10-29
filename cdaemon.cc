#ifndef _WIN32
#   include <unistd.h>
#endif
#include <node.h>

namespace cdaemon {

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::NewStringType;
using v8::Object;
using v8::Value;
using v8::String;
using v8::Boolean;

void Daemonize(const FunctionCallbackInfo<Value>& args) {
    int nochdir = 0, noclose = 0;
    Isolate* isolate = args.GetIsolate();

    if (args.Length() > 2) {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate,
                                "Wrong number of arguments",
                                NewStringType::kNormal).ToLocalChecked())
        );
    }

    if (args.Length() > 0) {
        if (!args[0]->IsBoolean()) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate,
                                    "Wrong arguments",
                                    NewStringType::kNormal).ToLocalChecked())
            );
            return;
        }

        nochdir = args[0].As<Boolean>()->Value() ? 1 : 0;
    }  

    if (args.Length() > 1) {
        if (!args[1]->IsBoolean()) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate,
                                    "Wrong arguments",
                                    NewStringType::kNormal).ToLocalChecked())
            );
            return;
        }

        noclose = args[1].As<Boolean>()->Value() ? 1 : 0;
    }  

#ifndef _WIN32
    daemon(nochdir, noclose);
#endif
}

void Initialize(Local<Object> exports, Local<Value> module, void* priv) {
    NODE_SET_METHOD(exports, "daemonize", Daemonize);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}