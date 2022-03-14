#include "rpi_hw.h"

napi_ref rpi_hw_obj_ref;

napi_status init_rpi_hw_obj(napi_env env, napi_value *target) {
  napi_status              status;
  napi_property_descriptor descriptors[RPI_HW_PROPS];

  if (ws2811.rpi_hw != NULL) {
    napi_create_object(env, target);

    descriptors[0] = make_rpi_hw_type_prop(env);
    descriptors[1] = make_rpi_hw_hwver_prop(env);
    descriptors[2] = make_rpi_hw_periph_base_prop(env);
    descriptors[3] = make_rpi_hw_videocore_base_prop(env);
    descriptors[4] = make_rpi_hw_desc_prop(env);

    status = napi_define_properties(env, *target, RPI_HW_PROPS, descriptors);

    status = napi_create_reference(env, *target, 1, &rpi_hw_obj_ref);
  } else {
    status = napi_get_undefined(env, target);
  }

  return status;
}

napi_status free_rpi_hw_obj(napi_env env) {
  napi_status status;

  status = free_reference(env, rpi_hw_obj_ref);

  return status;
}

napi_property_descriptor make_rpi_hw_type_prop(napi_env env) {
  static char name[] = "type";

  return make_accessor_prop(name, &get_rpi_hw_type_val, NULL, NULL);
}

napi_value get_rpi_hw_type_val(napi_env env, napi_callback_info info) {
  napi_value  target;
  napi_status status;

  if (ws2811.rpi_hw == NULL) {
    return NULL;
  }

  status = napi_create_uint32(env, ws2811.rpi_hw->type, &target);

  if (status != napi_ok) {
    return NULL;
  }

  return target;
}

napi_property_descriptor make_rpi_hw_hwver_prop(napi_env env) {
  static char name[] = "hwver";

  return make_accessor_prop(name, &get_rpi_hw_hwver_val, NULL, NULL);
}

napi_value get_rpi_hw_hwver_val(napi_env env, napi_callback_info info) {
  napi_value  target;
  napi_status status;

  if (ws2811.rpi_hw == NULL) {
    return NULL;
  }

  status = napi_create_uint32(env, ws2811.rpi_hw->hwver, &target);

  if (status != napi_ok) {
    return NULL;
  }

  return target;
}

napi_property_descriptor make_rpi_hw_periph_base_prop(napi_env env) {
  static char name[] = "periph_base";

  return make_accessor_prop(name, &get_rpi_hw_periph_base_val, NULL, NULL);
}

napi_value get_rpi_hw_periph_base_val(napi_env env, napi_callback_info info) {
  napi_value  target;
  napi_status status;

  if (ws2811.rpi_hw == NULL) {
    return NULL;
  }

  status = napi_create_uint32(env, ws2811.rpi_hw->periph_base, &target);

  if (status != napi_ok) {
    return NULL;
  }

  return target;
}

napi_property_descriptor make_rpi_hw_videocore_base_prop(napi_env env) {
  static char name[] = "videocore_base";

  return make_accessor_prop(name, &get_rpi_hw_videocore_base_val, NULL, NULL);
}

napi_value get_rpi_hw_videocore_base_val(napi_env env, napi_callback_info info) {
  napi_value  target;
  napi_status status;

  if (ws2811.rpi_hw == NULL) {
    return NULL;
  }

  status = napi_create_uint32(env, ws2811.rpi_hw->videocore_base, &target);

  if (status != napi_ok) {
    return NULL;
  }

  return target;
}

napi_property_descriptor make_rpi_hw_desc_prop(napi_env env) {
  static char name[] = "desc";

  return make_accessor_prop(name, &get_rpi_hw_desc_val, NULL, NULL);
}

napi_value get_rpi_hw_desc_val(napi_env env, napi_callback_info info) {
  napi_value  target;
  napi_status status;
  size_t      length;

  if (ws2811.rpi_hw == NULL || ws2811.rpi_hw->desc == NULL) {
    return NULL;
  }

  length = strlen(ws2811.rpi_hw->desc);
  status = napi_create_string_utf16(env, (char16_t *)ws2811.rpi_hw->desc, length, &target);

  if (status != napi_ok) {
    return NULL;
  }

  return target;
}