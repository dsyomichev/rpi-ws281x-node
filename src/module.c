#include "module.h"

ws2811_t ws2811;

NAPI_MODULE(RPI_WS281X_NODE, make_module)

napi_value make_module(napi_env env, napi_value exports) {
  napi_status status;
  napi_value  driver_obj;

  status = init_driver_obj(env, &driver_obj);

  if (status != napi_ok) {
    throw_generic_error(env);
    return NULL;
  }

  return driver_obj;
}

napi_property_descriptor make_accessor_prop(const char *name, napi_callback get, napi_callback set, void *data) {
  napi_property_descriptor descriptor;

  descriptor.utf8name = name;
  descriptor.name = NULL;
  descriptor.method = NULL;
  descriptor.getter = get;
  descriptor.setter = set;
  descriptor.value = NULL;
  descriptor.attributes = napi_enumerable;
  descriptor.data = data;

  return descriptor;
}

napi_property_descriptor make_method_prop(const char *name, napi_callback function, void *data) {
  napi_property_descriptor descriptor;

  descriptor.utf8name = name;
  descriptor.name = NULL;
  descriptor.method = function;
  descriptor.getter = NULL;
  descriptor.setter = NULL;
  descriptor.value = NULL;
  descriptor.attributes = napi_enumerable;
  descriptor.data = data;

  return descriptor;
}

napi_property_descriptor make_value_prop(const char *name, napi_value value, void *data) {
  napi_property_descriptor descriptor;

  descriptor.utf8name = name;
  descriptor.name = NULL;
  descriptor.method = NULL;
  descriptor.getter = NULL;
  descriptor.setter = NULL;
  descriptor.value = value;
  descriptor.attributes = napi_enumerable | napi_writable;
  descriptor.data = data;

  return descriptor;
}

napi_status parse_arg_value_uint32(napi_env env, napi_callback_info info, uint32_t *result, void **data) {
  napi_status status;
  napi_value  arg;
  double      double_val;

  status = parse_arg_value_double(env, info, &double_val, data);

  if (status != napi_ok) {
    return status;
  }

  if (double_val < 0 || double_val > __UINT32_MAX__ || ceil(double_val) != double_val) {
    return napi_invalid_arg;
  }

  status = napi_create_double(env, double_val, &arg);

  if (status != napi_ok) {
    return status;
  }

  status = napi_get_value_uint32(env, arg, result);

  if (status != napi_ok) {
    return status;
  }

  return status;
}

napi_status parse_arg_value_int32(napi_env env, napi_callback_info info, int *result, void **data) {
  napi_status status;
  napi_value  arg;
  double      double_val;

  status = parse_arg_value_double(env, info, &double_val, data);

  if (status != napi_ok) {
    return status;
  }

  if (double_val < __INT32_MAX__ * -1 || double_val > __INT32_MAX__ || ceil(double_val) != double_val) {
    return napi_invalid_arg;
  }

  status = napi_create_double(env, double_val, &arg);

  if (status != napi_ok) {
    return status;
  }

  status = napi_get_value_int32(env, arg, result);

  if (status != napi_ok) {
    return status;
  }

  return status;
}

napi_status parse_arg_value_double(napi_env env, napi_callback_info info, double *result, void **data) {
  napi_status    status;
  napi_valuetype type;
  napi_value     argv[1];
  size_t         argc = 1;

  status = napi_get_cb_info(env, info, &argc, argv, NULL, data);

  if (status != napi_ok) {
    return status;
  }

  status = napi_typeof(env, argv[0], &type);

  if (type != napi_number) {
    return napi_invalid_arg;
  }

  status = napi_get_value_double(env, argv[0], result);

  if (status != napi_ok) {
    return napi_invalid_arg;
  }

  return status;
}

napi_status free_reference(napi_env env, napi_ref ref) {
  napi_status status;
  int         i;
  uint32_t    count;

  status = napi_reference_unref(env, ref, &count);

  if (status == napi_ok) {
    for (i = count; i > 0; i--) {
      status = napi_reference_unref(env, ref, &count);

      if (status != napi_ok) {
        return status;
      }
    }

    status = napi_delete_reference(env, ref);

    if (status != napi_ok) {
      return status;
    }
  }

  return status;
}

napi_status throw_invalid_arg_error(napi_env env) {
  static const char code[] = "ERR_INVALID_ARG_TYPE";
  static const char message[] = "The argument must match the property type.";

  return napi_throw_type_error(env, code, message);
}

napi_status throw_init_error(napi_env env) {
  static const char code[] = "ERR_INVALID_STATE";
  static const char message[] = "The driver must be initialized before use.";

  return napi_throw_type_error(env, code, message);
}

napi_status throw_generic_error(napi_env env) {
  static const char code[] = "ERR_SYSTEM_ERROR";
  static const char message[] = "An unknown error has occured.";

  return napi_throw_error(env, code, message);
}

napi_status throw_status_error(napi_env env, ws2811_return_t status) {
  static const char code[] = "ERR_INVALID_STATE";

  return napi_throw_error(env, code, ws2811_get_return_t_str(status));
}