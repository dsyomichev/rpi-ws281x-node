#include "channel.h"

napi_ref channel_arr_ref, channel_obj_ref[RPI_PWM_CHANNELS];

napi_status init_channel_arr(napi_env env, napi_value *target) {
  napi_status status;
  int         channel_arr_index;

  status = napi_create_array_with_length(env, RPI_PWM_CHANNELS, target);

  if (status != napi_ok) {
    return status;
  }

  for (channel_arr_index = 0; channel_arr_index < RPI_PWM_CHANNELS; channel_arr_index++) {
    napi_value               channel, leds;
    napi_property_descriptor prop[CHANNEL_PROPS];

    status = napi_create_object(env, &channel);

    if (status != napi_ok) {
      return status;
    }

    if (ws2811.channel[channel_arr_index].leds != NULL) {

      status = init_channel_leds_arr(env, &leds, channel_arr_index);

      if (status != napi_ok) {
        return status;
      }
    } else {
      status = napi_get_undefined(env, &leds);

      if (status != napi_ok) {
        return status;
      }
    }

    prop[0] = make_channel_gpionum_prop(channel_arr_index);
    prop[1] = make_channel_invert_prop(channel_arr_index);
    prop[2] = make_channel_count_prop(channel_arr_index);
    prop[3] = make_channel_strip_type_prop(channel_arr_index);
    prop[4] = make_channel_leds_prop(env, channel_arr_index, leds);
    prop[5] = make_channel_brightness_prop(channel_arr_index);
    prop[6] = make_channel_wshift_prop(channel_arr_index);
    prop[7] = make_channel_rshift_prop(channel_arr_index);
    prop[8] = make_channel_gshift_prop(channel_arr_index);
    prop[9] = make_channel_bshift_prop(channel_arr_index);
    prop[10] = make_channel_gamma_prop(channel_arr_index);

    status = napi_define_properties(env, channel, CHANNEL_PROPS, prop);

    if (status != napi_ok) {
      return status;
    }

    status = napi_set_element(env, *target, channel_arr_index, channel);

    if (status != napi_ok) {
      return status;
    }

    status = napi_create_reference(env, channel, 1, &channel_obj_ref[channel_arr_index]);

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

  status = free_reference(env, channel_arr_ref);

  return status;
}

napi_status init_channel_leds_arr(napi_env env, napi_value *target, int channel_arr_index) {
  napi_status       status = napi_ok;
  ws2811_channel_t *channel = &ws2811.channel[channel_arr_index];

  if (channel->leds != NULL) {
    napi_value buffer;
    uint32_t  *buffer_data;
    int        led_index;

    status = napi_create_arraybuffer(env, channel->count * sizeof(uint32_t), (void **)&buffer_data, &buffer);

    if (status != napi_ok) {
      return status;
    }

    for (led_index = 0; led_index < channel->count; led_index++) {
      buffer_data[led_index] = channel->leds[led_index];
    }

    status = napi_create_typedarray(env, napi_uint32_array, channel->count, buffer, 0, target);

    if (status != napi_ok) {
      return status;
    }
  }

  return status;
}

napi_status free_channel_leds_arr(napi_env env, int channel_arr_index) {
  napi_status status;

  status = free_reference(env, channel_obj_ref[channel_arr_index]);

  return status;
}

napi_status push_channel_leds_arr(napi_env env, int channel_arr_index) {
  napi_value           channel_obj, buffer, name;
  uint32_t            *buffer_data;
  napi_status          status;
  int                  led_index;
  size_t               count;
  napi_typedarray_type arr_type;
  char                 prop_name[] = "leds";
  ws2811_channel_t    *channel = &ws2811.channel[channel_arr_index];

  status = napi_get_reference_value(env, channel_obj_ref[channel_arr_index], &channel_obj);

  if (status != napi_ok) {
    return status;
  }

  status = napi_create_string_utf8(env, prop_name, strlen(prop_name), &name);

  if (status != napi_ok) {
    return status;
  }

  status = napi_get_property(env, channel_obj, name, &buffer);

  if (status != napi_ok) {
    return status;
  }

  status = napi_get_typedarray_info(env, buffer, &arr_type, &count, (void **)&buffer_data, NULL, NULL);

  if (status != napi_ok) {
    return status;
  }

  if (arr_type != napi_uint32_array) {
    return napi_invalid_arg;
  }

  if ((int)count != channel->count) {
    return napi_invalid_arg;
  }

  for (led_index = 0; led_index < channel->count; led_index++) {
    ws2811.channel[channel_arr_index].leds[led_index] = buffer_data[led_index];
  }

  return napi_ok;
}

napi_property_descriptor make_channel_gpionum_prop(int channel_arr_index) {
  static prop_data channel_gpionum_prop_data[RPI_PWM_CHANNELS];
  static char      name[] = "gpionum";
  prop_data       *data = &channel_gpionum_prop_data[channel_arr_index];

  data->name = name;
  data->channel_arr_index = channel_arr_index;

  return make_accessor_prop(name, get_channel_gpionum_val, set_channel_gpionum_val, (void *)data);
}

napi_value get_channel_gpionum_val(napi_env env, napi_callback_info info) {
  napi_value  result;
  napi_status status;
  prop_data  *data;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&data);

  if (status != napi_ok) {
    throw_generic_error(env);
    return NULL;
  }

  status = napi_create_int32(env, ws2811.channel[data->channel_arr_index].gpionum, &result);

  if (status != napi_ok) {
    throw_generic_error(env);
    return NULL;
  }

  return result;
}

