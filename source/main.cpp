#include <RSGL/RSGL.hpp>

bool running = true;

RSGL::window win("RSGLLonic Popcorn Shop",{500,500,481,351},{255,255,255});

std::vector<RSGL::point> mouseStates;
std::string images = "res/images/", curLonic="LonicRun1.png";

int popy=-2000; bool stop = false, stop2=true, introP=true, intro=false, options=false,play=false, gameover=false; int tick=0, hits=3;
int switchTick=0;

std::vector<RSGL::point> cords={{-45,290},{-55,300},{-25,50},{-25,20}};
std::vector<std::vector<bool>> stops = {{false,true},{false,true},{false,true},{false,true}};
std::vector<int> ticks = {0,0,0,0}; 

int main(int args,char** argv){
    srand(time(NULL));
    while (running){
        win.checkEvents(); tick++;
        if (win.event.type==RSGL::quit) running=false;
        if (!options && !gameover) RSGL::drawImage("res/images/background.png",{0,0,481,351});
        RSGL::drawImage(images+"popcorn.png",{0,popy,487,655});

        if (popy != 0 && stop2) popy+=20; else if (stop2) stop=true; 
        if (stop){ 
            if (stop2 & tick >= 40 ){ popy-=20;  stop2=false; tick=0; }
            if (!stop2 && tick >= 5 ){ popy+=20;  stop=false; tick=0; }
        } 
        else if (!stop2){
            RSGL::drawImage(images+"RSGL.png",{20,cords.at(0).x,70,50});
            RSGL::drawText("©RSGL 2022",{330,cords.at(1).x,12},"res/fonts/PublicPixel.ttf",{210,0,60});
            RSGL::drawText("RSGLLONIC",{20,cords.at(2).x,30},"res/fonts/SansPosterBold.ttf",{210,0,60});
            RSGL::drawImage(images+"shop.png",{-40,cords.at(3).x,532,288});
            for (int i=0; i < cords.size(); i++){
                if ( cords.at(i).x <= cords.at(i).y && stops.at(i).at(1)) cords.at(i).x+=18; else if (stops.at(i).at(1)) stops.at(i).at(0)=true;
                if (stops.at(i).at(0) && stops.at(i).at(1) & ticks.at(i) >= 0 ){ cords.at(i).x-=40;  stops.at(i).at(1)=false; ticks.at(i)=0; }
                if (stops.at(i).at(0) && !stops.at(i).at(1) && ticks.at(i) >= 15 ){ cords.at(i).x+=40;  stops.at(i).at(0)=false; ticks.at(i)=0; 
                    if (i==cords.size()-1) introP=false;
                } ticks.at(i)++;
            }
        } if (tick == 480 && !introP) intro=true;
        if (intro && !options && !play && !gameover){
            if(!(popy >= 369)){ for (int i=0; i < cords.size(); i++) cords.at(i).x++; popy++;} 
            else{
                RSGL::drawImage(images+"buttons.png",{0,150,300,200});
                RSGL::drawText("left-click\n(play)",{10,295,10},"res/fonts/PublicPixel.ttf",{0,0,0});
                RSGL::drawText("right-click\n(options)",{120,295,10},"res/fonts/PublicPixel.ttf",{0,0,0});     

                if (win.event.type == RSGL::MouseButtonPressed && win.event.button==RSGL::mouseLeft){ play=true; tick=0;}
                else if (win.event.type == RSGL::MouseButtonPressed && win.event.button==RSGL::mouseRight) options=true;   
            } 
        }
        if (play){
            int wait=0;
            RSGL::drawImage(images+"ramp.png",{0,210,481,53});
            RSGL::drawImage(images+"Biden.png",{200,105,130,120});
            RSGL::drawImage(images+curLonic,{320,105,120,120});
                        
            mouseStates.insert(mouseStates.end(),win.event.mouse);
            if (!hits) play=false;
            RSGL::drawText("Hits " + std::to_string(hits),{200,80,20},"res/fonts/PublicPixel.ttf",{255,0,0});
            if (!(win.event.type == RSGL::MousePosChanged) && rand() % 25 == 2 && hits > 0 && tick >= wait+600){ 
                hits--; 
                wait=tick;
            } 
            if (tick >= 900 && hits) hits=0; 
            if (hits == 0){play=false; gameover=true;}
            if (switchTick == 6){
                curLonic == "LonicRun1.png" ? curLonic="LonicRun2.png" : curLonic="LonicRun1.png";
                switchTick=0;
            }
            switchTick++;
        }
        if (options){
            RSGL::drawText("RSGLLonic Popcorn Shop is a parody of the Sonic game,\nSegaSonic Popcorn Shop. The controls are quite\nsimple, instead of moving the wheelaround like\nyou do in the original arcade game,\nyou move your mouse around in a circle.\nleftclick to play.",{5,10,20},"res/fonts/DejaVuSans.ttf",{0,0,0});
            if (win.event.type == RSGL::MouseButtonPressed && win.event.button==RSGL::mouseLeft){ options=false; tick=0; play=true;}
        }
        if (gameover){
             RSGL::drawText("Biden caugh up to Lonic and stole all his monies :(",{5,10,10},"res/fonts/DejaVuSans.ttf",{0,0,0});
        }
        win.clear();
    } win.close();
}
