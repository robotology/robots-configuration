
#!/usr/bin/expect -f

set address [lindex $argv 0]

spawn sudo bluetoothctl

# Set timeout to 30 sec (-1 for infinity)
set timeout 30

# Remove the device if it was already connected
send "remove $address\r"
expect {
    -re "Device $address not available" {send_user \
        "\n--------------\nDevice was not paired before. Continuing.\n\n--------------\n"}
    -re "Device has been removed"
    }

# Scan for the device
send "scan on\r"
expect {
    timeout {send_user "\n!!!!!!!\nDevice does not seem to be available.\n\n!!!!!!!!\n" ; \
        send "quit\r" ; expect eof ; exit 1}
    -re "$address"
    }
send_user "\n--------------\n$address found!\n\n--------------\n"
send "scan off\r"

# Trust the device (useful since we are not setting any PIN)
send "trust $address\r"
expect {
    timeout {send_user "\n!!!!!!!\nUnable to trust the device.\n\n!!!!!!!!\n" ; \
        send "quit\r" ; expect eof ; exit 1}
    -re "trust succeeded"
    }
send_user "\n--------------\nTrust succeded!\n\n--------------\n"

#Pair the device
send "pair $address\r"
expect {
    timeout {send_user "\n!!!!!!!\nUnable to pair the device.\n\n!!!!!!!!\n" ; \
    send "quit\r" ; expect eof ; exit 1}
    -re "Pairing successful"
    }
send_user "\n--------------\nPairing succeded!\n\n--------------\n"

#Connect the device
send "connect $address\r"
expect {
        timeout {send_user "\n!!!!!!!\nUnable to connect to the device.\n\n!!!!!!!!\n" ; \
        send "quit\r" ; expect eof ; exit 1}
        -re "Connection successful"
    }
send_user "\n--------------\nConnection succeded! The Joystick is ready to be used!!\n\n--------------\n"

#Exit
send "quit\r"
expect eof
exit 0

#iCubGenova04 joypad address: 28:9A:4B:0A:5F:6D
