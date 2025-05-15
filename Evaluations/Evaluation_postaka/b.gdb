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

restore ./firmware/postaka.log binary 0x40000000 0x25048D4 0x25048DB

## MainDB
restore ./firmware/postaka.log binary 0x40000000 0x25859D8 0x2585c88
## TaskArray
restore ./firmware/postaka.log binary 0x40000000 0x25CB1D0 0x25cd798
## SAEQM
restore ./firmware/postaka.log binary 0x40000000 0x25DF774 0x25ea094
## MAC Verification
set *0x4075e4d4 = 0x20012001

c

c