/* 
 * File:   main.c
 * Author: Mercedes
 *
 * Created on 26 de mayo de 2015, 23:05
 */

#include "stdio.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;

int main(int argc, char** argv) {
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   ALLEGRO_BITMAP *LED0 = NULL;
   ALLEGRO_BITMAP *LED1 = NULL;
   ALLEGRO_BITMAP *LED2 = NULL;
   ALLEGRO_BITMAP *LED3 = NULL;
   ALLEGRO_BITMAP *LED4 = NULL;
   ALLEGRO_BITMAP *LED5 = NULL;
   ALLEGRO_BITMAP *LED6 = NULL;
   ALLEGRO_BITMAP *LED7 = NULL;
   
   float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0; //pongo la pelotita en el medio
   float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;

   bool key[4] = { false, false, false, false };
   bool redraw = true;
   bool doexit = false;
   
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
 
         if(!al_install_keyboard()) {
      fprintf(stderr, "failed to initialize the keyboard!\n");
      return -1;
   }

   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }
 
   display = al_create_display(800,600);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      return -1;
   }
 
   LED0 = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
   LED1 = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
   LED2 = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
   LED3 = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
   LED4 = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
   LED5 = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
   LED6 = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
   LED7 = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
   
   if(!LED0 || !LED1 || !LED2 || !LED3 || !LED4 || !LED5 || !LED6 || !LED7) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   } 
   
   al_set_target_bitmap(LED0);
   al_clear_to_color(al_map_rgb(255, 0, 255));
   al_set_target_bitmap(LED1);
   al_clear_to_color(al_map_rgb(255, 0, 255));
   al_set_target_bitmap(LED2);
   al_clear_to_color(al_map_rgb(255, 0, 255));
   al_set_target_bitmap(LED3);
   al_clear_to_color(al_map_rgb(255, 0, 255));
   al_set_target_bitmap(LED4);
   al_clear_to_color(al_map_rgb(255, 0, 255));
   al_set_target_bitmap(LED5);
   al_clear_to_color(al_map_rgb(255, 0, 255));
   al_set_target_bitmap(LED6);
   al_clear_to_color(al_map_rgb(255, 0, 255));
   al_set_target_bitmap(LED7);
   al_clear_to_color(al_map_rgb(255, 0, 255));
 
   al_set_target_bitmap(al_get_backbuffer(display));
 
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_bitmap(LED0);
        al_destroy_bitmap(LED1);
        al_destroy_bitmap(LED2);
        al_destroy_bitmap(LED3);
        al_destroy_bitmap(LED4);
        al_destroy_bitmap(LED5);
        al_destroy_bitmap(LED6);
        al_destroy_bitmap(LED7);      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
 
   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
 
   al_clear_to_color(al_map_rgb(0,0,0));
 
   al_flip_display();
 
   al_start_timer(timer);   
   
   while(1)
   {
       ALLEGRO_EVENT ev;
       al_wait_for_event(event_queue, &ev);
       
      if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
        
         al_clear_to_color(al_map_rgb(0,0,0));
 
         al_draw_bitmap(LED0, 50, 300, 0);
         al_draw_bitmap(LED1, 150, 300, 0);
         al_draw_bitmap(LED2, 250, 300, 0);
         al_draw_bitmap(LED3, 350, 300, 0);
         al_draw_bitmap(LED4, 450, 300, 0);
         al_draw_bitmap(LED5, 550, 300, 0);
         al_draw_bitmap(LED6, 650, 300, 0);
         al_draw_bitmap(LED7, 750, 300, 0);
         al_flip_display();
       

   }
   
   
   al_destroy_bitmap(LED0);
   al_destroy_bitmap(LED1);
   al_destroy_bitmap(LED2);
   al_destroy_bitmap(LED3);
   al_destroy_bitmap(LED4);
   al_destroy_bitmap(LED5);
   al_destroy_bitmap(LED6);
   al_destroy_bitmap(LED7);
   
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
   
   return(0);
}

