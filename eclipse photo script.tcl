# Set ISO, Aperture (F/#), and Shutter Speed lists
set iso_list {100 100 100 100 200 200 200 400 400 800}
set f_list {8 11 16 22 11 16 22 16 22 22}
set speed_list {1/4000 1/2000 1/1000 1/500 1/4000 1/2000 1/1000 1/4000 1/2000 1/4000}

# Loop to capture images at different settings
for {set i 0} {$i < [llength $iso_list]} {incr i} {
    # Get ISO, Aperture (F/#), and Shutter Speed for this iteration
    set iso [lindex $iso_list $i]
    set aperture [lindex $f_list $i]
    set shutter_speed [lindex $speed_list $i]

    # Set ISO, Aperture (F/#), and Shutter Speed
    digicam.SetIso $iso
    digicam.SetAperture $aperture
    digicam.SetSpeed $shutter_speed

    # Capture Image
    digicam.Capture

    # Delay between captures (adjust as needed)
    digicam.Delay 1000  ;# Delay 1 second (1000 milliseconds) before capturing the next image
}
