#pragma once

#include "pebble.h"

typedef struct TransparentImageLayer {
  BitmapLayer *white_layer;
  BitmapLayer *black_layer;
} TransparentImageLayer;

typedef struct TransparentImage {
  GBitmap *white_image;
  GBitmap *black_image;
  GRect bounds;
} TransparentImage;

TransparentImage *trasparent_image_create_with_resources(
  uint32_t bitmap_black_res_id, uint32_t bitmap_white_res_id);

void transparent_image_layer_set_image(const TransparentImageLayer *layer,
  const TransparentImage *image);

TransparentImageLayer *transparent_image_layer_create(GRect image_frame);

Layer *transparent_image_layer_get_layer(const TransparentImageLayer *layer);

void transparent_image_layer_destroy(TransparentImageLayer *layer);

void transparent_image_destroy(TransparentImage *image);