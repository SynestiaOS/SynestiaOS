//
// Created by XingfengYang on 2020/7/16.
//
#ifndef __LIBRARY_LIBGUI_ANIMATION_H__
#define __LIBRARY_LIBGUI_ANIMATION_H__

#include <stdint.h>
#include <gui_component.h>

typedef enum GUIAnimationType{
    AnimationTranslation,
    AnimationRotate,
} GUIAnimationType;

typedef struct GUIAnimation{
    GUIAnimationType animationType;
    GUIComponent *component;
    uint32_t time;
} GUIAnimation;

typedef struct GUIAnimationTranslation{
    GUIAnimation animation;
    uint32_t posX;
    uint32_t posY;
    uint32_t posZ;
} GUIAnimationTranslation;

typedef struct GUIAnimationRotateX{
    GUIAnimation animation;
    uint32_t angle;
} GUIAnimationRotateX;

void gui_animation_translation_create(GUIAnimation *animation, GUIComponent *component, uint32_t time, uint32_t targetX,uint32_t targetY);

void gui_animation_update(GUIAnimation *animation);

void gui_animation_start(GUIAnimation *animation);

#endif // __LIBRARY_LIBGUI_ANIMATION_H__