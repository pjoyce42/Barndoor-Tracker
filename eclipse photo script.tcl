echo "start"
# Set ISO, Aperture (F/#), and Shutter Speed lists
set iso_list {100 100 200 100 200 400 100 200 400 800}
set f_list {8 11 11 16 16 16 22 22 22 22}
set speed_list {1/4000 1/2000 1/4000 1/1000 1/2000 1/4000 1/500 1/1000 1/2000 1/4000}

# Set Compression Type to JPEG (fine)
set compressionsetting JPEG

# Loop to capture images at different settings
for {set i 0} {$i < [llength $iso_list]} {incr i} {
    # Get ISO, Aperture (F/#), and Shutter Speed for this iteration
    set iso [lindex $iso_list $i]
    set aperture [lindex $f_list $i]
    set shutter_speed [lindex $speed_list $i]

    # Set ISO, Aperture (F/#), and Shutter Speed
    dcc Set Iso $iso
    dcc Set Aperture $aperture
    dcc Set Shutterspeed $shutter_speed

    # Capture 2-shot burst
	dcc capture
	echo "Photo $i captured with ISO: $iso, Aperture: $aperture, Shutter Speed: $shutter_speed"
}

echo "fin beads"
echo "start totality"

	


set iso_list {100	100	100	100	100	100	100	100	100	100	100	100	100	100	100	100	100	100	400	400	400	400	400	400	400	100	100	100	100	100	100	100	100	100	100	100	100	100	100	100	100	100	100	100	100	100	100	100	100	100	100	400	400	400	400	400	400	400	100	100	100	100	100	100	100	100}
set f_list	{11	11	11	11	11	11	11	11	11	5.6	5.6	5.6	5.6	5.6	5.6	5.6	5.6	5.6	5.6	5.6	5.6	5.6	5.6	5.6	5.6	22	22	22	22	22	22	22	22	11	11	11	11	11	11	11	11	11	5.6	5.6	5.6	5.6	5.6	5.6	5.6	5.6	5.6	5.6	5.6	5.6	5.6	5.6	5.6	5.6	22	22	22	22	22	22	22	22}
set speed_list	{1/1000	1/500	1/125	1/30	1/8	1/2	1	2	8	1/4000	1/2000	1/500	1/125	1/30	1/8	1/4	1/2	2	1/2000	1/500	1/125	1/30	1/15	1/8	1/2	1/250	1/125	1/30	1/8	1/2	2	4	8	1/1000	1/500	1/125	1/30	1/8	1/2	1	2	8	1/4000	1/2000	1/500	1/125	1/30	1/8	1/4	1/2	2	1/2000	1/500	1/125	1/30	1/15	1/8	1/2	1/250	1/125	1/30	1/8	1/2	2	4	8}



# Set Compression Type to RAW
set compressionsetting RAW

# Loop to capture images at different settings
for {set i 0} {$i < [llength $iso_list]} {incr i} {
    # Get ISO, Aperture (F/#), and Shutter Speed for this iteration
    set iso [lindex $iso_list $i]
    set aperture [lindex $f_list $i]
    set shutter_speed [lindex $speed_list $i]

    # Set ISO, Aperture (F/#), and Shutter Speed
    dcc Set Iso $iso
    dcc Set Aperture $aperture
    dcc Set Shutterspeed $shutter_speed

    # Capture 2-shot burst
	dcc capture
	echo "Photo $i captured with ISO: $iso, Aperture: $aperture, Shutter Speed: $shutter_speed"
}

echo "fin totality"
echo "start beads"

# Set ISO, Aperture (F/#), and Shutter Speed lists
set iso_list {100 100 200 100 200 400 100 200 400 800}
set f_list {8 11 11 16 16 16 22 22 22 22}
set speed_list {1/4000 1/2000 1/4000 1/1000 1/2000 1/4000 1/500 1/1000 1/2000 1/4000}

# Set Compression Type to JPEG (fine)
set compressionsetting JPEG

# Loop to capture images at different settings
for {set i 0} {$i < [llength $iso_list]} {incr i} {
    # Get ISO, Aperture (F/#), and Shutter Speed for this iteration
    set iso [lindex $iso_list $i]
    set aperture [lindex $f_list $i]
    set shutter_speed [lindex $speed_list $i]

    # Set ISO, Aperture (F/#), and Shutter Speed
    dcc Set Iso $iso
    dcc Set Aperture $aperture
    dcc Set Shutterspeed $shutter_speed

    # Capture 2-shot burst
	dcc capture
	echo "Photo $i captured with ISO: $iso, Aperture: $aperture, Shutter Speed: $shutter_speed"

}

echo "fin beads"