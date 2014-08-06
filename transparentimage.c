#include "transparentimage.h"

TransparentImage *trasparent_image_create_with_resources(
    uint32_t bitmap_black_res_id, uint32_t bitmap_white_res_id) {
  TransparentImage *transparent_image = (TransparentImage*)malloc(sizeof(TransparentImage));
  transparent_image->white_image = gbitmap_create_with_resource(bitmap_white_res_id);
  transparent_image->black_image = gbitmap_create_with_resource(bitmap_black_res_id);
  transparent_image->bounds = transparent_image->white_image->bounds;
  return transparent_image;
}

BitmapLayer *transparent_white_layer_create(GRect image_frame) {
  BitmapLayer *white_image_layer = bitmap_layer_create(image_frame);
  return white_image_layer;
}

BitmapLayer *transparent_black_layer_create(GRect image_frame) {
  image_frame.origin.x = 0;
  image_frame.origin.y = 0;
  BitmapLayer *black_image_layer = bitmap_layer_create(image_frame);
  return black_image_layer;
}

TransparentImageLayer *transparent_image_layer_create(GRect image_frame) {
  TransparentImageLayer *transparent_layer = (TransparentImageLayer*)malloc(sizeof(TransparentImageLayer));
  transparent_layer->white_layer = transparent_white_layer_create(image_frame);
  transparent_layer->black_layer = transparent_black_layer_create(image_frame);
  return transparent_layer;
}

void transparent_image_layer_set_image(const TransparentImageLayer *layer,
    const TransparentImage *image) {
  bitmap_layer_set_bitmap(layer->black_layer, image->black_image);
  bitmap_layer_set_compositing_mode(layer->black_layer, GCompOpClear);
  bitmap_layer_set_bitmap(layer->white_layer, image->white_image);
  bitmap_layer_set_compositing_mode(layer->white_layer, GCompOpOr);
}

Layer *transparent_image_layer_get_layer(const TransparentImageLayer *layer) {
  Layer *white_layer = bitmap_layer_get_layer(layer->white_layer);
  layer_add_child(white_layer, bitmap_layer_get_layer(layer->black_layer));
  return white_layer;
}

void transparent_image_layer_destroy(TransparentImageLayer *layer) {
  bitmap_layer_destroy(layer->white_layer);
  bitmap_layer_destroy(layer->black_layer);
  free(layer);
  layer = 0;
}

void transparent_image_destroy(TransparentImage *image) {
  gbitmap_destroy(image->white_image);
  gbitmap_destroy(image->black_image);
  free(image);
  image = 0;
}