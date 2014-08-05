/*

   Official Pebble sample rewritten using transparentimage

   The demonstration image is a modified version of the following SVG
   exported from Inkscape:

       <http://openclipart.org/detail/48919/panda-with-bamboo-leaves-by-adam_lowe>

 */

#include "pebble.h"
#include "transparentimage.h"

static TransparentImage *tr_img;
static TransparentImageLayer *tr_layer;

static Window *window;

static TextLayer *text_layer; // Used as a background to help demonstrate transparency.

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // We do this to account for the offset due to the status bar
  // at the top of the app window.
  GRect layer_frame_description = layer_get_frame(window_layer);
  layer_frame_description.origin.x = 0;
  layer_frame_description.origin.y = 0;

  // Add some background content to help demonstrate transparency.
  text_layer = text_layer_create(layer_frame_description);
  text_layer_set_text(text_layer,
      "pandamonium pandamon\n"
      "ium pandamonium panda\n"
      "monium     pandamonium\n"
      "pandamonium pandamon\n"
      "ium pandamonium panda\n"
      "monium     pandamonium\n"
      "pandamonium pandamon\n"
      "ium pandamonium panda\n"
      "monium pandamonium p\n"
      "andamonium pandamoni\n");
  layer_add_child(window_layer, text_layer_get_layer(text_layer));

  tr_img = trasparent_image_create_with_resources(RESOURCE_ID_IMAGE_PANDA_BLACK,
    RESOURCE_ID_IMAGE_PANDA_WHITE);

  const GPoint center = grect_center_point(&bounds);
  GRect image_frame = (GRect) { .origin = center, .size = tr_img->bounds.size };
  image_frame.origin.x -= tr_img->bounds.size.w/2;
  image_frame.origin.y -= tr_img->bounds.size.h/2;

  tr_layer = transparent_image_layer_create(image_frame);
  transparent_image_layer_set_image(tr_layer, tr_img);
  layer_add_child(window_layer, transparent_image_layer_get_layer(tr_layer));
}

static void window_unload(Window *window) {
  transparent_image_layer_destroy(tr_layer);
  transparent_image_destroy(tr_img);
}

static void init(void) {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload
  });
  window_stack_push(window, true /* Animated */);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}