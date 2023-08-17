with open("/home/scc23nop1/lambda/pmon_sound/lap-pmon-master/zloader.ls1b/gzrom.bin", "rb") as f:
    stream = f.read()

print(stream)

"53f91fff"
corr_bytes = b'\x53\xf9\x1f\xff'

print(corr_bytes)

# Find the first occurrence of the binary string b'found'
offset = stream.find(corr_bytes)
print(offset)