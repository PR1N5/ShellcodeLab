import sys

if len(sys.argv) != 2:
    print("Specify the string you want to convert")
    print(f"Usage: {sys.argv[0]} '<STRING>'")
    sys.exit(1)

s = sys.argv[1] + '\0'

# divide in blocks of 8 bytes (x64 windows)
blocks = [s[i:i+8] for i in range(0, len(s), 8)]

for block in reversed(blocks):
    # fill with null bytes
    block = block.ljust(8, '\0')
    
    # little endian and convert in hex
    hex_value = ''.join(f'{ord(c):02x}' for c in reversed(block))
    print(hex_value)