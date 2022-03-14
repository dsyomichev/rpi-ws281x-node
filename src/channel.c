#include "channel.h"

int      channel_obj_id[RPI_PWM_CHANNELS];
napi_ref channel_arr_ref, channel_leds_arr_ref[RPI_PWM_CHANNELS];

napi_status init_channel_arr(napi_env env, napi_value *target) {
  napi_status status;
  int         i;

  status = napi_create_array_with_length(env, RPI_PWM_CHANNELS, target);

  if (status != napi_ok) {
    return status;
  }

  for (i = 0; i < RPI_PWM_CHANNELS; i++) {
    napi_value               channel, leds;
    napi_property_descriptor descriptors[CHANNEL_PROPS];

    channel_obj_id[i] = i;
    status = init_channel_leds_arr(env, &leds, i);

    if (status != napi_ok) {
      return status;
    }

    status = napi_create_object(env, &channel);

    if (status != napi_ok) {
      return status;
    }

    descriptors[0] = make_channel_gpionum_prop(&channel_obj_id[i]);
    descriptors[1] = make_channel_invert_prop(&channel_obj_id[i]);
    descriptors[2] = make_channel_count_prop(&channel_obj_id[i]);
    descriptors[3] = make_channel_strip_type_prop(&channel_obj_id[i]);
    descriptors[4] = make_channel_leds_prop(env, &channel_obj_id[i]);
    descriptors[5] = make_channel_brightness_prop(&channel_obj_id[i]);
    descriptors[6] = make_channel_wshift_prop(&channel_obj_id[i]);
    descriptors[7] = make_channel_rshift_prop(&channel_obj_id[i]);
    descriptors[8] = make_channel_gshift_prop(&channel_obj_id[i]);
    descriptors[9] = make_channel_bshift_prop(&channel_obj_id[i]);
    descriptors[10] = make_channel_gamma_prop(&channel_obj_id[i]);

    status = napi_define_properties(env, channel, CHANNEL_PROPS, descriptors);

    if (status != napi_ok) {
      return status;
    }

    status = napi_set_element(env, *target, i, channel);

    if (status != napi_ok) {
      return status;
    }
  }

  status = napi_create_reference(env, *target, 1, &channel_arr_ref);

  if (status != napi_ok) {
    return status;
  }

  return status;
}

napi_status free_channel_arr(napi_env env) {
  napi_status status;
  int         i;

  status = free_reference(env, channel_arr_ref);

  for (i = 0; i < RPI_PWM_CHANNELS; i++) {
    free_channel_leds_arr(env, i);
  }

  return status;
}

napi_status init_channel_leds_arr(napi_env env, napi_value *target, int channel_id) {
  napi_status status;

  if (ws2811.channel[channel_id].leds != NULL) {
    napi_value buffer;
    uint32_t  *buffer_data;
    int        i, buffer_size = ws2811.channel[channel_id].count * sizeof(uint32_t);

    status = napi_create_arraybuffer(env, buffer_size, (void **)&buffer_data, &buffer);

    if (status != napi_ok) {
      return status;
    }

    for (i = 0; i < ws2811.channel[channel_id].count; i++) {
      buffer_data[i] = ws2811.channel[channel_id].leds[i];
    }

    status = napi_create_typedarray(env, napi_uint32_array, buffer_size / sizeof(uint32_t), buffer, 0, target);

    if (status != napi_ok) {
      return status;
    }

    status = napi_create_reference(env, *target, 1, &channel_leds_arr_ref[channel_id]);

    if (status != napi_ok) {
      return status;
    }

  } else {
    status = napi_get_undefined(env, target);
  }

  return status;
}

napi_status free_channel_leds_arr(napi_env env, int channel_id) {
  napi_status status;

  status = free_reference(env, channel_leds_arr_ref[channel_id]);

  return status;
}

napi_status push_channel_leds_arr(napi_env env, int channel_id) {
  napi_value  buffer;
  uint32_t   *buffer_data;
  napi_status status;
  int         i;

  status = napi_get_reference_value(env, channel_leds_arr_ref[channel_id], &buffer);

  if (status != napi_ok) {
    return status;
  }

  status = napi_get_typedarray_info(env, buffer, NULL, NULL, (void **)&buffer_data, NULL, NULL);

  if (status != napi_ok) {
    return status;
  }

  for (i = 0; i < ws2811.channel[channel_id].count; i++) {
    ws2811.channel[channel_id].leds[i] = buffer_data[i];
  }

  return napi_ok;
}

