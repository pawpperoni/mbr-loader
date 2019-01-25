# MBR loader

> Simple MBR

This is a code to define an MBR in FASM.

You can install all the MBR (boot.bin) or you could only install the code of the
MBR into your drive:

```bash
[root@host]# dd if=boot.bin of=/dev/sdaX bs=436 count=1 conv=notrunc
```

This order doesn't erases the partition table.

The process of the MBR code is the following:

- Set up registers and a stack
- Rellocate itself to the address 0x000:0x0600
- Search for the first active partition
- Load the first sector of the first active partition (the VBR) into
  0x0000:0x7c00
- Check if the data has the executable flag (0xaa55)
- Jump to the VBR code

You could also write manually the partition table and assemble the code again,
with the proper partition table.