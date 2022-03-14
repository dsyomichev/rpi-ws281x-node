#ifndef _MODULE_H_
#define _MODULE_H_

#define NAPI_VERSION 6

#include <math.h>
#include <node_api.h>
#include <pwm.h>
#include <stdio.h>
#include <string.h>
#include <ws2811.h>

typedef struct {
  char *name;
  int   channel_arr_index;
} prop_data;

#include "driver.h"

ws2811_t ws2811;

napi_value make_module(napi_env env, napi_value exports);

napi_property_descriptor make_accessor_prop(const char *name, napi_callback get, napi_callback set, void *data);
napi_property_descriptor make_method_prop(const char *name, napi_callback method, void *data);
napi_property_descriptor make_value_prop(const char *name, napi_value value, void *data);

napi_status parse_arg_value_uint32(napi_env env, napi_callback_info info, uint32_t *result, void **data);
napi_status parse_arg_value_int32(napi_env env, napi_callback_info info, int *result, void **data);
napi_status parse_arg_value_double(napi_env env, napi_callback_info info, double *result, void **data);

napi_status throw_invalid_arg_error(napi_env env);

napi_status free_reference(napi_env env, napi_ref ref);

#endif