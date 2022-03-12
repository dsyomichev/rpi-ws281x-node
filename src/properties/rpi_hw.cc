#include "rpi_hw.h"

Napi::Object init_rpi_hw(Napi::Env env) {
  Napi::Object rpi_hw = Napi::Object::New(env);

  rpi_hw.DefineProperty(type_desc(NULL));
  rpi_hw.DefineProperty(hwver_desc(NULL));
  rpi_hw.DefineProperty(periph_base_desc(NULL));
  rpi_hw.DefineProperty(videocore_base_desc(NULL));
  rpi_hw.DefineProperty(desc_desc(NULL));

  return rpi_hw;
}

/** Descriptors **/

Napi::PropertyDescriptor type_desc(void *data) {
  return Napi::PropertyDescriptor::Accessor<type_get>("type", napi_enumerable, data);
}

Napi::PropertyDescriptor hwver_desc(void *data) {
  return Napi::PropertyDescriptor::Accessor<hwver_get>("hwver", napi_enumerable, data);
}

Napi::PropertyDescriptor periph_base_desc(void *data) {
  return Napi::PropertyDescriptor::Accessor<periph_base_get>("periph_base", napi_enumerable, data);
}

Napi::PropertyDescriptor videocore_base_desc(void *data) {
  return Napi::PropertyDescriptor::Accessor<videocore_base_get>("videocore_base", napi_enumerable, data);
}

Napi::PropertyDescriptor desc_desc(void *data) {
  return Napi::PropertyDescriptor::Accessor<desc_get>("desc", napi_enumerable, data);
}

/** Getters **/

Napi::Value type_get(const Napi::CallbackInfo &info) {
  if (controller.rpi_hw == NULL) {
    return info.Env().Undefined();
  }

  return Napi::Number::New(info.Env(), controller.rpi_hw->type);
}

Napi::Value hwver_get(const Napi::CallbackInfo &info) {
  if (controller.rpi_hw == NULL) {
    return info.Env().Undefined();
  }

  return Napi::Number::New(info.Env(), controller.rpi_hw->hwver);
}

Napi::Value periph_base_get(const Napi::CallbackInfo &info) {
  if (controller.rpi_hw == NULL) {
    return info.Env().Undefined();
  }

  return Napi::Number::New(info.Env(), controller.rpi_hw->periph_base);
}

Napi::Value videocore_base_get(const Napi::CallbackInfo &info) {
  if (controller.rpi_hw == NULL) {
    return info.Env().Undefined();
  }

  return Napi::Number::New(info.Env(), controller.rpi_hw->videocore_base);
}

Napi::Value desc_get(const Napi::CallbackInfo &info) {
  if (controller.rpi_hw == NULL) {
    return info.Env().Undefined();
  } else if (controller.rpi_hw->desc == NULL) {
    return info.Env().Undefined();
  }

  return Napi::String::New(info.Env(), controller.rpi_hw->desc);
}
