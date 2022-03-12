#include "module.h"

ws2811_t controller;

NODE_API_MODULE(rpi_ws281x_node, init_driver);

Napi::Object init_driver(Napi::Env env, Napi::Object exports) {
  Napi::Object driver = Napi::Object::New(env);

  driver.DefineProperty(render_wait_time_desc(NULL));
  driver.DefineProperty(rpi_hw_desc(NULL));
  driver.DefineProperty(freq_desc(NULL));
  driver.DefineProperty(dmanum_desc(NULL));
  driver.DefineProperty(channel_desc(NULL));
  driver.DefineProperty(init_desc(NULL));
  driver.DefineProperty(fini_desc(NULL));
  driver.DefineProperty(render_desc(NULL));
  driver.DefineProperty(wait_desc(NULL));
  driver.DefineProperty(set_custom_gamma_factor_desc(NULL));

  return driver;
}

/** Descriptors **/

Napi::PropertyDescriptor render_wait_time_desc(void *data) {
  return Napi::PropertyDescriptor::Accessor<render_wait_time_get>("render_wait_time", napi_enumerable, data);
}

Napi::PropertyDescriptor rpi_hw_desc(void *data) {

  return Napi::PropertyDescriptor::Accessor<rpi_hw_get>("rpi_hw", napi_enumerable, data);
}

Napi::PropertyDescriptor freq_desc(void *data) {
  return Napi::PropertyDescriptor::Accessor<freq_get, freq_set>("freq", napi_enumerable, data);
}

Napi::PropertyDescriptor dmanum_desc(void *data) {
  return Napi::PropertyDescriptor::Accessor<dmanum_get, dmanum_set>("dmanum", napi_enumerable, data);
}

Napi::PropertyDescriptor channel_desc(void *data) {
  return Napi::PropertyDescriptor::Accessor<channel_get>("channel", napi_enumerable, data);
}

Napi::PropertyDescriptor init_desc(void *data) {
  return Napi::PropertyDescriptor::Function("init", init_func, napi_enumerable, data);
}

Napi::PropertyDescriptor fini_desc(void *data) {
  return Napi::PropertyDescriptor::Function("fini", fini_func, napi_enumerable, data);
}

Napi::PropertyDescriptor render_desc(void *data) {
  return Napi::PropertyDescriptor::Function("render", render_func, napi_enumerable, data);
}

Napi::PropertyDescriptor wait_desc(void *data) {
  return Napi::PropertyDescriptor::Function("wait", wait_func, napi_enumerable, data);
}

Napi::PropertyDescriptor set_custom_gamma_factor_desc(void *data) {
  return Napi::PropertyDescriptor::Function(
      "set_custom_gamma_factor", set_custom_gamma_factor_func, napi_enumerable, data);
}

/** Functions **/

void init_func(const Napi::CallbackInfo &info) {

  ws2811_return_t result = ws2811_init(&controller);

  if (result != WS2811_SUCCESS) {
    Napi::Error::New(info.Env(), ws2811_get_return_t_str(result)).ThrowAsJavaScriptException();
  }
}

void fini_func(const Napi::CallbackInfo &info) {
  ws2811_fini(&controller);
}

void render_func(const Napi::CallbackInfo &info) {
  ws2811_return_t result = ws2811_render(&controller);

  if (result != WS2811_SUCCESS) {
    Napi::Error::New(info.Env(), ws2811_get_return_t_str(result)).ThrowAsJavaScriptException();
  }
}

void wait_func(const Napi::CallbackInfo &info) {
  ws2811_return_t result = ws2811_wait(&controller);

  if (result != WS2811_SUCCESS) {
    Napi::Error::New(info.Env(), ws2811_get_return_t_str(result)).ThrowAsJavaScriptException();
  }
}

void set_custom_gamma_factor_func(const Napi::CallbackInfo &info) {
  ws2811_set_custom_gamma_factor(&controller, info[0].As<Napi::Number>().DoubleValue());
}

/** Getters **/

Napi::Value render_wait_time_get(const Napi::CallbackInfo &info) {
  return Napi::Number::New(info.Env(), controller.render_wait_time);
}

Napi::Value rpi_hw_get(const Napi::CallbackInfo &info) {
  if (controller.rpi_hw == NULL) {
    return info.Env().Undefined();
  }

  return init_rpi_hw(info.Env());
}

Napi::Value freq_get(const Napi::CallbackInfo &info) {
  return Napi::Number::New(info.Env(), controller.freq);
}

Napi::Value dmanum_get(const Napi::CallbackInfo &info) {
  return Napi::Number::New(info.Env(), controller.dmanum);
}

Napi::Value channel_get(const Napi::CallbackInfo &info) {
  if (controller.channel == NULL) {
    return info.Env().Undefined();
  }

  return init_channel(info.Env());
}

/** Setters **/

void freq_set(const Napi::CallbackInfo &info) {
  controller.freq = info[0].As<Napi::Number>().Int32Value();
}

void dmanum_set(const Napi::CallbackInfo &info) {
  controller.dmanum = info[0].As<Napi::Number>().Int32Value();
}