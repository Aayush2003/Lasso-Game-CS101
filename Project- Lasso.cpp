#include <simplecpp>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
// ctime needed to generate sequence of "random" numbers at start of program
using namespace simplecpp;

//movingObject.h
#ifndef _MOVINGOBJECT_INCLUDED_
#define _MOVINGOBJECT_INCLUDED_

#include <simplecpp>
#include <vector>
#include <composite.h>
#include <sprite.h>

using namespace simplecpp;

class MovingObject : public Sprite {
  vector<Sprite*> parts;
  double vx, vy;
  double ax, ay;
  bool paused;
  void initMO(double argvx, double argvy, double argax, double argay, bool argpaused=true) {
    vx=argvx; vy=argvy; ax=argax; ay=argay; paused=argpaused;
  }
 public:
 MovingObject(double argvx, double argvy, double argax, double argay, bool argpaused=true)
    : Sprite() {
    initMO(argvx, argvy, argax, argay, argpaused);
  }
 MovingObject(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : Sprite() {
   double angle_rad = angle_deg*PI/180.0;
   double argvx = speed*cos(angle_rad);
   double argvy = -speed*sin(angle_rad);
   initMO(argvx, argvy, argax, argay, argpaused);
  }
  void set_vx(double argvx) { vx = argvx; }
  void set_vy(double argvy) { vy = argvy; }
  void set_ax(double argax) { ax = argax; }
  void set_ay(double argay) { ay = argay; }
  double getXPos();
  double getYPos();
  void reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta);

  void pause() { paused = true; }
  void unpause() { paused = false; }
  bool isPaused() { return paused; }

  void addPart(Sprite* p) {
    parts.push_back(p);
  }
  void nextStep(double t);
  void getAttachedTo(MovingObject *m);
};

#endif

//MovingObject.cpp

void MovingObject::nextStep(double t) {
  if(paused) { return; }
  //cerr << "x=" << getXPos() << ",y=" << getYPos() << endl;
  //cerr << "vx=" << vx << ",vy=" << vy << endl;
  //cerr << "ax=" << ax << ",ay=" << ay << endl;

  for(size_t i=0; i<parts.size(); i++){
    parts[i]->move(vx*t, vy*t);
  }
  vx += ax*t;
  vy += ay*t;
} // End MovingObject::nextStep()

double MovingObject::getXPos() {
  return (parts.size() > 0) ? parts[0]->getX() : -1;
}

double MovingObject::getYPos() {
  return (parts.size() > 0) ? parts[0]->getY() : -1;
}

void MovingObject::reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) {
  for(size_t i=0; i<parts.size(); i++){
    parts[i]->moveTo(argx, argy);
  }
  double angle_rad = angle_deg*PI/180.0;
  double argvx = speed*cos(angle_rad);
  double argvy = -speed*sin(angle_rad);
  vx = argvx; vy = argvy; ax = argax; ay = argay; paused = argpaused;
} // End MovingObject::reset_all()

void MovingObject::getAttachedTo(MovingObject *m) {
  double xpos = m->getXPos();
  double ypos = m->getYPos();
  for(size_t i=0; i<parts.size(); i++){
    parts[i]->moveTo(xpos, ypos);
  }
  initMO(m->vx, m->vy, m->ax, m->ay, m->paused);
}

//coin.h    other sprites also present here
#ifndef __COIN_H__
#define __COIN_H__

class Coin : public MovingObject {
  double coin_start_x;
  double coin_start_y;
  double release_speed;
  double release_angle_deg;
  double coin_ax;
  double coin_ay;

  // Moving parts
  Circle coin_circle;

 public:
 Coin(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    coin_ax = argax;
    coin_ay = argay;
    initCoin();
  }

  void initCoin();
  void resetCoin();

}; // End class Coin
// Bomb
class Bomb : public MovingObject {
  double bomb_start_x;
  double bomb_start_y;
  double release_speed;
  double release_angle_deg;
  double bomb_ax;
  double bomb_ay;

  // Moving parts
  Circle bomb_circle;

 public:
 Bomb(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    bomb_ax = argax;
    bomb_ay = argay;
    initBomb();
  }

  void initBomb();
  void resetBomb();
}; // End class Bomb
// Mystery Box
class Mystery : public MovingObject {
  double mystery_start_x;
  double mystery_start_y;
  double release_speed;
  double release_angle_deg;
  double mystery_ax;
  double mystery_ay;