napi_property_descriptor make_channel_gpionum_prop(int *channel_id) {
  static char name[] = "gpionum";
  return make_accessor_prop(name, get_channel_gpionum_val, set_channel_gpionum_val, (void *)channel_id);
}

napi_value get_channel_gpionum_val(napi_env env, napi_callback_info info) {
  napi_value  result;
  napi_status status;
  int        *channel_id;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&channel_id);

  if (status != napi_ok) {
    return NULL;
  }

  status = napi_create_int32(env, ws2811.channel[*channel_id].gpionum, &result);

  if (status != napi_ok) {
    return NULL;
  }

  return result;
}

napi_value set_channel_gpionum_val(napi_env env, napi_callback_info info) {
  napi_status status;
  int         value;
  int        *channel_id;

  status = parse_value_int32(env, info, &value, (void **)&channel_id);

  if (status != napi_ok) {
    throw_invalid_argument_error(env);
    return NULL;
  }

  ws2811.channel[*channel_id].gpionum = value;

  return NULL;
}

napi_property_descriptor make_channel_invert_prop(int *channel_id) {
  static char name[] = "invert";
  return make_accessor_prop(name, get_channel_invert_val, set_channel_invert_val, (void *)channel_id);
}

napi_value get_channel_invert_val(napi_env env, napi_callback_info info) {
  napi_value  result;
  napi_status status;
  int        *channel_id;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&channel_id);

  if (status != napi_ok) {
    return NULL;
  }

  status = napi_create_int32(env, ws2811.channel[*channel_id].invert, &result);

  if (status != napi_ok) {
    return NULL;
  }

  return result;
}

napi_value set_channel_invert_val(napi_env env, napi_callback_info info) {
  napi_status status;
  int         value;
  int        *channel_id;

  status = parse_value_int32(env, info, &value, (void **)&channel_id);

  if (status != napi_ok) {
    throw_invalid_argument_error(env);
    return NULL;
  }

  ws2811.channel[*channel_id].invert = value;

  return NULL;
}

napi_property_descriptor make_channel_count_prop(int *channel_id) {
  static char name[] = "count";
  return make_accessor_prop(name, get_channel_count_val, set_channel_count_val, (void *)channel_id);
}

napi_value get_channel_count_val(napi_env env, napi_callback_info info) {
  napi_value  result;
  napi_status status;
  int        *channel_id;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&channel_id);

  if (status != napi_ok) {
    return NULL;
  }

  status = napi_create_int32(env, ws2811.channel[*channel_id].count, &result);

  if (status != napi_ok) {
    return NULL;
  }

  return result;
}

napi_value set_channel_count_val(napi_env env, napi_callback_info info) {
  napi_status status;
  int         value;
  int        *channel_id;

  status = parse_value_int32(env, info, &value, (void **)&channel_id);

  if (status != napi_ok) {
    throw_invalid_argument_error(env);
    return NULL;
  }

  ws2811.channel[*channel_id].count = value;

  return NULL;
}

napi_property_descriptor make_channel_strip_type_prop(int *channel_id) {
  static char name[] = "strip_type";
  return make_accessor_prop(name, get_channel_strip_type_val, set_channel_strip_type_val, (void *)channel_id);
}

napi_value get_channel_strip_type_val(napi_env env, napi_callback_info info) {
  napi_value  result;
  napi_status status;
  int        *channel_id;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&channel_id);

  if (status != napi_ok) {
    return NULL;
  }

  status = napi_create_int32(env, ws2811.channel[*channel_id].strip_type, &result);

  if (status != napi_ok) {
    return NULL;
  }

  return result;
}

napi_value set_channel_strip_type_val(napi_env env, napi_callback_info info) {
  napi_status status;
  int         value;
  int        *channel_id;

  status = parse_value_int32(env, info, &value, (void **)&channel_id);

  if (status != napi_ok) {
    throw_invalid_argument_error(env);
    return NULL;
  }

  ws2811.channel[*channel_id].strip_type = value;

  return NULL;
}

napi_property_descriptor make_channel_leds_prop(napi_env env, int *channel_id) {
  static char name[] = "leds";
  napi_value  value;
  napi_status status;

  status = napi_get_reference_value(env, channel_leds_arr_ref[*channel_id], &value);

  if (status != napi_ok) {
    napi_get_undefined(env, &value);
  }

  return make_value_prop(name, value, (void *)channel_id);
}

