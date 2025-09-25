#ifndef PSEUDO_3D_ROTATING_SPRITE_H
#define PSEUDO_3D_ROTATING_SPRITE_H

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class Pseudo3DRotatingSprite : public Sprite2D{
    GDCLASS(Pseudo3DRotatingSprite, Sprite2D);

    private:
        float angle = 0.0f;             
        float rotation_speed = 1.0f;    
        float max_squash = 1.0f;        

        
        float fade_intensity = 1.0f;    
        bool fade_enabled = true;       

        
        bool is_playing = true;

    public:
        
        void set_rotation_speed(float s);
        float get_rotation_speed() const;

        void set_max_squash(float s);
        float get_max_squash() const;

        void set_fade_intensity(float f);
        float get_fade_intensity() const;

        void set_fade_enabled(bool e);
        bool get_fade_enabled() const;

        
        void play() {is_playing = true;}
        void pause() {is_playing = false;}
        void stop() {is_playing = false; reset_rotation();}

        
        void _process(double delta) override;

        
        void reset_rotation();

    protected:
        static void _bind_methods();
};

#endif // PSEUDO_3D_ROTATING_SPRITE_H