  // Moving parts
  Rectangle mystery_box;

 public:
 Mystery(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    mystery_ax = argax;
    mystery_ay = argay;
    initMystery();
  }

  void initMystery();
  void resetMystery();

}; // End class Mystery

#endif

//lasso.h
#ifndef __LASSO_H__
#define __LASSO_H__

//#define WINDOW_X 1200
//#define WINDOW_Y 960
#define WINDOW_X 800
#define WINDOW_Y 600

#define STEP_TIME 0.05

#define PLAY_X_START 100
#define PLAY_Y_START 0
#define PLAY_X_WIDTH (WINDOW_X-PLAY_X_START)
#define PLAY_Y_HEIGHT (WINDOW_Y-100)

#define LASSO_X_OFFSET 100
#define LASSO_Y_HEIGHT 100
#define LASSO_BAND_LENGTH LASSO_X_OFFSET
#define LASSO_THICKNESS 5

#define COIN_GAP 1

#define RELEASE_ANGLE_STEP_DEG 5
#define MIN_RELEASE_ANGLE_DEG 0
#define MAX_RELEASE_ANGLE_DEG (360-RELEASE_ANGLE_STEP_DEG)
#define INIT_RELEASE_ANGLE_DEG 45

#define RELEASE_SPEED_STEP 20
#define MIN_RELEASE_SPEED 0
#define MAX_RELEASE_SPEED 200
#define INIT_RELEASE_SPEED 110

#define COIN_SPEED 120
#define BOMB_SPEED 120
#define MYSTERY_SPEED 120
#define COIN_ANGLE_DEG 90
#define BOMB_ANGLE_DEG 110
#define MYSTERY_ANGLE_DEG 95
#define LASSO_G 30
#define COIN_G 30

#define LASSO_SIZE 10
#define LASSO_RADIUS 50
#define COIN_SIZE 5

double coin_throw_angle = COIN_ANGLE_DEG;  // Global variable indicating angle of throw of coin
double coin_xattraction = 0;  // Global variable indicating attraction of coin along x axis

class Lasso : public MovingObject {
  double lasso_start_x;
  double lasso_start_y;
  double release_speed;
  double release_angle_deg;
  double lasso_ax;
  double lasso_ay;

  // Moving parts
  Circle lasso_circle;
  Circle lasso_loop;

  // Non-moving parts
  Line lasso_line;
  Line lasso_band;

  // State info
  bool lasso_looped;
  Coin *the_coin;
  Bomb *the_bomb;
  Mystery *the_mystery;
  int num_coins;
  int lives;
  void initLasso();
 public:
 Lasso(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    lasso_ax = argax;
    lasso_ay = argay;
    initLasso();
  }

  void draw_lasso_band();
  void yank();
  void loopit();
  void addAngle(double angle_deg);
  void addSpeed(double speed);

  void nextStep(double t);
  void check_for_coin(Coin *coin);
  void check_for_bomb(Bomb *bomb);
  bool check_for_mystery(Mystery *mystery);  // Checks whether mystery box has been caught, and returns true/false, so that state changes can take place in main program
  int getNumCoins() { return num_coins; }
  int getNumLives() { return lives; }

}; // End class Lasso

#endif

//coin.h   other sprites also present here

void Coin::initCoin() {
  coin_start_x = (PLAY_X_START+WINDOW_X)/2;
  coin_start_y = PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  coin_circle.setColor(COLOR("yellow"));
  coin_circle.setFill(true);
  addPart(&coin_circle);
}

void Coin::resetCoin() {
  double coin_speed = COIN_SPEED;
  // Random angle of throw and global value of ax
  double coin_angle_deg = coin_throw_angle;
  coin_ax = coin_xattraction;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}
//Bomb
void Bomb::initBomb() {
  bomb_start_x = (PLAY_X_START+WINDOW_X)/2;
  bomb_start_y = PLAY_Y_HEIGHT;
  bomb_circle.reset(bomb_start_x, bomb_start_y, COIN_SIZE);
  bomb_circle.setColor(COLOR("black"));
  bomb_circle.setFill(true);
  addPart(&bomb_circle);
}

