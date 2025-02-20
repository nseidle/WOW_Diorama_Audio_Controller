// ============================================================================
// WOW Phone Attachment
// Author: Jude Vrazel
// Date: 12_23_24
// Description: This script generates a 3D model for the WOW Phone Attachment,
//              consisting of an inner wire channel, an outer base, and
//              attachment components. 
// ============================================================================

// Main Module
WOWPhoneAttachment();

// ============================================================================
// Modules
// ============================================================================

// Main WOW Phone Attachment
module WOWPhoneAttachment() {
    InnerWireChannel();
    OuterBase();
}

// Inner Wire Channel
module InnerWireChannel() { 
    difference() {
        // Create the wire channel base
        translate([0, 5.0 - 6, -2]) cube([25, 11, 20], center = true);
        
        // Subtract the wirehole
        translate([0, -1, 0]) wirehole();
    }
}

// Outer Base with Wirehole (Optional)
module OuterBaseW_Wirehole() {
    difference() {
        OuterBase();
        translate([0, -1, 0]) wirehole();
    }
}

// Outer Base
module OuterBase() { 
    difference() {
        BaseOuterShell();
        
        // Subtract the blue attachment area
        translate([0, 0, 17]) BaseBlueAttachmentArea();
    }
}

// Blue Attachment Area
module BaseBlueAttachmentArea() {
    // Create a scaled cylinder
    translate([0, 0, 4]) scale([0.8, 1.1, 1]) cylinder(h = 4, r = 20 / 2, $fn = 100, center = true);

    // Create a base cube
    translate([0, 0, 0]) cube([22, 22, 5], center = true);
}

// Wire Hole
module wirehole() {
    // Create a cylinder for the wire hole
    translate([0, 0, 0]) cylinder(h = 80, r = 8 / 2, $fn = 100, center = true);    
}

// Base Outer Shell
module BaseOuterShell() {
    // Dimensions for start, end, and other parameters
    start_x = 34 - 3;
    start_y = 21 - 3;
    end_x = 38 - 2;
    end_y = 25 + 8 - 3;
    z_dim = 9;
    rounding_radius = 2;  // Radius for rounding edges

    translate([0, 0, 10]) {
        minkowski() {
            // Tapered shape with rounded base
            minkowski() {
                linear_extrude(height = z_dim, scale = [end_x / start_x, end_y / start_y]) {
                    square([start_x - 2 * rounding_radius, start_y - 2 * rounding_radius], center = true);
                }
                
                // Sphere for base edge rounding
                sphere(r = rounding_radius, $fn = 100);
            }
            
            // Cylinder for Z-axis rounding
            cylinder(h = rounding_radius * 2, r = rounding_radius, $fn = 100, center = true);
        }
    }
}
