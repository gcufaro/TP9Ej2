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
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

const float FPS = 10;
const int SCREEN_W = 850;
const int SCREEN_H = 600;
const int BOUNCER_SIZE = 32;
enum MYKEYS {
   KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_B, KEY_C, KEY_S,
};
//enum MYKEYS {
  // KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
//};


typedef  struct
{
 unsigned int  bit0        : 1;
 unsigned int  bit1	   : 1;
 unsigned int  bit2        : 1;  
 unsigned int  bit3        : 1;  
 unsigned int  bit4        : 1;  
 unsigned int  bit5        : 1;
 unsigned int  bit6        : 1;
 unsigned int  bit7        : 1;
} MYPORT;

void encender(ALLEGRO_BITMAP *LED0a, ALLEGRO_DISPLAY *displaya, int numa);
void apagar(ALLEGRO_BITMAP *LED0b, ALLEGRO_DISPLAY *displayb, int numb);
void bitSet(int a, MYPORT *p1);
void bitClr(int b, MYPORT *p2);
void bitToggle(int c, MYPORT *p3);
unsigned int bitGet(int d, MYPORT *p4);
void maskOn(char mask, MYPORT *p5);
void maskOff(char mask, MYPORT *p6);



int main(int argc, char** argv) {
    
    MYPORT portA;
    MYPORT*p2port;
    p2port=&portA;
    portA.bit0=0;
    portA.bit1=0;
    portA.bit2=0;
    portA.bit3=0;
    portA.bit4=0;
    portA.bit5=0;
    portA.bit6=0;
    portA.bit7=0;
            
    
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
   //bool key[4] = { false, false, false, false };

   bool key[12] = { false, false, false, false, false, false, false, false, false, false, false, false};
   bool redraw = true;
   bool doexit = false;
   
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }

   al_init_font_addon(); // initialize the font addon
   al_init_ttf_addon();// initialize the ttf (True Type Font) addon
   
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
   
   ALLEGRO_FONT *font = al_load_ttf_font("pirulen.ttf",30,0 );
   if (!font){
      fprintf(stderr, "Could not load 'pirulen.ttf'.\n");
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
   al_clear_to_color(al_map_rgb(255, 0, 0));
   al_set_target_bitmap(LED1);
   al_clear_to_color(al_map_rgb(255, 0, 0));
   al_set_target_bitmap(LED2);
   al_clear_to_color(al_map_rgb(255, 0, 0));
   al_set_target_bitmap(LED3);
   al_clear_to_color(al_map_rgb(255, 0, 0));
   al_set_target_bitmap(LED4);
   al_clear_to_color(al_map_rgb(255, 0, 0));
   al_set_target_bitmap(LED5);
   al_clear_to_color(al_map_rgb(255, 0, 0));
   al_set_target_bitmap(LED6);
   al_clear_to_color(al_map_rgb(255, 0, 0));
   al_set_target_bitmap(LED7);
   al_clear_to_color(al_map_rgb(255, 0, 0));
 
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
   
   al_register_event_source(event_queue, al_get_keyboard_event_source()); //meti los tres eventos en la misma cola

   al_clear_to_color(al_map_rgb(0,0,0));
 
   al_flip_display();
 
   al_start_timer(timer);   
   
   al_clear_to_color(al_map_rgb(0,0,0));
   
   while(!doexit)
   {
       ALLEGRO_EVENT ev;
       al_wait_for_event(event_queue, &ev);
       
        

         
         
         al_draw_text(font, al_map_rgb(255,255,255), SCREEN_W/2, (SCREEN_H/5),ALLEGRO_ALIGN_CENTER, "Banco de Pruebas");
         //al_draw_bitmap(LED0, 50, 300, 0);
         //al_draw_bitmap(LED1, 150, 300, 0);
         //al_draw_bitmap(LED2, 250, 300, 0);
         //al_draw_bitmap(LED3, 350, 300, 0);
         //al_draw_bitmap(LED4, 450, 300, 0);
         //al_draw_bitmap(LED5, 550, 300, 0);
         //al_draw_bitmap(LED6, 650, 300, 0);
         //al_draw_bitmap(LED7, 750, 300, 0);

      if(ev.type == ALLEGRO_EVENT_TIMER) { //me fijo si hubo evento de timer
         if(portA.bit0) { //luego lo vinculo con la tecla que apreté.
                 encender(LED0,display,0);
         }  else apagar(LED0,display,0);
         if(portA.bit1) { //luego lo vinculo con la tecla que apreté.
                 encender(LED1,display,1);
         }  else apagar(LED1,display,1);
         if(portA.bit2) { //luego lo vinculo con la tecla que apreté.
                 encender(LED2,display,2);
         }  else apagar(LED2,display,2);
         if(portA.bit3) { //luego lo vinculo con la tecla que apreté.
                 encender(LED3,display,3);
         }  else apagar(LED3,display,3);
         if(portA.bit4) { //luego lo vinculo con la tecla que apreté.
                 encender(LED4,display,4);
         }  else apagar(LED4,display,4);
         if(portA.bit5) { //luego lo vinculo con la tecla que apreté.
                 encender(LED5,display,5);
         }  else apagar(LED5,display,5);
         if(portA.bit6) { //luego lo vinculo con la tecla que apreté.
                 encender(LED6,display,6);
         }  else apagar(LED6,display,6);
         if(portA.bit7) { //luego lo vinculo con la tecla que apreté.
                 encender(LED7,display,7);
         }  else apagar(LED7,display,7);
    //     if(key[KEY_C]) { //luego lo vinculo con la tecla que apreté.
    //             apagar(LED0,display,0);
    //             apagar(LED1,display,1);
   //              apagar(LED2,display,2);
    //             apagar(LED3,display,3);
    //             apagar(LED4,display,4);
    //             apagar(LED5,display,5);
  //               apagar(LED6,display,6);
    //             apagar(LED7,display,7);
    //             key[KEY_C]=false;
    //     }
    //     if(key[KEY_S]) { //luego lo vinculo con la tecla que apreté.
    //             encender(LED0,display,0);
    //             encender(LED1,display,1);
     //            encender(LED2,display,2);
     //            encender(LED3,display,3);
   //              encender(LED4,display,4);
    //             encender(LED5,display,5);
  ///               encender(LED6,display,6);
     //            encender(LED7,display,7);
     //            key[KEY_S]=false;
     //    }
 
         redraw = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) { //quiero registrar solo el momento que presione
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_1:
               bitToggle(0, p2port);
               break;
            case ALLEGRO_KEY_2:
               bitToggle(1, p2port);
               break;
            case ALLEGRO_KEY_3:
               bitToggle(2, p2port);
               break;
            case ALLEGRO_KEY_4:
               bitToggle(3, p2port);
               break;
            case ALLEGRO_KEY_5:
               bitToggle(4, p2port);
               break;
            case ALLEGRO_KEY_6:
               bitToggle(5, p2port);
               break;
            case ALLEGRO_KEY_7:
               bitToggle(6, p2port);
               break;
            case ALLEGRO_KEY_8:
               bitToggle(7, p2port);
               break;
            case ALLEGRO_KEY_C:
                maskOff(255, p2port);
               break;
            case ALLEGRO_KEY_S:
                maskOn(255, p2port);
               break;
            case ALLEGRO_KEY_B:
                apagar(LED0,display,0);
                apagar(LED1,display,1);
                apagar(LED2,display,2);
                apagar(LED3,display,3);
                apagar(LED4,display,4);
                apagar(LED5,display,5);
                apagar(LED6,display,6);
                apagar(LED7,display,7);
 
         }
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) { //cuando suelto, quiero que el programa lo registre
         switch(ev.keyboard.keycode) {
             case ALLEGRO_KEY_ESCAPE:
               doexit = true;
               break;
         }
      }

         
         
         
         
         
         
         
         
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

void encender(ALLEGRO_BITMAP *LED0a, ALLEGRO_DISPLAY *displaya, int numa)
{
    numa=50+100*numa;
   al_set_target_bitmap(LED0a);
   al_clear_to_color(al_map_rgb(255, 0, 0));
   al_set_target_bitmap(al_get_backbuffer(displaya));
   al_draw_bitmap(LED0a, numa, 300, 0);
}

void apagar(ALLEGRO_BITMAP *LED0b, ALLEGRO_DISPLAY *displayb, int numb)
{
    numb=50+100*numb;
   al_set_target_bitmap(LED0b);
   al_clear_to_color(al_map_rgb(0, 0, 0));
   al_set_target_bitmap(al_get_backbuffer(displayb));
   al_draw_bitmap(LED0b, numb, 300, 0);
}

void bitSet(int a, MYPORT *p1)
{
    switch (a)
    {
        case 0:    p1->bit0=1; 
            break;
        case 1:    p1->bit1=1;
            break;
        case 2:    p1->bit2=1; 
            break;
        case 3:    p1->bit3=1;
            break;
        case 4:    p1->bit4=1;
            break;
        case 5:    p1->bit5=1;
            break;
        case 6:    p1->bit6=1;
            break;
        case 7:    p1->bit7=1;
            break;
        default: printf("Bit no valido\n");
            break;
    }
}

void bitClr(int b, MYPORT *p2)
{
    switch (b)
    {
        case 0:    p2->bit0=0; 
            break;
        case 1:    p2->bit1=0;
            break;
        case 2:    p2->bit2=0; 
            break;
        case 3:    p2->bit3=0;
            break;
        case 4:    p2->bit4=0;
            break;
        case 5:    p2->bit5=0;
            break;
        case 6:    p2->bit6=0;
            break;
        case 7:    p2->bit7=0;
            break;
        default: printf("Bit no valido\n");
            break;
    }
}

void bitToggle(int c, MYPORT *p3)
{
    switch (c)
    {
        case 0:    if(p3->bit0==0)
                    (p3->bit0=1); else{
                    p3->bit0=0;
                    }; 
            break;
        case 1:    if(p3->bit1==0)
                    (p3->bit1=1); else{
                    p3->bit1=0;
                    }; 
            break;
        case 2:    if(p3->bit2==0)
                    (p3->bit2=1); else{
                    p3->bit2=0;
                    }; 
            break;
        case 3:    if(p3->bit3==0)
                    (p3->bit3=1); else{
                    p3->bit3=0;
                    }; 
            break;
        case 4:    if(p3->bit4==0)
                    (p3->bit4=1); else{
                    p3->bit4=0;
                    }; 
            break;
        case 5:    if(p3->bit5==0)
                    (p3->bit5=1); else{
                    p3->bit5=0;
                    }; 
            break;
        case 6:    if(p3->bit6==0)
                    (p3->bit6=1); else{
                    p3->bit6=0;
                    }; 
            break;
        case 7:    if(p3->bit7==0)
                    (p3->bit7=1); else{
                    p3->bit7=0;
                    }; 
            break;
        default: printf("Bit no valido\n");
            break;
    }
}

unsigned int bitGet(int d, MYPORT *p4)
{
    switch (d)
    {
        case 0:    return(p4->bit0); 
            break;
        case 1:    return(p4->bit1); 
            break;
        case 2:    return(p4->bit2); 
            break;
        case 3:    return(p4->bit3); 
            break;
        case 4:    return(p4->bit4); 
            break;
        case 5:    return(p4->bit5); 
            break;
        case 6:    return(p4->bit6); 
            break;
        case 7:    return(p4->bit7); 
            break;
        default: printf("Bit no valido\n");
            break;
    }    
}

// Función que carga una máscara en MYPORT//

void maskOn(char maskon, MYPORT *p5)
{
    if(128&maskon)
        p5->bit7=1;
    if(64&maskon)
        p5->bit6=1;
    if(32&maskon)
        p5->bit5=1;
    if(16&maskon)
        p5->bit4=1;
    if(8&maskon)
        p5->bit3=1;
    if(4&maskon)
        p5->bit2=1;
    if(2&maskon)
        p5->bit1=1;
    if(1&maskon)
        p5->bit0=1;
    
    
//	*p5=(*p5|maskon);       //Prendo los bits que deseo con la máscara
}



void maskOff(char maskoff, MYPORT *p6)
{
    
    if(128&maskoff)
        p6->bit7=0;
    if(64&maskoff)
        p6->bit6=0;
    if(32&maskoff)
        p6->bit5=0;
    if(16&maskoff)
        p6->bit4=0;
    if(8&maskoff)
        p6->bit3=0;
    if(4&maskoff)
        p6->bit2=0;
    if(2&maskoff)
        p6->bit1=0;
    if(1&maskoff)
        p6->bit0=0;
    
    
//	*p6=(*p6&(!maskoff));	//Apago los bits que deseo con la màscara
}
