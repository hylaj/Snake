#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h> 
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

#define display_height 600
#define display_width 600
enum DIR { R, L, U, D };

struct Body {
  int x;
  int y;
  Body* next;
  Body* previous;
  DIR direction;
};

struct Snake {
  Body* head;
  Body* tail;
  int length;
};

Snake* New_Snake() {
  Snake* new_snake = new Snake;
  new_snake->head = 0;
  new_snake->tail = 0;
  return new_snake;
}

void Add_Body(Snake* S, int x_body, int y_body, DIR dir) {
  Body* new_part = new Body;
  new_part->x = x_body;
  new_part->y = y_body;
  new_part->direction = dir;
  new_part->previous = 0;
  new_part->next = S->head;
  S->head = new_part;
  S->length++;
  if (new_part->next) new_part->next->previous = new_part;
  else S->tail = new_part;
}

void Move_Snake(Snake* S, int dx, int dy) {
  Body* temp = S->tail;
  while (temp->previous != NULL)
  {
    temp->x = temp->previous->x;
    temp->y = temp->previous->y;
    temp->direction = temp->previous->direction;
    temp = temp->previous;
  }
  S->head->x += dx;
  S->head->y += dy;
}

struct Apple {
  int x;
  int y;
  int which_fruit_v;
  int which_fruit_h;
};

void Apple_lottery(Apple* apple)
{
  //losowanie rodzaju jabłka
  apple->which_fruit_v = (rand() % 4) * 30;
  apple->which_fruit_h = (rand() % 5) * 30;
}

void Generate_apple(Snake* snake, Apple* apple, int dx, int dy) {

  //jeśli jabłko zostało zjedzone to wąż się wydłuża
  if (snake->head) Add_Body(snake, snake->head->x + dx, snake->head->y + dy, snake->head->direction);

  apple->x = (rand() % 20) * 30;
  apple->y = (rand() % 20) * 30;

  //czy jabłko nie koliduje z wężem
  Body* temp1 = snake->head;
  while (temp1)
  {
    if (abs(apple->x - temp1->x) < 60 && abs(apple->y - temp1->y) < 60)
    {
      temp1 = snake->head;
      apple->x = (rand() % 20) * 30;
      apple->y = (rand() % 20) * 30;
    }
    else
    {
      temp1 = temp1->next;
    }
  }

  Apple_lottery(apple);
}

void Draw_Snake(Snake* S, ALLEGRO_BITMAP* bitmap, int dx, int dy) {

  Body* temp = S->head;
  while (temp)
  {
    if (temp->previous == 0) //rysowanie głowy
    {
      if (temp->direction == R)
        al_draw_bitmap_region(bitmap, 4 * 30, 0 * 30, 30, 30, temp->x, temp->y, 0);

      if (temp->direction == L)
        al_draw_bitmap_region(bitmap, 4 * 30, 1 * 30, 30, 30, temp->x, temp->y, 0);

      if (temp->direction == D)
        al_draw_bitmap_region(bitmap, 3 * 30, 1 * 30, 30, 30, temp->x, temp->y, 0);

      if (temp->direction == U)
        al_draw_bitmap_region(bitmap, 3 * 30, 0 * 30, 30, 30, temp->x, temp->y, 0);
    }

    else if (temp->next != 0) // rysowanie ciała
    {
      if (temp->direction == U && temp->previous->direction != D && temp->next->direction == R)
        al_draw_bitmap_region(bitmap, 6 * 30, 1 * 30, 30, 30, temp->x, temp->y, 0);

      else if (temp->direction == L && temp->previous->direction != R && temp->next->direction == D)
        al_draw_bitmap_region(bitmap, 6 * 30, 1 * 30, 30, 30, temp->x, temp->y, 0);

      else if (temp->direction == D && temp->previous->direction != U && temp->next->direction == L)
        al_draw_bitmap_region(bitmap, 5 * 30, 1 * 30, 30, 30, temp->x, temp->y, 0);

      else if (temp->direction == R && temp->previous->direction != L && temp->next->direction == U)
        al_draw_bitmap_region(bitmap, 5 * 30, 1 * 30, 30, 30, temp->x, temp->y, 0);

      else if (temp->direction == U && temp->previous->direction != D && temp->next->direction == L)
        al_draw_bitmap_region(bitmap, 5 * 30, 0 * 30, 30, 30, temp->x, temp->y, 0);

      else if (temp->direction == R && temp->previous->direction != L && temp->next->direction == D)
        al_draw_bitmap_region(bitmap, 5 * 30, 0 * 30, 30, 30, temp->x, temp->y, 0);

      else if (temp->direction == D && temp->previous->direction != U && temp->next->direction == R)
        al_draw_bitmap_region(bitmap, 6 * 30, 0 * 30, 30, 30, temp->x, temp->y, 0);

      else if (temp->direction == L && temp->previous->direction != R && temp->next->direction == U)
        al_draw_bitmap_region(bitmap, 6 * 30, 0 * 30, 30, 30, temp->x, temp->y, 0);

      else if (temp->x == temp->previous->x && temp->y != temp->previous->y)
        al_draw_bitmap_region(bitmap, 2 * 30, 0 * 30, 30, 30, temp->x, temp->y, 0);

      else if (temp->y - temp->previous->y == 0 && temp->x != temp->previous->x)
        al_draw_bitmap_region(bitmap, 2 * 30, 1 * 30, 30, 30, temp->x, temp->y, 0);
    }
    else if (temp->next == 0) // rysowanie ogona
    {
      if (temp->direction == R)
        al_draw_bitmap_region(bitmap, 1 * 30, 0 * 30, 30, 30, temp->x, temp->y, 0);
      if (temp->direction == L)
        al_draw_bitmap_region(bitmap, 0 * 30, 1 * 30, 30, 30, temp->x, temp->y, 0);
      if (temp->direction == U)
        al_draw_bitmap_region(bitmap, 0 * 30, 0 * 30, 30, 30, temp->x, temp->y, 0);
      if (temp->direction == D)
        al_draw_bitmap_region(bitmap, 1 * 30, 1 * 30, 30, 30, temp->x, temp->y, 0);
    }
    temp = temp->next;
  }
}