napi_value set_channel_gpionum_val(napi_env env, napi_callback_info info) {
  napi_status status;
  prop_data  *data;
  int         value;

  status = parse_arg_value_int32(env, info, &value, (void **)&data);

  if (status != napi_ok) {
    throw_invalid_arg_error(env);
    return NULL;
  }

  ws2811.channel[data->channel_arr_index].gpionum = value;

  return NULL;
}

napi_property_descriptor make_channel_invert_prop(int channel_arr_index) {
  static prop_data channel_invert_prop_data[RPI_PWM_CHANNELS];
  static char      name[] = "invert";
  prop_data       *data = &channel_invert_prop_data[channel_arr_index];

  data->name = name;
  data->channel_arr_index = channel_arr_index;

  return make_accessor_prop(name, get_channel_invert_val, set_channel_invert_val, (void *)data);
}

napi_value get_channel_invert_val(napi_env env, napi_callback_info info) {
  napi_value  result;
  napi_status status;
  prop_data  *data;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&data);

  if (status != napi_ok) {
    throw_generic_error(env);
    return NULL;
  }

  status = napi_create_int32(env, ws2811.channel[data->channel_arr_index].invert, &result);

  if (status != napi_ok) {
    throw_generic_error(env);
    return NULL;
  }

  return result;
}

napi_value set_channel_invert_val(napi_env env, napi_callback_info info) {
  napi_status status;
  int         value;
  prop_data  *data;

  status = parse_arg_value_int32(env, info, &value, (void **)&data);

  if (status != napi_ok) {
    throw_invalid_arg_error(env);
    return NULL;
  }

  ws2811.channel[data->channel_arr_index].invert = value;

  return NULL;
}

napi_property_descriptor make_channel_count_prop(int channel_arr_index) {
  static prop_data channel_count_prop_data[RPI_PWM_CHANNELS];
  static char      name[] = "count";
  prop_data       *data = &channel_count_prop_data[channel_arr_index];

  data->name = name;
  data->channel_arr_index = channel_arr_index;

  return make_accessor_prop(name, get_channel_count_val, set_channel_count_val, (void *)data);
}

napi_value get_channel_count_val(napi_env env, napi_callback_info info) {
  napi_value  result;
  napi_status status;
  prop_data  *data;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&data);

  if (status != napi_ok) {
    throw_generic_error(env);
    return NULL;
  }

  status = napi_create_int32(env, ws2811.channel[data->channel_arr_index].count, &result);

  if (status != napi_ok) {
    throw_generic_error(env);
    return NULL;
  }

  return result;
}

napi_value set_channel_count_val(napi_env env, napi_callback_info info) {
  napi_status status;
  prop_data  *data;
  int         value;

  status = parse_arg_value_int32(env, info, &value, (void **)&data);

  if (status != napi_ok) {
    throw_invalid_arg_error(env);
    return NULL;
  }

  ws2811.channel[data->channel_arr_index].count = value;

  return NULL;
}

