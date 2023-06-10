

difference()
{

    union()
    {
        difference()
        {
            circle($fn=360, r=180);
            circle($fn=360, r=150);
            // translate([0,0,-1]) cylinder($fn=360, h=22, r=150);
        }
        
        rotate([0,0,0]) for(i = [1 : 4])
        {
            rotate([0,0,(360/4)*i]) translate([180,0,0]) circle($fn = 32, r=10);
        }
    }

    for(i = [1 : 30])
    {
        rotate([0,0, 12*i]) blockSlot();
    }
    
    rotate([0,0,0]) for(i = [1 : 4])
    {
        rotate([0,0,(360/4)*i]) translate([180,0,0]) circle($fn = 32, r=4);
    }
}



module blockSlot() {
    translate([5+160,2+5,0]) square([10,4], center=true);
    translate([5+160,-(2+5),0]) square([10,4], center=true);
}