void Draw_Apple(Apple* A, ALLEGRO_BITMAP* bitmap) {
  al_draw_bitmap_region(bitmap, A->which_fruit_v, A->which_fruit_h, 30, 30, A->x, A->y, 0);
}

int empty(Snake* s) {
  return s->head == 0;
}

void Delete_Snake(Snake* snake) {
  if (empty(snake)) return;
  Body* deleted_part = snake->head;

  while (snake->head)
  {
    deleted_part = snake->head;
    snake->head = deleted_part->next;
    delete(deleted_part);
  }
}

void Delete_Apple(Apple* apple)
{
  delete(apple);
}

int Best_score(int score) {
  int best_score;
  fstream file;
  file.open("BestScore.txt", ios::in);
  if (!file)
  {
    return 1;
  }
  else {
    file >> best_score;
    file.close();

    if (best_score < score)
    {
      file.open("BestScore.txt", ios::out);
      file << score;
      best_score = score;
    }
    file.close();
  }
  return best_score;
}

//ustawianie początkowych wartości
void Reset_Game(Snake* snake, Apple* apple, int x, int y)
{
  snake->head->x = x;
  snake->head->y = y;
  snake->head->direction = R;
  snake->head->next->x = x - 30;
  snake->head->next->y = y;
  snake->head->next->direction = R;
  snake->head->next->next->x = x - 60;
  snake->head->next->next->y = y;
  snake->head->next->next->direction = R;
  snake->head->next->next->next = 0;

  snake->length = 3;

  apple->x = x + 120;
  apple->y = y;
}