void Bomb::resetBomb() {
  double bomb_speed = BOMB_SPEED;
  double bomb_angle_deg = coin_throw_angle+10;  // Thrown 10deg off coin
  bomb_ax = 0;
  bomb_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(bomb_start_x, bomb_start_y, bomb_speed, bomb_angle_deg, bomb_ax, bomb_ay, paused, rtheta);
}
//Mystery Box
void Mystery::initMystery() {
  mystery_start_x = (PLAY_X_START+WINDOW_X)/2;
  mystery_start_y = PLAY_Y_HEIGHT;
  mystery_box.reset(mystery_start_x, mystery_start_y, 10,10);
  mystery_box.setColor(COLOR("green"));
  mystery_box.setFill(true);
  addPart(&mystery_box);
}

void Mystery::resetMystery() {
  double mystery_speed = MYSTERY_SPEED;
  double mystery_angle_deg = coin_throw_angle-7;   // Thrown 7deg off coin
  mystery_ax = 0;
  mystery_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(mystery_start_x, mystery_start_y, mystery_speed, mystery_angle_deg, mystery_ax, mystery_ay, paused, rtheta);
}

//lasso.cpp

void Lasso::draw_lasso_band() {
  double len = (release_speed/MAX_RELEASE_SPEED)*LASSO_BAND_LENGTH;
  double arad = release_angle_deg*PI/180.0;
  double xlen = len*cos(arad);
  double ylen = len*sin(arad);
  lasso_band.reset(lasso_start_x, lasso_start_y, (lasso_start_x-xlen), (lasso_start_y+ylen));
  lasso_band.setThickness(LASSO_THICKNESS);
} // End Lasso::draw_lasso_band()

void Lasso::initLasso() {
  lasso_start_x = (PLAY_X_START+LASSO_X_OFFSET);
  lasso_start_y = (PLAY_Y_HEIGHT-LASSO_Y_HEIGHT);
  lasso_circle.reset(lasso_start_x, lasso_start_y, LASSO_SIZE);
  lasso_circle.setColor(COLOR("red"));
  lasso_circle.setFill(true);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setColor(COLOR("black"));
  lasso_loop.setFill(true);
  addPart(&lasso_circle);
  addPart(&lasso_loop);
  lasso_looped = false;
  the_coin = NULL;
  the_bomb = NULL;
  the_mystery=NULL;
  num_coins = 0;
  lives=3;
  lasso_line.reset(lasso_start_x, lasso_start_y, lasso_start_x, lasso_start_y);
  lasso_line.setColor(COLOR("black"));

  lasso_band.setColor(COLOR("blue"));
  draw_lasso_band();

} // End Lasso::initLasso()

void Lasso::yank() {
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setFill(true);
  lasso_looped = false;
  if(the_coin != NULL) {
    the_coin->resetCoin();
    the_coin=NULL;    // Setting coin status back to NULL
  }
  if(the_bomb != NULL) {
    the_bomb->resetBomb();
    the_bomb=NULL;    // Setting bomb status back to NULL
  }
  if(the_mystery != NULL) {
    the_mystery->resetMystery();
    the_mystery=NULL;  // Setting mystery box status back to NULL
  }
} // End Lasso::yank()

void Lasso::loopit() {
  if(lasso_looped) { return; } // Already looped
  lasso_loop.reset(getXPos(), getYPos(), LASSO_RADIUS);
  lasso_loop.setFill(false);
  lasso_looped = true;
} // End Lasso::loopit()

