#include <pebble.h>
#include <time.h>
#include "SweFuzClock.h"

//#define DEBUG true

static Window *window;
static TextLayer *text_layer;


/*
########  ##     ## ######## ########  #######  ##    ##  ######  
##     ## ##     ##    ##       ##    ##     ## ###   ## ##    ## 
##     ## ##     ##    ##       ##    ##     ## ####  ## ##       
########  ##     ##    ##       ##    ##     ## ## ## ##  ######  
##     ## ##     ##    ##       ##    ##     ## ##  ####       ## 
##     ## ##     ##    ##       ##    ##     ## ##   ### ##    ## 
########   #######     ##       ##     #######  ##    ##  ######
*/
/*
  Enable use of buttons to easily change the timestring (Must also set watchface in
  appinfo to false)
*/
#ifdef DEBUG

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Select");
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Up");
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Down");
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

#endif
/*
##      ## #### ##    ## ########   #######  ##      ## 
##  ##  ##  ##  ###   ## ##     ## ##     ## ##  ##  ## 
##  ##  ##  ##  ####  ## ##     ## ##     ## ##  ##  ## 
##  ##  ##  ##  ## ## ## ##     ## ##     ## ##  ##  ## 
##  ##  ##  ##  ##  #### ##     ## ##     ## ##  ##  ## 
##  ##  ##  ##  ##   ### ##     ## ##     ## ##  ##  ## 
 ###  ###  #### ##    ## ########   #######   ###  ###  
*/

static void window_load(Window *window) {

  FuzTime* ft = (FuzTime*)malloc(sizeof(FuzTime));
  time_t now = time(NULL);
  struct tm* tim = localtime(&now);
  FuzTime_create(ft,tim);

  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, 20 } });
  text_layer_set_text(text_layer, ft->lineOne);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
  
  FuzTime_destroy(ft);
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void init(void) {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);

  #ifdef DEBUG
    window_set_click_config_provider(window, click_config_provider);
  #endif
}

static void deinit(void) {
  window_destroy(window);
}

/*
##     ##    ###    #### ##    ## 
###   ###   ## ##    ##  ###   ## 
#### ####  ##   ##   ##  ####  ## 
## ### ## ##     ##  ##  ## ## ## 
##     ## #########  ##  ##  #### 
##     ## ##     ##  ##  ##   ### 
##     ## ##     ## #### ##    ## 
*/

int main(void) {
  init();
/*
  FuzTime* ft = (FuzTime*)malloc(sizeof(FuzTime));
  time_t now = time(NULL);
  //struct tm* tim = localtime(&now);
  struct tm* tim = (struct tm*)malloc(sizeof(struct tm*));
  tim->tm_hour = 12;
  tim->tm_min = 34;
  
  FuzTime_create(ft, tim);
*/
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}