int main()
{
  srand(time(NULL));
  al_init();
  al_install_keyboard();
  al_init_image_addon();
  al_init_font_addon();
  al_init_ttf_addon();


  ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
  ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
  ALLEGRO_DISPLAY* display = al_create_display(display_width, display_height);
  ALLEGRO_FONT* font_small = al_load_ttf_font("courbdd.ttf", 24, 0);
  ALLEGRO_FONT* font_small1 = al_load_ttf_font("courbdd.ttf", 18, 0);
  ALLEGRO_FONT* font = al_load_ttf_font("courbd.ttf", 24, 0);
  ALLEGRO_FONT* font_big = al_load_ttf_font("courbd.ttf", 80, 0);
  ALLEGRO_BITMAP* fruits = al_load_bitmap("food.png");
  ALLEGRO_BITMAP* animal = al_load_bitmap("waz.png");
  ALLEGRO_BITMAP* background = al_load_bitmap("szaszki.png");
  ALLEGRO_BITMAP* background_start = al_load_bitmap("night.png");


  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(display));
  al_register_event_source(queue, al_get_timer_event_source(timer));

  int last_score = 0;
  int score = 0;
  bool game_start = 0;
  bool running = 1;
  int next_game = 0;
  bool redraw = true;
  int check = 0;
  bool alive = 0;
  bool moving = 1;
  bool is_apple = 1;
  int x = display_width / 2 - 30;
  int y = display_height / 2 - 30;
  int dx = 30, dy = 0;
  bool pressed_keys[ALLEGRO_KEY_MAX];
  memset(pressed_keys, 0, sizeof(pressed_keys)); // inicjowanie pamięci

  // tworzenie początkowego węża
  Snake* snake = New_Snake();
  snake->length = 0;
  Add_Body(snake, x - 60, y, R);
  Add_Body(snake, x - 30, y, R);
  Add_Body(snake, x, y, R);

  alive = 0;

  Apple* apple = new Apple;
  apple->x = x + 120;
  apple->y = y;
  Apple_lottery(apple);

  ALLEGRO_EVENT event;
  al_start_timer(timer);

  while (running)
  {
    al_wait_for_event(queue, &event);

    switch (event.type) {
    case ALLEGRO_EVENT_TIMER:

      //start przy wciśnięciu enter (możliwość restaru też)
      if (alive == 0 && pressed_keys[ALLEGRO_KEY_ENTER])
      {
        Reset_Game(snake, apple, x, y);
        check = 0;
        alive = 1;
        dx = 30; dy = 0;
        next_game = 0;
        is_apple = 1;
        game_start = 1;

      }
      // reakcja na wciśnięcie klawiszy - odpowiedzialna za zmiane kierunku i poruszanie
      if (alive && pressed_keys[ALLEGRO_KEY_RIGHT] && dx != -30 && moving == 1)
      {
        dx = 30;  dy = 0;
        moving = 0;
        snake->head->direction = R;
      }
      if (alive && pressed_keys[ALLEGRO_KEY_LEFT] && dx != 30 && moving == 1)
      {
        dx = -30;  dy = 0;
        moving = 0;
        snake->head->direction = L;
      }
      if (alive && pressed_keys[ALLEGRO_KEY_UP] && dy != 30 && moving == 1)
      {
        dx = 0;  dy = -30;
        moving = 0;
        snake->head->direction = U;
      }
      if (alive && pressed_keys[ALLEGRO_KEY_DOWN] && dy != -30 && moving == 1)
      {
        dx = 0;  dy = 30;
        moving = 0;
        snake->head->direction = D;
      }

      // jeśli wąż żyje, to co 6 klatek poruszamy węża 
      if (alive && check > 6)
      {
        check = 0;

        // czy wąż nie uderzył w ramy
        if (snake->head->x + dx <0 || snake->head->x + dx >(display_width - 30)) alive = 0;
        if (snake->head->y + dy <0 || snake->head->y + dy >(display_height - 30)) alive = 0;

        //czy wąż nie uderzył w siebie
        Body* temp = snake->head->next;
        while (temp)
        {
          if (snake->head->x == temp->x && snake->head->y == temp->y) alive = 0;
          temp = temp->next;
        }
        if (alive == 0) last_score = Best_score(score);

        // jeśli wąż żyje, to sie rusza
        if (alive == 1)
        {
          Move_Snake(snake, dx, dy);
          moving = 1;
        }
      }

      //tworzenie jablka
      if (is_apple == 0)
      {
        Generate_apple(snake, apple, dx, dy);
        is_apple = 1;
      }

      // czy wąż zjadł jabłko
      if (snake->head && alive) {
        if ((abs(snake->head->x - apple->x) + abs(snake->head->y - apple->y)) < 30)
        {
          apple->x = -30;
          apple->y = -30;
          is_apple = 0;
        }
      }

      if (pressed_keys[ALLEGRO_KEY_ESCAPE]) running = 0;

      redraw = 1;
      check++;
      break;

    case ALLEGRO_EVENT_KEY_DOWN:
      pressed_keys[event.keyboard.keycode] = true;
      break;

    case ALLEGRO_EVENT_KEY_UP:
      pressed_keys[event.keyboard.keycode] = false;
      break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE: running = 0;
    }
    score = snake->length - 3;

    if (redraw && al_is_event_queue_empty(queue))
    {
      al_clear_to_color(al_map_rgb(0, 0, 0));

      if (alive == 0) // liczymy 120 klatek aby wyświetlać w tym czasie stare ustawienie węża
      {
        next_game++;

      }

      if (game_start == 0) // rysowanie ekranu startowego
      {
        al_draw_bitmap(background_start, 0, 0, 0);
        al_draw_textf(font_big, al_map_rgb(255, 255, 255), 180, 230, 0, "SNAKE");
        al_draw_textf(font_small, al_map_rgb(255, 255, 255), 195, 330, 0, "Press ENTER to start");
      }

      if (game_start == 1)
      {
        al_draw_bitmap(background, 0, 0, 0);

        if (next_game < 120) { // rysowanie
          Draw_Apple(apple, fruits);
          Draw_Snake(snake, animal, dx, dy);
        }
        else {
          Reset_Game(snake, apple, x, y); // reset i rysowanie ustawień początkowych jeśli wąż nie żyje
          Draw_Apple(apple, fruits);
          Draw_Snake(snake, animal, dx, dy);
          al_draw_textf(font_small, al_map_rgb(255, 255, 255), 125, 330, 0, "Press ENTER to start a new game");
          al_draw_textf(font_small1, al_map_rgb(255, 255, 255), 220, 370, 0, "Press ESCAPE to exit");
          al_draw_textf(font, al_map_rgb(255, 255, 255), 205, 470, 0, "Your best score: %d", last_score);
        }

        if (alive == 0)
        {
          al_draw_textf(font_big, al_map_rgb(255, 255, 255), 80, 160, 0, "GAME OVER");
        }

        al_draw_textf(font, al_map_rgb(255, 255, 255), 250, 33, 0, "SCORE: %d", score); // wyswietlanie punktow
      }
      al_flip_display();

      redraw = false;
    }
  }

  al_destroy_font(font);
  al_destroy_font(font_small);
  al_destroy_font(font_small1);
  al_destroy_font(font_big);
  al_destroy_bitmap(fruits);
  al_destroy_bitmap(animal);
  al_destroy_bitmap(background);
  al_destroy_bitmap(background_start);
  al_destroy_display(display);
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);
  al_uninstall_keyboard();

  Delete_Snake(snake);
  Delete_Apple(apple);

  return 0;
}