void Lasso::addAngle(double angle_deg) {
  release_angle_deg += angle_deg;
  if(release_angle_deg < MIN_RELEASE_ANGLE_DEG) { release_angle_deg = MIN_RELEASE_ANGLE_DEG; }
  if(release_angle_deg > MAX_RELEASE_ANGLE_DEG) { release_angle_deg = MAX_RELEASE_ANGLE_DEG; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addAngle()

void Lasso::addSpeed(double speed) {
  release_speed += speed;
  if(release_speed < MIN_RELEASE_SPEED) { release_speed = MIN_RELEASE_SPEED; }
  if(release_speed > MAX_RELEASE_SPEED) { release_speed = MAX_RELEASE_SPEED; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addSpeed()

void Lasso::nextStep(double stepTime) {
  draw_lasso_band();
  MovingObject::nextStep(stepTime);
  if(getYPos() > PLAY_Y_HEIGHT) { yank(); }
  lasso_line.reset(lasso_start_x, lasso_start_y, getXPos(), getYPos());
} // End Lasso::nextStep()

void Lasso::check_for_coin(Coin *coinPtr) {
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();
  double xdiff = (lasso_x - coin_x);
  double ydiff = (lasso_y - coin_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <= LASSO_RADIUS) {
    num_coins++;
    the_coin = coinPtr;
    the_coin->getAttachedTo(this);
  }
} // End Lasso::check_for_coin()

void Lasso::check_for_bomb(Bomb *bombPtr) {
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double bomb_x = bombPtr->getXPos();
  double bomb_y = bombPtr->getYPos();
  double xdiff = (lasso_x - bomb_x);
  double ydiff = (lasso_y - bomb_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <= LASSO_RADIUS) {
    lives-=1;
    the_bomb = bombPtr;
    the_bomb->getAttachedTo(this);
  }
} // End Lasso::check_for_bomb()

bool Lasso::check_for_mystery(Mystery *mysteryPtr) {
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double mystery_x = mysteryPtr->getXPos();
  double mystery_y = mysteryPtr->getYPos();
  double xdiff = (lasso_x - mystery_x);
  double ydiff = (lasso_y - mystery_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <= LASSO_RADIUS) {
    the_mystery = mysteryPtr;
    the_mystery->getAttachedTo(this);
    return true;
  }
  return false;
}  // End Lasso::check_for_mystery()

// Functions to generate random number and angle , as learnt from stackoverflow
int randomizer(){
    return rand();
}

double give_angle(){   // Function to generate random angle of throw
    return 95.0+randomizer()%11;
}

main_program {
  cout<<"  #     #   ###  ###  ###"<<endl;
  cout<<"  #    # #  #    #    # #"<<endl;
  cout<<"  #    ###  ###  ###  # #"<<endl;
  cout<<"  #    # #    #    #  # #"<<endl;
  cout<<"  ###  # #  ###  ###  ###"<<endl;
  cout<<"\n"; wait(2);
  cout<<"Howdy, cowboy! Show off your skills with the lasso as you set off on a journey to unlock treasures and mysteries."<<endl;
  cout<<"But be wary of the bandits who may attempt to hurl a bomb at you!"<<endl; wait(2);
  cout<<"\n"<<"RULES:"<<endl;
  cout<<"1.You have 3 lives only to try and maximise your score over 3 levels."<<endl;
  cout<<"2.In level 1, there is just one coin being projected vertically upwards. Catch 3 such yellow coins, and you move on to level 2."<<endl;
  cout<<"3.In level 2, coins, black bombs, and the occasional green mystery box are projected at random angles. Catching a bomb leads to the loss of a life."<<endl;
  cout<<"  The mystery box may increase/decrease your lasso speed, earn you bonus points, or activate a limited period magnet that attracts coins to the left."<<endl;
  cout<<"  Upon catching 10 more coins, you move on to level 3."<<endl;
  cout<<"4.Level 3 has a limited time in which you have to try and catch as many coins as possible. There are no mystery boxes here. Time left will appear on top right."<<endl;
  cout<<"5.Final score will be displayed on THIS window."<<endl; wait(2);
  cout<<"\n"<<"CONTROLS:"<<endl;
  cout<<"When t is pressed, throw lasso."<<endl;
  cout<<"When l is pressed, loop lasso. If objects within loop, they stick."<<endl;
  cout<<"When y is pressed, yank lasso."<<endl;
  cout<<"When q is pressed, quit during game."<<endl;
  cout<<"When ] is pressed, angle of throw of lasso increases."<<endl;
  cout<<"When [ is pressed, angle of throw of lasso decreases."<<endl;
  cout<<"\n"<<"Are you ready cowboy? Click the game window if ready."<<endl;
  //Initalising Game.
  simplecpp::srand((unsigned)time(0));    // Generating sequence of random numbers, as learnt from stackoverflow
  initCanvas("Lasso", WINDOW_X, WINDOW_Y);
  int stepCount = 0;
  float stepTime = STEP_TIME;
  float runTime = -1; // sec; -ve means infinite
  float currTime = 0;
  float magTime = 100000000;
  int time_left=-1;   // Time left in level (for level 3)
  int time_over=0;

  // Draw lasso at start position
  double release_speed = INIT_RELEASE_SPEED; // m/s
  double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
  double lasso_ax = 0;
  double lasso_ay = LASSO_G;
  bool paused = true;
  bool rtheta = true;
  Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);

  Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
  b1.setColor(COLOR("blue"));
  Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);
  b2.setColor(COLOR("blue"));

  string msg("Cmd: _");
  Text charPressed(PLAY_X_START+50, PLAY_Y_HEIGHT+20, msg);
  char coinScoreStr[256];
  char life[256];
  char level_no[256];
  char timeTaken[256];
  char timeLeft[256]=" ";
  sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
  sprintf(life, "Lives: %d", lasso.getNumLives());
  Text coinScore(PLAY_X_START+50, PLAY_Y_HEIGHT+50, coinScoreStr);                     // Displays coins collected
  Text lifeLeft(PLAY_X_START+150, PLAY_Y_HEIGHT+50, life);                             // Displays lives left
  Text levelStatus(PLAY_X_START+250, PLAY_Y_HEIGHT+50, level_no);                      // Displays level number
  Text enhancements(PLAY_X_START+550, PLAY_Y_HEIGHT+50, "Last Enhancement: None");     // Displays enhancements from mystery box
  Text timer(PLAY_X_START+550, 30, timeTaken);                                         // Displays time taken
  Text countdown(PLAY_X_START+550, 80, timeLeft);                                      // Displays time left in level 3
  //Creating sprites and their required parameters.
  paused = true; rtheta = true;
  double coin_speed = COIN_SPEED;
  double bomb_speed = BOMB_SPEED;
  double mystery_speed= MYSTERY_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  double bomb_angle_deg = BOMB_ANGLE_DEG;
  double mystery_angle_deg = MYSTERY_ANGLE_DEG;
  double coin_ax = 0;
  double coin_ay = COIN_G;
  Coin coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
  Bomb bomb(bomb_speed, bomb_angle_deg, coin_ax, coin_ay, paused, rtheta);
  Mystery mystery(mystery_speed, mystery_angle_deg, coin_ax, coin_ay, paused, rtheta);   // Initial position and acceleration of coin, bomb and mystery box are same
  Rectangle rpole(PLAY_X_START+15,PLAY_Y_HEIGHT-220,30,50);
  Rectangle lpole(PLAY_X_START-15,PLAY_Y_HEIGHT-220,30,50);
  rpole.setColor(COLOR("white"));
  rpole.setFill(true);
  lpole.setColor(COLOR("white"));
  lpole.setFill(true);
  bomb.pause();
  mystery.pause();
  char b='d';    //Indicating bombs are deactivated
  char m='d';    //Indicating mystery boxes are deactivated
  int level=1;
  int coin_bonus=0;
  bool mystery_found=false;
  bool want_to_leave=false;
  // After every COIN_GAP sec, make the coin jump
  double last_coin_jump_end = 0;
  getClick();
  // Game Begins
  for(;;) {
    if((runTime > 0) && (currTime > runTime)) { break; }
    if(lasso.getNumLives()<=0) { break; }
    if(currTime > magTime) {   // Magnet Expiry
        magTime=100000000;
        coin_xattraction=0;
        rpole.setColor(COLOR("white"));
        lpole.setColor(COLOR("white"));
        rpole.setFill(true);
        lpole.setFill(true);
    }
    if(lasso.getNumCoins()==3 && level==1){
        level=2;
        b='a'; // Bombs are activated
        m='s'; // Mystery Boxes are activated, but decrease speed
        coin_throw_angle=give_angle();  // Generating random coin angle from level 2
    }
    else if(lasso.getNumCoins()==13 && level==2){
        level=3;
        m='d'; // Mystery Boxes are deactivated
        runTime=currTime+24; // Finite time limit
    }
    // Take in character
    XEvent e;
    bool pendingEv = checkEvent(e);
    if(pendingEv) {
      char c = charFromEvent(e);
      msg[msg.length()-1] = c;
      charPressed.setMessage(msg);
      switch(c) {
      case 't':
	lasso.unpause();
	break;
      case 'y':
	if(mystery_found==true){
        if(m=='s'){
            lasso.addSpeed(-RELEASE_SPEED_STEP);  // Slows down lasso
            enhancements.setMessage("Last Enhancement: Slow Down");
        }
        else if(m=='f'){
            lasso.addSpeed(+RELEASE_SPEED_STEP);  // Speeds up lasso
            enhancements.setMessage("Last Enhancement: Speed Up");
        }
        else if(m=='m'){
            enhancements.setMessage("Last Enhancement: Coin Magnet");
            magTime=currTime+12;
            coin_xattraction=-15;    // Magnetization in effect
            rpole.setColor(COLOR("red"));
            lpole.setColor(COLOR("blue"));
            rpole.setFill(true);
            lpole.setFill(true);
        }
        else if(m=='b'){
            enhancements.setMessage("Last Enhancement: Coin Bonus");
            coin_bonus=coin_bonus+1+randomizer()%5;   // Bonus points added
        }
        mystery_found=false;
    }

    lasso.yank();
	break;
      case 'l':
	lasso.loopit();
	lasso.check_for_coin(&coin);
	if(b!='d'){
        lasso.check_for_bomb(&bomb);   // Checking for bomb, if in use
    }
	if(m!='d' && m!='n'){
        mystery_found=lasso.check_for_mystery(&mystery);  // Checking for mystery box, if in use
    }
	wait(STEP_TIME*5);
	break;
      case '[':
	if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
	break;
      case ']':
	if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
	break;
      case '-':   // CHEAT CODE, not to be used in actual game
	if(lasso.isPaused()) { lasso.addSpeed(-RELEASE_SPEED_STEP); }
	break;
      case '=':   // CHEAT CODE, not to be used in actual game
	if(lasso.isPaused()) { lasso.addSpeed(+RELEASE_SPEED_STEP); }
	break;
      case 'q':
	want_to_leave=true;
      default:
	break;
      }
    }
    if(want_to_leave){break;}  // Quit game
    lasso.nextStep(stepTime);
    coin.nextStep(stepTime);
    bomb.nextStep(stepTime);
    mystery.nextStep(stepTime);

    // Launching sprites, only IF coin is set to be launched
    if(coin.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
        if(level!=1){coin_throw_angle=give_angle();}
        coin.unpause();
        if(b!='d'){  // Launch bomb if in use
            bomb.unpause();
        }
        if(mystery.isPaused() && m!='d'){  // Launch mystery box if in use and assign characteristics
            int n=randomizer()%15;   // Generate a number from 0 to 14
            if(n<=4){
                m='n';  // Mystery Box not used
            }
            else if(n>4 && n<=7){
                m='s';  // Mystery Box decreases speed of lasso
                mystery.unpause();
            }
            else if(n>7 && n<=10){
                m='f';  // Mystery Box increases speed of lasso
                mystery.unpause();
            }
            else if(n>10 && n<=12){
                m='m';  // Magnet On
                mystery.unpause();
            }
            else{
                m='b';  // Bonus Coins
                mystery.unpause();
            }
        }
      }
    }
    //Resetting sprites if they go out of frame
    if(coin.getYPos() > PLAY_Y_HEIGHT) {
      coin.resetCoin();
      last_coin_jump_end = currTime;
    }
    if(bomb.getYPos() > PLAY_Y_HEIGHT) {
      bomb.resetBomb();
    }
    if(mystery.getYPos() > PLAY_Y_HEIGHT) {
      mystery.resetMystery();
    }
    // Formatting attributes to be displayed
    sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
    sprintf(life, "Lives: %d", lasso.getNumLives());
    sprintf(level_no, "Level: %d", level);
    time_over=2.5*currTime;
    sprintf(timeTaken, "Time Taken: %d", time_over);
    coinScore.setMessage(coinScoreStr);
    lifeLeft.setMessage(life);
    levelStatus.setMessage(level_no);
    timer.setMessage(timeTaken);
    if(level==3){
        time_left=2.5*(runTime-currTime);
        sprintf(timeLeft, "Time Left: %d", time_left);
        countdown.setMessage(timeLeft);
    }

    stepCount++;
    currTime += stepTime;
    wait(stepTime);
  } // End for(;;)

  wait(3);
  int finalscore;
  // Calculate final score based on parameters
  if(level==1){
    finalscore=lasso.getNumCoins()*20;
  }
  else if(level==2){
    finalscore=lasso.getNumCoins()*20+50+lasso.getNumLives()*10+coin_bonus*10;
  }
  else if(level==3){
    finalscore=lasso.getNumCoins()*20+100+lasso.getNumLives()*20+coin_bonus*10;
  }
  cout<<"\n"<<"GAME OVER!"<<endl; wait(1);
  cout<<"Final level reached: "<<level<<endl; wait(1);
  cout<<"Number of coins collected: "<<lasso.getNumCoins()<<endl; wait(1);
  cout<<"Number of lives left: "<<lasso.getNumLives()<<endl; wait(1);
  cout<<"Coin Bonus Collected: "<<coin_bonus<<endl; wait(1);
  cout<<"Final Score: "<<finalscore<<endl; wait(1);
  cout<<"Time Taken: "<<time_over<<endl; wait(1);
  cout<<"Thank You for playing!"<<endl; wait(3);
} // End main_program
