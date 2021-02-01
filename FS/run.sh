#Ubuntu Run Script
dd if=/dev/zero of=initrd.img bs=1024 count=65536
mkfs.ext2 -F -m0 initrd.img
cp initrd.img ~
mount -t ext2 -o loop ~/initrd.img   /mnt
cp -r   ./initrd/* /mnt
umount /mnt
cp ~/initrd.img  .
rm ~/initrd.img
#Should Not Be a Mac-Ubuntu Share Directory
