#include "RockPaperScissors.h"
#include "../core/Input.h"
#include "../render/Primitives.h"
#include <cstdio>
#include <cstdlib>
void RockPaperScissors::reset() { player_=cpu_=result_=playerScore_=cpuScore_=0; }
void RockPaperScissors::update(const Input& input) {
    if (input.pressed('n')) { reset(); return; }
    for (int i=1;i<=3;++i) if (input.pressed(static_cast<unsigned char>('0'+i))) {
        player_=i; cpu_=1+std::rand()%3;
        result_=(player_==cpu_)?0:((player_-cpu_+3)%3==1?1:-1);
        if (result_==1) ++playerScore_; else if (result_==-1) ++cpuScore_;
    }
}
void RockPaperScissors::render(int, int) const {
    const char* names[]={"None","Rock","Paper","Scissors"}; char line[128];
    render::text2d(55,75,title(),{1,.85f,.25f});
    render::text2d(55,125,"1 Rock   2 Paper   3 Scissors   N reset score   Esc menu",{1,1,1});
    std::snprintf(line,sizeof line,"You: %s    CPU: %s",names[player_],names[cpu_]); render::text2d(55,190,line,{1,1,1});
    render::text2d(55,235,player_==0?"Choose a hand":result_==0?"Tie":result_>0?"You win":"CPU wins",{1,.9f,.4f});
    std::snprintf(line,sizeof line,"Score: You %d   CPU %d",playerScore_,cpuScore_); render::text2d(55,285,line,{1,1,1});
}
