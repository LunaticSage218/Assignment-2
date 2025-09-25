#include "pseudo_3d_rotating_sprite.h"
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/core/math.hpp>
#include <cmath>
#include <algorithm> 

void Pseudo3DRotatingSprite::set_rotation_speed(float s) {rotation_speed = s;}
float Pseudo3DRotatingSprite::get_rotation_speed() const {return rotation_speed;}

void Pseudo3DRotatingSprite::set_max_squash(float s) {max_squash = s;}
float Pseudo3DRotatingSprite::get_max_squash() const {return max_squash;}

void Pseudo3DRotatingSprite::set_fade_intensity(float f){
    fade_intensity = std::clamp(f, 0.0f, 1.0f);
}

float Pseudo3DRotatingSprite::get_fade_intensity() const {return fade_intensity;}

void Pseudo3DRotatingSprite::set_fade_enabled(bool e) {fade_enabled = e;}
bool Pseudo3DRotatingSprite::get_fade_enabled() const {return fade_enabled;}

void Pseudo3DRotatingSprite::_process(double delta){
    if (!is_playing) return; 

    angle += rotation_speed * delta;

    float squash = std::cos(angle) * max_squash;
    set_scale(Vector2(squash, 1.0f));

    if (fade_enabled){
        float fade = (std::cos(angle) * 0.5f + 0.5f) * fade_intensity;
        set_modulate(Color(1.0f, 1.0f, 1.0f, fade));
    }

    else {
        set_modulate(Color(1.0f, 1.0f, 1.0f, 1.0f));
    }

    
    if (std::fmod(angle, Math_PI * 2) < 0.01){
        emit_signal("rotation_completed");
    }
}

void Pseudo3DRotatingSprite::reset_rotation(){
    angle = 0.0f;
    set_scale(Vector2(1.0f, 1.0f));
    set_modulate(Color(1.0f, 1.0f, 1.0f, 1.0f));
}

void Pseudo3DRotatingSprite::_bind_methods(){
    
    ClassDB::bind_method(D_METHOD("set_rotation_speed", "s"), &Pseudo3DRotatingSprite::set_rotation_speed);
    ClassDB::bind_method(D_METHOD("get_rotation_speed"), &Pseudo3DRotatingSprite::get_rotation_speed);
    ClassDB::bind_method(D_METHOD("set_max_squash", "s"), &Pseudo3DRotatingSprite::set_max_squash);
    ClassDB::bind_method(D_METHOD("get_max_squash"), &Pseudo3DRotatingSprite::get_max_squash);
    
    ClassDB::bind_method(D_METHOD("set_fade_intensity", "f"), &Pseudo3DRotatingSprite::set_fade_intensity);
    ClassDB::bind_method(D_METHOD("get_fade_intensity"), &Pseudo3DRotatingSprite::get_fade_intensity);
    ClassDB::bind_method(D_METHOD("set_fade_enabled", "e"), &Pseudo3DRotatingSprite::set_fade_enabled);
    ClassDB::bind_method(D_METHOD("get_fade_enabled"), &Pseudo3DRotatingSprite::get_fade_enabled);
    
    ClassDB::bind_method(D_METHOD("play"), &Pseudo3DRotatingSprite::play);
    ClassDB::bind_method(D_METHOD("pause"), &Pseudo3DRotatingSprite::pause);
    ClassDB::bind_method(D_METHOD("stop"), &Pseudo3DRotatingSprite::stop);

    ClassDB::bind_method(D_METHOD("reset_rotation"), &Pseudo3DRotatingSprite::reset_rotation);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rotation_speed"), "set_rotation_speed", "get_rotation_speed");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_squash"), "set_max_squash", "get_max_squash");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "fade_intensity", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"), "set_fade_intensity", "get_fade_intensity");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "fade_enabled"), "set_fade_enabled", "get_fade_enabled");

    ADD_SIGNAL(MethodInfo("rotation_completed"));
}
