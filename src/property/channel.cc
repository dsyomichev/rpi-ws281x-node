#include "channel.h"

Napi::Array init_channel(Napi::Env env) {
  static int  id[RPI_PWM_CHANNELS];
  Napi::Array channels = Napi::Array::New(env, RPI_PWM_CHANNELS);

  for (int i = 0; i < RPI_PWM_CHANNELS; i++) {
    id[i] = i;

    Napi::Object channel = Napi::Object::New(env);

    channel.DefineProperty(gpionum_desc(&id[i]));
    channel.DefineProperty(invert_desc(&id[i]));
    channel.DefineProperty(count_desc(&id[i]));
    channel.DefineProperty(strip_type_desc(&id[i]));
    channel.DefineProperty(leds_desc(&id[i]));
    channel.DefineProperty(brightness_desc(&id[i]));
    channel.DefineProperty(wshift_desc(&id[i]));
    channel.DefineProperty(rshift_desc(&id[i]));
    channel.DefineProperty(gshift_desc(&id[i]));
    channel.DefineProperty(bshift_desc(&id[i]));
    channel.DefineProperty(gamma_desc(&id[i]));

    channels.Set(i, channel);
  }

  return channels;
}

/** Descriptors **/

Napi::PropertyDescriptor gpionum_desc(void *data) {
  return Napi::PropertyDescriptor::Accessor<gpionum_get, gpionum_set>("gpionum", napi_enumerable, data);
}

Napi::PropertyDescriptor invert_desc(void *data) {
  return Napi::PropertyDescriptor::Accessor<invert_get, invert_set>("invert", napi_enumerable, data);
}

Napi::PropertyDescriptor count_desc(void *data) {
  return Napi::PropertyDescriptor::Accessor<count_get, count_set>("count", napi_enumerable, data);
}

Napi::PropertyDescriptor strip_type_desc(void *data) {
  return Napi::PropertyDescriptor::Accessor<strip_type_get, strip_type_set>("strip_type", napi_enumerable, data);
}

Napi::PropertyDescriptor leds_desc(void *data) {
  return Napi::PropertyDescriptor::Accessor<leds_get, leds_set>("leds", napi_enumerable, data);
}

Napi::PropertyDescriptor brightness_desc(void *data) {
  return Napi::PropertyDescriptor::Accessor<brightness_get, brightness_set>("brightness", napi_enumerable, data);
}

Napi::PropertyDescriptor wshift_desc(void *data) {
  return Napi::PropertyDescriptor::Accessor<wshift_get>("wshift", napi_enumerable, data);
}

Napi::PropertyDescriptor rshift_desc(void *data) {
  return Napi::PropertyDescriptor::Accessor<rshift_get>("rshift", napi_enumerable, data);
}

Napi::PropertyDescriptor gshift_desc(void *data) {
  return Napi::PropertyDescriptor::Accessor<gshift_get>("gshift", napi_enumerable, data);
}

Napi::PropertyDescriptor bshift_desc(void *data) {
  return Napi::PropertyDescriptor::Accessor<bshift_get>("bshift", napi_enumerable, data);
}

Napi::PropertyDescriptor gamma_desc(void *data) {
  return Napi::PropertyDescriptor::Accessor<gamma_get>("gamma", napi_enumerable, data);
}

/** Getters **/
Napi::Value gpionum_get(const Napi::CallbackInfo &info) {
  int *i = (int *)info.Data();
  return Napi::Number::New(info.Env(), controller.channel[*i].gpionum);
}

Napi::Value invert_get(const Napi::CallbackInfo &info) {
  int *i = (int *)info.Data();
  return Napi::Number::New(info.Env(), controller.channel[*i].invert);
}

void gpionum_set(const Napi::CallbackInfo &info) {
  int *i = (int *)info.Data();
  controller.channel[*i].gpionum = info[0].As<Napi::Number>().Int32Value();
}

Napi::Value count_get(const Napi::CallbackInfo &info) {
  int *i = (int *)info.Data();
  return Napi::Number::New(info.Env(), controller.channel[*i].count);
}
Napi::Value strip_type_get(const Napi::CallbackInfo &info) {
  int *i = (int *)info.Data();
  return Napi::Number::New(info.Env(), controller.channel[*i].strip_type);
}

Napi::Value leds_get(const Napi::CallbackInfo &info) {
  int              *i = (int *)info.Data();
  ws2811_channel_t *channel = &controller.channel[*i];

  if (channel->leds == NULL) {
    return info.Env().Undefined();
  }

  Napi::TypedArrayOf<uint32_t> leds = Napi::TypedArrayOf<uint32_t>::New(info.Env(), channel->count);

  for (int l = 0; l < channel->count; l++) {
    leds.Set(l, channel->leds[l]);
  }

  return leds;
}

Napi::Value brightness_get(const Napi::CallbackInfo &info) {
  int *i = (int *)info.Data();
  return Napi::Number::New(info.Env(), controller.channel[*i].brightness);
}

Napi::Value wshift_get(const Napi::CallbackInfo &info) {
  int *i = (int *)info.Data();
  return Napi::Number::New(info.Env(), controller.channel[*i].wshift);
}

Napi::Value rshift_get(const Napi::CallbackInfo &info) {
  int *i = (int *)info.Data();
  return Napi::Number::New(info.Env(), controller.channel[*i].rshift);
}

Napi::Value gshift_get(const Napi::CallbackInfo &info) {
  int *i = (int *)info.Data();
  return Napi::Number::New(info.Env(), controller.channel[*i].gshift);
}

Napi::Value bshift_get(const Napi::CallbackInfo &info) {
  int *i = (int *)info.Data();
  return Napi::Number::New(info.Env(), controller.channel[*i].bshift);
}

Napi::Value gamma_get(const Napi::CallbackInfo &info) {
  int              *i = (int *)info.Data();
  ws2811_channel_t *channel = &controller.channel[*i];

  if (channel->gamma == NULL) {
    return info.Env().Undefined();
  }

  Napi::TypedArrayOf<uint32_t> gamma = Napi::TypedArrayOf<uint32_t>::New(info.Env(), 256);

  for (int k = 0; k < 256; k++) {
    gamma.Set(k, channel->gamma[k]);
  }

  return gamma;
}

/** Setters **/

void invert_set(const Napi::CallbackInfo &info) {
  int *i = (int *)info.Data();
  controller.channel[*i].invert = info[0].As<Napi::Number>().Int32Value();
}

void count_set(const Napi::CallbackInfo &info) {
  int *i = (int *)info.Data();
  controller.channel[*i].count = info[0].As<Napi::Number>().Int32Value();
}

void strip_type_set(const Napi::CallbackInfo &info) {
  int *i = (int *)info.Data();
  controller.channel[*i].strip_type = info[0].As<Napi::Number>().Int32Value();
}

void leds_set(const Napi::CallbackInfo &info) {
  int              *i = (int *)info.Data();
  ws2811_channel_t *channel = &controller.channel[*i];

  if (channel->leds == NULL) {
    return;
  }

  Napi::TypedArrayOf<uint32_t> leds = info[0].As<Napi::TypedArrayOf<uint32_t>>();

  for (int l = 0; l < channel->count; l++) {
    channel->leds[l] = leds.Get(l).As<Napi::Number>().Uint32Value();
  }
}

void brightness_set(const Napi::CallbackInfo &info) {
  int *i = (int *)info.Data();
  controller.channel[*i].brightness = info[0].As<Napi::Number>().Int32Value();
}