napi_property_descriptor make_channel_strip_type_prop(int channel_arr_index) {
  static prop_data channel_strip_type_prop_data[RPI_PWM_CHANNELS];
  static char      name[] = "strip_type";
  prop_data       *data = &channel_strip_type_prop_data[channel_arr_index];

  data->name = name;
  data->channel_arr_index = channel_arr_index;

  return make_accessor_prop(name, get_channel_strip_type_val, set_channel_strip_type_val, (void *)data);
}

napi_value get_channel_strip_type_val(napi_env env, napi_callback_info info) {
  napi_value  result;
  napi_status status;
  prop_data  *data;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&data);

  if (status != napi_ok) {
    throw_generic_error(env);
    return NULL;
  }

  status = napi_create_int32(env, ws2811.channel[data->channel_arr_index].strip_type, &result);

  if (status != napi_ok) {
    throw_generic_error(env);
    return NULL;
  }

  return result;
}

napi_value set_channel_strip_type_val(napi_env env, napi_callback_info info) {
  napi_status status;
  prop_data  *data;
  int         value;

  status = parse_arg_value_int32(env, info, &value, (void **)&data);

  if (status != napi_ok) {
    throw_invalid_arg_error(env);
    return NULL;
  }

  ws2811.channel[data->channel_arr_index].strip_type = value;

  return NULL;
}

napi_property_descriptor make_channel_leds_prop(napi_env env, int channel_arr_index, napi_value value) {
  static prop_data channel_leds_prop_data[RPI_PWM_CHANNELS];
  static char      name[] = "leds";
  prop_data       *data = &channel_leds_prop_data[channel_arr_index];

  data->name = name;
  data->channel_arr_index = channel_arr_index;

  return make_value_prop(name, value, (void *)data);
}

napi_property_descriptor make_channel_brightness_prop(int channel_arr_index) {
  static prop_data channel_brightnesss_prop_data[RPI_PWM_CHANNELS];
  static char      name[] = "brightness";
  prop_data       *data = &channel_brightnesss_prop_data[channel_arr_index];

  data->name = name;
  data->channel_arr_index = channel_arr_index;

  return make_accessor_prop(name, get_channel_brightness_val, set_channel_brightness_val, (void *)data);
}

napi_value get_channel_brightness_val(napi_env env, napi_callback_info info) {
  napi_value  result;
  napi_status status;
  prop_data  *data;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&data);

  if (status != napi_ok) {
    throw_generic_error(env);
    return NULL;
  }

  status = napi_create_uint32(env, ws2811.channel[data->channel_arr_index].brightness, &result);

  if (status != napi_ok) {
    throw_generic_error(env);
    return NULL;
  }

  return result;
}

napi_value set_channel_brightness_val(napi_env env, napi_callback_info info) {
  napi_status status;
  int         value;
  prop_data  *data;

  status = parse_arg_value_int32(env, info, &value, (void **)&data);

  if (status != napi_ok) {
    throw_invalid_arg_error(env);
    return NULL;
  }

  ws2811.channel[data->channel_arr_index].brightness = value;

  return NULL;
}

napi_property_descriptor make_channel_wshift_prop(int channel_arr_index) {
  static prop_data channel_wshift_prop_data[RPI_PWM_CHANNELS];
  static char      name[] = "wshift";
  prop_data       *data = &channel_wshift_prop_data[channel_arr_index];

  data->name = name;
  data->channel_arr_index = channel_arr_index;

  return make_accessor_prop(name, get_channel_wshift_val, NULL, (void *)data);
}

napi_value get_channel_wshift_val(napi_env env, napi_callback_info info) {
  napi_value  result;
  napi_status status;
  prop_data  *data;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&data);

  if (status != napi_ok) {
    throw_generic_error(env);
    return NULL;
  }

  status = napi_create_int32(env, ws2811.channel[data->channel_arr_index].wshift, &result);

  if (status != napi_ok) {
    throw_generic_error(env);
    return NULL;
  }

  return result;
}

prop_data channel_rshift_prop_data[RPI_PWM_CHANNELS];

