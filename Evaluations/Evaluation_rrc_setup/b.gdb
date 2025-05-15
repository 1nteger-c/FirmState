##################################################

# script.gdb
# for RRC
# snapshot : b* 0x4102D3B0
# Set a breakpoint at the specified address

##################################################


# for snapshot 
b * 0x4102D3B0

target remote :1234

c

restore ./firmware/preaka.log binary 0x40000000 0x25048D4 0x25048DB

c