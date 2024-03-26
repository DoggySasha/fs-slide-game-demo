#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include <xengine/app.hpp>
#include <xengine/math.hpp>
#include <xengine/input.hpp>
#include <xengine/enviroment.hpp>
#include <../../packages/xengine.audio/includes/audio.hpp>

using namespace XEngine;

Joystick main_j;
Audio a1("res//1.wav");
Audio a2("res//2.wav");
Audio a3("res//3.wav");
Audio a4("res//4.wav");
Audio success("res//s.wav");
Audio fail("res//f.wav");

class slide_game : public App {
    virtual void initialize() override {
        Renderer::print_host_info();
        AudioManager::initialize();
        AudioManager::print_host_info();
        main_j.update();
        srand((int)Renderer::get_time());
    }

    void play_key(int t_k) {
        switch (t_k) {
        case 1:
            Renderer::set_clear_color(glm::vec4(0.9f, 0.7f, 0.7f, 1.f));
            a1.play();
            break;
        case 2:
            Renderer::set_clear_color(glm::vec4(0.7f, 0.9f, 0.7f, 1.f));
            a2.play();
            break;
        case 3:
            Renderer::set_clear_color(glm::vec4(0.7f, 0.7f, 0.9f, 1.f));
            a3.play();
            break;
        case 4:
            Renderer::set_clear_color(glm::vec4(0.9f, 0.9f, 0.9f, 1.f));
            a4.play();
            break;
        }
    }

    int key_num = 1;
    int played = 0;
    int pl_played = 0;
    int timeoff = 2000;
    int timeoff_minus = 50;
    int cur_to = 2000;
    int first_ev_kn = 1;
    const char* seq = "";
    const char* pl_seq = "";
    virtual void update() override {
        if(window.height <= 0) return;
        if(first_ev_kn >= 5 && played==key_num) {
            if(Keyboard::key_down(KEY_1)) {play_key(1);pl_seq+=1;pl_played++;}
            if(Keyboard::key_down(KEY_2)) {play_key(2);pl_seq+=2;pl_played++;}
            if(Keyboard::key_down(KEY_3)) {play_key(3);pl_seq+=3;pl_played++;}
            if(Keyboard::key_down(KEY_4)) {play_key(4);pl_seq+=4;pl_played++;}
        }
        if(pl_played == key_num && first_ev_kn > 8) {
            if(seq == pl_seq) {
                success.play();
                cur_to = 4000;
                played = 0;
                pl_played = 0;
                seq = "";
                pl_seq = "";
                if(timeoff != 50) timeoff-=timeoff_minus;
                key_num++;
            }
            else {
                fail.play();
                cur_to = 4000;
                played = 0;
                pl_played = 0;
                seq = "";
                pl_seq = "";
                timeoff = 2000;
                key_num = 1;
            }
        }
        cur_to--;
        if(cur_to == 0) {
            cur_to = timeoff;
        } else return;
        if(first_ev_kn < 5)
            play_key(first_ev_kn);
        else if(first_ev_kn >  7 && played!=key_num) {
            int k = rand() % (4 - 1 + 1) + 1;
            seq+= k;
            play_key(k);
            played++;
        }
        first_ev_kn++;
    }

    virtual void on_shutdown() override {
    }
};

int main() { 
    //Create instance of app.
    auto app = std::make_unique<slide_game>();
    int returnC = app->start(800, 600, "Slide game");
    return 0;
}
