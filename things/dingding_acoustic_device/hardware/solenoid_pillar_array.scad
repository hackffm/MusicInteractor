for(x = [0:3], y =[0:1])
{
    translate([25*x,40*y,0]) solenoid_ring_pillar();
}

module solenoid_ring_pillar()
{
    include <solenoid_mount_pillar.scad>
}