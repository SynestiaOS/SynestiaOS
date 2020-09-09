//
// Created by XingfengYang on 2020/7/16.
//
#ifndef __LIBRARY_LIBGUI_ANIMATION_H__
#define __LIBRARY_LIBGUI_ANIMATION_H__

#include <gui_component.h>
#include <stdint.h>

typedef enum GUIAnimationType {
    ANIMATION_TRANSLATION,
    ANIMATION_ROTATE,
} GUIAnimationType;

typedef struct GUIAnimation {
    GUIAnimationType animationType;
    GUIComponent* component;
    uint32_t time;
} GUIAnimation;

typedef struct GUIAnimationTranslation {
    GUIAnimation animation;
    uint32_t beginX;
    uint32_t beginY;
    uint32_t currentX;
    uint32_t currentY;
    uint32_t posX;
    uint32_t posY;
    uint32_t targetX;
    uint32_t targetY;
    uint32_t speedX;
    uint32_t speedY;
} GUIAnimationTranslation;

typedef struct GUIAnimationRotateX {
    GUIAnimation animation;
    uint32_t angle;
} GUIAnimationRotateX;

void gui_animation_translation_create(GUIAnimationTranslation* animation, GUIComponent* component, uint32_t time,
    uint32_t targetX, uint32_t targetY);

void gui_animation_update(GUIAnimation* animation);

#endif // __LIBRARY_LIBGUI_ANIMATION_H__