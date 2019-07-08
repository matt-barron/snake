//An old snake game
//I will try to make it into a competitive player 1 v player 2 game
//must run in terminal as such g++ -lncurses snake.cpp
#include <cstdlib>
#include <ncurses.h>
bool gameOver;
const int width = 20;
const int height =20;
int x, y, fruitX, fruitY, score;
//position of the snake x, y, fruit x, y, and score
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
int TailX[100], TailY[100];
int nTail=0;
void setup(){
  initscr();
  clear();
  noecho();
  cbreak();
  curs_set(0);
  gameOver = false;
  dir = STOP;
  x = width/2;
  y = height/2;//starts the snake in the middle
  fruitX= (rand()%width)+1;
  fruitY= (rand()%height)+1;//makes sure that the fruit spawns within the border at random
  score=0;
}
void draw(){
  clear();

  for(int i = 0; i<width+2;i++){
    mvprintw(0,i,"+");//prints horizontal top border
  }
  for(int j = 0; j< height+2; j++){
    for(int i = 0; i<width+2;i++){
      if(j==0|j==21)
        {mvprintw(j,i,"+");}
      else if(i==0|i==21)
        {mvprintw(j,i,"+");}
      else if(j == y && i ==x)
          {mvprintw(j,i,"O");}//prints the first snake
      else if(j == fruitY && i == fruitX)
          {mvprintw(j,i,"@");} //prints the fruit
      else{
        for (int k = 0; k < nTail; k++) {
          if (TailX[k] == i && TailY[k] == j) {
            mvprintw(j, i, "o");
          }
        }
      }
    }
  }
  mvprintw(23,0,"Score1: %d",score);
  refresh();

}
void input(){
  keypad(stdscr, TRUE);
  halfdelay(1);
  int c = getch();
  switch(c){
    case KEY_LEFT:
      dir = LEFT;
      break;
    case KEY_RIGHT:
      dir = RIGHT;
      break;
    case KEY_UP:
      dir = UP;
      break;
    case KEY_DOWN:
      dir = DOWN;
      break;
    case 113:
     gameOver = true;
     break;
  }

}
void logic(){
  int prevX = TailX[0];
  int prevY = TailY[0];
  int prev2X, prev2Y;
  TailX[0] = x;
  TailY[0] = y;
  for (int i = 1; i < nTail; i++) {
    prev2X = TailX[i];
    prev2Y = TailY[i];
    TailX[i] = prevX;
    TailY[i] = prevY;
    prevX = prev2X;
    prevY = prev2Y;
  }
  switch(dir)
  {
    case LEFT:
      x--;
      break;
    case RIGHT:
      x++;
      break;
    case UP:
      y--;
      break;
    case DOWN:
      y++;
      break;
    default:
      break;
  }
  if(x > width || x < 1 || y < 1 || y > height)
  {gameOver = true;}
  if(x == fruitX && y == fruitY){
    score++;
    fruitX= (rand()%width)+1;
    fruitY= (rand()%height)+1;//makes sure that the fruit spawns within the border at random
    nTail++;//increases size of tail
  }
  for (int i = 0; i < nTail; i++) {
    if (TailX[i] == x && TailY[i] == y) {
      gameOver = true;
    }
  }
}
int main()
{
  setup();
   while(!gameOver){
     draw();
     input();
     logic();
   }// the game loop running until it is over
   getch();
   endwin();
  return 0;
}