napi_property_descriptor make_channel_brightness_prop(int *channel_id) {
  static char name[] = "brightness";
  return make_accessor_prop(name, get_channel_brightness_val, set_channel_brightness_val, (void *)channel_id);
}

napi_value get_channel_brightness_val(napi_env env, napi_callback_info info) {
  napi_value  result;
  napi_status status;
  int        *channel_id;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&channel_id);

  if (status != napi_ok) {
    return NULL;
  }

  status = napi_create_int32(env, ws2811.channel[*channel_id].brightness, &result);

  if (status != napi_ok) {
    return NULL;
  }

  return result;
}

napi_value set_channel_brightness_val(napi_env env, napi_callback_info info) {
  napi_status status;
  int         value;
  int        *channel_id;

  status = parse_value_int32(env, info, &value, (void **)&channel_id);

  if (status != napi_ok) {
    throw_invalid_argument_error(env);
    return NULL;
  }

  ws2811.channel[*channel_id].brightness = value;

  return NULL;
}

napi_property_descriptor make_channel_wshift_prop(int *channel_id) {
  static char name[] = "wshift";
  return make_accessor_prop(name, get_channel_wshift_val, NULL, (void *)channel_id);
}

napi_value get_channel_wshift_val(napi_env env, napi_callback_info info) {
  napi_value  result;
  napi_status status;
  int        *channel_id;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&channel_id);

  if (status != napi_ok) {
    return NULL;
  }

  status = napi_create_int32(env, ws2811.channel[*channel_id].wshift, &result);

  if (status != napi_ok) {
    return NULL;
  }

  return result;
}

napi_property_descriptor make_channel_rshift_prop(int *channel_id) {
  static char name[] = "rshift";
  return make_accessor_prop(name, get_channel_rshift_val, NULL, (void *)channel_id);
}

napi_value get_channel_rshift_val(napi_env env, napi_callback_info info) {
  napi_value  result;
  napi_status status;
  int        *channel_id;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&channel_id);

  if (status != napi_ok) {
    return NULL;
  }

  status = napi_create_int32(env, ws2811.channel[*channel_id].rshift, &result);

  if (status != napi_ok) {
    return NULL;
  }

  return result;
}

napi_property_descriptor make_channel_gshift_prop(int *channel_id) {
  static char name[] = "gshift";
  return make_accessor_prop(name, get_channel_gshift_val, NULL, (void *)channel_id);
}

napi_value get_channel_gshift_val(napi_env env, napi_callback_info info) {
  napi_value  result;
  napi_status status;
  int        *channel_id;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&channel_id);

  if (status != napi_ok) {
    return NULL;
  }

  status = napi_create_int32(env, ws2811.channel[*channel_id].gshift, &result);

  if (status != napi_ok) {
    return NULL;
  }

  return result;
}

napi_property_descriptor make_channel_bshift_prop(int *channel_id) {
  static char name[] = "bshift";
  return make_accessor_prop(name, get_channel_bshift_val, NULL, (void *)channel_id);
}

napi_value get_channel_bshift_val(napi_env env, napi_callback_info info) {
  napi_value  result;
  napi_status status;
  int        *channel_id;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&channel_id);

  if (status != napi_ok) {
    return NULL;
  }

  status = napi_create_int32(env, ws2811.channel[*channel_id].bshift, &result);

  if (status != napi_ok) {
    return NULL;
  }

  return result;
}

napi_property_descriptor make_channel_gamma_prop(int *channel_id) {
  static char name[] = "gamma";
  return make_accessor_prop(name, get_channel_gamma_val, NULL, (void *)channel_id);
}

napi_value get_channel_gamma_val(napi_env env, napi_callback_info info) {
  napi_value  result, buffer;
  napi_status status;
  int        *channel_id, i;
  uint8_t    *buffer_data;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&channel_id);

  if (status != napi_ok) {
    return NULL;
  }

  if (ws2811.channel[*channel_id].gamma == NULL) {
    return NULL;
  }

  status = napi_create_arraybuffer(env, GAMMA_TABLE_SIZE * sizeof(uint8_t), (void **)&buffer_data, &buffer);

  if (status != napi_ok) {
    return NULL;
  }

  for (i = 0; i < GAMMA_TABLE_SIZE; i++) {
    buffer_data[i] = ws2811.channel[*channel_id].gamma[i];
  }

  status = napi_create_typedarray(env, napi_uint8_array, GAMMA_TABLE_SIZE, buffer, 0, &result);

  if (status != napi_ok) {
    return NULL;
  }

  return result;
}