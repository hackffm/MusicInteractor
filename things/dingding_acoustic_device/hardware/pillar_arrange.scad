include <dingding_ring_pillar.scad>

for(y=[1:4])
{
    for(x=[1:12])
    {
        translate([(x-1)*33,(y-1)*170]) pillar();
    }
}