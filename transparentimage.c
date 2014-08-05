#include "transparentimage.h"

TransparentImage* trasparent_image_create_with_resources(
  uint32_t bitmap_black_res_id, uint32_t bitmap_white_res_id) {
  TransparentImage* transparent_image = (TransparentImage*)malloc(sizeof(TransparentImage));
  transparent_image->white_image = gbitmap_create_with_resource(bitmap_white_res_id);
  transparent_image->black_image = gbitmap_create_with_resource(bitmap_black_res_id);
  transparent_image->bounds = transparent_image->white_image->bounds;
  return transparent_image;
}

BitmapLayer* transparent_white_layer_create(GRect image_frame,
  const GBitmap* white_image) {
  BitmapLayer* white_image_layer = bitmap_layer_create(image_frame);
  bitmap_layer_set_bitmap(white_image_layer, white_image);
  bitmap_layer_set_compositing_mode(white_image_layer, GCompOpOr);
  return white_image_layer;
}

BitmapLayer* transparent_black_layer_create(GRect image_frame,
  const GBitmap* black_image) {
  image_frame.origin.x = 0;
  image_frame.origin.y = 0;
  BitmapLayer* black_image_layer = bitmap_layer_create(image_frame);
  bitmap_layer_set_bitmap(black_image_layer, black_image);
  bitmap_layer_set_compositing_mode(black_image_layer, GCompOpClear);
  return black_image_layer;
}

TransparentImageLayer* transparent_image_layer_create(GRect image_frame,
  const TransparentImage* transparent_image) {
  TransparentImageLayer* transparent_layer = (TransparentImageLayer*)malloc(sizeof(TransparentImageLayer));
  transparent_layer->white_layer = transparent_white_layer_create(image_frame,
    transparent_image->white_image);
  transparent_layer->black_layer = transparent_black_layer_create(image_frame,
    transparent_image->black_image);
  return transparent_layer;
}

Layer* transparent_image_layer_get_layer(const TransparentImageLayer* layer) {
  Layer* white_layer = bitmap_layer_get_layer(layer->white_layer);
  layer_add_child(white_layer, bitmap_layer_get_layer(layer->black_layer));
  return white_layer;
}

void transparent_image_layer_destroy(TransparentImageLayer* layer) {
  bitmap_layer_destroy(layer->white_layer);
  bitmap_layer_destroy(layer->black_layer);
}

void transparent_image_destroy(TransparentImage* image) {
  gbitmap_destroy(image->white_image);
  gbitmap_destroy(image->black_image);
}