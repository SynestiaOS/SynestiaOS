#Ubuntu Run Script
dd if=/dev/zero of=initrd.img bs=1024 count=32768
mkfs.ext2 -F -m0 initrd.img
mount -t ext2 -o loop initrd.img   /mnt
cp -r   ./initrd/* /mnt
umount /mnt

#Should Not Be a Mac-Ubuntu Share Directory