napi_property_descriptor make_channel_rshift_prop(int channel_arr_index) {
  static prop_data channel_rshift_prop_data[RPI_PWM_CHANNELS];
  static char      name[] = "rshift";
  prop_data       *data = &channel_rshift_prop_data[channel_arr_index];

  data->name = name;
  data->channel_arr_index = channel_arr_index;

  return make_accessor_prop(name, get_channel_rshift_val, NULL, (void *)data);
}

napi_value get_channel_rshift_val(napi_env env, napi_callback_info info) {
  napi_value  result;
  napi_status status;
  prop_data  *data;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&data);

  if (status != napi_ok) {
    throw_generic_error(env);
    return NULL;
  }

  status = napi_create_int32(env, ws2811.channel[data->channel_arr_index].rshift, &result);

  if (status != napi_ok) {
    throw_generic_error(env);
    return NULL;
  }

  return result;
}

prop_data channel_gshift_prop_data[RPI_PWM_CHANNELS];

napi_property_descriptor make_channel_gshift_prop(int channel_arr_index) {
  static prop_data channel_gshift_prop_data[RPI_PWM_CHANNELS];
  static char      name[] = "gshift";
  prop_data       *data = &channel_gshift_prop_data[channel_arr_index];

  data->name = name;
  data->channel_arr_index = channel_arr_index;

  return make_accessor_prop(name, get_channel_gshift_val, NULL, (void *)data);
}

napi_value get_channel_gshift_val(napi_env env, napi_callback_info info) {
  napi_value  result;
  napi_status status;
  prop_data  *data;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&data);

  if (status != napi_ok) {
    throw_generic_error(env);
    return NULL;
  }

  status = napi_create_int32(env, ws2811.channel[data->channel_arr_index].gshift, &result);

  if (status != napi_ok) {
    throw_generic_error(env);
    return NULL;
  }

  return result;
}

prop_data channel_bshift_prop_data[RPI_PWM_CHANNELS];

napi_property_descriptor make_channel_bshift_prop(int channel_arr_index) {
  static prop_data channel_bshift_prop_data[RPI_PWM_CHANNELS];
  static char      name[] = "bshift";
  prop_data       *data = &channel_bshift_prop_data[channel_arr_index];

  data->name = name;
  data->channel_arr_index = channel_arr_index;

  return make_accessor_prop(name, get_channel_bshift_val, NULL, (void *)data);
}

napi_value get_channel_bshift_val(napi_env env, napi_callback_info info) {
  napi_value  result;
  napi_status status;
  prop_data  *data;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&data);

  if (status != napi_ok) {
    throw_generic_error(env);
    return NULL;
  }

  status = napi_create_int32(env, ws2811.channel[data->channel_arr_index].bshift, &result);

  if (status != napi_ok) {
    throw_generic_error(env);
    return NULL;
  }

  return result;
}

napi_property_descriptor make_channel_gamma_prop(int channel_arr_index) {
  static prop_data channel_gamma_prop_data[RPI_PWM_CHANNELS];
  static char      name[] = "gamma";
  prop_data       *data = &channel_gamma_prop_data[channel_arr_index];

  data->name = name;
  data->channel_arr_index = channel_arr_index;

  return make_accessor_prop(name, get_channel_gamma_val, NULL, (void *)data);
}

napi_value get_channel_gamma_val(napi_env env, napi_callback_info info) {
  napi_value        result, buffer;
  napi_status       status;
  int               gamma_table_index;
  prop_data        *data;
  uint8_t          *buffer_data;
  ws2811_channel_t *channel;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&data);

  if (status != napi_ok) {
    throw_generic_error(env);
    return NULL;
  }

  channel = &ws2811.channel[data->channel_arr_index];

  if (channel->gamma == NULL) {
    return NULL;
  }

  status = napi_create_arraybuffer(env, GAMMA_TABLE_SIZE * sizeof(uint8_t), (void **)&buffer_data, &buffer);

  if (status != napi_ok) {
    throw_generic_error(env);
    return NULL;
  }

  for (gamma_table_index = 0; gamma_table_index < GAMMA_TABLE_SIZE; gamma_table_index++) {
    buffer_data[gamma_table_index] = channel->gamma[gamma_table_index];
  }

  status = napi_create_typedarray(env, napi_uint8_array, GAMMA_TABLE_SIZE, buffer, 0, &result);

  if (status != napi_ok) {
    throw_generic_error(env);
    return NULL;
  }

  return result;
}