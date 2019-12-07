#include "GameCamara.h"

GameCamara::GameCamara()
{
  // Status de movimiento inical
  FORWARD = false;
  BACKWARD = false;
  LEFT = false;
  RIGTH = false;

  // Status de Tiempo
  PREVIUSTIME = 0;
  moveforward_backward = 50.0f;
  moveSiteward = 30.9f;

  // Status del observador
  EYE_X = 0;
  EYE_Y = 0;
  EYE_Z = 0;
  CENTER_X=1;
  CENTER_Y=1;
  CENTER_Z=1;
  UP_X=0;
  UP_Y=1;
  UP_Z=0;

  // Status del Mouse
  mouseDirectionX = 0;
	mouseDirectionY = 0;

	mouseWarp = true;

}

GameCamara::~GameCamara()
{
    //dtor
}
