//
// Created by XingfengYang on 2020/7/16.
//

#include <gui_animation.h>
#include <list.h>

void gui_animation_translation_create(GUIAnimationTranslation *animation, GUIComponent *component, uint32_t time,
                                      uint32_t targetX, uint32_t targetY) {
  animation->animation.component = component;
  animation->animation.animationType = ANIMATION_TRANSLATION;
  animation->animation.time = time;

  animation->posX = component->position.x;
  animation->posY = component->position.y;

  animation->targetX = component->position.x + targetX;
  animation->targetY = component->position.y + targetY;

  animation->speedX = targetX / time;
  animation->speedY = targetY / time;
}

void gui_animation_update(GUIAnimation *animation) {
  switch (animation->animationType) {
  case ANIMATION_TRANSLATION: {
    GUIAnimationTranslation *translation = getNode(animation, GUIAnimationTranslation, animation);
    animation->component->position.x += translation->speedX;
    animation->component->position.y += translation->speedX;
    if (animation->component->position.x >= translation->targetX) {
      animation->component->position.x -= translation->posX;
    }
    if (animation->component->position.y >= translation->targetY) {
      animation->component->position.y -= translation->posY;
    }
  } break;

  default:
    break;
  }
}